#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include "kursvalut.h"

class Model : public QObject {
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    ~Model();

    void addRecord(Kursvalut* record);
    void deleteRecord(int index);
    bool loadFromFile(const QString& filename);
    const QVector<Kursvalut*>& getRecords() const;
    int sum(const QVector<int>& array);

signals:
    void errorOccurred(const QString& message);

private:
    QVector<Kursvalut*> records;
};

#endif // MODEL_H
