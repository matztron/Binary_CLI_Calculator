#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <cstdint>
#include <stdexcept>
#include <string>

struct GenericException : public std::runtime_error {
    //Position of error
    uint64_t position;
    
    GenericException(std::string msg, uint64_t pos)
        : std::runtime_error(msg)
        , position(pos)
    {
    }
};

#endif // _EXCEPTION_H_