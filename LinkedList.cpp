#include "LinkedList.hpp"

LinkedList::LinkedList()
{
    head = nullptr;
    length = 0;
}

LinkedList::~LinkedList()
{
    Node *current = head;
    Node *ahead;
    while (current != NULL)
    {
        ahead = current->next;
        delete current->data;
        delete current;
        current = ahead;
    }
    head = NULL;
    std::cout << "~list::list()";
}

bool LinkedList::isEmpty()
{
    if (head == nullptr)
        return true;
    else
        return false;
}

void LinkedList::append(Shape *s)
{
    Node *newObject = new Node(s);
    if (head == nullptr)
        head = newObject;
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newObject;
    }
    length++;
}

void LinkedList::Remove()
{

    Shape *rem = nullptr;
    if (head->next == nullptr)
    {
        rem = head->data;
        delete head->data;
        delete head;
        head = nullptr;
        delete[] head;
        // return rem;
    }
    else
    {
        Node *temp = head;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        rem = temp->next->data;
        delete temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        delete[] temp->next;
        // return rem;
    }
    length--;
}

int LinkedList::getSize()
{
    return length;
}

//void LinkedList::Reverse()
//{
//    Node* current = head;
//    Node* prev = nullptr;
//    Node* next = nullptr;
//    while (current != nullptr)
//    {
//        // Store next
//        next = current->next;
//        // Reverse current node's pointer
//        current->next = prev;
//        // Move pointers one position ahead.
//        prev = current;
//        current = next;
//    }
//    head = prev;
//}

//void LinkedList::Draw(SDL_Renderer* gRenderer, bool order) //Draw entire list in requested order of rendering
//{
//    if (head!=nullptr)
//    {
//        if (order == true) //switching
//        {
//            Reverse();
//        }
//
//        Node* temp = head;
//        while (temp!=nullptr)
//        {
//            temp->data->draw(gRenderer);
//            temp = temp->next;
//        }
//    }
//}

Shape *LinkedList::operator[](int num)
{
    Node *temp = head; // the node to be added

    for (int i = 0; i < num; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}