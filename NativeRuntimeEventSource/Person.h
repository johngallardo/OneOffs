#pragma once

#include "Person.g.h"

#include <ppl.h>

namespace winrt::NativeRuntimeEventSource::implementation
{
    struct Person : PersonT<Person>
    {
        Person() = default;
        Person(hstring const& firstName, hstring const& lastName) : _firstName(firstName), _lastName(lastName) {}

        hstring FirstName();
        void FirstName(hstring const& value);
        hstring LastName();
        void LastName(hstring const& value);

    private:
        winrt::hstring _firstName;
        winrt::hstring _lastName;
    };
}

namespace winrt::NativeRuntimeEventSource::factory_implementation
{
    struct Person : PersonT<Person, implementation::Person>
    {
    };
}
