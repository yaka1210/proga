#ifndef REGULARKURS_H
#define REGULARKURS_H

#include "kursvalut.h"

class Regularkurs : public Kursvalut {
private:
    QString country;
    QString unit;

public:
    Regularkurs();

    void input() override;
    void display(QTableWidget* table, int row) const override;
    void loadFromFile(QStringList& data) override;
};

#endif // REGULARKURS_H
