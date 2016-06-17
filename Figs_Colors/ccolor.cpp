#include "ccolor.h"

CColor::CColor()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    this->colorPlaced = CColorsType::NONE; ///1st level
    this->colorAsked = CColorsType::NONE; ///2nd level
    this->colorType = CColorsType::NONE;

    randomQVector();

    this->message2Robot = "";

    redLowH = 0; redHighH = 12;
    redLowS = 80; redHighS = 255;
    redLowV = 0; redHighV = 255;

    greenLowH = 40; greenHighH = 85;
    greenLowS = 35; greenHighS = 255;
    greenLowV = 0; greenHighV = 255;

    blueLowH = 85; blueHighH = 130;
    blueLowS = 100; blueHighS = 255;
    blueLowV = 50; blueHighV = 255;

    yellowLowH = 15; yellowHighH = 47;
    yellowLowS = 40; yellowHighS = 255;
    yellowLowV = 100; yellowHighV = 255;

    blackLowH = 0; blackHighH = 180;
    blackLowS = 0; blackHighS = 255;
    blackLowV = 0; blackHighV = 50;

    witeLowH = 0; witeHighH = 180;
    witeLowS = 0; witeHighS = 45;
    witeLowV = 105; witeHighV = 255;

    notwiteLowH = 0; notwiteHighH = 180;
    notwiteLowS = 16; notwiteHighS = 255;
    notwiteLowV = 0; notwiteHighV = 255;
}


void CColor::set_imgSharp(Mat sharp)
{
    this->imgSharp = sharp;
}

Mat CColor::get_imgSharp()
{
    return imgSharp;
}



