#include "cperformance.h"

CPerformance::CPerformance()
{
    this->rightSquare = 0;
    this->wrongSquare = 0;

    this->rightTriangle = 0;
    this->wrongTriangle = 0;

    this->rightCircle = 0;
    this->wrongCircle = 0;

    this->rightRectangle = 0;
    this->wrongRectangle = 0;

    this->rightPentagon = 0;
    this->wrongPentagon = 0;

    this->rightBlue = 0;
    this->wrongBlue = 0;

    this->rightRed = 0;
    this->wrongRed = 0;

    this->rightGreen = 0;
    this->wrongGreen = 0;

    this->rightYellow = 0;
    this->wrongYellow = 0;

    this->rightBlack = 0;
    this->wrongBlack = 0;

//    squareRights = QVector<double>();
//    triangleRights = QVector<double>();
//    QVector<double> circleRights;
//    QVector<double> rectangleRights;
    //    QVector<double> pentagonRights;
}

CPerformance::CPerformance(QString codeChild, CActivityType activity)
{
    this->rightSquare = 0;
    this->wrongSquare = 0;

    this->rightTriangle = 0;
    this->wrongTriangle = 0;

    this->rightCircle = 0;
    this->wrongCircle = 0;

    this->rightRectangle = 0;
    this->wrongRectangle = 0;

    this->rightPentagon = 0;
    this->wrongPentagon = 0;

    this->rightBlue = 0;
    this->wrongBlue = 0;

    this->rightRed = 0;
    this->wrongRed = 0;

    this->rightGreen = 0;
    this->wrongGreen = 0;

    this->rightYellow = 0;
    this->wrongYellow = 0;

    this->rightBlack = 0;
    this->wrongBlack = 0;

    loadInfoToGraph(codeChild, activity);
}

QString CPerformance::enum2QString(CActivityType type)
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

void CPerformance::rightAnswer(CFigsType figType)
{
    switch(figType)
    {
    case CFigsType::SQUARE:
        this->rightSquare++;
        break;

    case CFigsType::TRIANGLE:
        this->rightTriangle++;
        break;

    case CFigsType::CIRCLE:
        this->rightCircle++;
        break;

    case CFigsType::RECTANGLE:
        this->rightRectangle++;
        break;

    case CFigsType::PENTAGON:
        this->rightPentagon++;
        break;

    default:
        break;
    }
}

void CPerformance::rightAnswer(CColorsType colorType)
{
    switch(colorType)
    {
    case CColorsType::BLUE:
        this->rightBlue++;
        break;

    case CColorsType::RED:
        this->rightRed++;
        break;

    case CColorsType::GREEN:
        this->rightGreen++;
        break;

    case CColorsType::YELLOW:
        this->rightYellow++;
        break;

    case CColorsType::BLACK:
        this->rightBlack++;
        break;

    default:
        break;
    }
}

void CPerformance::right_or_wrongAnswer(QVector<CFigsType> answer)
{
    /// answer[0]_figBoard
    /// answer[1]_figPlaced

    switch(answer[0])
    {
    case CFigsType::SQUARE:
        if(answer[0] == answer[1])   ///Right answer
            rightSquare++;
        else                                       ///Wrong answer
            wrongSquare++;
        break;

    case CFigsType::TRIANGLE:
        if(answer[0] == answer[1])   ///Right answer
            rightTriangle++;
        else                                       ///Wrong answer
            wrongTriangle++;
        break;

    case CFigsType::RECTANGLE:
        if(answer[0] == answer[1])   ///Right answer
            rightRectangle++;
        else                                       ///Wrong answer
            wrongRectangle++;
        break;

    case CFigsType::CIRCLE:
        if(answer[0] == answer[1])   ///Right answer
            rightCircle++;
        else                                       ///Wrong answer
            wrongCircle++;
        break;

    case CFigsType::PENTAGON:
        if(answer[0] == answer[1])   ///Right answer
            rightPentagon++;
        else                                       ///Wrong answer
            wrongPentagon++;
        break;

    default:
        break;
    }
}

