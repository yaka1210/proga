#ifndef KURSVALUT_H
#define KURSVALUT_H

#include <QString>
#include <QTableWidget>

class Kursvalut {
protected:
    QString first, second, date;
    double kurs;

public:
    Kursvalut();
    virtual ~Kursvalut();

    virtual void input();
    virtual void display(QTableWidget* table, int row) const;
    virtual void loadFromFile(QStringList& data);
};

#endif // KURSVALUT_H
