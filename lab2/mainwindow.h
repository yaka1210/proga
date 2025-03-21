#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QVector>
#include "kursvalut.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void addRecord();
    void deleteRecord();
    void loadFromFile();
    void plusLabel();

private:
    QTableWidget* table;
    QVector<Kursvalut*> records;
    QLabel* label;
};

#endif // MAINWINDOW_H
