//
//  token.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

typedef enum
{
    VAR         = 0,
    AND         = 1,
    OR          = 2,
    NOT         = 3,
    /*NAND        = 4,
    NOR         = 5,
    XOR         = 6,*/
    BRC_OPEN    = 7,
    BRC_CLOSE   = 8,
    NONE        = 9
    //EQ          = 10
} TokenType;

class Token 
{
    public:
        //Contructor
        Token();

        Token(TokenType type, std::string value, int index);

        TokenType type;
        std::string value;
        int index;
};

#endif //_TOKEN_H_
