#include "LinkedList.h"

void LinkedList::insertNode(int data, int weight)///insert Node to the start of list
{
        Node* newHead;
        newHead = createNewNode(data, weight, NULL, NULL);
        insertNodeToStartList(this, newHead);
}

void LinkedList :: makeEmptyList(LinkedList* lst)
{
    lst->head = lst->tail = nullptr;
}

bool LinkedList :: isEmptyList(LinkedList* lst)
{
    if (lst->head == nullptr)
        return true;
    else
        return false;
}

Node* LinkedList :: createNewNode(int data, int weight, Node* next, Node* prev)
{
    Node* res;
    res = new Node;
    res->weight = weight;
    res->vertex = data;
    res->next = next;
    res->prev = prev;
    return res;
}

void LinkedList :: insertNodeToStartList(LinkedList* lst, Node* head)
{
    if (isEmptyList(lst) == true)
    {
        head->next = head->prev = NULL;
        lst->head = lst->tail = head;
    }
    else
    {
        head->next = lst->head;
        head->prev = NULL;
        lst->head->prev = head;
        lst->head = head;
    }
}

void LinkedList :: deleteNode(int key)
{
     Node* temp = head;
     Node* prev = nullptr;

    if (temp != nullptr && temp->vertex == key)
    {
        if (temp->next == nullptr)
        {
            head = tail = nullptr;
            delete temp;
            return;
        }
        else
        {
            head = temp->next;
            head->prev = nullptr;
            delete temp;
            return;
        }
    }
    // Find the key to be deleted
    while (temp != nullptr && temp->vertex != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not present
    if (temp == nullptr) return;

    // Remove the node
    if (temp == tail)
    {
        tail->prev->next = nullptr;
        tail = tail->prev;
    }
    else
    {
        temp->next->prev = temp->prev;
        prev->next = temp->next;
    }
    
     delete temp;
}

Node* LinkedList::getHead()
{
    return head;
}

LinkedList :: ~LinkedList()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}