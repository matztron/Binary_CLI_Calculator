//
//  truthTable.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _TRUTH_TABLE_H_
#define _TRUTH_TABLE_H_

#include <cmath>
#include <iostream>
#include <vector>

class TruthTable
{
private:
    
    bool** generateTable(int var_count);

    //2D array: Holds all variable value combinations
    bool** table;
    

public:
    //Dimensions of table
    int table_rows;
    int table_columns;
    
    //Here will the results of the calculation be inserted
    std::vector<bool> resultColumn;
    
    //Fills table variables with all combinations of 0s and 1s
    //Filled by counting upwards in binary
    void fillTable();

    //Debug style. !!!IMPROVE OUTPUT!!!
    //void plotTable();

    //Get an element from the table
    bool getElement(int row, int col);

    //Constructor
    TruthTable(int var_count);
    
    ~TruthTable();
};


#endif //_TRUTH_TABLE_H_
