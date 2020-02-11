//
//  binaryTree.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <iostream>
#include "token.h"

//source:   https://gist.github.com/toboqus/def6a6915e4abd66e922
//          https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
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

	//void insert(int key);
	//node *search(int key);
	void destroy_tree();
	//void inorder_print();
	//void postorder_print();
	//void preorder_print();

	void insert(Node* newNode, Node* parent);
    void plotTree(Node * parent);

	Node *root;

private:
	void destroy_tree(Node *leaf);
	//void insert(int key, node *leaf);
	//node *search(int key, node *leaf);
	//void inorder_print(node *leaf);
	//void postorder_print(node *leaf);
	//void preorder_print(node *leaf);

};

#endif //_BINARY_TREE_H_
