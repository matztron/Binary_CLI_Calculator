//
//  calculator.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "calculator.h"

//Constructor
Calculator::Calculator(int var_count) : table(var_count)
{
    //lol
}

//Calculate Parent and Children
bool Calculator::calculate()
{
    //traverse tree
    //idea:
    //  * start at root
    //  * if the branch to the left/right is not null and the type is not a VAR (so no leaf): call function for this branch again
    //  * the given return from this path is needed to calculate the current operator
    //  * if one of the branches contains a VAR use this one directly
    
    //  *- if we find a VAR we check what boolean value it should have in the current execution
    //  *- if you have computed up to the first node after the root node write this result into the truthTable
    //  *- plot the truthTable
    //  *- ???
    //  *- Profit!
    return true;
}
