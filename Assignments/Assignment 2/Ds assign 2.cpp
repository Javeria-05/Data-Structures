#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name;
    string condition;
    int priority;

    Patient(string n, string c, int p) : name(n), condition(c), priority(p) {}

    bool operator<(const Patient& p) const {
        return priority > p.priority;
    }
};

int getPriority(string condition) {
    if (condition == "Heart Attack" || condition == "Stroke") return 1;
    if (condition == "Severe Burn" || condition == "Broken Leg") return 2;
    if (condition == "Fever" || condition == "Food Poisoning") return 3;
    return 4;
}

int main() {
    priority_queue<Patient> pq;
    int choice;
    string name, condition;

    do {
        cout << "\n1. Add Patient\n2. Treat Patient\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter patient's name: ";
            getline(cin, name);
            cout << "Enter emergency condition: ";
            getline(cin, condition);

            int priority = getPriority(condition);
            pq.push(Patient(name, condition, priority));
            cout << "Patient added.\n";
        } else if (choice == 2) {
            if (!pq.empty()) {
                Patient p = pq.top();
                pq.pop();
                cout << "Treating: " << p.name << " | Condition: " << p.condition << " | Priority: " << p.priority << endl;
            } else {
                cout << "No patients in the queue.\n";
            }
        } else if (choice == 3) {
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 3);

    return 0;
}
