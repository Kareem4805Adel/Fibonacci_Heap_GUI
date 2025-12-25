#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
