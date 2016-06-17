#ifndef CPERFORMANCE_H
#define CPERFORMANCE_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QFont>

#include <QVector>

#include "qcustomplot.h"

#include "cactivitytype.h"
#include "cfigstype.h"
#include "ccolorstype.h"

class CPerformance
{
public:
    CPerformance();
    CPerformance(QString codeChild, CActivityType activity);

    QString enum2QString(CActivityType type);

    void rightAnswer(CFigsType figType);
    void rightAnswer(CColorsType colorType);

    ///NEW FUNCTIONS
    void right_or_wrongAnswer(QVector<CFigsType> answer);
    void right_or_wrongAnswer(QVector<CColorsType> answer);

    void wrongAnswer(CFigsType figType);
    void wrongAnswer(CColorsType colorType);

    bool savePerformance(QString codeChild, int codeSession, CActivityType activity);

    bool loadInfoToGraph(QString codeChild, CActivityType activity);

    bool updateGraph(QString codeChild, CActivityType activity, QCustomPlot *customPlot);
    void graphFigs(QCustomPlot *customPlot);
    void graphColors(QCustomPlot *customPlot);

    void clearQVectors();


private:

    ///Figures Activity
    int rightSquare, wrongSquare;
    int rightTriangle, wrongTriangle;
    int rightCircle, wrongCircle;
    int rightRectangle, wrongRectangle;
    int rightPentagon, wrongPentagon;

    QVector<double> squareRights;
    QVector<double> triangleRights;
    QVector<double> circleRights;
    QVector<double> rectangleRights;
    QVector<double> pentagonRights;

    ///Colors Activity
    int rightBlue, wrongBlue;
    int rightRed, wrongRed;
    int rightGreen, wrongGreen;
    int rightYellow, wrongYellow;
    int rightBlack, wrongBlack;

    QVector<double> blueRights;
    QVector<double> redRights;
    QVector<double> greenRights;
    QVector<double> yellowRights;
    QVector<double> blackRights;

};

#endif // CPERFORMANCE_H
