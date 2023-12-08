#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

struct Player
{
    int ID;
    string Name;
    int Age;
    double Salary;

    Player(int id, const string &name, int age, double salary) : ID(id), Name(name), Age(age), Salary(salary) {}
};

class Team
{
private:
    int id;
    string name;
    string president;
    LinkedList<Player> *players;

public:
    Team(int teamId, const string &teamName, const string &teamPresident) : id(teamId), name(teamName), president(teamPresident), players(nullptr) {}

    void AddPlayer(int id, const string &name, int age, double salary)
    {
        if (players == nullptr)
        {
            players = new LinkedList<Player>();
        }
        players->add({id, name, age, salary});
    }

    void DisplayTeam()
    {
        cout << "Team ID: " << id << ", Name: " << name << ", President: " << president << endl;
        if (players != nullptr)
        {
            cout << "Players:\n";
            players->display();
        }
        cout << endl;
    }

    ~Team()
    {
        delete players;
    }
};

template <typename T>
struct Node
{
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
            cout << current->data.ID << ": " << current->data.Name << " (Age: " << current->data.Age << ", Salary: $" << current->data.Salary << ")\n";
            current = current->next;
        }
        cout << endl;
    }

    ~LinkedList()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
    }
};

int main()
{
    LinkedList<Team> teams;

    // Team team1(1, "Team A", "President A");

    // team1.AddPlayer(1, "Player 1", 25, 50000);
    // team1.AddPlayer(2, "Player 2", 28, 60000);

    // teams.add(team1);

    // teams.display();

    return 0;
}
