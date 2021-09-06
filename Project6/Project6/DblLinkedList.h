#pragma once
#ifndef DOUBLY_LINKEDLIST_H
#define DOUBLY_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int Element;
typedef struct Node
{
    Element data;
    struct Node* prev;
    struct Node* next;
}Node;
Node* DLL_CreateNode(Element NewData); //1.create node
void DLL_DestroyNode(Node* Node);//2.destroy node
void DLL_AppendNode(Node** Head, Node* NewNode);//3.append node
/*
4.insert node
connect
prev-insert-next
*/
void DLL_InsertAfter(Node* Current, Node* NewNode);
void DLL_RemoveNode(Node** Head, Node* Remove);//5.remove node
Node* DLL_GetNodeAt(Node* Head, int location);//6.search node 
int DLL_GetNodeCount(Node* Head);//7.count the number of nodes
#endif
