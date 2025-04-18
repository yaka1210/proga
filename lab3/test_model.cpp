#include "test_model.h"

void TestModel::init()
{
    m_model = new Model();
}

void TestModel::cleanup()
{
    delete m_model;
    m_model = nullptr;
}

void TestModel::testAddRecord()
{
    // Тест добавления криптовалюты
    Cryptokurs* crypto = new Cryptokurs();
    m_model->addRecord(crypto);
    QCOMPARE(m_model->getRecords().size(), 1);
    // Тест добавления обычной валюты
    Regularkurs* regular = new Regularkurs();
    m_model->addRecord(regular);
    QCOMPARE(m_model->getRecords().size(), 2);
}

void TestModel::testDeleteRecord()
{
    // Подготовка тестовых данных
    m_model->addRecord(new Cryptokurs());
    m_model->addRecord(new Regularkurs());
    const int initialCount = m_model->getRecords().size();
    // Удаление первой записи
    m_model->deleteRecord(0);
    QCOMPARE(m_model->getRecords().size(), initialCount - 1);
}

void TestModel::testLoadValidData()
{
    QSignalSpy spy(m_model, &Model::errorOccurred);
    // Создаем временный тестовый файл
    QTemporaryFile tempFile;
    if (tempFile.open()) {
        QTextStream out(&tempFile);
        out << "crypto USD BTC 1.0 2023.01.01 Satoshi 2008\n";
        out << "regular USD RUB 75.5 2023.01.01 Russia 1\n";
        tempFile.close();
        // Тестируем загрузку
        QVERIFY(m_model->loadFromFile(tempFile.fileName()));
        QCOMPARE(m_model->getRecords().size(), 2);
        QCOMPARE(spy.count(), 0); // Нет ошибок
    }
}

void TestModel::testLoadInvalidData() {
    QSignalSpy spy(m_model, &Model::errorOccurred);
    QTemporaryFile tempFile;
    if (tempFile.open()) {
        QTextStream out(&tempFile);
        out << "ggg USD BTC 1.0 2023.01.01 Satoshi 2008\n"; // Неверный тип
        out << "crypto USD BTC 1.0 2023.01.01 Satoshi\n";   // Недостаточно данных для криптовалюты
        out << "regular USD RUB 75.5 2023.01.01 Russia\n";  // Недостаточно данных для обычной валюты
        tempFile.close();
        // Тестируем загрузку
        QVERIFY(m_model->loadFromFile(tempFile.fileName()));
        QCOMPARE(m_model->getRecords().size(), 0); // Ничего не загружено
        QCOMPARE(spy.count(), 1); // Один общий сигнал об ошибках
        QCOMPARE(spy.first().first().toString(), "Загружено с 3 ошибк(ой/ами)");
    }
}

void TestModel::testSum()
{
    QVector<int> a = {1, 2, 3, 4, 5, 6};
    int result = m_model->sum(a);
    QCOMPARE(result, 12);

    QVector<int> b = {1, 3, 5, 7};
    result = m_model->sum(b);
    QCOMPARE(result, 0);

    QVector<int> c;
    result = m_model->sum(c);
    QCOMPARE(result, 0);
}

QTEST_APPLESS_MAIN(TestModel)
