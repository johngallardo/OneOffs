#include "pch.h"
#include "Timer.h"
#include "ThreadpoolTimer.h"

namespace winrt::NativeRuntimeEventSource::implementation
{

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
