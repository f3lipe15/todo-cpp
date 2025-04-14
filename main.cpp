#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Task {
    std::string content;
    bool done;
};

std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream file("tasks.txt");
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        bool done = line[0] == '1';
        std::string content = line.substr(2);
        tasks.push_back({content, done});
    }

    return tasks;
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << (task.done ? "1" : "0") << " " << task.content << "\n";
    }
}

void showTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- Twoje zadania ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". "
                  << (tasks[i].done ? "[✔] " : "[ ] ")
                  << tasks[i].content << "\n";
    }
}

int main() {
    std::vector<Task> tasks = loadTasks();
    int choice;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Pokaż zadania\n"
                  << "2. Dodaj zadanie\n"
                  << "3. Oznacz jako wykonane\n"
                  << "4. Usuń zadanie\n"
                  << "0. Wyjście\n"
                  << "Twój wybór: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1:
                showTasks(tasks);
                break;
            case 2: {
                std::string content;
                std::cout << "Podaj treść zadania: ";
                std::getline(std::cin, content);
                tasks.push_back({content, false});
                saveTasks(tasks);
                break;
            }
            case 3: {
                int index;
                showTasks(tasks);
                std::cout << "Które zadanie oznaczyć jako wykonane? (numer): ";
                std::cin >> index;
                if (index >= 1 && index <= (int)tasks.size()) {
                    tasks[index - 1].done = true;
                    saveTasks(tasks);
                }
                break;
            }
            case 4: {
                int index;
                showTasks(tasks);
                std::cout << "Które zadanie usunąć? (numer): ";
                std::cin >> index;
                if (index >= 1 && index <= (int)tasks.size()) {
                    tasks.erase(tasks.begin() + index - 1);
                    saveTasks(tasks);
                }
                break;
            }
            default:
                std::cout << "Niepoprawna opcja.\n";
        }
    }

    std::cout << "Do zobaczenia!\n";
    return 0;
}
