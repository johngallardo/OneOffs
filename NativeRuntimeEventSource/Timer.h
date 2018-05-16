#pragma once

#include "Timer.g.h"
#include "ThreadpoolTimer.h"

namespace winrt::NativeRuntimeEventSource::implementation
{
    struct Timer : TimerT<Timer>
    {
        Timer(int32_t tick) : _tick(tick) {}
        int32_t Tick() { return _tick; }

        void Start();

        event_token Ticked(const Windows::Foundation::TypedEventHandler<NativeRuntimeEventSource::Timer, Windows::Foundation::IInspectable>& handler);
        void Ticked(const event_token& token);

        void SignalTicked();

    private:
        int32_t _tick;
        winrt::event<Windows::Foundation::TypedEventHandler<NativeRuntimeEventSource::Timer, Windows::Foundation::IInspectable>> _tickedEvent;
        std::unique_ptr<ThreadpoolTimer> _threadpoolTimer;
    };
}

namespace winrt::NativeRuntimeEventSource::factory_implementation
{
    struct Timer : TimerT<Timer, winrt::NativeRuntimeEventSource::implementation::Timer>
    {
    };
}
