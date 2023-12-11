#include <bits/stdc++.h>

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
        cout << id << " " << name << " " << age << " " << salary << "$" << endl;
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

    void display(string filter = "default")
    {
        if (filter == "default")
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
        else if (filter == "bySalary")
        {
            cout << "Team ID: " << id << endl;
            cout << "Team Name: " << name << endl;
            cout << "Team President: " << president << endl;
            cout << "Team Players: " << endl;
            if (players != nullptr)
            {
                Node<Player> *current = players->getHead();
                vector<Player> playersVector;
                while (current != nullptr)
                {
                    playersVector.push_back(current->data);
                    current = current->next;
                }

                sort(playersVector.begin(), playersVector.end(), [](const Player &a, const Player &b)
                     { return a.salary > b.salary; });

                for (int i = 0; i < playersVector.size(); i++)
                {
                    playersVector[i].display();
                }
            }

            cout << endl;
        }
    }

    void updateTeamInfo(const string &newName, const string &newPresident)
    {
        name = (!newName.empty()) ? newName : name;
        president = (!newPresident.empty()) ? newPresident : president;
        cout << "Team information updated successfully" << endl;
    }

    ~Team()
    {
        delete players;
    }
};

void displayMenu()
{
    cout << "----- Menu -----" << endl;
    cout << "1. Add Team" << endl;
    cout << "2. Add Player to Team" << endl;
    cout << "3. Update Player Information" << endl;
    cout << "4. Remove Player from Team" << endl;
    cout << "5. Update Team Information" << endl;
    cout << "6. Display Team Details" << endl;
    cout << "7. Remove Team" << endl;
    cout << "8. Exit" << endl;
}

int main()
{
    LinkedList<Team> egyptianLeague;

    int choice;
    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {

            int teamId;
            string teamName, teamPresident;
            cout << "Enter Team ID: ";
            cin >> teamId;
            cout << "Enter Team Name: ";
            cin.ignore();
            getline(cin, teamName);
            cout << "Enter Team President: ";
            getline(cin, teamPresident);

            Team newTeam(teamId, teamName, teamPresident);
            egyptianLeague.add(newTeam);

            cout << "Team added successfully!" << endl;
            break;
        }
        case 2:
        {

            int teamId, playerId, age;
            double salary;
            string playerName;

            cout << "Enter Team ID: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                cout << "Enter Player ID: ";
                cin >> playerId;
                cout << "Enter Player Name: ";
                cin.ignore();
                getline(cin, playerName);
                cout << "Enter Player Age: ";
                cin >> age;
                cout << "Enter Player Salary: ";
                cin >> salary;

                teamNode->data.addPlayer(playerId, playerName, age, salary);
                cout << "Player added to the team successfully!" << endl;
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 3:
        {

            int teamId, playerId, age;
            double salary;
            string playerName;

            cout << "Enter Team ID: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                cout << "Enter Player ID: ";
                cin >> playerId;
                cout << "Enter New Player Name (Press Enter to keep the same): ";
                cin.ignore();
                getline(cin, playerName);
                cout << "Enter New Player Age (Press 0 to keep the same): ";
                cin >> age;
                cout << "Enter New Player Salary (Press 0.0 to keep the same): ";
                cin >> salary;

                teamNode->data.updatePlayer(playerId, playerName, age, salary);
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 4:
        {

            int teamId, playerId;
            cout << "Enter Team ID: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                cout << "Enter Player ID to remove: ";
                cin >> playerId;
                teamNode->data.removePlayer(playerId);
                cout << "Player removed from the team successfully!" << endl;
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 5:
        {

            int teamId;
            string newName, newPresident;
            cout << "Enter Team ID: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                cout << "Enter New Team Name (Press Enter to keep the same): ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter New Team President (Press Enter to keep the same): ";
                getline(cin, newPresident);

                teamNode->data.updateTeamInfo(newName, newPresident);
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 6:
        {

            int teamId;
            cout << "Enter Team ID: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                teamNode->data.display();
            }
            else
            {
                cout << "Team not found!" << endl;
            }
        }
        case 7:
        {

            int teamId;
            cout << "Enter Team ID to remove: ";
            cin >> teamId;

            Node<Team> *teamNode = egyptianLeague.searchById(teamId);

            if (teamNode != nullptr)
            {
                egyptianLeague.remove(teamId);
                cout << "Team removed successfully!" << endl;
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 8:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}
