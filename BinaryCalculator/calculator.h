//
//  calculator.hpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef calculator_hpp
#define calculator_hpp

#include "truthTable.h"
#include "binaryTree.h"

class Calculator
{
public:
    
    Calculator(int var_count);
    
    TruthTable table;
    
    bool calculateBooleanValue(Node* parent);
    
private:
    bool and_gate(bool op_one, bool op_two);
};

#endif /* calculator_hpp */
