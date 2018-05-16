#pragma once

#include "Timer.g.h"

namespace winrt::NativeRuntimeEventSource::implementation
{
    class ThreadpoolTimer;

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

    class ThreadpoolTimer : public std::enable_shared_from_this<ThreadpoolTimer>
    {
    public:
        ThreadpoolTimer(std::chrono::seconds waitTime) :_waitTime(waitTime) {}

        ~ThreadpoolTimer();

        void StartTimer(std::function<void()> callback);

    private:
        void TimerCallback(_Inout_ PTP_TIMER /*timer*/);

        FILETIME ComputeFileTime()
        {
            ULARGE_INTEGER dueTime{};
            dueTime.QuadPart = (ULONGLONG)-(static_cast<LONG>(_waitTime.count()) * 10 * 1000 * 1000);
            FILETIME ft{};
            ft.dwHighDateTime = dueTime.HighPart;
            ft.dwLowDateTime = dueTime.LowPart;
            return ft;
        }

        static VOID CALLBACK s_TimerCallback(
            _Inout_ PTP_CALLBACK_INSTANCE /*Instance*/,
            _Inout_opt_ PVOID Context,
            _Inout_ PTP_TIMER Timer)
        {
            reinterpret_cast<ThreadpoolTimer*>(Context)->TimerCallback(Timer);
        }

        std::chrono::seconds _waitTime;
        std::function<void()> _callback;
        PTP_TIMER _timer{ nullptr };
        bool _onTimerThread{ false };
    };
}

namespace winrt::NativeRuntimeEventSource::factory_implementation
{
    struct Timer : TimerT<Timer, winrt::NativeRuntimeEventSource::implementation::Timer>
    {
    };
}
