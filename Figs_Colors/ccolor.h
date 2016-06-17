#ifndef CCOLOR_H
#define CCOLOR_H

#include "cposcenter.h"
#include "cfigure.h"



class CColor
{
    public:
        CColor();

        void set_imgSharp(Mat sharp);
        Mat get_imgSharp();

        ///Colors 1st Level
        void setALLBoardColorPosition();
        Mat setColorPosition();

        QVector<CColorsType> getCorBoard_CorPlaced();
        void setMessage2Robot(bool right, CColorsType corBoard, CColorsType corPlaced);
        QString getMessage2Robot();
        QString enum2QString(CColorsType colorType);

        ///Colors 2nd Level
        void newRandomColor(int pos);
        CColorsType getColorAsked();
        CColorsType randomColor(int pos);
         void randomQVector();

        QString printAskColor(CColorsType cor);


        QVector<CColorsType> getCorAsked_CorPlaced(CColorsType colorAsked);
        QString CheckColor(CColorsType cor);
        bool existColor(Mat imgCnny);



        void SetColor(CColorsType opc);
        Mat Frame2HSV(Mat InputFrame);
        Mat Frame2HSV(Mat InputFrame, CColorsType opc);
        Mat Frame2HSVBoard(Mat InputFrame, int LH, int HH, int LS, int HS, int LV, int HV);


        void setiLowH(int position);
        int getiLowH();

        void setHighH(int position);
        int getiHighH();

        void setiLowS(int position);
        int getiLowS();

        void setHighS(int position);
        int getiHighS();

        void setiLowV(int position);
        int getiLowV();

        void setHighV(int position);
        int getiHighV();

    private:
        QVector<int> vAskColor;

        int redLowH, redHighH;
        int redLowS, redHighS;
        int redLowV, redHighV;

        int greenLowH, greenHighH;
        int greenLowS, greenHighS;
        int greenLowV, greenHighV;

        int blueLowH, blueHighH;
        int blueLowS, blueHighS;
        int blueLowV, blueHighV;

        int yellowLowH, yellowHighH;
        int yellowLowS, yellowHighS;
        int yellowLowV, yellowHighV;

        int blackLowH, blackHighH;
        int blackLowS, blackHighS;
        int blackLowV, blackHighV;

        int witeLowH, witeHighH;
        int witeLowS, witeHighS;
        int witeLowV, witeHighV;

        int notwiteLowH, notwiteHighH;
        int notwiteLowS, notwiteHighS;
        int notwiteLowV, notwiteHighV;

        int iLowH, iHighH;
        int iLowS, iHighS;
        int iLowV, iHighV;

        Mat OutputFrameHSV;
        Mat OutputFinalFrameHSV;


        ////////////Figures e Colors////////////
        CFigure fig;
        CColorsType colorPlaced; ///1st level
        CColorsType colorAsked; ///2nd level
        CColorsType colorType;

        CPosCenter poscenter;

        Mat imgSharp;
        Mat drawingContours;

        Mat imgFHSV;
        Mat imgFHSVBoard;
        Mat imgFComper;
        Mat imgCanny;

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        vector<Point> approx;

        QString message2Robot;   ///Mensagem para o Robot "Right/Wrong;FigBoard;FigPlaced"
};


#endif // CCOLOR_H