///Level 1
void CColor::setALLBoardColorPosition()
{
    Scalar colorContours;
    imgFHSVBoard = Frame2HSV(imgSharp, CColorsType::NOTWHITE);
    ///setColorPosition2Board(CColorsType::RED);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::RED);
    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //sumar a figura imgFHSVBoard com imgFHSV para obter só a cor
    Canny(imgFComper, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    drawingContours = Mat::zeros(imgCanny.size(), CV_8UC3);
    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(fig.isSquare(approx)) {
                poscenter.ChooseSaveBoardColorCenter( CColorsType::RED, contours[i]);

                colorContours = CV_RGB(255, 0, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Board(CColorsType::GREEN);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::GREEN);
    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //sumar a figura imgFHSVBoard com imgFHSV para obter só a cor
    Canny(imgFComper, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(fig.isSquare(approx)) {
                poscenter.ChooseSaveBoardColorCenter( CColorsType::GREEN, contours[i]);

                colorContours = CV_RGB(0, 255, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Board(CColorsType::BLUE);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLUE);
    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //sumar a figura imgFHSVBoard com imgFHSV para obter só a cor
    Canny(imgFComper, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(fig.isSquare(approx)) {
                poscenter.ChooseSaveBoardColorCenter( CColorsType::BLUE, contours[i]);

                colorContours = CV_RGB(0, 0, 255);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ////setColorPosition2Board(CColorsType::YELLOW);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::YELLOW);
    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //sumar a figura imgFHSVBoard com imgFHSV para obter só a cor
    Canny(imgFComper, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(fig.isSquare(approx)) {
                poscenter.ChooseSaveBoardColorCenter( CColorsType::YELLOW, contours[i]);

                colorContours = CV_RGB(255, 255, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Board(CColorsType::BLACK);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLACK );
    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //sumar a figura imgFHSVBoard com imgFHSV para obter só a cor
    Canny(imgFComper, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(fig.isSquare(approx)) {
                poscenter.ChooseSaveBoardColorCenter( CColorsType::BLACK, contours[i]);

                colorContours = CV_RGB(255, 255, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    //imshow("drawingContours", drawingContours);
}

Mat CColor::setColorPosition()
{
    Scalar colorContours;
    drawingContours = Mat::zeros(imgCanny.size(), CV_8UC3);

    ///setColorPosition2Piece(CColorsType::RED);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::RED);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(!fig.isSquare(approx)) {
                poscenter.ChooseSaveColorCenter( CColorsType::RED, contours[i]);

                fig.setContourRectangle(imgSharp, contours[i]);

                colorContours = CV_RGB(255, 0, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
                drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Piece(CColorsType::GREEN);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::GREEN);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(!fig.isSquare(approx)) {
                poscenter.ChooseSaveColorCenter( CColorsType::GREEN, contours[i]);

                fig.setContourRectangle(imgSharp, contours[i]);

                colorContours = CV_RGB(0, 255, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
                drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Piece(CColorsType::BLUE);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLUE);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(!fig.isSquare(approx)) {
                poscenter.ChooseSaveColorCenter( CColorsType::BLUE, contours[i]);

                fig.setContourRectangle(imgSharp, contours[i]);

                colorContours = CV_RGB(0, 0, 255);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
                drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Piece(CColorsType::YELLOW);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::YELLOW);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(!fig.isSquare(approx)) {
                poscenter.ChooseSaveColorCenter( CColorsType::YELLOW, contours[i]);

                fig.setContourRectangle(imgSharp, contours[i]);

                colorContours = CV_RGB(255, 255, 0);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
                drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }

    ///setColorPosition2Piece(CColorsType::BLACK);
    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLACK);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if(!fig.isSquare(approx)) {
                poscenter.ChooseSaveColorCenter( CColorsType::BLACK, contours[i]);

                fig.setContourRectangle(imgSharp, contours[i]);

                colorContours = CV_RGB(100, 100, 100);
                drawContours(drawingContours, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
                drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }
        }
    }
//    imshow("drawingContours", drawingContours);
    return drawingContours;
}

QVector<CColorsType> CColor::getCorBoard_CorPlaced()
{

    imgFHSV = Frame2HSV(imgSharp, CColorsType::YELLOW);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if( ! fig.isSquare(approx)) {///                     YELLOW                 ///As peças jogadas são retangulos
                CColorsType colorBoard =  poscenter.getBoardColor(CColorsType::YELLOW);
                if(colorBoard == CColorsType::YELLOW)  ///Right Answer
                {
                    setMessage2Robot(true, colorBoard, CColorsType::YELLOW);
                    return QVector<CColorsType>() << colorBoard << CColorsType::YELLOW;
                }
                else
                {
                    setMessage2Robot(false, colorBoard, CColorsType::YELLOW);
                    return QVector<CColorsType>() << colorBoard << CColorsType::YELLOW;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::RED);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     RED                 ///As peças jogadas são retangulos
                CColorsType colorBoard =  poscenter.getBoardColor(CColorsType::RED);
                if(colorBoard == CColorsType::RED)
                {
                    setMessage2Robot(true, colorBoard, CColorsType::RED);
                    return QVector<CColorsType>() << colorBoard << CColorsType::RED;
                }
                else
                {
                    setMessage2Robot(false, colorBoard, CColorsType::RED);
                    return QVector<CColorsType>() << colorBoard << CColorsType::RED;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::GREEN);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     GREEN                 ///As peças jogadas são retangulos
                CColorsType colorBoard =  poscenter.getBoardColor(CColorsType::GREEN);
                if(colorBoard == CColorsType::GREEN)
                {
                    setMessage2Robot(true, colorBoard, CColorsType::GREEN);
                    return QVector<CColorsType>() << colorBoard << CColorsType::GREEN;
                }
                else
                {
                    setMessage2Robot(false, colorBoard, CColorsType::GREEN);
                    return QVector<CColorsType>() << colorBoard << CColorsType::GREEN;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLUE);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     BLUE                 ///As peças jogadas são retangulos
                CColorsType colorBoard =  poscenter.getBoardColor(CColorsType::BLUE);
                if(colorBoard == CColorsType::BLUE)
                {
                    setMessage2Robot(true, colorBoard, CColorsType::BLUE);
                    return QVector<CColorsType>() << colorBoard << CColorsType::BLUE;
                }
                else
                {
                    setMessage2Robot(false, colorBoard, CColorsType::BLUE);
                    return QVector<CColorsType>() << colorBoard << CColorsType::BLUE;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLACK);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     BLACK                 ///As peças jogadas são retangulos
                CColorsType colorBoard =  poscenter.getBoardColor(CColorsType::BLACK);
                if(colorBoard == CColorsType::BLACK)
                {
                    setMessage2Robot(true, colorBoard, CColorsType::BLACK);
                    return QVector<CColorsType>() << colorBoard << CColorsType::BLACK;
                }
                else
                {
                    setMessage2Robot(false, colorBoard, CColorsType::BLACK);
                    return QVector<CColorsType>() << colorBoard << CColorsType::BLACK;
                }
            }
        }
    }

    return QVector<CColorsType>() << CColorsType::NONE  << CColorsType::NONE;  ///REVER
}

void CColor::setMessage2Robot(bool right, CColorsType corBoard, CColorsType corPlaced)
{
    QString sColorBoard = enum2QString(corBoard);
    QString sColorPlaced = enum2QString(corPlaced);

    if(right)
    {
        this->message2Robot = "R;" + sColorBoard + ';' + sColorPlaced;
    }
    else
    {
        this->message2Robot = "W;" + sColorBoard + ';' + sColorPlaced;
    }

}

QString CColor::getMessage2Robot()
{
        return this->message2Robot;
}

QString CColor::enum2QString(CColorsType colorType)
{
    switch(colorType)
    {
    case CColorsType::YELLOW:
        return "YELLOW";
        break;

    case CColorsType::RED:
        return "RED";
        break;

    case CColorsType::GREEN:
        return "GREEN";
        break;

    case CColorsType::BLUE:
        return "BLUE";
        break;

    case CColorsType::BLACK:
        return "BLACK";
        break;

    default:
        return "";
        break;
    }
}


///Level 2
void CColor::newRandomColor(int pos)
{
    this->colorAsked =  randomColor(pos);
}

CColorsType CColor::getColorAsked()
{
    return this->colorAsked;
}

CColorsType CColor::randomColor(int pos)
{
    switch(vAskColor[pos] )
    {
    case 1:
        return CColorsType::RED;
        break;
    case 2:
        return CColorsType::GREEN;
        break;
    case 3:
        return CColorsType::BLUE;
        break;
    case 4:
        return CColorsType::YELLOW;
        break;
    default:
        return CColorsType::BLACK;
        break;
    }
}

void CColor::randomQVector()
{
    switch(qrand() % ((7 +1) - 1) + 1)
    {
    case 1:
        this->vAskColor = QVector<int>() << 1 << 2 << 3 << 4 << 5;
        break;
    case 2:
        this->vAskColor = QVector<int>() << 1 << 3 << 5 << 2 << 4;
        break;
    case 3:
        this->vAskColor = QVector<int>() << 5 << 1 << 4 << 2 << 3;
        break;
    case 4:
        this->vAskColor = QVector<int>() << 2 << 4 << 1 << 3 << 5;
        break;
    case 5:
        this->vAskColor = QVector<int>() << 3 << 1 << 4 << 2 << 5;
        break;
    case 6:
        this->vAskColor = QVector<int>() << 4 << 2 << 3 << 5 << 1;
        break;
    default:
        this->vAskColor = QVector<int>() << 2 << 3 << 5 << 4 << 1;
        break;
    }
}

QString CColor::printAskColor(CColorsType cor)
{
    switch (cor) {
    case CColorsType::RED:
        return "RED";
        break;
    case CColorsType::GREEN:
        return "GREEN";
        break;
    case CColorsType::BLUE:
        return "BLUE";
        break;
    case CColorsType::YELLOW:
        return "YELLOW";
        break;
    case CColorsType::BLACK:
        return "BLACK";
        break;
    default:
        return "NONE";
        break;
    }
}

QVector<CColorsType> CColor::getCorAsked_CorPlaced(CColorsType colorAsked)
{
    Scalar colorContours;

    imgFHSV = Frame2HSV(imgSharp, CColorsType::YELLOW);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4)
        {
            if( ! fig.isSquare(approx)) {///                     YELLOW                 ///As peças jogadas são retangulos
                if(colorAsked == CColorsType::YELLOW)  ///Right Answer
                {
                    fig.setContourRectangle(imgSharp, contours[i], CV_RGB(0, 255, 0)); //feedback on screen
                    colorContours = CV_RGB(255, 255, 0);
                    drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());

                    setMessage2Robot(true, colorAsked, CColorsType::YELLOW);
                    return QVector<CColorsType>() << colorAsked << CColorsType::YELLOW;
                }
                else
                {
                    fig.setContourRectangle(imgSharp, contours[i], Scalar(0, 0, 255)); //feedback on screen

                    setMessage2Robot(false, colorAsked, CColorsType::YELLOW);
                    return QVector<CColorsType>() << colorAsked << CColorsType::YELLOW;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::RED);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     RED                 ///As peças jogadas são retangulos
                if(colorAsked == CColorsType::RED)
                {
                    fig.setContourRectangle(imgSharp, contours[i], CV_RGB(0, 255, 0)); //feedback on screen
                    colorContours = CV_RGB(255, 0, 0);
                    drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());

                    setMessage2Robot(true, colorAsked, CColorsType::RED);
                    return QVector<CColorsType>() << colorAsked << CColorsType::RED;
                }
                else
                {
                    fig.setContourRectangle(imgSharp, contours[i], Scalar(0, 0, 255)); //feedback on screen

                    setMessage2Robot(false, colorAsked, CColorsType::RED);
                    return QVector<CColorsType>() << colorAsked << CColorsType::RED;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::GREEN);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     GREEN                 ///As peças jogadas são retangulos
                if(colorAsked == CColorsType::GREEN)
                {
                    fig.setContourRectangle(imgSharp, contours[i], CV_RGB(0, 255, 0)); //feedback on screen
                    colorContours = CV_RGB(0, 255, 0);
                    drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());

                    setMessage2Robot(true, colorAsked, CColorsType::GREEN);
                    return QVector<CColorsType>() << colorAsked << CColorsType::GREEN;
                }
                else
                {
                    fig.setContourRectangle(imgSharp, contours[i], Scalar(0, 0, 255)); //feedback on screen

                    setMessage2Robot(false, colorAsked, CColorsType::GREEN);
                    return QVector<CColorsType>() << colorAsked << CColorsType::GREEN;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLUE);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     BLUE                 ///As peças jogadas são retangulos
                if(colorAsked == CColorsType::BLUE)
                {
                    fig.setContourRectangle(imgSharp, contours[i], CV_RGB(0, 255, 0)); //feedback on screen
                    colorContours = CV_RGB(0, 0, 255);
                    drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());


                    setMessage2Robot(true, colorAsked, CColorsType::BLUE);
                    return QVector<CColorsType>() << colorAsked << CColorsType::BLUE;
                }
                else
                {
                    fig.setContourRectangle(imgSharp, contours[i], Scalar(0, 0, 255)); //feedback on screen

                    setMessage2Robot(false, colorAsked, CColorsType::BLUE);
                    return QVector<CColorsType>() << colorAsked << CColorsType::BLUE;
                }
            }
        }
    }

    imgFHSV = Frame2HSV(imgSharp, CColorsType::BLACK);
    Canny(imgFHSV, imgCanny, 180, 120);
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4) //este if não deve ser necessario
        {
            if( ! fig.isSquare(approx)){///                     BLACK                 ///As peças jogadas são retangulos
                if(colorAsked == CColorsType::BLACK)
                {
                    fig.setContourRectangle(imgSharp, contours[i], CV_RGB(0, 255, 0)); //feedback on screen
                    colorContours = CV_RGB(0, 0, 0);
                    drawContours(imgSharp, contours, (int)i, colorContours, 2, /*CV_AA*/8, hierarchy, 0, Point());


                    setMessage2Robot(true, colorAsked, CColorsType::BLACK);
                    return QVector<CColorsType>() << colorAsked << CColorsType::BLACK;
                }
                else
                {
                    fig.setContourRectangle(imgSharp, contours[i], Scalar(0, 0, 255)); //feedback on screen

                    setMessage2Robot(false, colorAsked, CColorsType::BLACK);
                    return QVector<CColorsType>() << colorAsked << CColorsType::BLACK;
                }
            }
        }
    }

    return QVector<CColorsType>() << CColorsType::NONE  << CColorsType::NONE;  ///REVER
}

