#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Node structure for a task
struct Task {
    int id;
    string description;
    int priority;
    unique_ptr<Task> next;

    Task(int id, string desc, int priority) : id(id), description(desc), priority(priority), next(nullptr) {}
};

class TaskManager {
private:
    unique_ptr<Task> head; // Head of the linked list

public:
    TaskManager() : head(nullptr) {}

    // Function to add a new task based on priority
    void addTask(int id, const string& desc, int priority) {
        auto newTask = make_unique<Task>(id, desc, priority);
        if (!head || head->priority < priority) {
            newTask->next = move(head);
            head = move(newTask);
            return;
        }
        Task* temp = head.get();
        while (temp->next && temp->next->priority >= priority) {
            temp = temp->next.get();
        }
        newTask->next = move(temp->next);
        temp->next = move(newTask);
    }

    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks available to remove.\n";
            return;
        }
        cout << "Removing task: ID=" << head->id << ", Description=" << head->description << "\n";
        head = move(head->next);
    }

    // Function to remove a task by its ID
    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available to remove.\n";
            return;
        }
        if (head->id == id) {
            cout << "Removing task: ID=" << head->id << ", Description=" << head->description << "\n";
            head = move(head->next);
            return;
        }
        Task* temp = head.get();
        while (temp->next && temp->next->id != id) {
            temp = temp->next.get();
        }
        if (!temp->next) {
            cout << "Task with ID " << id << " not found.\n";
            return;
        }
        cout << "Removing task: ID=" << temp->next->id << ", Description=" << temp->next->description << "\n";
        temp->next = move(temp->next->next);
    }

    // Function to update a task by ID
    void updateTask(int id, const string& newDesc, int newPriority) {
        Task* temp = head.get();
        while (temp && temp->id != id) {
            temp = temp->next.get();
        }
        if (!temp) {
            cout << "Task with ID " << id << " not found.\n";
            return;
        }
        temp->description = newDesc;
        temp->priority = newPriority;
        cout << "Task with ID " << id << " updated successfully.\n";
    }

    // Function to display all tasks
    void viewTasks() const {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        cout << "Task List:\n";
        cout << "-------------------------\n";
        const Task* temp = head.get();
        while (temp) {
            cout << "ID: " << temp->id << " | Description: " << temp->description << " | Priority: " << temp->priority << "\n";
            temp = temp->next.get();
        }
        cout << "-------------------------\n";
    }
};

int main() {
    TaskManager manager;
    int choice, id, priority;
    string desc;

    while (true) {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Remove Highest Priority Task\n";
        cout << "4. Remove Task by ID\n";
        cout << "5. Update Task\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Task Description: ";
                getline(cin, desc);
                cout << "Enter Priority (higher number = higher priority): ";
                cin >> priority;
                manager.addTask(id, desc, priority);
                break;
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;
            case 5:
                cout << "Enter Task ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Description: ";
                getline(cin, desc);
                cout << "Enter New Priority: ";
                cin >> priority;
                manager.updateTask(id, desc, priority);
                break;
            case 6:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
