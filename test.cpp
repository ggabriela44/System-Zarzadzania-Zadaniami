#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Klasa zadania
class Task {
public:
    Task(int id, const std::string& description)
        : id(id), description(description) {}

    int getId() const { return id; }
    std::string getDescription() const { return description; }
    void setDescription(const std::string& desc) { description = desc; }

private:
    int id;
    std::string description;
};

// Interfejs obserwatora
class Observer {
public:
    virtual void update() = 0;
};

// Klasa zarządzająca zadaniami (Singleton)
class TaskManager {
public:
    static TaskManager& getInstance() {
        static TaskManager instance;
        return instance;
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
        notifyObservers();
    }

    void editTask(int id, const std::string& newDescription) {
        auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
            return task.getId() == id;
            });
        if (it != tasks.end()) {
            it->setDescription(newDescription);
            notifyObservers();
        }
        else {
            std::cout << "Task not found.\n";
        }
    }

    void removeTask(int id) {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
            return task.getId() == id;
            }), tasks.end());
        notifyObservers();
    }

    const std::vector<Task>& getTasks() const {
        return tasks;
    }

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() { // Przeniesiono do sekcji publicznej
        for (Observer* observer : observers) {
            observer->update();
        }
    }

private:
    TaskManager() {}
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    std::vector<Task> tasks;
    std::vector<Observer*> observers;
};

// Klasa obserwatora wypisująca listę zadań
class TaskListPrinter : public Observer {
public:
    void update() override {
        const std::vector<Task>& tasks = TaskManager::getInstance().getTasks();
        std::cout << "Current tasks:\n";
        for (const Task& task : tasks) {
            std::cout << "ID: " << task.getId() << ", Description: " << task.getDescription() << '\n';
        }
        std::cout << '\n';
    }
};

// Funkcje pomocnicze do interfejsu użytkownika
void printMenu() {
    std::cout << "1. Add Task\n";
    std::cout << "2. Edit Task\n";
    std::cout << "3. Remove Task\n";
    std::cout << "4. Print Tasks\n";
    std::cout << "5. Exit\n";
}

void addTask() {
    int id;
    std::string description;
    std::cout << "Enter task ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter task description: ";
    std::getline(std::cin, description);

    TaskManager::getInstance().addTask(Task(id, description));
}

void editTask() {
    int id;
    std::string description;
    std::cout << "Enter task ID to edit: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter new task description: ";
    std::getline(std::cin, description);

    TaskManager::getInstance().editTask(id, description);
}

void removeTask() {
    int id;
    std::cout << "Enter task ID to remove: ";
    std::cin >> id;

    TaskManager::getInstance().removeTask(id);
}

int main() {
    TaskListPrinter printer;
    TaskManager::getInstance().addObserver(&printer);

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            editTask();
            break;
        case 3:
            removeTask();
            break;
        case 4:
            TaskManager::getInstance().notifyObservers(); // Upewnij się, że notifyObservers jest publiczne
            break;
        case 5:
            return 0;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}
