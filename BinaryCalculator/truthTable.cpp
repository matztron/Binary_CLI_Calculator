//
//  truthTable.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "truthTable.h"

TruthTable::TruthTable(int var_count) 
{
    table = generateTable(var_count);
}

TruthTable::~TruthTable()
{
    delete table;
}

bool** TruthTable::generateTable(int var_count) 
{
    table_rows = std::pow(2,var_count);
    table_columns = var_count;
    
    bool** ary = new bool*[table_rows];
    for(size_t i = 0; i < table_rows; ++i) 
    {
        ary[i] = new bool[table_columns];
    }

    return ary;
}

void TruthTable::fillTable() 
{
    //currently:
    //lsb  msb
    // 0 0 0 | 0
    // 0 0 1 | 1
    // 0 1 0 | 2
    // 0 1 1 | 3
    // 1 0 0 | 4
    // 1 0 1 | 5
    // 1 1 0 | 6
    // 1 1 1 | 7
    
    for (int row = 0; row < table_rows; row++)
    {
        int difference = row;
        for (int col = table_columns-1; col >= 0; col--)
        {
            if (std::pow(2,col) <= difference) 
            {
                difference -= std::pow(2,col);
                //Insert the value (for row) the other way around (LSB at end of array)
                table[row][table_columns - col - 1] = true;
            }
            else
            {
                //Insert the value (for row) the other way around (LSB at end of array)
                table[row][table_columns - col - 1] = false;
            }   
        }   
    }
}

//Give back one cell of the truthTable
bool TruthTable::getElement(int row, int col)
{
    return table[row][col];
}
