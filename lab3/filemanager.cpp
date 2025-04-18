#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QRegularExpression>
#include <stdexcept>
#include "filemanager.h"
#include "cryptokurs.h"
#include "regularkurs.h"

bool FileManager::loadFromFile(const QString& filename, std::vector<Kursvalut*>& records, int& errorCount) {
    errorCount = 0;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл");
    }
    QTextStream in(&file);
    records.clear();
    QRegularExpression regex("\\s+");
    int lineNumber = 0;
    bool hasErrors = false;
    while (!in.atEnd()) {
        lineNumber++;
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        try {
            QStringList data = line.split(regex);
            QString currencyType = data.takeFirst();
            Kursvalut* record = nullptr;

            if (currencyType == "crypto") {
                if (data.size() < 6) throw std::runtime_error("Недостаточно данных для криптовалюты");
                record = new Cryptokurs();
            }
            else if (currencyType == "regular") {
                if (data.size() < 6) throw std::runtime_error("Недостаточно данных для обычной валюты");
                record = new Regularkurs();
            }
            else {
                throw std::runtime_error("Неизвестный тип валюты");
            }

            record->loadFromFile(data);
            records.push_back(record);
        }
        catch (const std::exception& e) {
            errorCount++; // Увеличиваем счетчик ошибок
            hasErrors = true;
            qWarning() << "Ошибка в строке" << lineNumber << ":" << e.what();
            continue;
        }
    }
    if (hasErrors) {
        qWarning() << "Загрузка завершена с ошибками. Некоторые строки были пропущены.";
    }
    return true;
}
