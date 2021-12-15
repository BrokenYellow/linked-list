#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <exception>

class BaseError: public std::exception
{
public:
    const char* what() const noexcept override{
        return "Unknown Error";
    }
};

class RangeError: public BaseError
{
public:
    const char* what() const noexcept override{
        return "Range Error";
    }
};

class EmptyError: public BaseError
{
public:
    const char* what() const noexcept override{
        return "Empty Error";
    }
};

class MemoryError: public BaseError
{
public:
    const char* what() const noexcept override{
        return "Memory Error";
    }
};

class IteratorError: public BaseError
{
public:
    const char* what() const noexcept override{
        return "Iterator Error";
    }
};

#endif // ERRORS_H
