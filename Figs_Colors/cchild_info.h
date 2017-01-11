#ifndef CCHILD_INFO_H
#define CCHILD_INFO_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardItemModel>

class CChild_Info
{
public:
    CChild_Info();
    CChild_Info(QString code, QString name, QString gender, QString age, QString td);
    CChild_Info(QStringList &Child);

    bool addNewChild();

    bool loadChildtoTable(QStandardItemModel *model);
    bool updateChildInfo(QString child_code);

    void stop_activity();

    QString getChildCode();
    int getnSessions();
    QString getChildInfo();   ///VERIFICAR SE É REALMENTE NECESSÁRIA

private:
    QString code;
    QString name;
    QString age;
    QString gender;
    QString td;    //Typically developed
    int nSessions;

};

#endif // CCHILD_INFO_H
