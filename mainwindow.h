#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ersystem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_extractButton_clicked();
    void on_nameInput_editingFinished();
    void on_conditionInput_textChanged();
    void on_ageInput_valueChanged(int arg1);
    void on_riskInput_valueChanged(int arg1);
    void on_waitingListTable_itemSelectionChanged();
    void on_statusLabel_linkActivated(const QString &link);
    void on_conditionInput_undoAvailable(bool b);

private:
    Ui::MainWindow *ui;
    ERsystem *erSystem;

    // Helper methods
    void updateTable();
    void removePatient(int patientId);
    void changePriority(int patientId);  // Changed from increasePriority
};

#endif // MAINWINDOW_H