void CPerformance::right_or_wrongAnswer(QVector<CColorsType> answer)
{
    /// answer[0]_colorBoard
    /// answer[1]_colorPlaced

    switch(answer[0])
    {
    case CColorsType::BLACK:
        if(answer[0] == answer[1])   ///Right answer
            rightBlack++;
        else                                       ///Wrong answer
            wrongBlack++;
        break;

    case CColorsType::BLUE:
        if(answer[0] == answer[1])   ///Right answer
            rightBlue++;
        else                                       ///Wrong answer
            wrongBlue++;
        break;

    case CColorsType::GREEN:
        if(answer[0] == answer[1])   ///Right answer
            rightGreen++;
        else                                       ///Wrong answer
            wrongGreen++;
        break;

    case CColorsType::RED:
        if(answer[0] == answer[1])   ///Right answer
            rightRed++;
        else                                       ///Wrong answer
            wrongRed++;
        break;

    case CColorsType::YELLOW:
        if(answer[0] == answer[1])   ///Right answer
            rightYellow++;
        else                                       ///Wrong answer
            wrongYellow++;
        break;

    default:
        break;
    }
}



void CPerformance::wrongAnswer(CFigsType figType)
{
    switch(figType)
    {
    case CFigsType::SQUARE:
        this->wrongSquare++;
        break;

    case CFigsType::TRIANGLE:
        this->wrongTriangle++;
        break;

    case CFigsType::CIRCLE:
        this->wrongCircle++;
        break;

    case CFigsType::RECTANGLE:
        this->wrongRectangle++;
        break;

    case CFigsType::PENTAGON:
        this->wrongPentagon++;
        break;

    default:
        break;
    }
}

void CPerformance::wrongAnswer(CColorsType colorType)
{
    switch(colorType)
    {
    case CColorsType::BLUE:
        this->wrongBlue++;
        break;

    case CColorsType::RED:
        this->wrongRed++;
        break;

    case CColorsType::GREEN:
        this->wrongGreen++;
        break;

    case CColorsType::YELLOW:
        this->wrongYellow++;
        break;

    case CColorsType::BLACK:
        this->wrongBlack++;
        break;

    default:
        break;
    }
}

bool CPerformance::savePerformance(QString codeChild, int codeSession, CActivityType activity)
{
    QDir dir("ChildrenData/Child_" + codeChild + "/Performance");
    QString sActivity = enum2QString(activity);

    if(!dir.exists())
    {
        dir.mkdir(".");
    }

    if(activity == CActivityType::F1 || activity == CActivityType::F2)
    {
        ///Figures Activity
        QFile file1("ChildrenData/Child_" + codeChild + "/Performance/" + sActivity + "_Performance.csv");

        if(!file1.exists())
        {
            if(file1.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                ///Writes the table headers
                QTextStream write(&file1);
                write << "ChildCode;CodeSession;Activity;"
                      << "SquareRight;SquareWrong;"
                      << "TriangleRight;TriangleWrong;"
                      << "CircleRight;CircleWrong;"
                      << "RectangleRight;RectangleWrong;"
                      << "PentagonRight;PentagonWrong" << endl;
                file1.close();
            }
            else
                return false;
        }

        if(file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream write(&file1);
            write << codeChild << ';' << codeSession << ';' << sActivity << ';'
                  << rightSquare << ';' << wrongSquare << ';'
                  << rightTriangle << ';' << wrongTriangle << ';'
                  << rightCircle << ';' << wrongCircle << ';'
                  << rightRectangle << ';' << wrongRectangle << ';'
                  << rightPentagon << ';' << wrongPentagon << endl;
        }
        else
            return false;

        file1.close();
        return true;
    }
    else if(activity == CActivityType::C1 || activity == CActivityType::C2)
    {
        ///Colors Activity
        QFile file2("ChildrenData/Child_" + codeChild + "/Performance/" + sActivity + "_Performance.csv");

        if(!file2.exists())
        {
            if(file2.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                ///Writes the table headers
                QTextStream write(&file2);
                write << "ChildCode;CodeSession;Activity;"
                      << "BlueRight;BlueWrong;"
                      << "RedRight;RedWrong;"
                      << "GreenRight;GreenWrong;"
                      << "YellowRight;YellowWrong;"
                      << "BlackRight;BlackWrong" << endl;
                file2.close();
            }
            else
                return false;
        }

        if(file2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream write(&file2);
            write << codeChild << ';' << codeSession << ';' << sActivity << ';'
                  << rightBlue << ';' << wrongBlue << ';'
                  << rightRed << ';' << wrongRed << ';'
                  << rightGreen << ';' << wrongGreen << ';'
                  << rightYellow << ';' << wrongYellow << ';'
                  << rightBlack << ';' << wrongBlack << endl;
            file2.close();
        }
        else
            return false;

        file2.close();
        return true;
    }
    return false;
}

