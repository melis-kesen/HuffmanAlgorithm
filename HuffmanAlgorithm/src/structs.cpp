//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: MELİS KEŞEN
//---Student Number: 504211561
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    /*If queue is empty or head is larger than new node add new node as a head*/
    if (head == NULL || newnode->token.val < head->token.val)
    {
        Node *prevHead = head;
        head = newnode;
        newnode->next = prevHead;
    }
    /*Else, loop through temp's next null, if it is break and add new node after the temp */
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            if (newnode->token.val < temp->next->token.val)
            {
                break;
            }

            temp = temp->next;
        }

        newnode->next = temp->next;
        temp->next = newnode;
    }
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    Node *temp = head;
    /*If queue is empty means head is null, return null*/
    if (head == NULL)
    {
        cout << "Priority Queue is underflow" << endl;
        return NULL;
    }
    /*Else, dequeu head of the queue */
    else
    {
        head = temp->next;
        return temp;
    }
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree()
{
    deleteTree(root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    if (node == NULL)
        return;

    /* first delete both subtrees */
    deleteTree(node->left);
    deleteTree(node->right);

    /* then delete the node */
    // cout << "\n Deleting node: " << node->data;
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    /*Take two nodes and assign the larger one as a right and smaller one as a left*/
    Node *merged = new Node();
    if (temp1->token.val > temp2->token.val)
    {
        merged->right = temp1;
        merged->left = temp2;
    }
    else
    {
        merged->right = temp2;
        merged->left = temp1;
    }
    /*Merge these two nodes by adding*/
    merged->token.symbol = temp1->token.symbol + temp2->token.symbol;
    merged->token.val = temp1->token.val + temp2->token.val;
    //  cout << "merged value " << merged->token.val << " symbol " << merged->token.symbol << " left: " << merged->left->token.val << " right: " << merged->right->token.val << endl;

    return merged;
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};
