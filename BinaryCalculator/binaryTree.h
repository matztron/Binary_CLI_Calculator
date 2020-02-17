//
//  binaryTree.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

//#include <iostream>
#include "token.h"
#include "exception.h"

using namespace std;

class Node{
public:
    
    Node()
    {
        //token = NULL ?
        left = NULL;
        right = NULL;
    }
    //int value;
	Token token;
	Node *left;
	Node *right;
};


class Btree{
public:
	Btree();
    
	~Btree();

	void destroy_tree();

	void insert(Node* newNode, Node* parent);
    //void plotTree(Node * parent);

	Node *root;

private:
	void destroy_tree(Node *leaf);
};

#endif //_BINARY_TREE_H_
