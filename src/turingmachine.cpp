#include "turingmachine.h"

TuringMachine::TuringMachine()
{
    state = '0';
    Ptr = 1;
    tape = "B";
    isHalt = false;
}

void TuringMachine::run()
{
    bool transitionFound = false;
    for (const QString &function : functions)
    {
        if (function[0] == state && function[1] == tape[Ptr])
        {
            state = function[2];
            tape[Ptr] = function[3];
            if (function[4] == 'R')
            {
                Ptr++;
                if (Ptr >= tape.size())
                {
                    tape += 'B';
                }
            }
            else if (function[4] == 'L')
            {
                Ptr--;
                if (Ptr < 0)
                {
                    tape = 'B' + tape;
                    Ptr = 0;
                }
            }
            transitionFound = true;
            transition = function;
            break;
        }
    }
    if (state == stop_state)
    {
        qDebug() << "停机状态：" << state;
        isHalt = true;
    }
    if (!transitionFound)
    {
        QMessageBox::warning(nullptr, "错误", "没有找到匹配的状态转移。");
        qWarning() << "没有找到匹配的状态转移。";
    }
}

void TuringMachine::loadFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "无法打开文件:" << filename;
        return;
    }
    functions.clear();
    QTextStream in(&file);
    input = in.readLine();
    qDebug() << "input:" << input;
    stop_state = in.readLine();
    qDebug() << "stop_state:" << stop_state;
    while (!in.atEnd())
    {
        functions.push_back(in.readLine());
    }
    file.close();
}

void TuringMachine::setData(const QString &input)
{
    this->input = input;
    tape = "B" + input + "B";
    Ptr = 1; // 指向输入带子的第一个字符
    state = '0';
}
