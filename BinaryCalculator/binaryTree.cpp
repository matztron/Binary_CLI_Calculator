//
//  binaryTree.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "binaryTree.h"

//Constructor
Btree::Btree()
{
	//root = NULL;
	root = new Node();
}

//Destructor
Btree::~Btree(){
    //Destroy entire tree
	destroy_tree();
}

//Public: Destroy entire tree
void Btree::destroy_tree()
{
    destroy_tree(root);
}

//Private: Destroy node and all sub nodes
void Btree::destroy_tree(Node *leaf)
{
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void Btree::insert(Node* newNode, Node* parent /*, Token leftChild, Token rightChild*/)
{
	if (parent->left == NULL)
	{
		//insert right
		parent->left = newNode;
	}
	else if (parent->right == NULL)
	{
		//insert left
		parent->right = newNode;
	}
    else
    {
        throw GenericException("Internal error. This has likely nothing to do with your input (Parent is satisified)", 0);
    }
}