bool CPerformance::loadInfoToGraph(QString codeChild, CActivityType activity)
{
    QString sActivity = enum2QString(activity);

    QFile file("ChildrenData/Child_" + codeChild + "/Performance/" + sActivity + "_Performance.csv");

    if(file.open(QIODevice::ReadOnly))
    {
        clearQVectors();

        QTextStream read(&file);

        if(CActivityType::F1 == activity || CActivityType::F2 == activity)
            read.seek(166); ///Position of the second line
        else if(CActivityType::C1 == activity || CActivityType::C2 == activity)  ///DESCOBRIR A POSIÇAO DA SEGUNDA LINHA
            read.seek(138); ///Position of the second line

        while(!read.atEnd())
        {
            QString buffer = read.readLine();
            QStringList listInfo = buffer.split(';');

            if(CActivityType::F1 == activity || CActivityType::F2 == activity)
            {
                squareRights.append(listInfo[3].toFloat() / (listInfo[3].toFloat() + listInfo[4].toFloat()) * 100);
                triangleRights.append(listInfo[5].toFloat() / (listInfo[5].toFloat() + listInfo[6].toFloat()) * 100);
                circleRights.append(listInfo[7].toFloat() / (listInfo[7].toFloat() + listInfo[8].toFloat()) * 100);
                rectangleRights.append(listInfo[9].toFloat() / (listInfo[9].toFloat() + listInfo[10].toFloat()) * 100);
                pentagonRights.append(listInfo[11].toFloat() / (listInfo[11].toFloat() + listInfo[12].toFloat()) * 100);
            }
            else if(CActivityType::C1 == activity || CActivityType::C2 == activity)
            {
                blueRights.append(listInfo[3].toFloat() / (listInfo[3].toFloat() + listInfo[4].toFloat()) * 100);
                redRights.append(listInfo[5].toFloat() / (listInfo[5].toFloat() + listInfo[6].toFloat()) * 100);
                greenRights.append(listInfo[7].toFloat() / (listInfo[7].toFloat() + listInfo[8].toFloat()) * 100);
                yellowRights.append(listInfo[9].toFloat() / (listInfo[9].toFloat() + listInfo[10].toFloat()) * 100);
                blackRights.append(listInfo[11].toFloat() / (listInfo[11].toFloat() + listInfo[12].toFloat()) * 100);
            }
        }
    }
    else
        return false;

    file.close();
    return true;
}

bool CPerformance::updateGraph(QString codeChild, CActivityType activity, QCustomPlot *customPlot)
{
    ///Load info to QVectors
    if(!loadInfoToGraph(codeChild, activity))
        return false;

    if(CActivityType::F1 == activity || CActivityType::F2 == activity)
    {
        graphFigs(customPlot);
    }
    else if(CActivityType::C1 == activity || CActivityType::C2 == activity)
    {
        graphColors(customPlot);
    }
    return true;
}