bool CColor::existColor(Mat imgCanny)
{
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000 && approx.size() == 4 ){
            if(! fig.isSquare( approx ))
                return true;
        }
    }
    return false;
}


void CColor::SetColor(CColorsType cor)
{
    switch (cor)
    {
        case CColorsType::RED:   ///RED
            iLowH = redLowH; iHighH = redHighH;
            iLowS = redLowS; iHighS = redHighS;
            iLowV = redLowV; iHighV = redHighV;
            break;

        case CColorsType::GREEN: ///GREEN
            iLowH = greenLowH; iHighH = greenHighH;
            iLowS = greenLowS; iHighS = greenHighS;
            iLowV = greenLowV; iHighV = greenHighV;
            break;

        case CColorsType::BLUE: ///BLUE
            iLowH = blueLowH; iHighH = blueHighH;
            iLowS = blueLowS; iHighS = blueHighS;
            iLowV = blueLowV; iHighV = blueHighV;
            break;

        case CColorsType::YELLOW: ///YELLOW
            iLowH = yellowLowH; iHighH = yellowHighH;
            iLowS = yellowLowS; iHighS = yellowHighS;
            iLowV = yellowLowV; iHighV = yellowHighV;
            break;

        case CColorsType::BLACK: ///BLACK
            iLowH = blackLowH; iHighH = blackHighH;
            iLowS = blackLowS; iHighS = blackHighS;
            iLowV = blackLowV; iHighV = blackHighV;
            break;

        case CColorsType::WHITE: ///WITE
            iLowH = witeLowH; iHighH = witeLowH;
            iLowS = witeLowS; iHighS = witeLowS;
            iLowV = witeLowV; iHighV = witeLowV;
            break;

        case CColorsType::NOTWHITE: ///NOTWITE
            iLowH = notwiteLowH; iHighH = notwiteHighH;
            iLowS = notwiteLowS; iHighS = notwiteHighS;
            iLowV = notwiteLowV; iHighV = notwiteHighV;
            break;

        case CColorsType::NONE: //não faz nada serve para os ajustes
            break;

        default:
            //cout << "No option existent!" << endl;
            break;
    }
}

