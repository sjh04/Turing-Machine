#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include <Qstring>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <qvector.h>
#include <vector>
#include <qmessagebox.h>

class TuringMachine
{
public:
    QString input;
    QString tape;
    QString stop_state;
    QChar state;
    QString transition;
    bool isHalt;
    int Ptr;
    std::vector<QString> functions;

    TuringMachine();

    void run();
    void loadFile(const QString &filename);
    void setData(const QString &input);
};

#endif // TURINGMACHINE_H