void CPerformance::graphFigs(QCustomPlot *customPlot)
{
    QVector<double> datax = QVector<double>() << 1 << 2 << 3 << 4  << 5;

    customPlot->clearPlottables();

//    QCPPlotTitle  *title = new QCPPlotTitle(customPlot, "Figures Performance");

//    ///To print only one time the title
//    if(customPlot->plotLayout()->rowCount() < 2)
//    {
//        customPlot->plotLayout()->insertRow(0);
//    }

//    title->setTextColor(QColor(255, 255, 255));
//    title->setText("Figures Performance");
//    customPlot->plotLayout()->addElement(0, 0, title);

    QCPBarsGroup *group1 = new QCPBarsGroup(customPlot);
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, squareRights);
    bars->setBrush(QColor(25, 115, 215, 50));
    bars->setPen(QColor(25, 115, 215));
    bars->setWidth(0.15);

    group1->insert(1, bars);
//        bars->setBarsGroup(group1);
    bars->setName("Square");
//        customPlot->plottable(0)->setName("squareRights");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax,triangleRights);
    bars->setBrush(QColor(240, 0, 0, 50));
    bars->setPen(QColor(240, 0, 0));
    bars->setWidth(0.15);

    group1->insert(2,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Triangle");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, circleRights);
    bars->setBrush(QColor(30, 210, 60, 50));
    bars->setPen(QColor(30, 210, 60));
    bars->setWidth(0.15);

    group1->insert(3,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Circle");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, rectangleRights);
    bars->setBrush(QColor(240, 230, 0, 50));
    bars->setPen(QColor(240, 230, 0));
    bars->setWidth(0.15);

    group1->insert(4,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Rectangle");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, pentagonRights);
    bars->setBrush(QColor(0, 0, 0, 50));
    bars->setPen(QColor(0, 0, 0));
    bars->setWidth(0.15);

    group1->insert(5,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Pentagon");

    customPlot->legend->setVisible(true);
    customPlot->replot();

}

void CPerformance::graphColors(QCustomPlot *customPlot)
{
    QVector<double> datax = QVector<double>() << 1 << 2 << 3 << 4  << 5;

    customPlot->clearPlottables();

//    QCPPlotTitle *title = new QCPPlotTitle(customPlot, "Colors Performance");

//    ///To print only one time the title
//    if(customPlot->plotLayout()->rowCount() < 2)
//    {
//        customPlot->plotLayout()->insertRow(0);
//    }

//    title->setTextColor(QColor(255, 255, 255));
//    customPlot->plotLayout()->addElement(0, 0, title);

    QCPBarsGroup *group1 = new QCPBarsGroup(customPlot);
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, blueRights);
    bars->setBrush(QColor(25, 115, 215, 50));
    bars->setPen(QColor(25, 115, 215));
    bars->setWidth(0.15);

    group1->insert(1, bars);
//        bars->setBarsGroup(group1);
    bars->setName("Blue");
//        customPlot->plottable(0)->setName("squareRights");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax,redRights);
    bars->setBrush(QColor(240, 0, 0, 50));
    bars->setPen(QColor(240, 0, 0));
    bars->setWidth(0.15);

    group1->insert(2,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Red");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, greenRights);
    bars->setBrush(QColor(30, 210, 60, 50));
    bars->setPen(QColor(30, 210, 60));
    bars->setWidth(0.15);

    group1->insert(3,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Green");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, yellowRights);
    bars->setBrush(QColor(240, 230, 0, 50));
    bars->setPen(QColor(240, 230, 0));
    bars->setWidth(0.15);

    group1->insert(4,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Yellow");

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(bars);
    bars->setData(datax, blackRights);
    bars->setBrush(QColor(0, 0, 0, 50));
    bars->setPen(QColor(0, 0, 0));
    bars->setWidth(0.15);

    group1->insert(5,bars);
//        bars->setBarsGroup(group1);
    bars->setName("Black");

    customPlot->legend->setVisible(true);
    customPlot->replot();
}

void CPerformance::clearQVectors()
{
    squareRights.clear();
    triangleRights.clear();
    circleRights.clear();
    rectangleRights.clear();
    pentagonRights.clear();

    blueRights.clear();
    redRights.clear();
    greenRights.clear();
    yellowRights.clear();
    blackRights.clear();
}