Mat CColor::Frame2HSV(Mat InputFrame)
{
    cvtColor(InputFrame, OutputFrameHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

     //setColor(5);   //escolha da cor para filtrar

    //Threshold the image
    inRange(OutputFrameHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), OutputFinalFrameHSV);

    //morphological opening (remove small objects from the foreground)
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //morphological closing (fill small holes in the foreground)
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    return OutputFinalFrameHSV;
}

Mat CColor::Frame2HSV(Mat InputFrame, CColorsType cor)
{
    SetColor(cor);
    cvtColor(InputFrame, OutputFrameHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

     //SetColor(5);   //escolha da cor para filtrar

    inRange(OutputFrameHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), OutputFinalFrameHSV); //Threshold the image

                                                                                                  //morphological opening (remove small objects from the foreground)
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //morphological closing (fill small holes in the foreground)
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    return OutputFinalFrameHSV;
}

Mat CColor::Frame2HSVBoard(Mat InputFrame, int LH, int HH, int LS, int HS, int LV, int HV)
{
    cvtColor(InputFrame, OutputFrameHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

     //setColor(5);   //escolha da cor para filtrar

    inRange(OutputFrameHSV, Scalar(LH, LS, LV), Scalar(HH, HS, HV), OutputFinalFrameHSV); //Threshold the image

                                                                                                  //morphological opening (remove small objects from the foreground)
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //morphological closing (fill small holes in the foreground)
    dilate(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(OutputFinalFrameHSV, OutputFinalFrameHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    return OutputFinalFrameHSV;
}



void CColor::setiLowH(int position)
{
    this->iLowH = position;
}

void CColor::setHighH(int position)
{
    this->iHighH = position;
}

int CColor::getiLowH()
{
    return iLowH;
}

int CColor::getiHighH()
{
    return iHighH;
}

void CColor::setiLowS(int position)
{
    this->iLowS = position;
}

void CColor::setHighS(int position)
{
    this->iHighS = position;
}

int CColor::getiLowS()
{
    return iLowS;
}

int CColor::getiHighS()
{
    return iHighS;
}

void CColor::setiLowV(int position)
{
    this->iLowV = position;
}

void CColor::setHighV(int position)
{
    this->iHighV = position;
}

int CColor::getiLowV()
{
    return iLowV;
}

int CColor::getiHighV()
{
    return iHighV;
}


