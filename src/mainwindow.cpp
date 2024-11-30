#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_flie_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("打开状态转移文件"), "", tr("Text Files (*.txt);;All Files (*)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "打开文件失败:" << fileName;
        return;
    }
    Myturing = TuringMachine();
    ui->function->clear();
    Myturing.loadFile(fileName);
    ui->tape->setPlainText(Myturing.tape);
    ui->state->setPlainText(QString(Myturing.state));
    ui->pos->setPlainText(QString::number(Myturing.Ptr - 1));
    ui->stop_sign->setPlainText(Myturing.stop_state);
    file.close();

}

void MainWindow::reset()
{
    if (Myturing.isHalt)
    {
        Myturing = TuringMachine();
        Myturing.loadFile(fileName);
        ui->tape->setPlainText(Myturing.tape);
    }
}

void MainWindow::on_start_clicked()
{
    reset();
    ui->function->clear();
    Myturing.setData(Myturing.input);
    ui->tape->setPlainText(Myturing.tape);
}

void MainWindow::on_step_clicked()
{
    Myturing.run();
    ui->tape->setPlainText(Myturing.tape);
    ui->state->setPlainText(QString(Myturing.state));
    ui->pos->setPlainText(QString::number(Myturing.Ptr - 1));
    ui->function->append(Myturing.transition);
    if (Myturing.isHalt)
    {
        qDebug() << "finished";
        ui->state->setPlainText("finished");
        QMessageBox::information(this, "information", "success");
    }
}
