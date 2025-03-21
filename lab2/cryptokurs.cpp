#include "cryptokurs.h"
#include <QInputDialog>

Cryptokurs::Cryptokurs() : founder(""), year(0) {}

void Cryptokurs::input() {
    Kursvalut::input();
    founder = QInputDialog::getText(nullptr, "Введите имя основателя криптовалюты", "Основатель:");
    year = QInputDialog::getInt(nullptr, "Введите год выпуска криптовалюты", "Год выпуска:");
}

void Cryptokurs::display(QTableWidget* table, int row) const {
    Kursvalut::display(table, row);
    table->setItem(row, 4, new QTableWidgetItem(founder));
    table->setItem(row, 5, new QTableWidgetItem(QString::number(year)));
}

void Cryptokurs::loadFromFile(QStringList& data) {
    Kursvalut::loadFromFile(data);
    founder = data[4];
    year = data[5].toInt();
}
