#ifndef CANSWERS_H
#define CANSWERS_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QVector>

#include "cactivitytype.h"
#include "cfigstype.h"
#include "ccolorstype.h"

class CAnswers
{
public:
    CAnswers();
    CAnswers(QString codeChild, int codeSession, CActivityType activity);

    bool saveAnswers(CFigsType input, CFigsType output, QString rightAnswer, int duration);
    bool saveAnswers(CColorsType input, CColorsType output, bool rightAnswer, int duration);

    ///NEW FUNCTIONS
    bool saveAnswers(QVector<CFigsType> answer, int duration);
    bool saveAnswers(QVector<CColorsType> answer, int duration);

    QString enum2QString(CActivityType activity);
    QString enum2QString(CFigsType figType);
    QString enum2QString(CColorsType colorType);


private:
    QString codeChild;
    int codeSession;
    CActivityType activity;
    QString sActivity;

//    bool rightAnswer;
    //int duration;
};

#endif // CANSWERS_H
