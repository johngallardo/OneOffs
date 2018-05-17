#include "pch.h"
#include "AsyncDooDad.h"
#include "Person.h"

using namespace std::chrono_literals;

namespace winrt::NativeRuntimeEventSource::implementation
{
    Windows::Foundation::IAsyncOperation<NativeRuntimeEventSource::Person> AsyncDooDad::GetPersonAsync(hstring const firstName, hstring const lastName)
    {
        co_await winrt::resume_background();
        co_await winrt::resume_after(1s);
        co_return winrt::make<Person>(firstName, lastName );
    }
}
