#include "cfigure.h"

CFigure::CFigure()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    this->figType = CFigsType::NONE;
    this->figPlaced = CFigsType::NONE;
    this->figAsked = CFigsType::NONE;
    this->figBoard = CFigsType::NONE;

    randomQVector();

    this->message2Robot = "";

    squareCount = 0;
    triangleCount = 0;
    circleCount = 0;
    rectangleCount = 0;
    pentagonCount = 0;

    this->area = 0;
    this->raio = 0;

    this->COUNT = 10;
}


void CFigure::clearCounts()
{
    squareCount = 0;
    triangleCount = 0;
    circleCount = 0;
    rectangleCount = 0;
    pentagonCount = 0;
}


///***************************************************************
///          RETURN THE FIGURE REQUESTED AND PLACED ON THE BOARD
///          QVector<CFigsType>() << FigAsked  << Fig placed on the board
/// **************************************************************/
QVector<CFigsType> CFigure::getFigAsked_FigPlaced(Mat imgCanny)
{
    for (size_t i = 0; i < contours.size(); i++)
        {
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //

            if(fabs(contourArea(approx)) > 1000) //este if não deve ser necessario
            {
                //drawContours(drawingContours, contours, (int)i, Scalar(255, 255, 255), 2, /*CV_AA*/8, hierarchy, 0, Point());

                if (approx.size() == 3) ///TRIANGLE
                {
                    triangleCount++;
                    if(triangleCount > COUNT)
                    {
                        if( figAsked == CFigsType::TRIANGLE )  ///Right Answer
                        {
                            setMessage2Robot(true, figAsked, CFigsType::TRIANGLE);
                            return QVector<CFigsType>() << figAsked << CFigsType::TRIANGLE;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figBoard, CFigsType::TRIANGLE);
                            return QVector<CFigsType>() << figBoard << CFigsType::TRIANGLE;
                        }
                    }
                }
                else  if (approx.size() == 4)  ///POLINOMIOS
                {
                    if( isSquare(approx))   ///SQUARE
                    {
                        squareCount++;
                        if(squareCount > COUNT)
                        {
                            if( figAsked == CFigsType::SQUARE )  ///Right Answer
                            {
                                setMessage2Robot(true, figAsked, CFigsType::SQUARE);
                                return QVector<CFigsType>() << figAsked << CFigsType::SQUARE;
                            }
                            else   ///Wrong Answer
                            {
                                setMessage2Robot(false, figAsked, CFigsType::SQUARE);
                                return QVector<CFigsType>() << figAsked << CFigsType::SQUARE;
                            }
                        }
                    }
                    else if(!isSquare(approx))  ///RECTANGLE
                    {
                        rectangleCount++;
                        if(rectangleCount > COUNT)
                        {
                            if( figAsked == CFigsType::RECTANGLE  )  ///Right Answer
                            {
                                setMessage2Robot(true, figAsked, CFigsType::RECTANGLE);
                                return QVector<CFigsType>() << figAsked << CFigsType::RECTANGLE;
                            }
                            else   ///Wrong Answer
                            {
                                setMessage2Robot(false, figAsked, CFigsType::RECTANGLE);
                                return QVector<CFigsType>() << figAsked << CFigsType::RECTANGLE;
                            }
                        }
                    }
                }
                else if (approx.size() == 5)   ///PENTAGON
                {
                    pentagonCount++;
                    if(pentagonCount > COUNT)
                    {
                        if( figAsked == CFigsType::PENTAGON  )  ///Right Answer
                        {
                            setMessage2Robot(true, figAsked, CFigsType::PENTAGON);
                            return QVector<CFigsType>() << figAsked << CFigsType::PENTAGON;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figAsked, CFigsType::PENTAGON);
                            return QVector<CFigsType>() << figAsked << CFigsType::PENTAGON;
                        }
                    }
                }
                else  ///CIRCLE
                {
                    area = contourArea(contours[i]); // calcula o tamanho da area do circulo atravez dos contornos
                    r = boundingRect(contours[i]); //captura uma reta, que serve de diametro do circulo
                    raio = r.width / 2; // calcula o raio atravez da recta anterior
                    //verifica se a area obtida pelos contornos é aproximada mente igual à area obtida pelo raio.
                    if (abs(1 - ((double)r.width / r.height)) <= 0.15 && abs(1 - (area / (CV_PI * pow(raio, 2)))) <= 0.15)
                    {
                        if( figAsked == CFigsType::CIRCLE )  ///Right Answer
                        {
                            setMessage2Robot(true, figAsked, CFigsType::CIRCLE);
                            return QVector<CFigsType>() << figAsked << CFigsType::CIRCLE;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figAsked, CFigsType::CIRCLE);
                            return QVector<CFigsType>() << figAsked << CFigsType::CIRCLE;
                        }
                    }
                }

            }
        }
        return QVector<CFigsType>() << CFigsType::NONE  << CFigsType::NONE;  ///REVER
}


