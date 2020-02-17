//
//  token.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "token.h"

Token::Token() 
{
    this->type = NONE;
    this->value = "";
    this->index = 0;
}

Token::Token(TokenType type, std::string value, int index) 
{
    this->type = type;
    this->value = value;
    this->index = index;
}
