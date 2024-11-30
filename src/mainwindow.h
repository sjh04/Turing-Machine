#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QFileDialog>
#include "turingmachine.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void reset();

private slots:
    void on_open_flie_clicked();

    void on_start_clicked();

    void on_step_clicked();

private:
    QString fileName;
    Ui::MainWindow *ui;
    TuringMachine Myturing;
};
#endif // MAINWINDOW_H
