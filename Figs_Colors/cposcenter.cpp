#include "cposcenter.h"

CPosCenter::CPosCenter()
{
}

void CPosCenter::ChooseSaveBoardFigureCenter(CFigsType fig, vector<Point> contours)
{
    switch (fig) {
    case CFigsType::SQUARE:
        mcBoardSquare = CenterCalculation(contours);
        break;
    case CFigsType::RECTANGLE:
        mcBoardRectangle = CenterCalculation(contours);
        break;
    case CFigsType::TRIANGLE:
        mcBoardTriangle = CenterCalculation(contours);
        break;
    case CFigsType::CIRCLE:
        mcBoardCircle = CenterCalculation(contours);
        break;
    case CFigsType::PENTAGON:
        mcBoardPentagon = CenterCalculation(contours);
        break;
    default:
        //Zeca say: "ERROR !&?!.$#.. I'm gona explode!";
        break;
    }
}

void CPosCenter::ChooseSaveFigureCenter(CFigsType fig, vector<Point> contours)
{
    switch (fig) {
    case CFigsType::SQUARE:
        mcSquare = CenterCalculation(contours);
        break;
    case CFigsType::RECTANGLE:
        mcRectangle = CenterCalculation(contours);
        break;
    case CFigsType::TRIANGLE:
        mcTriangle = CenterCalculation(contours);
        break;
    case CFigsType::CIRCLE:
        mcCircle = CenterCalculation(contours);
        break;
    case CFigsType::PENTAGON:
        mcPentagon = CenterCalculation(contours);
        break;
    default:
        //Zeca say: "ERROR !$?#!.&.. I'm gona explode!";
        break;
    }
}


CFigsType CPosCenter::getBoardFig(CFigsType figPlaced)
{
    ///recebe a figura que foi colocada em cima do tabuleiro
    /// retorna a figura debaixo da fig colocada
    switch (figPlaced)
    {
    case CFigsType::SQUARE:
        if( RightFigurePosition(mcBoardSquare, mcSquare) )
            return CFigsType::SQUARE;
        else if( RightFigurePosition(mcBoardTriangle, mcSquare) )
                return CFigsType::TRIANGLE;  ///FOI COLOCADO UM SQUARE NO SITIO DO TRIANGLE
        else if( RightFigurePosition(mcBoardRectangle, mcSquare) )
                return CFigsType::RECTANGLE;
        else if( RightFigurePosition(mcBoardCircle, mcSquare) )
                return CFigsType::CIRCLE;
        else if( RightFigurePosition(mcBoardPentagon, mcSquare) )
                return CFigsType::PENTAGON;
        //provavelmente vai precisar aqui de um else para o caso de não estar perto de nenhuma outra figura
        break;

    case CFigsType::RECTANGLE:
        if( RightFigurePosition(mcBoardRectangle, mcRectangle) )
            return CFigsType::RECTANGLE;
        else if( RightFigurePosition(mcBoardTriangle, mcRectangle) )
                return CFigsType::TRIANGLE;
        else if( RightFigurePosition(mcBoardSquare, mcRectangle) )
                return CFigsType::SQUARE;
        else if( RightFigurePosition(mcBoardCircle, mcRectangle) )
                return CFigsType::CIRCLE;
        else if( RightFigurePosition(mcBoardPentagon, mcRectangle) )
                return CFigsType::PENTAGON;
        break;

    case CFigsType::TRIANGLE:
        if( RightFigurePosition(mcBoardTriangle, mcTriangle) )
            return CFigsType::TRIANGLE;
        else if( RightFigurePosition(mcBoardRectangle, mcTriangle) )
                return CFigsType::RECTANGLE;
        else if( RightFigurePosition(mcBoardSquare, mcTriangle) )
                return CFigsType::SQUARE;
        else if( RightFigurePosition(mcBoardCircle, mcTriangle) )
                return CFigsType::CIRCLE;
        else if( RightFigurePosition(mcBoardPentagon, mcTriangle) )
                return CFigsType::PENTAGON;
        break;

    case CFigsType::CIRCLE:
       if( RightFigurePosition(mcBoardCircle, mcCircle) )
            return CFigsType::CIRCLE;
       else if( RightFigurePosition(mcBoardTriangle, mcCircle) )
               return CFigsType::TRIANGLE;
       else if( RightFigurePosition(mcBoardSquare, mcCircle) )
               return CFigsType::SQUARE;
       else if( RightFigurePosition(mcBoardRectangle, mcCircle) )
               return CFigsType::RECTANGLE;
       else if( RightFigurePosition(mcBoardPentagon, mcCircle) )
               return CFigsType::PENTAGON;
        break;

    case CFigsType::PENTAGON:
        if( RightFigurePosition(mcBoardPentagon, mcPentagon) )
                return CFigsType::PENTAGON;
        else if( RightFigurePosition(mcBoardTriangle, mcPentagon) )
                return CFigsType::TRIANGLE;
        else if( RightFigurePosition(mcBoardSquare, mcPentagon) )
                return CFigsType::SQUARE;
        else if( RightFigurePosition(mcBoardCircle, mcPentagon) )
                return CFigsType::CIRCLE;
        else if( RightFigurePosition(mcBoardRectangle, mcPentagon) )
                return CFigsType::RECTANGLE;
        break;

    default:
        return CFigsType::NONE;
        break;
    }
    return CFigsType::NONE;
}

