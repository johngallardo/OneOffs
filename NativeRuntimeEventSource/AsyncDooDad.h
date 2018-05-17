#pragma once

#include "AsyncDooDad.g.h"

namespace winrt::NativeRuntimeEventSource::implementation
{
    struct AsyncDooDad : AsyncDooDadT<AsyncDooDad>
    {
        AsyncDooDad() = default;

        Windows::Foundation::IAsyncOperation<NativeRuntimeEventSource::Person> GetPersonAsync(hstring const firstName, hstring const lastName);
    };
}

namespace winrt::NativeRuntimeEventSource::factory_implementation
{
    struct AsyncDooDad : AsyncDooDadT<AsyncDooDad, implementation::AsyncDooDad>
    {
    };
}
