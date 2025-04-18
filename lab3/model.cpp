#include "model.h"
#include "filemanager.h"
#include <QDebug>

Model::Model(QObject *parent) : QObject(parent) {}

Model::~Model() {
    qDeleteAll(records);
}

void Model::addRecord(Kursvalut* record)
{
    records.append(record);
}

void Model::deleteRecord(int index) {
    delete records[index];
    records.remove(index);
}

bool Model::loadFromFile(const QString& filename) {
    try {
        std::vector<Kursvalut*> tempRecords;
        int errorCount = 0;
        if (FileManager::loadFromFile(filename, tempRecords, errorCount)) {
            qDeleteAll(records);
            records.clear();
            // Копируем только валидные записи
            for (auto* record : tempRecords) {
                records.append(record);
            }
            // Если были ошибки - отправляем сигнал
            if (errorCount > 0) {
                emit errorOccurred(QString("Загружено с %1 ошибк(ой/ами)").arg(errorCount));
            }
            return true;
        }
    } catch (const std::exception& e) {
        emit errorOccurred(e.what());
    }
    return false;
}

const QVector<Kursvalut*>& Model::getRecords() const {
    return records;
}

int Model::sum(const QVector<int>& array) {
    int sum = 0;
    for (int value : array) {
        if (value % 2 == 0) {
            sum += value;
        }
    }
    return sum;
}

