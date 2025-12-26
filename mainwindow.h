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

private:
    Ui::MainWindow *ui;
    ERsystem *erSystem;

    void updateTable();
    void removePatient(int patientId);
    void changePriority(int patientId);
};

#endif
