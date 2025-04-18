#include "mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include "cryptokurs.h"
#include "regularkurs.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
    table(new QTableWidget(this)),
    model(new Model(this)) {

    setWindowTitle("Управление курсами валют");
    setGeometry(100, 100, 800, 600);

    // Настройка таблицы
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"Первая валюта", "Вторая валюта", "Курс", "Дата", "Основатель/Страна", "Год/Единица"});
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setGeometry(10, 10, 780, 400);

    // Кнопки
    QPushButton* addButton = new QPushButton("Добавить запись", this);
    QPushButton* deleteButton = new QPushButton("Удалить запись", this);
    QPushButton* loadButton = new QPushButton("Загрузить из файла", this);
    QPushButton* pushButton = new QPushButton("Прибавить 1", this);

    addButton->setGeometry(10, 420, 180, 40);
    deleteButton->setGeometry(200, 420, 180, 40);
    loadButton->setGeometry(390, 420, 180, 40);
    pushButton->setGeometry(600, 420, 180, 40);

    label = new QLabel("0", this);
    label->setGeometry(700, 470, 80, 30);
    label->setAlignment(Qt::AlignCenter);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::plusLabel);
    connect(model, &Model::errorOccurred, this, &MainWindow::onError);
}

MainWindow::~MainWindow() {
    delete model;
}

void MainWindow::addRecord() {
    bool ok = false;
    QStringList types = {"crypto", "regular"};
    QString type = QInputDialog::getItem(this, "Выберите тип валюты", "Тип валюты:", types, 0, false, &ok);
    if (!ok) return;
    Kursvalut* kursvalut = nullptr;
    if (type == "crypto") {
        kursvalut = new Cryptokurs();
    } else if (type == "regular") {
        kursvalut = new Regularkurs();
    }
    if (kursvalut) {
        kursvalut->input();
        model->addRecord(kursvalut);
        updateTable();
    }
}

void MainWindow::deleteRecord() {
    int row = table->currentRow();
    if (row >= 0) {
        model->deleteRecord(row);
        updateTable();
    }
}

void MainWindow::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл для загрузки", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        model->loadFromFile(fileName);
        updateTable();
    }
}

void MainWindow::plusLabel() {
    int currentValue = label->text().toInt();
    currentValue++;
    label->setText(QString::number(currentValue));
}

void MainWindow::updateTable() {
    table->setRowCount(0);
    const auto& records = model->getRecords();
    for (int i = 0; i < records.size(); ++i) {
        int row = table->rowCount();
        table->insertRow(row);
        records[i]->display(table, row);
    }
}

void MainWindow::onError(const QString& message) {
    QMessageBox::warning(this, "Ошибка", message);
}
