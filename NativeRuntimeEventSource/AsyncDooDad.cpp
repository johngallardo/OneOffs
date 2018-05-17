#include "pch.h"
#include "AsyncDooDad.h"
#include "Person.h"

namespace winrt::NativeRuntimeEventSource::implementation
{
    Windows::Foundation::IAsyncOperation<NativeRuntimeEventSource::Person> AsyncDooDad::GetPersonAsync(hstring const firstName, hstring const lastName)
    {
        co_await winrt::resume_background();
        winrt::NativeRuntimeEventSource::implementation::Person p{ firstName, lastName };
        co_return p;
    }
}
