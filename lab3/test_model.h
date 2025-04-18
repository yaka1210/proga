#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include <QtTest>
#include <QSignalSpy>
#include "model.h"
#include "cryptokurs.h"
#include "regularkurs.h"

class TestModel : public QObject
{
    Q_OBJECT

public:
    TestModel() = default;
    ~TestModel() = default;

private slots:
    void init();           // Инициализация перед каждым тестом
    void cleanup();        // Очистка после каждого теста
    void testAddRecord();
    void testDeleteRecord();
    void testLoadValidData();
    void testLoadInvalidData();
    void testSum();

private:
    Model* m_model;
};

#endif // TEST_MODEL_H