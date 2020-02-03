#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include "token.h"
#include <iostream>
#include "exception.h"
#include "binaryTree.h"

class Parser 
{
    public:
        //List of user-inputted tokens
        Parser(std::vector<Token> tokens_);
        Btree *tree;

        void readTokens(std::vector<Token> subTokens, Node* parent, int pos);
        //void checkToken(std::vector<Token> subTokens);
        void getMonoOperator(std::vector<Token> subTokens, Node* parent);
        void getDualOperator(std::vector<Token> subTokens, Node* parent);

        std::vector<Token> getBracketContent(std::vector<Token> subTokens, int index);

        std::vector<Token> getFirstOperand(std::vector<Token> subTokens);
        std::vector<Token> getSecondOperand(std::vector<Token> subTokens);

        //std::vector<int>
        int findClosingBracket(int openingBracketIndex , std::vector<Token> subTokens);


        void addChildren();


    private:
        std::vector<Token> tokens;

        //6
        int countVariables();

        //int tokenPos;
        //smart stuff below

        //std::vector<Token> getOperands(int index);
};

#endif // _PARSER_H_

//Parse-Tree
// S        ->  Expr | nix
// Expr     ->  ( Expr ) | NOT Expr | Expr Op Expr | VAR | nix
// Op   ->  AND | OR | XOR | EQ | _NOT_ | ... 

// a AND (b OR c)
// S -> Expr -> Expr AND Expr -> VAR AND (Expr) -> VAR AND (Expr OR Expr) -> VAR AND (VAR OR VAR)

// a OR b AND (c OR d)
//

//Setze für die Variablen die Wahrheitswerte ein
//First check for NOTs
//Then check for Brackets
//Execute Stuff in Brackets
//AND is more important than OR



//NOT( a OR ( (b) AND c ))

// NOT() aufrufen
// in Not nach rechts schauen
// wenn man eine Klammer findet OP_BRACKET() und CL_BRACKET aufrufen
// in Op_Bracket nach rechts schauen
// wenn man eine Klammer findet OP_BRACKET() und CL_BRACKET aufrufen
// in Op_Bracket nach rechts schauen
// man findet nur eine VAR bevor man die erwartete closing bracket findet
// return Wahrheitswert von VAR

//--- JULIAN HELP ---
//  NOT( a OR ( (b) AND c ))
//  NOT TRue -> False

//  0. setze für VARs die Wahrheitswerte ein
//  1. finde alle NOTs
//  2. rufe an allen NOTs den rechten Inhalt davon auf (als Übergabeparameter)
//  


//Entrypoint into calculations
        //void calculate();

        //void insertNextVariables();

        //Gates
        //void not_gate(std::vector<Token> v1);

        //void and_gate(std::vector<Token> v1, std::vector<Token> v2);

        //void or_gate(std::vector<Token> v1, std::vector<Token> v2);
