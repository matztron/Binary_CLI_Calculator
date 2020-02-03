#include "truthTable.h"

TruthTable::TruthTable(int var_count) 
{
    table = generateTable(var_count);
}

bool** TruthTable::generateTable(int var_count) 
{
    table_rows = std::pow(2,var_count);
    table_columns = var_count;

    //With vectors
    /*for (size_t rows = 0; rows < table_rows; rows++)
    {
        table.push_back( std::vector<bool>() );
        for (size_t cols = 0; cols < table_columns; cols++)
        {
            table[rows].push_back(false);
        }
        
    }*/
    
    bool** ary = new bool*[table_rows];
    for(size_t i = 0; i < table_rows; ++i) 
    {
        ary[i] = new bool[table_columns];
    }

    return ary;
    /*bool** a = new bool*[table_rows];
    for(int i = 0; i < table_rows; ++i) 
    {
        a[i] = new bool[table_columns];
    }
    return a;*/
    //a[row][column]

    // https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
}

void TruthTable::fillTable() 
{
    //lsb  msb
    // 0 0 0 | 0
    // 1 0 0 | 1 
    // 0 1 0 | 2
    // 1 1 0 | 3
    // 0 0 1 | 4
    // 1 0 1 | 5
    // 0 1 1 | 6
    // 1 1 1 | 7

    //Debug
    std::cout << "Rows: " << table_rows << std::endl;
    std::cout << "Columns: " << table_columns << std::endl;
    
    for (int row = 0; row < table_rows; row++)
    {
        int difference = row;
        for (int col = table_columns-1; col >= 0; col--)
        {
            if (std::pow(2,col) <= difference) 
            {
                difference -= std::pow(2,col);
                table[row][col] = true;
            }
            else
            {
                table[row][col] = false;
            }   
        }   
    }
}

void TruthTable::plotTable() 
{
    for (size_t i = 0; i < table_rows; i++)
    {
        std::cout << "---------------" << std::endl;
        //From right to left
        for (size_t j = 0; j < table_columns; j++)
        {
            std::cout << "|" << table[i][j] << "|";
        }
        std::cout << std::endl;
    }
}

void TruthTable::getTable() 
{
    return;
}