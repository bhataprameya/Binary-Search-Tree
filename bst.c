#include "bst.h"
#include<stdio.h>
#include<stdlib.h>

Tree * createTree()
{
	Tree *tree = malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}


Node * createNode(Data d, Node * parent)
{
	Node * new_node = malloc(sizeof(Node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;
	new_node->data = d;
	return new_node;
}

Data * insert(Tree * bst, Data value)
{
	if (bst->root == NULL)
	{
		bst->root = createNode(value, NULL);
	}
	else
	{
		return insertNode(bst->root, value);
	}
}

Data * insertNode(Node *n, Data d)
{
	if (d.value < n->data.value)
	{
		if (n->left == NULL)
		{
			n->left = createNode(d, n);
			return &(n->left->data);

		}
		else
		{
			return insertNode(n->left, d);
		}
	}
	else if (d.value > n->data.value)
	{
		if (n->right == NULL)
		{
			n->right = createNode(d, n);
			return &(n->right->data);
		}
		else
		{
			return insertNode(n->right, d);
		}
	}
	else return NULL;

}

Data * search(Tree * bst, Data value)
{
	if (bst->root == NULL)
	{
		return NULL;
	}
	else
	{
		Node * temp = searchNode(bst->root, value);
		return &temp->data;
	}
}


Node * searchNode(Node *n, Data d)
{
	if (d.value < n->data.value)
	{
		if (n->left == NULL)
		{
			return NULL;
		}
		else
		{
			return searchNode(n->left, d);
		}
	}
	else if (d.value > n->data.value)
	{
		if (n->right == NULL)
		{
			return NULL;
		}
		else
		{
			return searchNode(n->right, d);
		}
	}
	else if (d.value == n->data.value)
	{
		return n;
	}

}


void sort(Tree * tree, Data * data)
{

	if (tree->root != NULL)
	{
		sortInorder(tree->root, data);
	}
}

void sortInorder(Node * n, Data * data)
{
	static int i = 0;
	if (n != NULL)
	{
		sortInorder(n->left, data);
		data[i++] = n->data;
		sortInorder(n->right, data);
	}
}





Tree * clone(Tree *t)
{
	if (t->root != NULL)
	{
		Tree *tree = malloc(sizeof(Tree));
		tree->root = clonePreorder(t->root);
		return tree;

	}
}

Node * clonePreorder(Node *n)
{
	if (n != NULL)
	{
		Node *new_node = malloc(sizeof(Node));
		new_node->data = n->data;
		new_node->left = clonePreorder(n->left);
		new_node->right = clonePreorder(n->right);
		return new_node;
	}
}

int compare(Tree* tree1, Tree* tree2)
{
	if (tree1 != NULL && tree2 != NULL)
		return compareEqual(tree1->root, tree2->root);
	else return 0;
}

int compareEqual(Node * node1, Node * node2)
{
	if (node1 == NULL &&node2 == NULL)
		return 0;
	if (node1 != NULL &&node2 != NULL)
	{
		if (node1->data.value == node2->data.value)
		{
			int valid1 = compareEqual(node1->left, node2->left);
			int valid2 = compareEqual(node1->right, node2->right);
			if (valid1 == 1 && valid2 == 1) return 1;
			else return !(valid1 && valid2);
		}
		else  return 1;
	}
	return 0;
}


void removeData(Tree * bst, Data value)
{
	Node * to_delete = searchNode(bst->root, value);

	if (to_delete == bst->root)
	{
		dealewithrootcase(bst, to_delete);
		return;
	}
	if (to_delete != NULL)
	{
		if (to_delete->left == NULL && to_delete->right == NULL)
		{
			removeLeaf(bst, to_delete);
		}
		else if (to_delete->left == NULL || to_delete->right == NULL)
		{
			shortCircuit(bst, to_delete);
		}
		else
		{
			promotion(bst, to_delete);

		}
	}
}


void removeLeaf(Tree * bst, Node * node)
{
	if (node->parent->left == node)
	{
		node->parent->left = NULL;
	}
	else
	{
		node->parent->right = NULL;
	}
	free(node);
	node = NULL;
}


void shortCircuit(Tree * t, Node * n)
{
	if (n->parent->left == n)
	{
		if (n->right == NULL)
		{
			n->parent->left = n->left;
			n->left->parent = n->parent;
		}
		else
		{
			n->parent->left = n->right;
			n->right->parent = n->parent;
		}
	}
	else
	{
		if (n->right == NULL)
		{
			n->parent->right = n->left;
			n->left->parent = n->parent;
		}
		else
		{
			n->parent->right = n->right;
			n->right->parent = n->parent;
		}

	}
	free(n);
	n = NULL;
}

void promotion(Tree *t, Node *n)
{
	Node * d_node = searchMin(n);
	n->data = d_node->data;
	if (d_node->left == NULL && d_node->right == NULL){
		removeLeaf(t, d_node);
	}
	else{
		shortCircuit(t, d_node);
	}
}

void dealewithrootcase(Tree *tree, Node *to_delete)
{
	if (to_delete->left == NULL && to_delete->right == NULL)
	{
		free(to_delete);
		to_delete = NULL;
		tree->root = NULL;
	}
	else if (to_delete->left == NULL || to_delete->right == NULL)
	{
		if (to_delete->left == NULL)
		{
			to_delete->right->parent = NULL;
			tree->root = to_delete->right;
		}
		else
		{
			to_delete->left->parent = NULL;
			tree->root = to_delete->left;
		}
		free(to_delete);
		to_delete = NULL;
	}
	else
	{
		promotion(tree, to_delete);

	}
}

Node * searchMin(Node* n)
{

	if (n->right == NULL)
		return n;
	else
	{
		n = n->right;
		while (n->left != NULL)
			n = n->left;
		return n;
	}

}

void deleteTree(Tree * bst)
{
	if (bst->root == NULL)
	{
		free(bst);
		bst = NULL;
	}
	else
	{
		deleteNode(bst->root);
		free(bst);
		bst = NULL;
	}
}

void deleteNode(Node *n)
{
	if (n != NULL)
	{
		deleteNode(n->left);
		deleteNode(n->right);
		free(n);
	}
}