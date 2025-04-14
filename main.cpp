#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "include/json.hpp"

using json = nlohmann::json;

struct Task {
    std::string content;
    bool done;
};

std::vector<Task> loadTasks(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);

    if (!file.is_open()) return tasks;

    json data;
    file >> data;

    for (const auto& item : data) {
        tasks.push_back({item["content"], item["done"]});
    }

    return tasks;
}

void saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    json data = json::array();

    for (const auto& task : tasks) {
        data.push_back({
            {"content", task.content},
            {"done", task.done}
        });
    }

    std::ofstream file(filename);
    file << data.dump(4); // pretty print z wcięciem
}

void showTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- Twoje zadania ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". "
                  << (tasks[i].done ? "[✔] " : "[ ] ")
                  << tasks[i].content << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::string dataFile = "tasks.json";
    if (argc > 1 && std::string(argv[1]) == "test") {
        dataFile = "tasks_test.json";
        std::cout << "🔍 Uruchomiono program w trybie testowym\n";
    }

    std::vector<Task> tasks = loadTasks(dataFile);
    int choice;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Pokaż zadania\n"
                  << "2. Dodaj zadanie\n"
                  << "3. Oznacz jako wykonane\n"
                  << "4. Usuń zadanie\n"
                  << "5. Edytuj zadanie\n"
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
                saveTasks(tasks, dataFile);
                break;
            }

            case 3: {
                int index;
                showTasks(tasks);
                std::cout << "Które zadanie oznaczyć jako wykonane? (numer): ";
                std::cin >> index;
                if (index >= 1 && index <= (int)tasks.size()) {
                    tasks[index - 1].done = true;
                    saveTasks(tasks, dataFile);
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
                    saveTasks(tasks, dataFile);
                }
                break;
            }

            case 5: {
                int index;
                showTasks(tasks);
                std::cout << "Które zadanie chcesz edytować? (numer): ";
                std::cin >> index;
                std::cin.ignore();

                if (index >= 1 && index <= (int)tasks.size()) {
                    std::string newContent;
                    std::cout << "Nowa treść zadania: ";
                    std::getline(std::cin, newContent);

                    tasks[index - 1].content = newContent;
                    saveTasks(tasks, dataFile);
                    std::cout << "✅ Zadanie zostało zaktualizowane.\n";
                } else {
                    std::cout << "❌ Nieprawidłowy numer zadania.\n";
                }
                break;
            }

            default:
                std::cout << "❌ Niepoprawna opcja.\n";
        }
    }

    std::cout << "👋 Do zobaczenia!\n";
    return 0;
}