bool CPosCenter::RightFigurePosition(Point2d mcBoardPosition, Point2d mcPosition)
{
    double x = (mcBoardPosition.x - mcPosition.x) ;
    double y = (mcBoardPosition.y - mcPosition.y);
    double module = sqrt( x*x + y*y );
    //65 é o valor maximo em modulo da distancia admissivel entre os pontos centras mcBoardPosition e mcPosition
    if(module < 65)
        return true;
    else
        return false;
}



Point2d CPosCenter::CenterCalculation(vector<Point> contours)
{
    ///fazer os circulos centrais
    Moments mu = moments(contours, false);
    Point2d mc = Point2d( mu.m10/mu.m00 , mu.m01/mu.m00);//valores centrais do quadrdo
    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0); //só para dar feed back
    return mc;
}



void CPosCenter::ChooseSaveBoardColorCenter(CColorsType cor, vector<Point> contours)
{
    switch (cor) {
    case CColorsType::RED:
        mcBoardRed = CenterCalculation(contours);
        break;
    case CColorsType::GREEN:
        mcBoardGreen = CenterCalculation(contours);
        break;
    case CColorsType::BLUE:
        mcBoardBlue = CenterCalculation(contours);
        break;
    case CColorsType::YELLOW:
        mcBoardYellow = CenterCalculation(contours);
        break;
    case CColorsType::BLACK:
        mcBoardBlack = CenterCalculation(contours);
        break;
    default:
        //Zeca say: "ERROR !&?!.$#.. I'm gona explode!";
        break;
    }
}

void CPosCenter::ChooseSaveColorCenter(CColorsType cor, vector<Point> contours)
{
    double x = CenterCalculation(contours).x;
    double y = CenterCalculation(contours).y;
    double condition;

    switch (cor) {
        case CColorsType::RED:
            condition = sqrt( (mcBoardRed.x - x)*(mcBoardRed.x - x) + (mcBoardRed.y - y)*(mcBoardRed.y - y)  );
            if( condition < 65)
                mcRed = Point2d(0, 0);//não faz nada pois este é o contorno correspondente à cor do tabuleiro
            else
                mcRed = CenterCalculation(contours);
            break;

        case CColorsType::GREEN:
            condition = sqrt( (mcBoardGreen.x - x)*(mcBoardGreen.x - x) + (mcBoardGreen.y - y)*(mcBoardGreen.y - y)  );
            if( condition < 65)
                mcGreen = Point2d(0, 0);//não faz nada pois este é o contorno correspondente à cor do tabuleiro
            else
                mcGreen = CenterCalculation(contours);
            break;
        case CColorsType::BLUE:
            condition = sqrt( (mcBoardBlue.x - x)*(mcBoardBlue.x - x) + (mcBoardBlue.y - y)*(mcBoardBlue.y - y) ) ;
            if( condition < 65)
                mcBlue = Point2d(0, 0);//não faz nada pois este é o contorno correspondente à cor do tabuleiro
            else
                mcBlue = CenterCalculation(contours);
            break;

        case CColorsType::YELLOW:
            condition = sqrt( (mcBoardYellow.x - x)*(mcBoardYellow.x - x) + (mcBoardYellow.y - y)*(mcBoardYellow.y - y) ) ;
            if( condition < 65)
                mcYellow = Point2d(0, 0);//não faz nada pois este é o contorno correspondente à cor do tabuleiro
            else
                mcYellow = CenterCalculation(contours);
            break;

        case CColorsType::BLACK:
            condition = sqrt( (mcBoardBlack.x - x)*(mcBoardBlack.x - x) + (mcBoardBlack.y - y)*(mcBoardBlack.y - y) );
            if( condition < 65)
                mcBlack = Point2d(0, 0);//não faz nada pois este é o contorno correspondente à cor do tabuleiro
            else
                mcBlack = CenterCalculation(contours);
            break;

        default:
            //Zeca say: "ERROR !&?!.$#.. I'm gona explode!";
            break;
    }

}

