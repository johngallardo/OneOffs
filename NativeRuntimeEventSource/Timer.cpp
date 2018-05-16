#include "pch.h"
#include "Timer.h"

namespace winrt::NativeRuntimeEventSource::implementation
{

ThreadpoolTimer::~ThreadpoolTimer()
{
    if (_timer)
    {
        constexpr BOOL cancelPending = TRUE;
        if (!_onTimerThread)
        {
            WaitForThreadpoolTimerCallbacks(_timer, cancelPending);
        }
        CloseThreadpoolTimer(_timer);
        _timer = nullptr;
    }
}

void ThreadpoolTimer::StartTimer(std::function<void()> callback)
{
    _callback = callback;
    auto timer = CreateThreadpoolTimer(s_TimerCallback, this, nullptr);
    auto dueTime = ComputeFileTime();
    SetThreadpoolTimer(timer, &dueTime, static_cast<DWORD>(_waitTime.count()) * 1000, 0);
    _timer = timer;
}

void ThreadpoolTimer::TimerCallback(_Inout_ PTP_TIMER /*timer*/)
{
    struct OnTimerThread
    {
        OnTimerThread(ThreadpoolTimer& timer) : _timer(timer) { _timer._onTimerThread = true; }
        ~OnTimerThread() { _timer._onTimerThread = false; }
        ThreadpoolTimer& _timer;
    };

    OnTimerThread threadWatch{ *this };
    if (_callback)
    {
        _callback();
    }
}

void Timer::Start()
{
    auto callback = [weakthis = get_weak()]()
    {
        if (auto strong = weakthis.get())
        {
            strong->SignalTicked();
        }
    };

    _threadpoolTimer = std::make_unique<ThreadpoolTimer>(std::chrono::seconds{ _tick });
    _threadpoolTimer->StartTimer(callback);
}

event_token Timer::Ticked(const Windows::Foundation::TypedEventHandler<NativeRuntimeEventSource::Timer, Windows::Foundation::IInspectable>& handler)
{
    return _tickedEvent.add(handler);
}

void Timer::Ticked(const event_token& token)
{
    _tickedEvent.remove(token);
}

void Timer::SignalTicked()
{
    _tickedEvent(*this, nullptr);
}

}
