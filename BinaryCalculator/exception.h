//
//  exception.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

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
