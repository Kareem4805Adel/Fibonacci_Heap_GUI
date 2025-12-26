#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ersystem.h"
#include "patient.h"
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the ER system
    erSystem = new ERsystem();

    // Setup table headers
    ui->waitingListTable->setColumnCount(5);
    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Risk" << "Action";
    ui->waitingListTable->setHorizontalHeaderLabels(headers);

    // Make table read-only except for action buttons
    ui->waitingListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set column widths
    ui->waitingListTable->setColumnWidth(0, 50);
    ui->waitingListTable->setColumnWidth(1, 200);
    ui->waitingListTable->setColumnWidth(2, 80);
    ui->waitingListTable->setColumnWidth(3, 80);
    ui->waitingListTable->setColumnWidth(4, 150);

    // Initial status
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
        patient* p = patient::getPatient(i);
        if (p != nullptr && patient::arrPN[i-1] != nullptr) {
            // This patient is still in the waiting list
            ui->waitingListTable->insertRow(rowCount);

            // ID
            QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(i));
            ui->waitingListTable->setItem(rowCount, 0, idItem);

            // Name
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(p->getName()));
            ui->waitingListTable->setItem(rowCount, 1, nameItem);

            // Age
            QTableWidgetItem* ageItem = new QTableWidgetItem(QString::number(p->getAge()));
            ui->waitingListTable->setItem(rowCount, 2, ageItem);

            // Risk (Priority)
            QTableWidgetItem* riskItem = new QTableWidgetItem(QString::number(p->GetPriotiry()));
            ui->waitingListTable->setItem(rowCount, 3, riskItem);

            // Action buttons
            QPushButton* removeBtn = new QPushButton("Remove");
            QPushButton* changePriorityBtn = new QPushButton("Set Priority");

            QWidget* buttonWidget = new QWidget();
            QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
            layout->addWidget(changePriorityBtn);
            layout->addWidget(removeBtn);
            layout->setContentsMargins(2, 2, 2, 2);
            buttonWidget->setLayout(layout);

            ui->waitingListTable->setCellWidget(rowCount, 4, buttonWidget);

            // Connect buttons with patient ID
            connect(removeBtn, &QPushButton::clicked, this, [this, i]() {
                removePatient(i);
            });

            connect(changePriorityBtn, &QPushButton::clicked, this, [this, i]() {
                changePriority(i);
            });

            rowCount++;
        }
    }

    // Update status
    if (rowCount == 0) {
        ui->statusLabel->setText("Ready - No patients in queue");
    } else {
        node* nextPatient = erSystem->getHighestPriority();
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
    // Get input values
    QString name = ui->nameInput->text().trimmed();
    int age = ui->ageInput->value();
    QString condition = ui->conditionInput->toPlainText().trimmed();
    int risk = ui->riskInput->value();

    // Validate inputs
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter patient name.");
        return;
    }

    if (condition.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter medical condition.");
        return;
    }

    // Create new patient
    patient* newPatient = new patient(
        name.toStdString(),
        age,
        risk
        );

    // Add to ER system
    erSystem->AddToList(*newPatient);

    // Update table
    updateTable();

    // Clear inputs
    ui->nameInput->clear();
    ui->conditionInput->clear();
    ui->ageInput->setValue(30);
    ui->riskInput->setValue(5);

    // Show success message
    QMessageBox::information(this, "Success",
                             QString("Patient '%1' added to waiting list with priority %2.")
                                 .arg(name)
                                 .arg(risk));

    ui->nameInput->setFocus();
}

void MainWindow::on_extractButton_clicked()
{
    node* extracted = erSystem->AcceptPatiant();

    if (extracted == nullptr) {
        QMessageBox::information(this, "Queue Empty", "No patients in waiting list.");
        return;
    }

    // Find and mark this patient as extracted (set their arrPN to nullptr)
    for (int i = 1; i < patient::id; i++) {
        if (patient::arrPN[i-1] == extracted) {
            patient::arrPN[i-1] = nullptr;
            break;
        }
    }

    // Show message
    QMessageBox::information(this, "Patient Accepted",
                             QString("Now treating: %1\nPriority: %2")
                                 .arg(QString::fromStdString(extracted->Taskname))
                                 .arg(extracted->key));

    // Update table
    updateTable();
}

void MainWindow::removePatient(int patientId)
{
    patient* p = patient::getPatient(patientId);
    if (p == nullptr) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Removal",
                                  QString("Remove patient '%1' from waiting list?")
                                      .arg(QString::fromStdString(p->getName())),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        erSystem->RemoveFromList(*p);
        patient::arrPN[patientId - 1] = nullptr; // Mark as removed
        updateTable();
        ui->statusLabel->setText(QString("Patient '%1' removed from queue.")
                                     .arg(QString::fromStdString(p->getName())));
    }
}

void MainWindow::changePriority(int patientId)
{
    patient* p = patient::getPatient(patientId);
    if (p == nullptr) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    int currentPriority = p->GetPriotiry();

    // Show input dialog to get new priority
    bool ok;
    int newPriority = QInputDialog::getInt(this,
                                           "Change Priority",
                                           QString("Enter new priority for '%1'\n(1=Critical, 10=Minor)\nCurrent priority: %2")
                                               .arg(QString::fromStdString(p->getName()))
                                               .arg(currentPriority),
                                           currentPriority,  // default value
                                           1,                // minimum
                                           10,               // maximum
                                           1,                // step
                                           &ok);

    if (ok) {
        if (newPriority == currentPriority) {
            QMessageBox::information(this, "No Change",
                                     "Priority remains the same.");
            return;
        }

        // Update priority in the system
        erSystem->IncreasePriority(*p, newPriority);
        p->SetPriority(newPriority);

        updateTable();

        ui->statusLabel->setText(QString("Priority changed for '%1': %2 → %3")
                                     .arg(QString::fromStdString(p->getName()))
                                     .arg(currentPriority)
                                     .arg(newPriority));
    }
}

void MainWindow::on_nameInput_editingFinished()
{
    // Optional: Could add validation here
}

void MainWindow::on_conditionInput_textChanged()
{
    // Optional: Could add character count or validation here
}

void MainWindow::on_ageInput_valueChanged(int arg1)
{
    // Optional: Could add age-based priority suggestions
}

void MainWindow::on_riskInput_valueChanged(int arg1)
{
    // Optional: Could show risk level description
}

void MainWindow::on_waitingListTable_itemSelectionChanged()
{
    // Optional: Could show patient details when selected
}

void MainWindow::on_statusLabel_linkActivated(const QString &link)
{
    // Not used currently
}

void MainWindow::on_conditionInput_undoAvailable(bool b)
{
    // Optional: Handle undo availability
}
