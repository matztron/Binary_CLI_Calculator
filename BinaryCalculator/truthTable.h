#ifndef _TRUTH_TABLE_H_
#define _TRUTH_TABLE_H_

#include <cmath>
#include <iostream>
//#include <vector>

class TruthTable
{
private:
    //holds the input combinations
    //bool** table;
    int table_rows;
    int table_columns;

    bool** generateTable(int var_count);

    //void fillTable();

    /*std::vector< std::vector<bool> >*/ bool** table;

public:
    void fillTable();
    //---

    void plotTable();

    //Get an element from the table
    bool getElement(int row, int col);


    TruthTable(int var_count);
    
    //~TruthTable();
};


#endif //_TRUTH_TABLE_H_
