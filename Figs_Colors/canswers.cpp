#include "canswers.h"

CAnswers::CAnswers()
{
    this->codeChild = "";
    this->codeSession = 0;
    this->activity = CActivityType::NONE;
    this->sActivity = "";
//    this->duration = 0;
}

CAnswers::CAnswers(QString codeChild, int codeSession, CActivityType activity)
{
    this->codeChild = codeChild;
    this->codeSession = ++codeSession;
    this->activity = activity;
    this->sActivity = enum2QString(activity);
}

bool CAnswers::saveAnswers(CFigsType input, CFigsType output, QString rightAnswer, int duration)
{
    QDir dir("ChildrenData/Child_" + codeChild + "/Answers");

    QString sInput = enum2QString(input);
    QString sOutput = enum2QString(output);

    if(!dir.exists())
    {
        dir.mkdir(".");
    }

    ///Figures Activity
    QFile file("ChildrenData/Child_" + codeChild + "/Answers/FigsAnswers.csv");

    if(!file.exists())
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ///Writes the table headers
            QTextStream write(&file);
            write << "ChildCode;CodeSession;Activity;Input;Output;Right?;Duration" << endl;
            file.close();
        }
        else
            return false;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);
        write << codeChild << ';' << codeSession << ';' << sActivity << ';'
              << sInput << ';' << sOutput << ';'  << rightAnswer << ';'  << duration << endl;
    }
    else
        return false;

    file.close();
    return true;
}

bool CAnswers::saveAnswers(CColorsType input, CColorsType output, bool rightAnswer, int duration)
{
    QDir dir("ChildrenData/Child_" + codeChild + "/Answers");

    QString sInput = enum2QString(input);
    QString sOutput = enum2QString(output);

    if(!dir.exists())
    {
        dir.mkdir(".");
    }

    ///Colors Activity
    QFile file("ChildrenData/Child_" + codeChild + "/Answers/ColorsAnswers.csv");

    if(!file.exists())
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ///Writes the table headers
            QTextStream write(&file);
            write << "ChildCode;CodeSession;Activity;Input;Output;Right?;Duration" << endl;
            file.close();
        }
        else
            return false;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);
        write << codeChild << ';' << codeSession << ';' << sActivity << ';'
              << sInput << ';' << sOutput << ';'  << rightAnswer << ';'  << duration << endl;
    }
    else
        return false;

    file.close();
    return true;
}

bool CAnswers::saveAnswers(QVector<CFigsType> answer, int duration)
{
    /// answer[0]_figBoard - INPUT
    /// answer[1]_figPlaced - OUTPUT

    QDir dir("ChildrenData/Child_" + codeChild + "/Answers");

    QString sInput = enum2QString(answer[0]);
    QString sOutput = enum2QString(answer[1]);
    QString sRight;

    if(answer[0] == answer[1])
        sRight = "Right";
    else
        sRight = "Wrong";

    if(!dir.exists())
    {
        dir.mkdir(".");
    }

    ///Figures Activity
    QFile file("ChildrenData/Child_" + codeChild + "/Answers/" + sActivity + "_Answers.csv");

    if(!file.exists())
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ///Writes the table headers
            QTextStream write(&file);
            write << "ChildCode;CodeSession;Activity;Input;Output;Right?;Duration" << endl;
            file.close();
        }
        else
            return false;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);
        write << codeChild << ';' << codeSession << ';' << sActivity << ';'
              << sInput << ';' << sOutput << ';'  << sRight << ';'  << duration << endl;
    }
    else
        return false;

    file.close();
    return true;
}

bool CAnswers::saveAnswers(QVector<CColorsType> answer,  int duration)
{
    /// answer[0]_colorBoard - INPUT
    /// answer[1]_colorPlaced - OUTPUT

    QDir dir("ChildrenData/Child_" + codeChild + "/Answers");

    QString sInput = enum2QString(answer[0]);
    QString sOutput = enum2QString(answer[1]);
    QString sRight;

    if(answer[0] == answer[1])
        sRight = "Right";
    else
        sRight = "Wrong";

    if(!dir.exists())
    {
        dir.mkdir(".");
    }

    ///Colors Activity
    QFile file("ChildrenData/Child_" + codeChild + "/Answers/" + sActivity + "_Answers.csv");

    if(!file.exists())
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ///Writes the table headers
            QTextStream write(&file);
            write << "ChildCode;CodeSession;Activity;Input;Output;Right?;Duration" << endl;
            file.close();
        }
        else
            return false;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);
        write << codeChild << ';' << codeSession << ';' << sActivity << ';'
              << sInput << ';' << sOutput << ';'  << sRight << ';'  << duration << endl;
    }
    else
        return false;

    file.close();
    return true;
}

QString CAnswers::enum2QString(CActivityType activity)
{
    switch(activity)
    {
    case CActivityType::F1:
        return "F1";
        break;

    case CActivityType::F2:
        return "F2";
        break;

    case CActivityType::C1:
        return "C1";
        break;

    case CActivityType::C2:
        return "C2";
        break;

    default:
        return "";
        break;
    }
}

QString CAnswers::enum2QString(CFigsType figType)
{
    switch(figType)
    {
    case CFigsType::SQUARE:
        return "SQUARE";
        break;

    case CFigsType::TRIANGLE:
        return "TRIANGLE";
        break;

    case CFigsType::CIRCLE:
        return "CIRCLE";
        break;

    case CFigsType::RECTANGLE:
        return "RECTANGLE";
        break;

    case CFigsType::PENTAGON:
        return "PENTAGON";
        break;

    default:
        return "";
        break;
    }
}

QString CAnswers::enum2QString(CColorsType colorType)
{
    switch (colorType)
    {
    case CColorsType::BLUE:
        return "BLUE";
        break;

    case CColorsType::RED:
        return "RED";
        break;

    case CColorsType::GREEN:
        return "GREEN";
        break;

    case CColorsType::BLACK:
        return "BLACK";
        break;

    case CColorsType::YELLOW:
        return "YELLOW";
        break;

    default:
        return "";
        break;
    }
}






























