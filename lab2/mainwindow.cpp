#include "MainWindow.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include "fileManager.h"
#include "cryptokurs.h"
#include "regularkurs.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), table(new QTableWidget(this)) {
    setWindowTitle("Управление курсами валют");
    setGeometry(100, 100, 800, 600);

    // Настройка таблицы
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"Первая валюта", "Вторая валюта", "Курс", "Дата", "Основатель/Страна", "Год/Единица"});
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setGeometry(10, 10, 780, 400);

    // Кнопки для управления записями
    QPushButton* addButton = new QPushButton("Добавить запись", this);
    QPushButton* deleteButton = new QPushButton("Удалить запись", this);
    QPushButton* loadButton = new QPushButton("Загрузить из файла", this);
    QPushButton* pushButton = new QPushButton("Прибавить 1", this);

    addButton->setGeometry(10, 420, 180, 40);
    deleteButton->setGeometry(200, 420, 180, 40);
    loadButton->setGeometry(390, 420, 180, 40);
    pushButton->setGeometry(600, 420, 180, 40);

    // QLabel для отображения числа
    label = new QLabel("0", this);  // Изначальное значение 0
    label->setGeometry(700, 470, 80, 30);  // Позиционирование на форме
    label->setAlignment(Qt::AlignCenter);  // Центрирование текста

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::plusLabel);  // Подключение кнопки
}

void MainWindow::addRecord() {
    QString type = QInputDialog::getItem(this, "Выберите тип валюты", "Тип валюты:", {"crypto", "regular"});
    Kursvalut* kursvalut = nullptr;
    if (type == "crypto") {
        kursvalut = new Cryptokurs();
    } else if (type == "regular") {
        kursvalut = new Regularkurs();
    }

    if (kursvalut) {
        kursvalut->input();
        records.push_back(kursvalut);
        int row = table->rowCount();
        table->insertRow(row);
        kursvalut->display(table, row);
    }
}

void MainWindow::deleteRecord() {
    int row = table->currentRow();
    if (row >= 0 && row < static_cast<int>(records.size())) {
        delete records[row];  // Освобождаем память
        records.erase(records.begin() + row);  // Удаляем из вектора
        table->removeRow(row);  // Удаляем строку из таблицы
    }
}

void MainWindow::loadFromFile() {
    std::vector<Kursvalut*> tempRecords(records.begin(), records.end());
    if (FileManager::loadFromFile("in.txt", tempRecords)) {
        records = QVector<Kursvalut*>(tempRecords.begin(), tempRecords.end());
        table->setRowCount(0);
        for (int i = 0; i < records.size(); ++i) {
            int row = table->rowCount();
            table->insertRow(row);
            records[i]->display(table, row);
        }
    }
}

void MainWindow::plusLabel() {
    int currentValue = label->text().toInt();
    currentValue++;
    label->setText(QString::number(currentValue));
}
