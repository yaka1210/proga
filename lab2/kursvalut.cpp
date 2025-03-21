#include "kursvalut.h"
#include <QInputDialog>

Kursvalut::Kursvalut() : first(""), second(""), kurs(0.0), date("") {}

Kursvalut::~Kursvalut() {}

void Kursvalut::input() {
    first = QInputDialog::getText(nullptr, "Введите первую валюту", "Первая валюта:");
    second = QInputDialog::getText(nullptr, "Введите вторую валюту", "Вторая валюта:");
    kurs = QInputDialog::getDouble(nullptr, "Введите курс", "Курс:");
    date = QInputDialog::getText(nullptr, "Введите дату", "Дата (гггг.мм.дд):");
}

void Kursvalut::display(QTableWidget* table, int row) const {
    table->setItem(row, 0, new QTableWidgetItem(first));
    table->setItem(row, 1, new QTableWidgetItem(second));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(kurs)));
    table->setItem(row, 3, new QTableWidgetItem(date));
}

void Kursvalut::loadFromFile(QStringList& data) {
    first = data[0];
    second = data[1];
    kurs = data[2].toDouble();
    date = data[3];
}
