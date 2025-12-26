#include "mainwindow.h"
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include "./ui_mainwindow.h"
#include "ersystem.h"
#include "patient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    erSystem = new ERsystem();

    ui->waitingListTable->setColumnCount(5);
    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Risk" << "Action";
    ui->waitingListTable->setHorizontalHeaderLabels(headers);

    ui->waitingListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->waitingListTable->setColumnWidth(0, 50);
    ui->waitingListTable->setColumnWidth(1, 200);
    ui->waitingListTable->setColumnWidth(2, 80);
    ui->waitingListTable->setColumnWidth(3, 80);
    ui->waitingListTable->setColumnWidth(4, 150);

    ui->statusLabel->setText("Ready - No patients in queue");
}

MainWindow::~MainWindow()
{
    delete erSystem;
    delete ui;
}

void MainWindow::updateTable()
{
    // Clear the table
    ui->waitingListTable->setRowCount(0);

    // Get all patients and display them
    int rowCount = 0;
    for (int i = 1; i < patient::id; i++) {
        patient *p = patient::getPatient(i);
        if (p != nullptr && patient::arrPN[i - 1] != nullptr) {

            ui->waitingListTable->insertRow(rowCount);


            QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(i));
            ui->waitingListTable->setItem(rowCount, 0, idItem);

            QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(p->getName()));
            ui->waitingListTable->setItem(rowCount, 1, nameItem);

            QTableWidgetItem *ageItem = new QTableWidgetItem(QString::number(p->getAge()));
            ui->waitingListTable->setItem(rowCount, 2, ageItem);

            QTableWidgetItem *riskItem = new QTableWidgetItem(QString::number(p->GetPriotiry()));
            ui->waitingListTable->setItem(rowCount, 3, riskItem);

            QPushButton *removeBtn = new QPushButton("Remove");
            QPushButton *changePriorityBtn = new QPushButton("Set Priority");

            QWidget *buttonWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
            layout->addWidget(changePriorityBtn);
            layout->addWidget(removeBtn);
            layout->setContentsMargins(2, 2, 2, 2);
            buttonWidget->setLayout(layout);

            ui->waitingListTable->setCellWidget(rowCount, 4, buttonWidget);

            connect(removeBtn, &QPushButton::clicked, this, [this, i]() { removePatient(i); });

            connect(changePriorityBtn, &QPushButton::clicked, this, [this, i]() {
                changePriority(i);
            });

            rowCount++;
        }
    }

    if (rowCount == 0) {
        ui->statusLabel->setText("Ready - No patients in queue");
    } else {
        node *nextPatient = erSystem->getHighestPriority();
        if (nextPatient != nullptr) {
            ui->statusLabel->setText(QString("Patients in queue: %1 | Next: %2 (Priority: %3)")
                                         .arg(rowCount)
                                         .arg(QString::fromStdString(nextPatient->Taskname))
                                         .arg(nextPatient->key));
        } else {
            ui->statusLabel->setText(QString("Patients in queue: %1").arg(rowCount));
        }
    }
}

void MainWindow::on_addButton_clicked()
{
    QString name = ui->nameInput->text().trimmed();
    int age = ui->ageInput->value();
    QString condition = ui->conditionInput->toPlainText().trimmed();
    int risk = ui->riskInput->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter patient name.");
        return;
    }

    if (condition.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter medical condition.");
        return;
    }

    patient *newPatient = new patient(name.toStdString(), age, risk);

    erSystem->AddToList(*newPatient);

    updateTable();

    ui->nameInput->clear();
    ui->conditionInput->clear();
    ui->ageInput->setValue(30);
    ui->riskInput->setValue(5);

    QMessageBox::information(this,
                             "Success",
                             QString("Patient '%1' added to waiting list with priority %2.")
                                 .arg(name)
                                 .arg(risk));

    ui->nameInput->setFocus();
}

void MainWindow::on_extractButton_clicked()
{
    node *extracted = erSystem->AcceptPatiant();

    if (extracted == nullptr) {
        QMessageBox::information(this, "Queue Empty", "No patients in waiting list.");
        return;
    }

    for (int i = 1; i < patient::id; i++) {
        if (patient::arrPN[i - 1] == extracted) {
            patient::arrPN[i - 1] = nullptr;
            break;
        }
    }

    QMessageBox::information(this,
                             "Patient Accepted",
                             QString("Now treating: %1\nPriority: %2")
                                 .arg(QString::fromStdString(extracted->Taskname))
                                 .arg(extracted->key));

    updateTable();
}

void MainWindow::removePatient(int patientId)
{
    patient *p = patient::getPatient(patientId);
    if (p == nullptr) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Confirm Removal",
                                  QString("Remove patient '%1' from waiting list?")
                                      .arg(QString::fromStdString(p->getName())),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        erSystem->RemoveFromList(*p);
        patient::arrPN[patientId - 1] = nullptr;
        updateTable();
        ui->statusLabel->setText(
            QString("Patient '%1' removed from queue.").arg(QString::fromStdString(p->getName())));
    }
}

void MainWindow::changePriority(int patientId)
{
    patient *p = patient::getPatient(patientId);
    if (p == nullptr) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    int currentPriority = p->GetPriotiry();

    bool ok;
    int newPriority = QInputDialog::getInt(
        this,
        "Change Priority",
        QString("Enter new priority for '%1'\n(1 = Critical, 10 = Minor)\nCurrent priority: %2")
            .arg(QString::fromStdString(p->getName()))
            .arg(currentPriority),
        currentPriority,
        1,
        10,
        1,
        &ok);

    if (!ok)
        return;

    if (newPriority > currentPriority) {
        QMessageBox::warning(this,
                             "Invalid Priority Change",
                             "You can only increase priority by entering a LOWER number.\n"
                             "Higher numbers mean lower priority.");
        return;
    }

    if (newPriority == currentPriority) {
        QMessageBox::information(this, "No Change", "Priority remains the same.");
        return;
    }

    erSystem->IncreasePriority(*p, newPriority);
    p->SetPriority(newPriority);

    updateTable();

    ui->statusLabel->setText(QString("Priority changed for '%1': %2 → %3")
                                 .arg(QString::fromStdString(p->getName()))
                                 .arg(currentPriority)
                                 .arg(newPriority));
}
