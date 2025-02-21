#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Kursvalut {
protected:
    string first, second, date;
    double kurs;

public:
    Kursvalut() : first(""), second(""), kurs(0.0), date("") {}
    virtual ~Kursvalut() = default;

    virtual void input() {
        cout << "Введите первую валюту: ";
        cin >> first;
        cout << "Введите вторую валюту: ";
        cin >> second;
        cout << "Введите курс: ";
        cin >> kurs;
        cout << "Введите дату (гггг.мм.дд): ";
        cin >> date;
    }

    virtual void display() const {
        cout << first << " -> " << second << " | Курс: " << kurs << " | Дата: " << date << endl;
    }

    virtual void saveToFile(ofstream& fout) const {
        fout << first << " " << second << " " << kurs << " " << date;  
    }

    virtual void loadFromFile(ifstream& fin) {
        fin >> first >> second >> kurs >> date;
    }
};

class Cryptokurs : public Kursvalut {
private:
    string founder;
    int year;

public:
    Cryptokurs() : founder(""), year(0) {}

    void input() override {
        Kursvalut::input();
        cout << "Введите имя основателя криптовалюты: ";
        cin >> founder;
        cout << "Введите год выпуска криптовалюты: ";
        cin >> year;
    }

    void display() const override {
        Kursvalut::display();
        cout << "Основатель: " << founder << " | Год выпуска: " << year << endl;
    }

    void saveToFile(ofstream& fout) const override {
        Kursvalut::saveToFile(fout);  
        fout << " " << founder << " " << year;  
    }

    void loadFromFile(ifstream& fin) override {
        Kursvalut::loadFromFile(fin);
        fin >> founder >> year;
    }
};

class Regularkurs : public Kursvalut {
private:
    string country;
    string unit;

public:
    Regularkurs() : country(""), unit("") {}

    void input() override {
        Kursvalut::input();
        cout << "Введите страну валюты: ";
        cin >> country;
        cout << "Введите единицу измерения: ";
        cin >> unit;
    }

    void display() const override {
        Kursvalut::display();
        cout << "Страна валюты: " << country << " | Единица измерения: " << unit << endl;
    }

    void saveToFile(ofstream& fout) const override {
        Kursvalut::saveToFile(fout);  
        fout << " " << country << " " << unit;  
    }

    void loadFromFile(ifstream& fin) override {
        Kursvalut::loadFromFile(fin);
        fin >> country >> unit;
    }
};

void menu() {
    cout << "1. Добавить запись" << endl;
    cout << "2. Вывести данные" << endl;
    cout << "3. Сохранить в файл" << endl;
    cout << "4. Загрузить из файла" << endl;
    cout << "5. Выйти" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Kursvalut*> records;
    int choice;

    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
        case 1: {
            string type;
            cout << "Введите тип валюты: ";
            cin >> type;

            if (type == "crypto") {
                Cryptokurs* crypto = new Cryptokurs();
                crypto->input();
                records.push_back(crypto);
            }
            else if (type == "regular") {
                Regularkurs* regular = new Regularkurs();
                regular->input();
                records.push_back(regular);
            }
            break;
        }
        case 2:
            for (const auto& record : records) {
                record->display();
                cout << "-------------------------" << endl;
            }
            break;
        case 3: {
            ofstream fout("out.txt");
            for (const auto& record : records) {
                record->saveToFile(fout);  
                fout << endl;  
            }
            cout << "Данные сохранены!" << endl;
            break;
        }
        case 4: {
            ifstream fin("in.txt");
            records.clear();
            string type;
            while (fin >> type) {
                Kursvalut* record = nullptr;
                if (type == "crypto") {
                    record = new Cryptokurs();
                }
                else if (type == "regular") {
                    record = new Regularkurs();
                }
                if (record) {
                    record->loadFromFile(fin);
                    records.push_back(record);
                }
            }
            cout << "Данные загружены!" << endl;
            break;
        }
        case 5:
            for (auto record : records) {
                delete record;
            }
            return 0;
        }
    }
}