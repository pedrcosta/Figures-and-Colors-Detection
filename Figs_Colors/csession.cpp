#include "csession.h"

CSession::CSession()
{
    this->codeSession = 0;
    this->date = "";
//    this->startTime = new QTime();
//    this->endTime = new QTime();
    this->duration = 0;
    //    this->activity = NULL;
}


CSession::CSession(CActivityType activity, int codeSession)
{
//    this->codeSession = codeSession + 1;
    this->codeSession = ++codeSession;
    this->duration = 0;
    this->activity = activity;
    this->date = QDate::currentDate().toString("dd/MM/yyyy");
    this->startTime = QTime::currentTime();
}

CSession::CSession(int code, QString date, QTime startTime, QTime endTime, int duration, CActivityType activity)
{
    this->codeSession = code;
    this->date = date;
    this->startTime = startTime;
    this->endTime = endTime;
    this->duration = duration;
    this->activity = activity;
}

void CSession::stopSession()
{
    this->endTime = QTime::currentTime();
    this->duration = startTime.msecsTo(endTime)/1000;
}

QString CSession::enumToString(CActivityType type)
{
    switch(type)
    {
    case CActivityType::C1:
        return "C1";
        break;

    case CActivityType::C2:
        return "C2";
        break;

    case CActivityType::F1:
        return "F1";
        break;

    case CActivityType::F2:
        return "F2";
        break;

    default:
        return "";
        break;

    }
}

/**************************************************************
  GO TO FOLDER SESSIONS OF FOLDER'S CHILD
                                                            AND SAVE SESSION INFORMATION
                                        Informations in the file:
                      Code;Date;StartTime;EndTime;Duration;Activity
**************************************************************/
bool CSession::saveSession(QString childCode)
{
    QDir dir("ChildrenData/Child_" + childCode + "/Sessions");

    if(!dir.exists())  //If directory doesn't exist creat the folder
    {
        dir.mkdir(".");
    }

    QFile file("ChildrenData/Child_" + childCode + "/Sessions/Sessions.csv");

    if(!file.exists()) //First time the file is created, print the headers
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream write(&file);
            write << "Code;Date;StartTime;EndTime;Duration;Activity" << endl;
        }
        file.close();
    }

    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);

        write << codeSession << ';' << date << ';'
               << startTime.toString("hh:mm") << ';'
               << endTime.toString("hh:mm") << ';'
               << duration << ';'
               << enumToString(activity) << endl;
    }
    else
        return false;

    file.close();
    return true;
}

CActivityType CSession::getActivity()
{
    return activity;
}

int CSession::getCodeSession()
{
    return this->codeSession;
}
