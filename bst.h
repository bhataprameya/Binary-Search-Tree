#ifndef BST_H
#define BST_H
typedef struct
{
	int value;
}Data;

typedef struct node
{
	Data data;
	struct node * left;
	struct node * right;
	struct node * parent;
}Node;

typedef struct
{
	Node * root;
}Tree;


Node * createNode(Data d, Node * parent);
Tree * createTree();
Data * insert(Tree *, Data);
Data * search(Tree * bst, Data value);
int compare(Tree *, Tree *);
Tree * clone(Tree *t);
void deleteTree(Tree * bst);
void removeData(Tree * bst, Data value);
Data * insertNode(Node * node, Data value);
Node * searchNode(Node *n, Data d);
void sort(Tree *, Data *);
void sortInorder(Node * n, Data * data);
Node * clonePreorder(Node *n);
int compareEqual(Node *, Node *);
void removeLeaf(Tree *, Node *);
void shortCircuit(Tree *, Node *);
void promotion(Tree *, Node *);
Node * searchMin(Node *);
void dealewithrootcase(Tree *, Node *);
void deleteNode(Node *);
#endif