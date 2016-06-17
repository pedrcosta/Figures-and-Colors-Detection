#include "cchild_info.h"

CChild_Info::CChild_Info()
{
    this->code = "";
    this->name = "";
    this->age = "";
    this->gender = "";
    this->td = "";
    this->nSessions = 0;
}

CChild_Info::CChild_Info(QString code, QString name, QString gender, QString age, QString td)
{
    this->code = code;
    this->name = name;
    this->gender = gender;
    this->age = age;
    this->td = td;
    this->nSessions = 0;
}

CChild_Info::CChild_Info(QStringList &Child)
{
    ///Code, Name, Gender, Age, TD, nSessions
    this->code = Child[0];
    this->name = Child[1];
    this->gender = Child[2];
    this->age = Child[3];
    this->td = Child[4];
    this->nSessions = Child[5].toInt();
}

/**************************************************************
      CREATE A FOLDER FOR CHILD AND SAVE CHILD'S INFORMATION
                                        Informations in the file:
                      child_code, name, gender, age, td, nSessions
**************************************************************/
bool CChild_Info::addNewChild()
{
    QDir dir("ChildrenData/Child_" + code);

    if(!dir.exists())  ///If directory doesn't exist creat the folder
    {
        dir.mkdir(".");
    }

    QFile file("ChildrenData/Child_" + code + "/ChildInfo.csv");

    if(!file.exists()) ///First time the file is created, print the headers
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream write(&file);
            write << "Code;Name;Gender;Age;TD;nSessions" << endl;
            file.close();
        }
        else
            return false;
    }

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream write(&file);
        write << code << ';' << name << ';' << gender << ';' << age << ';' << td << ';' << nSessions << endl;
        ///write << this->getChildInfo() << endl;
    }
    else
    {
        return false;
    }
    file.close();
    return true;
}

/**************************************************************
     GO TO FOLDER OF EACH CHILD AND LOAD THE FILE CHILDINFO.CVS
                                        Informations in the file:
                      child_code, name, gender, age, td, nSessions
**************************************************************/
bool CChild_Info::loadChildtoTable(QStandardItemModel *model)
{
    QDir dir("ChildrenData");

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot );

    QStringList listDir = dir.entryList();

    for(int i = 0; i < listDir.size(); i++)
    {
        QFile file("ChildrenData/" + listDir[i] + "/ChildInfo.csv");

        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream read(&file);

            read.seek(35);  ///Go to second line in the file because the first is the headers

            QString buffer = read.readLine();
            QStringList listInfo = buffer.split(';');

            for(int col = 0; col < model->columnCount(); col++)
            {
                QStandardItem *item = new QStandardItem(listInfo[col]);
                model->setItem(i, col, item);
            }
            file.close();
        }
        else
            return false;
    }
    return true;
}

/**************************************************************
     GO TO FOLDER'S CHILD AND UPDATE THE FILE CHILDINFO.CVS
                                        Informations in the file:
                      child_code, name, gender, age, td, nSessions
**************************************************************/
bool CChild_Info::updateChildInfo(QString child_code)
{
    QFile file("ChildrenData/Child_" + child_code + "/ChildInfo.csv");

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream write(&file);

        if(write.seek(35)) ///Go to second line in the file because the first is the headers
        {
            write << getChildInfo() << endl;
        }
        file.close();
        return true;
    }
    else
        return false;
}

QString CChild_Info::getChildCode()
{
    return this->code;
}

int CChild_Info::getnSessions()
{
    return this->nSessions;
}

QString CChild_Info::getChildInfo()
{
    QString sessions;
    sessions.setNum(nSessions);

    return code + ';' + name + ';' + gender + ';' + age + ';' + td + ';' + sessions;
}

void CChild_Info::stop_activity()
{
    this->nSessions++;
}



