// Christopher Cao
// ch282858
// COP 3502, Fall 2020

// pre-processor directives
#include "KindredSpirits.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedListNode
{
	int data;
	
	struct linkedListNode *right;
}linkedListNode;

// struct taken from LinkedLists.h
typedef struct linkedList
{
	linkedListNode *head;
	linkedListNode *tail;
}linkedList;

// helper function taken from LinkedLists.c
linkedList *createList(void)
{
	return calloc(1, sizeof(linkedList));
}

// helper function taken from LinkedLists.c
node *createNode(int data)
{
	node *n = malloc(sizeof(node));
	
	n->data = data;
	n->right = NULL;
	n->left = NULL;
	
	return n;
}

// helper function modified from LinkedLists.c
linkedListNode *createLinkedListNode(int data)
{
	linkedListNode *n = malloc(sizeof(linkedListNode));
	
	n->data = data;
	n->right = NULL;
	
	return n;
}

// helper function taken from LinkedLists.c
void tailInsert(linkedList *list, int data)
{
	if (list == NULL)
	{
		return;
	}
	
	if (list->tail == NULL)
	{
		list->head = list->tail = createLinkedListNode(data);
		return;
	}
	
	list->tail->right = createLinkedListNode(data);
	list->tail = list->tail->right;
}

// helper function modified from bst.c
void preorderTraversal(node *root, linkedList *list)
{
	// statement to return if root value is invalid
	if (root == NULL)
	{
		return;
	}
	
	tailInsert(list, root->data);
	preorderTraversal(root->left, list);
	preorderTraversal(root->right, list);
}

// helper function modified from bst.c
void postorderTraversal(node *root, linkedList *list)
{
	// statement to return if root value is invalid
	if (root == NULL)
	{
		return;
	}
	
	postorderTraversal(root->left, list);
	postorderTraversal(root->right, list);
	tailInsert(list, root->data);
}

// helper function to calculate the size of a tree
int treeSize(node *root)
{
	// variable declaration
	int size = 0;
	
	// statement to return 0 if root value is invalid
	if (root == NULL)
	{
		return 0;
	}
	
	// statement to return 1 if left and right values are both NULL
	if ((root->right == NULL) && (root->left == NULL))
	{
		return 1;
	}
	
	// calculation for size of tree
	size = treeSize(root->right) + treeSize(root->left) + 1;
	
	return size;
}

// helper function to compare list values
int compareLists(linkedListNode *headA, linkedListNode *headB)
{
	// statement to return 1 if both heads are NULL
	if ((headA == NULL) && (headB == NULL))
	{
		return 1;
	}
	
	// statement to return 0 if only one node is NULL
	if ((headA == NULL) || (headB == NULL))
	{
		return 0;
	}
	
	// statement to return 0 if both heads are unequal
	if (headA->data != headB->data)
	{
		return 0;
	}
	
	// statement to recurse if list data are equal and non-NULL
	else if (headA->data == headB->data)
	{
		compareLists(headA->right, headB->right);
	}
}

// mandatory function
int isReflection(node *a, node *b)
{
	// statement to return 1 if both nodes are NULL
	if ((a == NULL) && (b == NULL))
	{
		return 1;
	}
	
	// statement to return 0 if only one node is NULL
	if ((a == NULL) || (b == NULL))
	{
		return 0;
	}
	
	// statement to return 0 if the nodes are unequal
	if (a->data != b->data)
	{
		return 0;
	}
	
	// statements to compare both trees and return 1 if they are kindred spirits
	if (a->data == b->data)
	{
		if ((a->right == NULL) && (a->left == NULL) && (b->right == NULL) && (b->left == NULL))
		{
			return 1;
		}
		
		else if ((isReflection(a->right, b->left) == 1) && (isReflection(a->left, b->right) == 1))
		{
			return 1;
		}
	}
	
	return 0;
}

// mandatory function
node *makeReflection(node *root)
{
	// statement to return NULL if root value is NULL
	if (root == NULL)
	{
		return NULL;
	}
	
	// node declaration
	node *n;
	n = malloc(sizeof(node));
	n->data = root->data;
	n->right = makeReflection(root->left);
	n->left = makeReflection(root->right);
	
	return n;
}

// mandatory function
int kindredSpirits(node *a, node *b)
{
	// variable declaration
	int treeSizeA, treeSizeB, returnValue;
	treeSizeA = treeSize(a);
	treeSizeB = treeSize(b);
	
	// statement to return 1 if both nodes are NULL
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	
	// statement to return 0 if only one node is NULL
	if (a == NULL || b == NULL)
	{
		return 0;
	}
	
	// statement to return 0 if the tree sizes are unequal
	if (treeSizeA != treeSizeB)
	{	
		return 0;
	}
	
	// execute tree transversals
	linkedList *listA = createList();
	linkedList *listB = createList();
	preorderTraversal(a, listA);
	postorderTraversal(b, listB);
	returnValue = compareLists(listA->head, listB->head);
	
	// statement to return 1 if returnValue is 1
	if (returnValue)
	{		
		return 1;
	}
	
	// attempt transversals in reverse if returnValue is not 1
	listA = createList();
	listB = createList();
	preorderTraversal(b, listB);
	postorderTraversal(a, listA);
	returnValue = compareLists(listA->head, listB->head);
	
	// statement to return 1 if returnValue is 1
	if (returnValue)
	{
		return 1;
	}
	
	return 0;
}

double difficultyRating(void)
{
	return 3.5;
}

double hoursSpent(void)
{
	return 14.0;
}
