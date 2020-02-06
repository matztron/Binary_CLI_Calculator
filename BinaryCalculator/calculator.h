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

class Calculator
{
public:
    
    Calculator(int var_count);
    
    TruthTable table;
    
    bool calculate();
    
private:
};

#endif /* calculator_hpp */
