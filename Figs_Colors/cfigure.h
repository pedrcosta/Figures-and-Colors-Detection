#ifndef CFIGURES_H
#define CFIGURES_H

#include <QVector>
#include <QTime>
#include <QString>

#include "cposcenter.h"


class CFigure
{
    public:
        CFigure();

        ///Figures 1st Level///
        QVector<CFigsType> getFigBoard_FigPlaced(Mat imgCanny);
        void SetBoardFigurePosition(Mat imgInitialCanny);
        Mat drawFigureContorns(Mat imgCanny);
        void clearCounts();

        ///Figures 2nd Level///
        QVector<CFigsType> getFigAsked_FigPlaced(Mat imgCanny);
        CFigsType getBoardFig(Mat imgCanny);
        bool existFigure(Mat imgCanny);

        void newRandomFig(int pos);   ///Set a new random figure
        CFigsType getFigAsked();
        CFigsType randomFig(int pos);
        void randomQVector();
        ///Print label with the requested figure
        QString printAskFigure(CFigsType fig);
        ///Print a label with the requested and placed figure



        ///For 1st and 2nd Levels///
        void setMessage2Robot(bool  right, CFigsType figBoard_figAsked, CFigsType figPlaced);
        QString getMessage2Robot();

        QString enum2QString(CFigsType figType);
        bool isSquare(vector<Point> approx);

        void Set_imgSharp(Mat sharp);
        Mat Get_imgSharp();

        void setContourRectangle(Mat &im, vector<Point> &contour);
        void setContourRectangle(Mat &im, vector<Point> &contour, Scalar corRectangle);

    private:
        int COUNT;
        int squareCount;
        int triangleCount;
        int circleCount;
        int rectangleCount;
        int pentagonCount;

        QVector<int> vAskFig;

        QString message2Robot;   ///Mensagem para o Robot "Right/Wrong;FigBoard;FigPlaced"

        CFigsType figType;
        CFigsType figBoard;
        CFigsType figPlaced;  ///Figure placed on the board
        CFigsType figAsked;  ///Figure asked in the 2nd level
        CPosCenter posCenter; //class que dá a posição central

        Mat imgSharp;
        Mat drawingContours;
        RNG rng;//gerador de numeros aleatorios

       ////////////Para os contornos////////////
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        vector<Point> approx;

        //void setContourRectangle(Mat &im, vector<Point> &contour);
        Rect rRectangle;
        //->para detectar os circulos
        double area;
        Rect r;
        int raio;
        //fim
        //para obter as posiçoes centrais
        Moments mu;
        Point2f mc;
};

#endif // CFIGURES_H
