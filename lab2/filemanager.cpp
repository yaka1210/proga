#include <QFile>
#include <QRegularExpression>
#include "fileManager.h"
#include "cryptokurs.h"
#include "regularkurs.h"

bool FileManager::loadFromFile(const QString& filename, std::vector<Kursvalut*>& records) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    records.clear();
    QRegularExpression regex("\\s+"); // Разделяем по пробелам

    while (!in.atEnd()) {
        QStringList data = in.readLine().trimmed().split(regex);
        QString currencyType = data.takeFirst();
        Kursvalut* record = (currencyType == "crypto") ? static_cast<Kursvalut*>(new Cryptokurs()) : static_cast<Kursvalut*>(new Regularkurs());
        record->loadFromFile(data);
        records.push_back(record);
    }
    return true;
}