QString CFigure::enum2QString(CFigsType figType)
{
    switch(figType)
    {
    case CFigsType::SQUARE:
        return "SQUARE";
        break;

    case CFigsType::TRIANGLE:
        return "TRIANGLE";
        break;

    case CFigsType::CIRCLE:
        return "CIRCLE";
        break;

    case CFigsType::RECTANGLE:
        return "RECTANGLE";
        break;

    case CFigsType::PENTAGON:
        return "PENTAGON";
        break;

    default:
        return "";
        break;
    }
}

void CFigure::setMessage2Robot(bool right, CFigsType figBoard, CFigsType figPlaced)
{
    QString sFigBoard = enum2QString(figBoard);
    QString sFigPlaced = enum2QString(figPlaced);

    if(right)
    {
        this->message2Robot = "R;" + sFigBoard + ';' + sFigPlaced;
    }
    else
    {
        this->message2Robot = "W;" + sFigBoard + ';' + sFigPlaced;
    }
}

QString CFigure::getMessage2Robot()
{
    return this->message2Robot;
}

void CFigure::newRandomFig(int pos)
{
    this->figAsked = randomFig(pos);
}

CFigsType CFigure::randomFig(int pos)
{
    switch(vAskFig[pos])
    {
    case 1:
        return CFigsType::CIRCLE;
        break;
    case 2:
        return CFigsType::PENTAGON;
        break;
    case 3:
        return CFigsType::RECTANGLE;
        break;
    case 4:
        return CFigsType::SQUARE;
        break;
    default:
        return CFigsType::TRIANGLE;
        break;
    }
}

void CFigure::randomQVector()
{
    switch(qrand() % ((7 +1) - 1) + 1)
    {
    case 1:
        this->vAskFig = QVector<int>() << 1 << 2 << 3 << 4 << 5;
        break;
    case 2:
        this->vAskFig = QVector<int>() << 1 << 3 << 5 << 2 << 4;
        break;
    case 3:
        this->vAskFig = QVector<int>() << 5 << 1 << 4 << 2 << 3;
        break;
    case 4:
        this->vAskFig = QVector<int>() << 2 << 4 << 1 << 3 << 5;
        break;
    case 5:
        this->vAskFig = QVector<int>() << 3 << 1 << 4 << 2 << 5;
        break;
    case 6:
        this->vAskFig = QVector<int>() << 4 << 2 << 3 << 5 << 1;
        break;
    default:
        this->vAskFig = QVector<int>() << 2 << 3 << 5 << 4 << 1;
        break;
    }
}

QString CFigure::printAskFigure(CFigsType fig)
{
    switch (fig)
    {
    case CFigsType::TRIANGLE:
        return "TRIANGLE";
        break;
    case CFigsType::SQUARE:
        return "SQUARE";
        break;
    case CFigsType::CIRCLE:
        return "CIRCLE";
        break;
    case CFigsType::PENTAGON:
        return "PENTAGON";
        break;
    case CFigsType::RECTANGLE:
        return "RECTANGLE";
        break;
    default:
        return "";
        break;
    }
}

///
/// \brief CFigure::existFigure
/// \param imgCanny
/// \return
///
bool CFigure::existFigure(Mat imgCanny)
{
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for (size_t i = 0; i< contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000) //este if não deve ser necessario
        {
            if (approx.size() == 3) {                     ///TRIANGLE
                return true;
            }

            else  if (approx.size() == 4) {                 ///POLINOMIOS
                if( isSquare(approx) ) {                     ///SQUARE
                    return true;
                }

                else if(!isSquare(approx)) {                     ///RECTANGLE
                    return true;
                }
            }

            else if (approx.size() == 5) {                     ///PENTAGON
                return true;
            }

            else {                      ///CIRCLE
                area = contourArea(contours[i]); // saca o tamanho da area do circulo atravez dos contornos
                r = boundingRect(contours[i]); //captura uma reta, que serve de diametro do circulo
                raio = r.width / 2; // calcula o raio atravez da recta anterior
                //verifica se a area obtida pelos contornos é aproximada mente igual à area obtida pelo raio.
                if (abs(1 - ((double)r.width / r.height)) <= 0.15
                        && abs(1 - (area / (CV_PI * pow(raio, 2)))) <= 0.15) {
                    return true;
                }
            }
        }

    }
    return false;
}

