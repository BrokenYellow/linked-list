#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <memory>

class Base
{
public:
    virtual ~Base() = default;
    virtual size_t len() const = 0;
    virtual operator bool() = 0;
};

#endif // BASE_H
