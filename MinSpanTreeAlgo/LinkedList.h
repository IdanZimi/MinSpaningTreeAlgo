#pragma once
#include "definitions.h"
#include "Node.h"

// Linked list class to implement a linked list.
class LinkedList {

private:
    Node* head;
    Node* tail;
    Node* createNewNode(int data, int weight, Node* next, Node* prev);
    void makeEmptyList(LinkedList* lst);
    bool isEmptyList(LinkedList* lst);
    void insertNodeToStartList(LinkedList* lst, Node* head);

public:
    LinkedList()
    {
        makeEmptyList(this);
    }
    void insertNode(int data, int weight);
    void deleteNode(int key);
    Node* getHead();
    ~LinkedList();
};