CFigsType CFigure::getFigAsked()
{
    return this->figAsked;
}



void CFigure::Set_imgSharp(Mat sharp)
{
    this->imgSharp = sharp;
}

Mat CFigure::Get_imgSharp()
{
    return imgSharp;
}

Mat CFigure::drawFigureContorns(Mat imgCanny)
{
    findContours(imgCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    drawingContours = Mat::zeros(imgCanny.size(), CV_8UC3);
    for (size_t i = 0; i< contours.size(); i++) {
        Scalar color = CV_RGB(255, 255, 255);

        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000)
        {
            //Scalar color = Scalar(rng.uniform(20, 255), rng.uniform(20, 255), rng.uniform(20, 255));
            //talvez mudar isto para dentro dos if's que assim só deseha as figuras geometricas
            ///o drawContours tem de imprimir somente o contorno e não uma linha grande
            //drawContours(drawingContours, contours, (int)i, color, 2, CV_AA, hierarchy, 0, Point());///se retirar daqui isto tem de ficar

            // verifica se é um triangulo
            if (approx.size() == 3) {                     ///TRIANGLE
                setContourRectangle(imgSharp, contours[i]);
                posCenter.ChooseSaveFigureCenter(CFigsType::TRIANGLE, contours[i]);

                //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }

            else  if (approx.size() == 4) {             ///POLINOMIOS
                // um if para diferenciar o quadrado do rectangulo
                if(isSquare(approx)) {                     ///SQUARE
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveFigureCenter(CFigsType::SQUARE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0); //depois preciso de retornar o valor central das peças para poder desenhar na figura original
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }

                else if(!isSquare(approx)) {                     ///RECTANGLE
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveFigureCenter(CFigsType::RECTANGLE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }

                else ; // é um polinomio qualquer
            }

            else if (approx.size() == 5) {                     ///PENTAGON
                //é melhor por ainda uma verificação para ver se todos os lados, ou dois a dois são mais ao menos iguais.
                setContourRectangle(imgSharp, contours[i]);
                posCenter.ChooseSaveFigureCenter(CFigsType::PENTAGON, contours[i]);

                //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }

            else {                      ///CIRCLE
                area = contourArea(contours[i]); // saca o tamanho da area do circulo atravez dos contornos
                r = boundingRect(contours[i]); //captura uma reta, que serve de diametro do circulo
                raio = r.width / 2; // calcula o raio atravez da recta anterior
                //verifica se a area obtida pelos contornos é aproximada mente igual à area obtida pelo raio.
                if (abs(1 - ((double)r.width / r.height)) <= 0.15 && abs(1 - (area / (CV_PI * pow(raio, 2)))) <= 0.15) {
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveFigureCenter(CFigsType::CIRCLE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }
                else ;
            }
        }
            else {}
    }

//    imshow("Drawing Contours", drawingContours);
    return drawingContours;
}

void CFigure::SetBoardFigurePosition(Mat imgInitialCanny)
{
    ///verificar se já tem a posição de todas as figuras
    findContours(imgInitialCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    drawingContours = Mat::zeros(imgInitialCanny.size(), CV_8UC3);
    for (size_t i = 0; i< contours.size(); i++) {
        Scalar color = CV_RGB(255, 255, 255);

        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //
        if(fabs(contourArea(approx)) > 1000)
        {
            //Scalar color = Scalar(rng.uniform(20, 255), rng.uniform(20, 255), rng.uniform(20, 255));
            //talvez mudar isto para dentro dos if's que assim só deseha as figuras geometricas
            ///o drawContours tem de imprimir somente o contorno e não uma linha grande
            //drawContours(drawingContours, contours, (int)i, color, 2, CV_AA, hierarchy, 0, Point());///se retirar daqui isto tem de ficar

            // verifica se é um triangulo
            if (approx.size() == 3) {                     ///TRIANGLE
                setContourRectangle(imgSharp, contours[i]);
                posCenter.ChooseSaveBoardFigureCenter(CFigsType::TRIANGLE, contours[i]);

                //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }

            else  if (approx.size() == 4) {             ///POLINOMIOS
                // um if para diferenciar o quadrado do rectangulo
                if(isSquare(approx)) {                     ///SQUARE
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveBoardFigureCenter(CFigsType::SQUARE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0); //depois preciso de retornar o valor central das peças para poder desenhar na figura original
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }

                else if(!isSquare(approx)) {                     ///RECTANGLE
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveBoardFigureCenter(CFigsType::RECTANGLE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }

                else ; // é um polinomio qualquer
            }

            else if (approx.size() == 5) {                     ///PENTAGON
                //é melhor por ainda uma verificação para ver se todos os lados, ou dois a dois são mais ao menos iguais.
                setContourRectangle(imgSharp, contours[i]);
                posCenter.ChooseSaveBoardFigureCenter(CFigsType::PENTAGON, contours[i]);

                //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
            }

            else {                      ///CIRCLE
                area = contourArea(contours[i]); // saca o tamanho da area do circulo atravez dos contornos
                r = boundingRect(contours[i]); //captura uma reta, que serve de diametro do circulo
                raio = r.width / 2; // calcula o raio atravez da recta anterior
                //verifica se a area obtida pelos contornos é aproximada mente igual à area obtida pelo raio.
                if (abs(1 - ((double)r.width / r.height)) <= 0.15 && abs(1 - (area / (CV_PI * pow(raio, 2)))) <= 0.15) {
                    setContourRectangle(imgSharp, contours[i]);
                    posCenter.ChooseSaveBoardFigureCenter(CFigsType::CIRCLE, contours[i]);

                    //circle(imgSharp, mc, 4, Scalar(0, 0, 255), 1, 8, 0);
                    drawContours(drawingContours, contours, (int)i, color, 2, /*CV_AA*/8, hierarchy, 0, Point());
                }
                else ;
            }
        }
            else {}
    }

    ///CONTORNOS
//    imshow("Drawing Contours", drawingContours);
}

bool CFigure::isSquare(vector<Point> approx)
{
    double module[3];
    module[0] = sqrt( (approx[0].x - approx[1].x)*(approx[0].x - approx[1].x) + (approx[0].y - approx[1].y)*(approx[0].y - approx[1].y) );
    module[1] = sqrt( (approx[0].x - approx[2].x)*(approx[0].x - approx[2].x) + (approx[0].y - approx[2].y)*(approx[0].y - approx[2].y) );
    module[2] = sqrt( (approx[0].x - approx[3].x)*(approx[0].x - approx[3].x) + (approx[0].y - approx[3].y)*(approx[0].y - approx[3].y) );

    //verificar qual é o maior para saber qual destes tamanhos é a diagunal
    for(int i = 0; i < 3; i++)
    {
        int j;
        if( i == 2 )
            j = 0;
        else
            j = i;

        if(module[j] > module[j+1]) {
            double aux = module[j];
            module[j] = module[j+1];
            module[j+1] = aux;
        }
        else ;
    }
//    bool c1, c2;
//    c1 = sqrt(module[0]*module[0] + module[1]*module[1]) - module[1]*sqrt(2) <= 5;
//    c2 = abs( module[2] - (module[0]*sqrt(2) ) ) <= 5;

    if( abs (  sqrt(module[0]*module[0] + module[1]*module[1]) - module[1]*sqrt(2)   ) <= 17   &&
            abs( module[2] - (module[1]*sqrt(2) ) ) <= 17  ){
        return true;
    }
    else
        return false;
}

void CFigure::setContourRectangle(Mat &im, vector<Point> &contour)
{
    rRectangle = boundingRect(contour);
    rectangle(im, rRectangle, Scalar(0, 0, 0), 1, 8, 0); //rectangulo grande do tamanho da figura geometrica capturada
}

void CFigure::setContourRectangle(Mat &im, vector<Point> &contour, Scalar corRectangle)
{
    rRectangle = boundingRect(contour);
    rectangle(im, rRectangle, corRectangle, 2, 8, 0); //rectangulo grande do tamanho da figura geometrica capturada
}


///***************************************************************
///          RETURN THE BOARD FIGURE AND PLACED ON THE BOARD
///                 QVector<CFigsType>() << figBoard  << figPlaced
/// **************************************************************/
QVector<CFigsType> CFigure::getFigBoard_FigPlaced(Mat imgCanny)
{
//    drawingContours = Mat::zeros(imgCanny.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);// 5, true); //

        if(fabs(contourArea(approx)) > 1000) //este if não deve ser necessario
        {
//            drawContours(drawingContours, contours, (int)i, Scalar(255, 255, 255), 2, /*CV_AA*/8, hierarchy, 0, Point());

            if (approx.size() == 3)    ///TRIANGLE
            {
                triangleCount++;
                if(triangleCount > COUNT)
                {
                    CFigsType figBoard = posCenter.getBoardFig(CFigsType::TRIANGLE);

                    if( figBoard == CFigsType::TRIANGLE )  ///Right Answer
                    {
                        setMessage2Robot(true, figBoard, CFigsType::TRIANGLE);
                        return QVector<CFigsType>() << figBoard << CFigsType::TRIANGLE;
                    }
                    else   ///Wrong Answer
                    {
                        setMessage2Robot(false, figBoard, CFigsType::TRIANGLE);
                        return QVector<CFigsType>() << figBoard << CFigsType::TRIANGLE;
                    }
                }
            }
            else  if (approx.size() == 4)     ///POLINOMIOS
            {
                if( isSquare(approx) )     ///SQUARE
                {
                    squareCount++;
                    if(squareCount > COUNT)
                    {
                        CFigsType figBoard = posCenter.getBoardFig(CFigsType::SQUARE);

                        if( figBoard == CFigsType::SQUARE )  ///Right Answer
                        {
                            setMessage2Robot(true, figBoard, CFigsType::SQUARE);
                            return QVector<CFigsType>() << figBoard << CFigsType::SQUARE;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figBoard, CFigsType::SQUARE);
                            return QVector<CFigsType>() << figBoard << CFigsType::SQUARE;
                        }
                    }
                }
                else if(!isSquare(approx))     ///RECTANGLE
                {
                    rectangleCount++;
                    if(rectangleCount > COUNT)
                    {
                        CFigsType figBoard = posCenter.getBoardFig(CFigsType::RECTANGLE);

                        if( figBoard == CFigsType::RECTANGLE  )  ///Right Answer
                        {
                            setMessage2Robot(true, figBoard, CFigsType::RECTANGLE);
                            return QVector<CFigsType>() << figBoard << CFigsType::RECTANGLE;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figBoard, CFigsType::RECTANGLE);
                            return QVector<CFigsType>() << figBoard << CFigsType::RECTANGLE;
                        }
                    }
                }
            }
            else if (approx.size() == 5)    ///PENTAGON
            {
                pentagonCount++;
                if(pentagonCount > COUNT)
                {
                    CFigsType figBoard = posCenter.getBoardFig(CFigsType::PENTAGON);

                    if( figBoard == CFigsType::PENTAGON  )  ///Right Answer
                    {
                        setMessage2Robot(true, figBoard, CFigsType::PENTAGON);
                        return QVector<CFigsType>() << figBoard << CFigsType::PENTAGON;
                    }
                    else   ///Wrong Answer
                    {
                        setMessage2Robot(false, figBoard, CFigsType::PENTAGON);
                        return QVector<CFigsType>() << figBoard << CFigsType::PENTAGON;
                    }
                }
            }
            else    ///CIRCLE
            {
                area = contourArea(contours[i]); // calcula o tamanho da area do circulo atravez dos contornos
                r = boundingRect(contours[i]); //captura uma reta, que serve de diametro do circulo
                raio = r.width / 2; // calcula o raio atravez da recta anterior

                //verifica se a area obtida pelos contornos é aproximadamente igual à area obtida pelo raio.
                if (abs(1 - ((double)r.width / r.height)) <= 0.15 && abs(1 - (area / (CV_PI * pow(raio, 2)))) <= 0.15)
                {
                    circleCount++;
                    if(circleCount  > COUNT)
                    {
                        CFigsType figBoard = posCenter.getBoardFig(CFigsType::CIRCLE);

                        if( figBoard == CFigsType::CIRCLE )  ///Right Answer
                        {
                            setMessage2Robot(true, figBoard, CFigsType::CIRCLE);
                            return QVector<CFigsType>() << figBoard << CFigsType::CIRCLE;
                        }
                        else   ///Wrong Answer
                        {
                            setMessage2Robot(false, figBoard, CFigsType::CIRCLE);
                            return QVector<CFigsType>() << figBoard << CFigsType::CIRCLE;
                        }
                    }
                }
            }
        }
    }
    return QVector<CFigsType>() << CFigsType::NONE  << CFigsType::NONE;  ///REVER
}
