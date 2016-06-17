#ifndef CPOSCENTER_H
#define CPOSCENTER_H

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

#include "cfigstype.h"
#include "ccolorstype.h"


using namespace cv;
using namespace std;

class CPosCenter
{
    public:
    CPosCenter();
    ///to figures
    void ChooseSaveBoardFigureCenter(CFigsType fig, vector<Point> contours);
    void ChooseSaveFigureCenter(CFigsType fig, vector<Point> contours);
    CFigsType getBoardFig(CFigsType figPlaced);
    bool RightFigurePosition(Point2d mcBoardPosition, Point2d mcPosition);

    Point2d CenterCalculation(vector<Point> contours);

    ///to colors
    void ChooseSaveBoardColorCenter(CColorsType cor, vector<Point> contours);
    void ChooseSaveColorCenter(CColorsType cor, vector<Point> contours);
    CColorsType getBoardColor(CColorsType corPlaced);
    bool RightColorPosition(Point2d mcBoardPosition, Point2d mcPosition);

private:
    //para guardar as posiçoes centrais de cada peça
    Point2d mcTriangle, mcRectangle, mcSquare, mcCircle, mcPentagon;
    Point2d mcBoardTriangle, mcBoardRectangle, mcBoardSquare, mcBoardCircle, mcBoardPentagon;

    Point2d mcRed, mcGreen, mcBlue, mcYellow, mcBlack;
    Point2d mcBoardRed, mcBoardGreen, mcBoardBlue, mcBoardYellow, mcBoardBlack;
};

#endif // CPOSCENTER_H
