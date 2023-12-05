#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& name, const T2& extime) : name(name), extime(extime) {}

    void displayPair() const {
        std::cout << name << ": " << extime << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const {
        outFile << name << " " << extime << " ";
    }
private:
    T1 name;
    T2 extime;
};


class Excursion {
public:
    Excursion(const std::string& name, std::string extime, std::string guide)
        : name(name), extime(extime), guide(guide) {}

    ~Excursion() {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getExtime() const {
        return extime;
    }

    const std::string& getGuide() const {
        return guide;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setExtime(const std::string& newTime) {
        extime = newTime;
    }

    void setGuide(const std::string& newGuide) {
        guide = newGuide;
    }

    virtual void displayInfo() const {
        std::cout << "Экскурсия: " << name << " , Время: " << extime << ", Гид: " << guide << std::endl;
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << name << " " << extime << " " << guide << " ";
    }

    static bool compareByTime(const Excursion* Excursion1, const Excursion* Excursion2) {
        return Excursion1->getExtime() < Excursion2->getExtime();
    }

private:
    std::string name;
    std::string extime;
    std::string guide;
};

class HistoricalTour : public Excursion {
public:
    void displayInfo() const override{
        std::cout << "Исторический тур: " << name << " , Время: " << extime << " , Гид: " << guide << std::endl;
    }
private:
    std::string name;
    std::string extime;
    std::string guide;
};

class CitySightseeing : public Excursion {
public:
    void displayInfo() const override {
        std::cout << "Экскурсия по городу: " << name << " , Время: " << extime << " , Гид: " << guide << std::endl;
    }
private:
    std::string name;
    std::string extime;
    std::string guide;
};

void modifyExcursion(Excursion* Excursion) {
    std::cout << "Экскурсия найдена. Что вы хотите изменить?" << std::endl;
    std::cout << "1. Название экскурсии" << std::endl;
    std::cout << "2. Время" << std::endl;
    std::cout << "3. Гида" << std::endl;

    int choice;
    std::cout << "Введите Ваш выбор:" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        std::string newName;
        std::cout << "Введите новое название экскурсии: " << std::endl;
        std::getline(std::cin, newName);
        Excursion->setName(newName);
        break;
    }
    case 2: {
        std::string newTime;
        std::cout << "Введите новое время проведения экскурсии: " << std::endl;
        std::getline(std::cin, newTime);
        Excursion->setExtime(newTime);
        break;
    }
    case 3: {
        std::string newGuide;
        std::cout << "Введите нового гида: " << std::endl;
        std::getline(std::cin, newGuide);
        Excursion->setGuide(newGuide);
        break;
    }
    default:
        std::cout << "Неверный выбор. " << std::endl;
    }
}

void saveExcursionsToFile(const std::vector<Excursion*>& Excursions, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи. " << std::endl;
        return;
    }

    for (const auto* Excursion : Excursions) {
        Excursion->saveToFile(outFile);
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Excursion*> Excursions;

    int choice;
    std::string filename;

    do {
        std::cout << "Меню: " << std::endl;
        std::cout << "1. Добавить экскурсию; " << std::endl;
        std::cout << "2. Изменить данные об экскурсии; " << std::endl;
        std::cout << "3. Удалить экскурсию; " << std::endl;
        std::cout << "4. Найти экскурсию; " << std::endl;
        std::cout << "5. Вывести список экскурсий; " << std::endl;
        std::cout << "6. Сохранить в файл; " << std::endl;
        std::cout << "7. Сортировать по цене; " << std::endl;
        std::cout << "8. Завершить работу программы; " << std::endl;

        std::cout << "Введите Ваш выбор: " << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            std::string extime;
            std::string guide;

            std::cout << "Введите данные об экскурсии: " << std::endl;
            std::cout << "Название: " << std::endl;
            std::getline(std::cin, name);
            std::cout << "Время: " << std::endl;
            std::getline(std::cin, extime);
            std::cout << "Гид: " << std::endl;
            std::getline(std::cin, guide);

            Excursions.push_back(new Excursion(name, extime, guide));

            break;
        }
        case 2: {
            std::string name;
            std::string extime;
            std::cout << "Введите данные экскурсии для изменения: " << std::endl;
            std::cout << "Название: " << std::endl;
            std::getline(std::cin, name);
            std::cout << "Время: " << std::endl;
            std::getline(std::cin, extime);

            auto it = std::find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Excursion) {
                return Excursion->getName() == name && Excursion->getExtime() == extime;
                });

            if (it != Excursions.end()) {
                modifyExcursion(*it);
            }
            else {
                std::cout << "Экскурсия с указанными данными не найдена. " << std::endl;
            }

            break;
        }
        case 3: {
            std::string name;
            std::string extime;
            std::cout << "Введите данные экскурсии для удаления: " << std::endl;
            std::cout << "Название: " << std::endl;
            std::cin >> name;
            std::cout << "Время: " << std::endl;
            std::cin >> extime;

            auto it = std::find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Excursion) {
                return Excursion->getName() == name && Excursion->getExtime() == extime;
                });

            if (it != Excursions.end()) {
                delete* it;
                Excursions.erase(it);
                std::cout << "Экскурсия удалена. " << std::endl;
            }
            else {
                std::cout << "Экскурсия с указанными параметрами не найдена. " << std::endl;
            }

            break;
        }
        case 4: {
            std::string name;
            std::string extime;
            std::cout << "Введите данные экскурсии для поиска: " << std::endl;
            std::cout << "Название: " << std::endl;
            std::cin >> name;
            std::cout << "Время: " << std::endl;
            std::cin >> extime;

            auto it = std::find_if(Excursions.begin(), Excursions.end(), [&](const Excursion* Excursion) {
                return Excursion->getName() == name && Excursion->getExtime() == extime;
                });

            if (it != Excursions.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "Экскурсия не найдена. " << std::endl;
            }

            break;
        }
        case 5: {
            std::cout << "Список экскурсий: " << std::endl;
            for (const auto* Excursion : Excursions) {
                Excursion->displayInfo();
            }
            break;
        }
        case 6: {
            std::cout << "Введите имя файла для сохранения данных: " << std::endl;
            std::cin >> filename;
            saveExcursionsToFile(Excursions, filename);
            break;
        }
        case 7: {
            std::sort(Excursions.begin(), Excursions.end(), Excursion::compareByTime);
            std::cout << "Список экскурсий отсортирован по времени. " << std::endl;
            break;
        }
        case 8:
            std::cout << "Программа завершена. " << std::endl;
            break;
        default:
            std::cout << "Неправильный выбор. " << std::endl;
        }
    } while (choice != 8);

    for (const auto* Excursion : Excursions) {
        delete Excursion;
    }

    return 0;
}