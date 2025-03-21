#include "regularkurs.h"
#include <QInputDialog>

Regularkurs::Regularkurs() : country(""), unit("") {}

void Regularkurs::input() {
    Kursvalut::input();
    country = QInputDialog::getText(nullptr, "Введите страну валюты", "Страна:");
    unit = QInputDialog::getText(nullptr, "Введите единицу измерения", "Единица измерения:");
}

void Regularkurs::display(QTableWidget* table, int row) const {
    Kursvalut::display(table, row);
    table->setItem(row, 4, new QTableWidgetItem(country));
    table->setItem(row, 5, new QTableWidgetItem(unit));
}

void Regularkurs::loadFromFile(QStringList& data) {
    Kursvalut::loadFromFile(data);
    country = data[4];
    unit = data[5];
}
