#ifndef CRYPTOKURS_H
#define CRYPTOKURS_H

#include "kursvalut.h"

class Cryptokurs : public Kursvalut {
private:
    QString founder;
    int year;

public:
    Cryptokurs();

    void input() override;
    void display(QTableWidget* table, int row) const override;
    void loadFromFile(QStringList& data) override;
};

#endif // CRYPTOKURS_H
