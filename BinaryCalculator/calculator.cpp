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
    //write true and false values into the table
    table.fillTable();
    
    table.plotTable();
}

//Calculate Parent and Children
bool Calculator::calculateBooleanValue(Node* parent)
{
    if (parent->left != nullptr) {
        if (parent->left->token.type == VAR)
        {
            //return wahrheitswert
        }
        return true;
    }
    if (parent->right != nullptr) {
        return true;
    }
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

bool Calculator::and_gate(bool op_one, bool op_two)
{
    if (op_one == true && op_two == true) {
        return true;
    }
    else
    {
        return false;
    }
}
