#ifndef CSESSION_H
#define CSESSION_H

#include <QString>
#include <QTime>
#include <QDate>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "cactivitytype.h"
#include "cfigstype.h"
#include "ccolorstype.h"


class CSession
{
public:
    CSession();
    CSession(CActivityType activity, int codeSession);
    CSession(int code, QString date, QTime startTime, QTime endTime, int duration, CActivityType activity);

    void stopSession();

    QString enumToString(CActivityType type);

    bool saveSession(QString child_code);

    CActivityType getActivity();
    int getCodeSession();

private:
    int codeSession;
    QString date;
    QTime startTime;
    QTime endTime;
    int duration;   ///Duration in seconds

    CActivityType activity;

};

#endif // CSESSION_H
