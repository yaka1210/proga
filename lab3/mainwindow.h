#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include "model.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addRecord();
    void deleteRecord();
    void loadFromFile();
    void plusLabel();
    void onError(const QString& message);

private:
    void updateTable();

    QTableWidget* table;
    Model* model;
    QLabel* label;
};

#endif // MAINWINDOW_H
