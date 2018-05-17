#include "pch.h"
#include "Person.h"

namespace winrt::NativeRuntimeEventSource::implementation
{
    hstring Person::FirstName()
    {
        return _firstName;
    }

    void Person::FirstName(hstring const& value)
    {
        _firstName = value;
    }

    hstring Person::LastName()
    {
        return _lastName;
    }

    void Person::LastName(hstring const& value)
    {
        _lastName = value;
    }
}
