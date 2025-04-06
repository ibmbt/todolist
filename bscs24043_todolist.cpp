#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int maxTasks = 10;

class Task {

public:
    string name;
    bool isComplete;

    Task(string taskName, bool status = false) : name(taskName), isComplete(status) {}

    void markComplete() {
        isComplete = true;
    }

    void display() const {
        cout << (isComplete ? "[Done] " : "[Pending] ") << name << endl;
    }
};

void showMenu() {
    cout << "======|TodoList Menu|=====\n";
    cout << "[1] Add Task\n";
    cout << "[2] View Tasks\n";
    cout << "[3] Mark Task as Complete\n";
    cout << "[4] Remove Task\n";
    cout << "[5] Pending Tasks\n";
    cout << "[6] ...\n";
    cout << "[7] ...\n";
    cout << "[8] ...\n";
    cout << "[9] Exit\n";
    cout << "Enter your choice: ";
}

void addTask(Task** todoList, int& count) {
    string taskName;
    cout << "Enter task name: ";
    getline(cin, taskName);

    Task* newTask = new Task(taskName);
    todoList[count] = newTask;
    count++;
}

void viewTasks(Task** todoList, int count) {
    if (count == 0) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "Todo List:\n";
    for (int i = 0; i < count; ++i) {
        cout << (i + 1) << ". ";
        todoList[i]->display();
    }
}

void markTaskComplete(Task** todoList, int count) {
    int taskIndex;
    cout << "Enter task number to mark as complete: ";
    cin >> taskIndex;
    cin.ignore();

    if (taskIndex > 0 && taskIndex <= count) {
        todoList[taskIndex - 1]->markComplete();
        cout << "Task marked as complete.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void removeTask(Task** todoList, int& count) {
    int taskIndex;
    cout << "Enter task number to remove: ";
    cin >> taskIndex;
    cin.ignore();

    if (taskIndex > 0 && taskIndex <= count) {
        
        delete todoList[taskIndex - 1];

        for (int i = taskIndex - 1; i < count - 1; ++i) {
            todoList[i] = todoList[i + 1];
        }

        todoList[count - 1] = nullptr;

        count--;

        cout << "Task removed.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void showPendingTasks(Task** todoList, int count) {
    bool hasPendingTasks = false;
    cout << "===== Pending Tasks =====\n";
    for (int i = 0; i < count; ++i) {
        if (!todoList[i]->isComplete) { 
            cout << (i + 1) << ". ";
            todoList[i]->display();
            hasPendingTasks = true;
        }
    }

    if (!hasPendingTasks) {
        cout << "No pending tasks.\n";
    }
}


void loadFromFile(Task** todoList, int& count) {
    ifstream fin("todolist.txt");
    if (!fin) {
        cout << "No previous tasks found, starting fresh.\n";
        return;
    }

    string taskName;
    bool isComplete;
    while (getline(fin, taskName)) {
        fin >> isComplete;
        fin.ignore();

        Task* newTask = new Task(taskName, isComplete);
        todoList[count] = newTask;
        count++;
    }

    fin.close();
}

void saveToFile(Task** todoList, int count) {
    ofstream fout("todolist.txt", ios::trunc);

    for (int i = 0; i < count; ++i) {
        fout << todoList[i]->name << "\n";
        fout << todoList[i]->isComplete << "\n";
    }

    fout.close();
}


void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void clearScreen() {
    system("cls");
}


int main() {

    int count = 0;
    Task* todoList[maxTasks];

    loadFromFile(todoList, count);


    int choice;
    do {

        cout << endl << endl;
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            clearScreen();
            if (count < maxTasks) {
                addTask(todoList, count);
            }
            else {
                cout << "Task list is full.\n";
            }
            break;
        case 2:
            clearScreen();
            viewTasks(todoList, count);
            break;
        case 3:
            clearScreen();
            viewTasks(todoList, count);
            cout << endl;
            markTaskComplete(todoList, count);
            break;
        case 4:
            clearScreen();
            viewTasks(todoList, count);
            cout << endl;
            removeTask(todoList, count);
            break;
        case 5:
            clearScreen();
            showPendingTasks(todoList, count);
            break;
        case 9:
            clearScreen();
            saveToFile(todoList, count);
            for (int i = 0; i < count; ++i) {
                delete todoList[i];
            }
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9);

	return 0;
}

