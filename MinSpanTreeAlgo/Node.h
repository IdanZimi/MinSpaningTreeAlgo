#pragma once
class Node 
{

private:
    int vertex;
    Node* next;
    Node* prev;
    int weight;

public:

    Node()
    {  
        next = nullptr;
        prev = nullptr;
    }

    // Parameterised Constructor
    Node(int data)
    {
        this->vertex = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
    
    friend class Graph;
    friend class LinkedList;
   
};