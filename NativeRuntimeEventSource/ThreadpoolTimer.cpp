#include "pch.h"
#include "ThreadpoolTimer.h"

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
