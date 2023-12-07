#include <bits/stdc++.h>

using namespace std;

template <typename T>

struct Node
{
public:
    T data;
    Node *next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>

class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList() : head(nullptr) {}

    void add(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // We can tweak it to take a key to search for it inside every (Team, Player) and remove it
    void remove(T value)
    {
        Node<T> *current = head;
        Node<T> *previous = nullptr;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
};

int main()
{
    // Example of using a Generic LinkedList
    // LinkedList<int> list;
    // list.add(1);
    // list.add(2);
    // list.add(3);
    // list.add(4);
    // list.display();
    // list.remove(3);
    // list.display();
    return 0;
}