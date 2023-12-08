#include <iostream>
#include <string>
#include <chrono>   // for this_thread::sleep_for
#include <thread>   // for this_thread::sleep_for

using namespace std;

// Player structure
struct Player {
    int ID;
    string Name;
    int Age;
    double Salary;

    // Add more player details as needed
    Player(int id, const string& name, int age, double salary) : ID(id), Name(name), Age(age), Salary(salary) {}
};
struct Team{
    int id ;
    string name ;
    string president;
    Player* players;
    Team*next;
    Team(int teamId, const string& teamName, const string& teamPresident) : id(teamId), name(teamName), president(teamPresident), players(nullptr), next(nullptr) {} 
};

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void AddTeam(int id, const string name, const string president) {
        Team* newTeam = new Team(id, name, president);
        newTeam->next = teams;
        teams = newTeam;
    }

    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data.ID << ": " << current->data.Name << " (Age: " << current->data.Age << ", Salary: $" << current->data.Salary << ")\n";
            current = current->next;
        }
        cout << endl;
    }
    void displayTeams() {
        Team* current = teams;
        while (current != nullptr) {
            std::cout << "Team ID: " << current->id << ", Name: " << current->name << ", President: " << current->president << std::endl;
            current = current->next;
        }
    }


    Team* SearchTeam(int id) {
        Team* current = teams;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removePlayer(int id) {
        Node<T>* current = head;
        Node<T>* previous = nullptr;

        while (current != nullptr) {
            if (current->data.ID == id) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // Search for a player by ID and display their information
    void searchPlayer(int id) {
        if (head == nullptr) {
            cout << "The player list is empty.\n";
            return;
        }

        Node<T>* current = head;

        while (current != nullptr) {
            if (current->data.ID == id) {
                cout << "Player found: " << current->data.ID << ": " << current->data.Name << " (Age: " << current->data.Age << ", Salary: $" << current->data.Salary << ")\n";
                return;
            }
            current = current->next;
        }

        cout << "Player not found with ID: " << id << endl;
    }
    

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList<Player> playersList;  // Use LinkedList to manage players

    int choice;
    do {
        cout << "1. Add Player\n";
        cout << "2. Display Players\n";
        cout << "3. Remove Player\n";
        cout << "4. Search Player\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, age;
                double salary;
                string name;
                cout << "Enter player ID: ";
                cin >> id;
                cout << "Enter player name: ";
                cin.ignore();  // Clear buffer
                getline(cin, name);
                cout << "Enter player age: ";
                cin >> age;
                cout << "Enter player salary: $";
                cin >> salary;
                playersList.add({id, name, age, salary});
                break;
            }
            case 2:
                cout << "Players:\n";
                playersList.display();
                this_thread::sleep_for(chrono::seconds(2));  // Sleep for 2 seconds
                break;
            case 3: {
                int idToRemove;
                cout << "Enter player ID to remove: ";
                cin >> idToRemove;
                playersList.removePlayer(idToRemove);
                cout << "Player removed successfully.\n";
                this_thread::sleep_for(chrono::seconds(2));  // Sleep for 2 seconds
                break;
            }
            case 4: {
                int idToSearch;
                cout << "Enter player ID to search: ";
                cin >> idToSearch;
                playersList.searchPlayer(idToSearch);
                this_thread::sleep_for(chrono::seconds(2));  // Sleep for 2 seconds
                break;
            }
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