CColorsType CPosCenter::getBoardColor(CColorsType corPlaced)
{
    switch (corPlaced) {
        case CColorsType::RED:
            if( RightColorPosition(mcBoardRed, mcRed) )
                return CColorsType::RED;
            else if( RightColorPosition(mcBoardBlue, mcRed) )
                    return CColorsType::BLUE;
            else if( RightColorPosition(mcBoardGreen, mcRed) )
                    return CColorsType::GREEN;
            else if( RightColorPosition(mcBoardYellow, mcRed) )
                    return CColorsType::YELLOW;
            else if( RightColorPosition(mcBoardBlack, mcRed) )
                    return CColorsType::BLACK;
            //provavelmente vai precisar aqui de um else para o caso de não estar perto de nenhuma outra figura
            break;

        case CColorsType::GREEN:
            if( RightColorPosition(mcBoardGreen, mcGreen) )
                return CColorsType::GREEN;
            else if( RightColorPosition(mcBoardBlue, mcGreen) )
                    return CColorsType::BLUE;
            else if( RightColorPosition(mcBoardRed, mcGreen) )
                    return CColorsType::RED;
            else if( RightColorPosition(mcBoardYellow, mcGreen) )
                    return CColorsType::YELLOW;
            else if( RightColorPosition(mcBoardBlack, mcGreen) )
                    return CColorsType::BLACK;

            break;

        case CColorsType::BLUE:
            if( RightColorPosition(mcBoardBlue, mcBlue) )
                return CColorsType::BLUE;
            else if( RightColorPosition(mcBoardGreen, mcBlue) )
                    return CColorsType::GREEN;
            else if( RightColorPosition(mcBoardRed, mcBlue) )
                    return CColorsType::RED;
            else if( RightColorPosition(mcBoardYellow, mcBlue) )
                    return CColorsType::YELLOW;
            else if( RightColorPosition(mcBoardBlack, mcBlue) )
                    return CColorsType::BLACK;

            break;

        case CColorsType::YELLOW:
           if( RightColorPosition(mcBoardYellow, mcYellow) )
                return CColorsType::YELLOW;
           else if( RightColorPosition(mcBoardBlue, mcYellow) )
                   return CColorsType::BLUE;
           else if( RightColorPosition(mcBoardRed, mcYellow) )
                   return CColorsType::RED;
           else if( RightColorPosition(mcBoardGreen, mcYellow) )
                   return CColorsType::GREEN;
           else if( RightColorPosition(mcBoardBlack, mcYellow) )
                   return CColorsType::BLACK;

            break;

        case CColorsType::BLACK:
            if( RightColorPosition(mcBoardBlack, mcBlack) )
                    return CColorsType::BLACK;
            else if( RightColorPosition(mcBoardBlue, mcBlack) )
                    return CColorsType::BLUE;
            else if( RightColorPosition(mcBoardRed, mcBlack) )
                    return CColorsType::RED;
            else if( RightColorPosition(mcBoardYellow, mcBlack) )
                    return CColorsType::YELLOW;
            else if( RightFigurePosition(mcBoardGreen, mcBlack) )
                    return CColorsType::GREEN;

            break;

        default:
            //Zeca say: "ERROR !$?#!.&.. I'm gona explode!";
            return CColorsType::NONE;
            break;
    }
    return CColorsType::NONE;
}

bool CPosCenter::RightColorPosition(Point2d mcBoardPosition, Point2d mcPosition)
{
    ///agora a posição correcta é longe da posição obtida do tabuleiro
    /// temos de arranjar outro metudo para calcular.
    double x = abs(mcBoardPosition.x - mcPosition.x) ;
    double y = abs(mcBoardPosition.y - mcPosition.y);
    double modulex = sqrt( x*x );
    double moduley = sqrt( y*y );


    //65 é o valor maximo em modulo da distancia admissivel entre os pontos centras mcBoardPosition e mcPosition
    if(moduley < 65 && modulex < ( 250 + 150) && modulex > ( 250 - 150) )
        return true;
    else
        return false;
}

