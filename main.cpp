#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

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

    Node<T> *getHead() const
    {
        return head;
    }

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
            current->data.display();

            current = current->next;
        }
    }

    Node<T> *searchById(int teamId)
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data.id == teamId)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(int id)
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->data.id == id)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node<T> *current = head;
        while (current->next != nullptr)
        {
            if (current->next->data.id == id)
            {
                Node<T> *temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
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

struct Player
{
public:
    int id;
    string name;
    int age;
    double salary;

    Player(int id, const string &name, int age, double salary) : id(id), name(name), age(age), salary(salary) {}

    void display()
    {
        cout << id << " " << name << " " << age << " " << salary << endl;
    }

    friend class LinkedList<Player>;
};

class Team
{
public:
    int id;
    string name;
    string president;
    LinkedList<Player> *players;

    Team(int teamId, const string &teamName, const string &teamPresident) : id(teamId), name(teamName), president(teamPresident), players(nullptr) {}

    void addPlayer(int id, const string &name, int age, double salary)
    {
        if (players == nullptr)
        {
            players = new LinkedList<Player>();
        }
        players->add({id, name, age, salary});
    }

    void updatePlayer(int id, string name, int age, double salary)
    {
        if (players == nullptr)
        {
            players = new LinkedList<Player>();
        }
        Node<Player> *current = players->getHead();
        while (current != nullptr)
        {
            if (current->data.id == id)
            {
                current->data.name = (!name.empty()) ? name : current->data.name;
                current->data.age = (age != 0) ? age : current->data.age;
                current->data.salary = (salary != 0.0) ? salary : current->data.salary;
                cout << "Player updated successfully" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Player not found" << endl;
    }

    void removePlayer(int id)
    {
        if (players != nullptr)
        {
            players->remove(id);
        }
    }

    void display()
    {
        cout << "Team ID: " << id << endl;
        cout << "Team Name: " << name << endl;
        cout << "Team President: " << president << endl;
        cout << "Team Players: " << endl;
        if (players != nullptr)
        {
            players->display();
        }

        cout << endl;
    }

    // TODO: Update team information
    // TODO: search for a player by name

    ~Team()
    {
        delete players;
    }
};

int main()
{
    LinkedList<Team> egyptianLeague;
    egyptianLeague.add({1, "Al Ahly", "Mahmoud El Khatib"});
    egyptianLeague.add({2, "Zamalek", "Mortada Mansour"});
    egyptianLeague.add({3, "Al Masry", "Samir Halabia"});
    egyptianLeague.add({4, "Al Ittihad", "Mohamed Moselhy"});
    egyptianLeague.add({5, "Al Mokawloon", "Mohamed Abdel Salam"});
    egyptianLeague.add({6, "Al Entag Al Harby", "Mohamed Kamel"});
    egyptianLeague.add({7, "Al Gouna", "Mohamed Abou El Soud"});

    // Add players to Al Ahly
    egyptianLeague.getHead()->data.addPlayer(11, "Mohamed Salah", 30, 1000000.0);
    egyptianLeague.getHead()->data.addPlayer(7, "Mohamed El Neny", 29, 800000.0);

    // Add players to Zamalek
    egyptianLeague.getHead()->next->data.addPlayer(10, "Achraf Bencharki", 27, 900000.0);
    egyptianLeague.getHead()->next->data.addPlayer(22, "Tarek Hamed", 29, 850000.0);

    // Add players to Al Masry
    egyptianLeague.getHead()->next->next->data.addPlayer(14, "Ahmed Gomaa", 25, 700000.0);
    egyptianLeague.getHead()->next->next->data.addPlayer(8, "Hossam Hassan", 22, 600000.0);

    // Display the league
    egyptianLeague.display();

    Node<Player> *player = egyptianLeague.getHead()->data.players->searchById(11);
    if (player == nullptr)
    {
        cout << "Player not found" << endl;
    }
    else
    {
        cout << "Player found" << endl;
        player->data.display();
    }

    return 0;
}
