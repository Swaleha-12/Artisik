#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Shape.hpp"

struct Node
{
    Shape *data; // To store data which is every shape object added
    Node *next;  // To store the address or link to the next node

    Node(Shape *s, Node *ptr = nullptr)
    {
        data = s;
        next = ptr;
    }
};

struct LinkedList
{
    Node *head;
    int length;

    LinkedList();
    ~LinkedList();

    bool isEmpty();
    void append(Shape *); //to add an element at the tail of list
    void Remove();        //to remove last element from the list
    void Reverse();
    //void Draw(SDL_Renderer*, bool); //Draw entire list in requested order of rendering
    Shape *operator[](int num); //to access a certain element in the list
    int getSize();              //get size of list
};