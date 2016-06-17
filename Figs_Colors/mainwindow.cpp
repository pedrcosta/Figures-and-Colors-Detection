#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cclient.h"
#include "cchild_info.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->run = false;
    this->waitNoFigure = false;
    this->newFigure = true;
    this->waitNoColor = false;
    this->newColor = true;
    this->countTimes = 0;

    this->waitStartF1 = true;
    this->waitStartF2 = true;
    this->waitStartC1 = true;
    this->waitStartC2 = true;

    setupTableViewChild();
    setupGraphBar();

    pClient = new CClient;
    pChild = new CChild_Info();
    pSession = new CSession();
    pPerformance = new CPerformance();
    pAnswers = new CAnswers();
    pFigure = new CFigure();
    pColor = new CColor();
    pPosCenter = new CPosCenter();

    pChild->loadChildtoTable(model2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTableViewChild()
{
    /// QStandardItemModel(int rows, int columns, QObject * parent = 0)
    model2 = new QStandardItemModel(0,6,this);
    ui->tableView_childs->setModel(model2);

    model2->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model2->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model2->setHeaderData(2, Qt::Horizontal, QObject::tr("Gender"));
    model2->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model2->setHeaderData(4, Qt::Horizontal, QObject::tr("TP"));
    model2->setHeaderData(5, Qt::Horizontal, QObject::tr("nSessions"));

    //ui->tableView->resizeColumnsToContents();

    ui->tableView_childs->setColumnWidth(0,30);
    ui->tableView_childs->setColumnWidth(1,120);
    ui->tableView_childs->setColumnWidth(2,50);
    ui->tableView_childs->setColumnWidth(3,40);
    ui->tableView_childs->setColumnWidth(4,40);
    ui->tableView_childs->setColumnWidth(5,60);
}

void MainWindow::setupGraphBar()
{
    ui->customPlot->xAxis->setRange(0.4, 5.9);
    ui->customPlot->yAxis->setRange(0,100);

    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);

    ui->customPlot->yAxis->setAutoTickStep(false);
    ui->customPlot->yAxis->setTickStep(10);

    ui->customPlot->xAxis->setLabel("Sessions");
    ui->customPlot->yAxis->setLabel("Answers");

    ui->customPlot->setBackground(QColor(50, 50, 50, 255));

//    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(50, 50, 50, 255));
    ui->customPlot->legend->setBorderPen(QColor(0, 0, 0));
    ui->customPlot->legend->setTextColor(QColor(255,255,255));

}

bool MainWindow::detectMoviment()
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    //Mat emptyImage = Mat::zeros(imgCanny.size(), CV_8UC3);

    if( foregroundMask.empty() ){
        foregroundMask.create(imgFrame.size(), imgFrame.type());
    }

//    bg_model->apply(imgFrame, foregroundMask, true ? -1 : 0);
    bg_model->apply(imgFrame, foregroundMask, 0.3);
    erode(foregroundMask, foregroundMask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(foregroundMask, foregroundMask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    GaussianBlur(foregroundMask, foregroundMask, Size(11,11), 3.5,3.5);
    threshold(foregroundMask, foregroundMask, 10,255,THRESH_BINARY);

    foregroundImg = Scalar::all(0);
    imgFrame.copyTo(foregroundImg, foregroundMask);
//    imshow("foreground mask", foregroundMask);
//    imshow("foreground image", foregroundImg);

    bg_model->getBackgroundImage(backgroundImage);
    if(!backgroundImage .empty()){
//        imshow("mean background image", backgroundImage );
        //int key5 = waitKey(40); ///por alguma razao sem isto, o cenas não funciona
    }

    findContours(foregroundMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    if( contours.size() == 0 )
        return false;

    return true; ///detetou movimento
}


void MainWindow::exitProgram()
{
    if(qtimer->isActive())
        qtimer->stop();  // if timer is running, stop timer
    QApplication::quit();  // and exit program
}

void MainWindow::processFrameAndUpdateGUI()
{
    ImageProcessing();

    //////////////////////////////////////////Cores//////////////////////////////////////////////////////////////////////
    //aqui talvez seja necessario os valores do branco, para depois fazer o and
    imgFHSVBoard = pColor->Frame2HSVBoard(imgSharp, 0, 180, 35, 255, 0, 255);

//    imshow("Inicial Canny", imgCanny);
    SetHSV();//para poder escolhes os valores de HSV para as respectivas cores.
    imgFHSV = pColor->Frame2HSV(imgSharp);//tem de ser imagem a cores

    bitwise_and(imgFHSVBoard, imgFHSV, imgFComper); //somar a figura imgFHSVBoard com imgFHSV para obter só a cor
    //threshold(imgFComper, imgFComper, 80, 255, THRESH_BINARY);
    //erode(imgFComper, imgFComper, getStructuringElement(MORPH_RECT, Size(3,3)));

    ///////////////////////////////////////Contornos///////////////////////////////////////////////////////////////////

    /////////Figuras Nivel 1/////////
    if(ui->radioButton_f1->isChecked() && !waitStartF1)
    {
        if(run && countTimes < 5) /// If the activity is runnig
        {
//            Mat Level1 = pColor->Frame2HSVBoard(imgSharp, 15, 47, 40, 255, 100, 255); //Yellow color
            Mat Level1 = pColor->Frame2HSV(imgSharp, CColorsType::BLUE); //Blue color
            Canny(Level1, imgCanny, 180, 120); // get Canny edges
            pFigure->Set_imgSharp(imgSharp); ///VERFICAR SE INICIALIZA OS CONTADORES A ZERO
            imgCanny = pFigure->drawFigureContorns(imgCanny);  ///Calcula os centros das figuras do tabuleiro vazio

            QTime startTime = QTime::currentTime();

            if(!detectMoviment())
            {
                QVector<CFigsType> figBoard_figPlaced = pFigure->getFigBoard_FigPlaced(imgCanny);

                //if(pFigure->getBoardFig(imgCanny) != CFigsType::NONE) ///When find 5 times the same figure
                if( figBoard_figPlaced[0] != CFigsType::NONE  && figBoard_figPlaced[1] != CFigsType::NONE && waitNoFigure == true)
                {
                    QTime endTime = QTime::currentTime();
                    pPerformance->right_or_wrongAnswer(figBoard_figPlaced);
                    pAnswers->saveAnswers(figBoard_figPlaced, startTime.msecsTo(endTime));

                    statusBar()->showMessage(pFigure->getMessage2Robot());
                    pClient->startTransfer(pFigure->getMessage2Robot());

                    this->countTimes++;
                    waitNoFigure = false;

                    delay(7);  ///While robot is playing an activity

                    do {
                        ImageProcessing();
                        showFramesWebcam();
                    } while(!detectMoviment());

                }
                else if((figBoard_figPlaced[0] == CFigsType::NONE || figBoard_figPlaced[1] == CFigsType::NONE ) && waitNoFigure == false)
                {
                    //delay(1);
                    waitNoFigure = true;
                    statusBar()->showMessage("No figure detected");
                }
            }
            if( countTimes >= 5)  ///End Activity
            {
                this->run = false;
                this->countTimes = 0;
                pFigure->clearCounts();
                pChild->stop_activity();
                statusBar()->showMessage("Activity Stoped", 3000);

                pSession->stopSession();
                pSession->saveSession(pChild->getChildCode());
                pPerformance->savePerformance(pChild->getChildCode(), pSession->getCodeSession(), pSession->getActivity());
                pClient->startTransfer("FIM\n");

                pChild->updateChildInfo(pChild->getChildCode());
                pChild->loadChildtoTable(model2);

                this->waitStartF1 = true;
                this->waitStartF2 = true;
                this->waitStartC1 = true;
                this->waitStartC2 = true;
            }
        }
    }
    /////////Figuras Nivel 2/////////
    else if(ui->radioButton_f2->isChecked() && !waitStartF2)
    {
        //        imshow("imgSharp", imgSharp);
//        Mat Level2 = pColor->Frame2HSVBoard(imgSharp, 15, 47, 70, 255, 100, 255); //Yellow color
        Mat Level2 = pColor->Frame2HSV(imgSharp, CColorsType::BLUE); //Blue color
        //        imshow("Level 2", Level2);
        Canny(Level2, imgCanny, 180, 120); // get Canny edges
        //        imshow("canny", imgCanny);
        //        figura.setImgCanny(imgCanny);

        QTime startTime;

        if(run && countTimes < 5) /// If the activity is runnig
        {
            if(newFigure) {   ///Send figure asked like "SQUARE"
                pFigure->newRandomFig(countTimes);
                statusBar()->showMessage(pFigure->printAskFigure(pFigure->getFigAsked()) + "?");
                pClient->startTransfer(pFigure->enum2QString(pFigure->getFigAsked()));
                newFigure = false;
                startTime = QTime::currentTime();
            }

           if(!detectMoviment())
            {
                ///Check if exist a figure on the board
                if(pFigure->existFigure(imgCanny))
                {
                    QVector<CFigsType> figAsked_figPlaced = pFigure->getFigAsked_FigPlaced(imgCanny);

                    if( figAsked_figPlaced[0] != CFigsType::NONE  && figAsked_figPlaced[1] != CFigsType::NONE && newFigure == false)
                    {
                        QTime endTime = QTime::currentTime();
                        pPerformance->right_or_wrongAnswer(figAsked_figPlaced);
                        pAnswers->saveAnswers(figAsked_figPlaced, startTime.msecsTo(endTime));

                        statusBar()->showMessage(pFigure->getMessage2Robot());
                        pClient->startTransfer(pFigure->getMessage2Robot());

                        this->countTimes++;

                        delay(10);


                        do{
                            ImageProcessing();
                            //Level2 = pColor->Frame2HSVBoard(imgSharp, 15, 47, 70, 255, 100, 255); //Yellow color
                            //Canny(Level2, imgCanny, 180, 120); // get Canny edges
                            showFramesWebcam();

                        }while(!detectMoviment());
                        // delay(15);

                        newFigure = true;
                        pFigure->clearCounts();
                    }
                }
           }
        }
        if( countTimes >= 5)  ///End Activity
        {
            this->run = false;
            this->countTimes = 0;
            pFigure->clearCounts();
            pFigure->randomQVector();

            pChild->stop_activity();
            statusBar()->showMessage("Activity Stoped", 3000);

            pSession->stopSession();
            pSession->saveSession(pChild->getChildCode());
            pPerformance->savePerformance(pChild->getChildCode(), pSession->getCodeSession(), pSession->getActivity());
            pClient->startTransfer("FIM\n");

            pChild->updateChildInfo(pChild->getChildCode());
            pChild->loadChildtoTable(model2);

            this->waitStartF1 = true;
            this->waitStartF2 = true;
            this->waitStartC1 = true;
            this->waitStartC2 = true;
        }

    }
    //////////Cores Nivel 1//////////
    else if(ui->radioButton_c1->isChecked() && !waitStartC1)
    {
        if(run && countTimes < 3) /// If the activity is runnig (3 colors on the board)
        {
            pColor->set_imgSharp(imgSharp);
            imgCanny = pColor->setColorPosition();
            imgSharp = pColor->get_imgSharp();

            QTime startTime = QTime::currentTime();

            if(!detectMoviment())
            {
                QVector<CColorsType> corBoard_corPlaced = pColor->getCorBoard_CorPlaced();

                if( corBoard_corPlaced[0] != CColorsType::NONE  && corBoard_corPlaced[1] != CColorsType::NONE && waitNoColor == true)
                {
                    QTime endTime = QTime::currentTime();
                    pPerformance->right_or_wrongAnswer(corBoard_corPlaced);
                    pAnswers->saveAnswers(corBoard_corPlaced,  startTime.msecsTo(endTime));

                    statusBar()->showMessage(pColor->getMessage2Robot());
                    pClient->startTransfer(pColor->getMessage2Robot());

                    this->countTimes++;
                    waitNoColor = false;

//                    delay(7);  ///While robot is playing an activity
                }
                else if((corBoard_corPlaced[0] == CColorsType::NONE || corBoard_corPlaced[1] == CColorsType::NONE ) && waitNoColor == false)
                {
                    waitNoColor = true;
                    statusBar()->showMessage("No color detected");
                }
            }
        }
        if( countTimes >= 3)  ///End Activity
        {
            this->run = false;
            this->countTimes = 0;
            ///pFigure->clearCounts(); //será preciso em versao cores
            pChild->stop_activity();
            statusBar()->showMessage("Activity Stoped", 3000);

            pSession->stopSession();
            pSession->saveSession(pChild->getChildCode());
            pPerformance->savePerformance(pChild->getChildCode(), pSession->getCodeSession(), pSession->getActivity());
            pClient->startTransfer("FIM\n");

            pChild->updateChildInfo(pChild->getChildCode());
            pChild->loadChildtoTable(model2);

            this->waitStartF1 = true;
            this->waitStartF2 = true;
            this->waitStartC1 = true;
            this->waitStartC2 = true;
        }
    }
    //////////Cores Nivel 2//////////
    else if(ui->radioButton_c2->isChecked() && !waitStartC2)
    {
        QTime startTime;

        if(run && countTimes < 5) /// If the activity is runnig
        {
            if(newColor){
                pColor->newRandomColor(countTimes); ///aqui par dár a primeira peça a jogar
                statusBar()->showMessage(pColor->printAskColor(pColor->getColorAsked()) + "?");
                pClient->startTransfer(pColor->enum2QString(pColor->getColorAsked()));
                newColor = false;
                startTime = QTime::currentTime();
            }

            pColor->set_imgSharp(imgSharp);

            if(!detectMoviment())
            {
                if(pColor->existColor(imgCanny))
                {
                    QVector<CColorsType> corAsked_corPlaced = pColor->getCorAsked_CorPlaced( pColor->getColorAsked() );

                    if( corAsked_corPlaced[0] != CColorsType::NONE  && corAsked_corPlaced[1] != CColorsType::NONE && newColor == false)
                    {
                        QTime endTime = QTime::currentTime();
                        pPerformance->right_or_wrongAnswer(corAsked_corPlaced);
                        pAnswers->saveAnswers(corAsked_corPlaced, startTime.msecsTo(endTime));

                        statusBar()->showMessage(pColor->getMessage2Robot());
                        pClient->startTransfer(pColor->getMessage2Robot());

                        this->countTimes++;
                        delay(5);

//                        do{
//                            ImageProcessing();
//                            pColor->set_imgSharp(imgSharp);
//                            showFramesWebcam();
//                        }while(pColor->existColor(imgCanny));

                        do{
                            ImageProcessing();
                            //Level2 = pColor->Frame2HSVBoard(imgSharp, 15, 47, 70, 255, 100, 255); //Yellow color
                            //Canny(Level2, imgCanny, 180, 120); // get Canny edges
                            showFramesWebcam();

                        }while(!detectMoviment());

                        newColor = true;
                    }
                }
            }
        }
        if( countTimes >= 5)  ///End Activity
        {
            this->run = false;
            this->countTimes = 0;
            pFigure->clearCounts();
            pFigure->randomQVector();

            pChild->stop_activity();
            statusBar()->showMessage("Activity Stoped", 3000);

            pSession->stopSession();
            pSession->saveSession(pChild->getChildCode());
            pPerformance->savePerformance(pChild->getChildCode(), pSession->getCodeSession(), pSession->getActivity());
            pClient->startTransfer("FIM\n");

            pChild->updateChildInfo(pChild->getChildCode());
            pChild->loadChildtoTable(model2);

            this->waitStartF1 = true;
            this->waitStartF2 = true;
            this->waitStartC1 = true;
            this->waitStartC2 = true;
        }
    }
    showFramesWebcam();
}


QImage MainWindow::convertOpenCVMatToQtQImage(Mat mat)
{
    if(mat.channels() == 1)  // if grayscale image
    {
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    }
    else if(mat.channels() == 3)  // if 3 channel color image
    {
        cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    }
    else
    {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();  //return a blank QImage if the above did not work
}

/**************************************************************
                                START A CONNECTION TO ROBOT
**************************************************************/
void MainWindow::on_pushButton_connect_clicked()
{
    QString IP_addr;

    IP_addr=ui->IP_addr->text();

    if(IP_addr==" IP")
    {
       if(pClient->start("127.0.0.1", 9898))
       {
           statusBar()->showMessage("Connection acepted",3000);
       }
       else
           statusBar()->showMessage("Failed to connect",3000);
    }
    else
    {
        if(pClient->start(IP_addr, 9898))
        {
            statusBar()->showMessage("Connected "+ IP_addr);
        }
        else
        {
            statusBar()->showMessage("Failed to connect");
        }
    }
}

/**************************************************************
                                 CLOSE CONNECTION TO ROBOT
**************************************************************/
void MainWindow::on_pushButton_close_clicked()
{
    QString qtStrData;
    QByteArray inBytes;
    const char *cStrData;

    qtStrData = "Fim\n";
    inBytes = qtStrData.toUtf8();
    cStrData = inBytes.constData();

    pClient->startTransfer(cStrData, qtStrData.length());

    pClient->stop();

    statusBar()->showMessage("Connection Closed", 3000);
}

/**************************************************************
                                    SEND A COMAND TO ROBOT
**************************************************************/
void MainWindow::on_pushButton_send_clicked()
{
    //Convert QString to Const char *
    QString qtStrData;
    QByteArray inBytes;
    const char *cStrData;

    qtStrData = ui->lineEdit_send->text();
    statusBar()->showMessage(qtStrData);

    qtStrData +="\n";
    inBytes = qtStrData.toUtf8();
    cStrData = inBytes.constData();

    //client.startTransfer(cStrData, qtStrData.length());
    pClient->startTransfer(cStrData, strlen(cStrData));
}

/**************************************************************
                                       SEND A VOICE MESSAGE
**************************************************************/
void MainWindow::on_pushButton_send_2_clicked()
{
    //Convert QString to Const char *
    QString qtStrData;
    QByteArray inBytes;
    const char *cStrData;

    qtStrData = "#" + ui->lineEdit_send->text();
    //ui->label_status->setText(qtStrData);

    qtStrData +="\n";
    inBytes = qtStrData.toUtf8();
    cStrData = inBytes.constData();

    //client.startTransfer(cStrData, qtStrData.length()-1);
    statusBar()->showMessage(pClient->qStringTransfer(cStrData, strlen(cStrData)));
}

/**************************************************************
                                        START ACTIVITY
**************************************************************/
void MainWindow::on_pushButton_start_clicked()
{
    if(ui->radioButton_f1->isChecked() || ui->radioButton_f2->isChecked() ||
            ui->radioButton_c1->isChecked() || ui->radioButton_c2->isChecked())
    {
        if(ui->radioButton_f1->isChecked())
        {
            statusBar()->showMessage("Starting first level of Figures Activity ", 3000);
            GetBoardFigureCoordenates(); ///para saber se as figuras estão no sitio certo
            pSession = new CSession(CActivityType::F1, pChild->getnSessions());
            pPerformance = new CPerformance(pChild->getChildCode(), CActivityType::F1);
            pAnswers = new CAnswers(pChild->getChildCode(), pChild->getnSessions(), CActivityType::F1);

            ///para impedir que comesse a fazer o codigo do processFrameAndUpdateGUI referente a cada nivel
            waitStartF1 = false; //para iniviar este nivel
            waitStartF2 = true;
            waitStartC1 = true;
            waitStartC2 = true;
        }
        else if(ui->radioButton_f2->isChecked())
        {
            statusBar()->showMessage("Starting second level of Figures Activity ", 3000);
            pSession = new CSession(CActivityType::F2, pChild->getnSessions());
            pPerformance = new CPerformance(pChild->getChildCode(), CActivityType::F2);
            pAnswers = new CAnswers(pChild->getChildCode(), pChild->getnSessions(), CActivityType::F2);

            waitStartF1 = true;
            waitStartF2 = false; //para iniviar este nivel
            waitStartC1 = true;
            waitStartC2 = true;
        }
        else if(ui->radioButton_c1->isChecked())
        {
            statusBar()->showMessage("Starting first level of Colors Activity ", 3000);
            GetBoardColorsCoordenates();///para saber se as cores estão no sitio certo
            pSession = new CSession(CActivityType::C1, pChild->getnSessions());
            pPerformance = new CPerformance(pChild->getChildCode(), CActivityType::C1);
            pAnswers = new CAnswers(pChild->getChildCode(), pChild->getnSessions(), CActivityType::C1);

            ///para impedir que comesse a fazer o codigo do processFrameAndUpdateGUI referente a cada nivel
            waitStartF1 = true;
            waitStartF2 = true;
            waitStartC1 = false; //para iniviar este nivel
            waitStartC2 = true;
        }
        else if(ui->radioButton_c2->isChecked())
        {
            statusBar()->showMessage("Starting second level of Colors Activity ", 3000);
            pSession = new CSession(CActivityType::C2, pChild->getnSessions());
            pPerformance = new CPerformance(pChild->getChildCode(), CActivityType::C2);
            pAnswers = new CAnswers(pChild->getChildCode(), pChild->getnSessions(), CActivityType::C2);

            ///para impedir que comesse a fazer o codigo do processFrameAndUpdateGUI referente a cada nivel
            waitStartF1 = true;
            waitStartF2 = true;
            waitStartC1 = true;
            waitStartC2 = false; //para iniviar este nivel
        }

        run = true;

    }
    else
    {
        QMessageBox::information(this, "", "Select an Activity!");
    }
}

/**************************************************************
                                              STOP ACTIVITY
**************************************************************/
void MainWindow::on_pushButton_stop_clicked()
{
    run = false;
    pChild->stop_activity();
    statusBar()->showMessage("Activity Stoped", 3000);

    pSession->stopSession();
    pSession->saveSession(pChild->getChildCode());

    pPerformance->savePerformance(pChild->getChildCode(), pChild->getnSessions(), pSession->getActivity());

    pChild->updateChildInfo(pChild->getChildCode());
    pChild->loadChildtoTable(model2);

    this->waitStartF1 = true;
    this->waitStartF2 = true;
    this->waitStartC1 = true;
    this->waitStartC2 = true;
}

/**************************************************************
                                             RIGHT ANSWER
**************************************************************/
void MainWindow::on_pushButton_right_clicked()
{
    if(run)
    {
        pClient->startTransfer("success\n",8);
        pPerformance->rightAnswer(CFigsType::SQUARE);
    }
    else
        statusBar()->showMessage("You need to start the activity", 4000);
}

/**************************************************************
                                            WRONG ANSWER
**************************************************************/
void MainWindow::on_pushButton_wrong_clicked()
{
    if(run)
    {
        pClient->startTransfer("insuccess\n",10);
        pPerformance->wrongAnswer(CFigsType::SQUARE);
    }
    else
        statusBar()->showMessage("You need to start the activity", 4000);
}

/**************************************************************
                                              OPEN WEBCAM
**************************************************************/
void MainWindow::on_pushButton_open_webcam_clicked()
{
    if(ui->radioButton_webcam_original->isChecked() ||
            ui->radioButton_webcam_canny->isChecked() || ui->radioButton_webcam_colors->isChecked())
    {
//        capWebcam.open(0); //Open the webcam MICROSOFT LIFECAM VX-1000 V1.0
        capWebcam.open(1); //Open the webcam PS3 EYE

        if(!capWebcam.isOpened()) //If unsuccessful
        {
            QMessageBox::information(this, "", "ERROR: capWebcam\n\n Exiting program...\n");
            exitProgram();
            return;
        }

        //Ajust the width and height to show webCam
        capWebcam.set(CAP_PROP_FRAME_WIDTH, 640);
        capWebcam.set(CAP_PROP_FRAME_HEIGHT, 480);

        qtimer = new QTimer(this);                                                      // instantiate timer
        connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));     // associate timer to processFrameAndUpdateGUI
        qtimer->start(20);                  // start timer, set to cycle every 20 msec (50x per sec), it will not actually cycle this often

    }
}

/**************************************************************
                                              CLOSE WEBCAM
**************************************************************/
void MainWindow::on_pushButton_close_webcam_clicked()
{
    if(capWebcam.isOpened()) //If successful
    {
        capWebcam.release();

        if(qtimer->isActive())
            qtimer->stop();  //if timer is running, stop timer
    }
}

void MainWindow::on_radioButton_girl_clicked()
{
    QPixmap pixmap("assets/Little_Girl_Pink_128x128.png");
    ui->label_icon_child->setPixmap(pixmap);
}

void MainWindow::on_radioButton_boy_clicked()
{
    QPixmap pixmap("assets/Little_Boy_Blue_128x128.png");
    ui->label_icon_child->setPixmap(pixmap);
}

/**************************************************************
                                              ADD NEW CHILD
**************************************************************/
void MainWindow::on_pushButton_add_child_clicked()
{
    QString code;
    QString name;
    QString gender;
    QString age;
    QString td;

    if(ui->spinBox_child_code->value() != NULL &&
            !ui->lineEdit_child_name->text().isEmpty() &&
            (ui->radioButton_boy->isChecked() || ui->radioButton_girl->isChecked()) &&
            ui->spinBox_child_age->value() != NULL &&
            (ui->radioButton_tp_yes->isChecked() || ui->radioButton_tp_no->isChecked()))

    {
        code = QString("%1").arg(ui->spinBox_child_code->value(), 2, 10, QChar('0'));

        ui->spinBox_child_code->clear();

        name=ui->lineEdit_child_name->text();
        ui->lineEdit_child_name->clear();

        if(ui->radioButton_boy->isChecked())
        {
            gender = "Male";
            ui->radioButton_boy->setAutoExclusive(false);
            ui->radioButton_boy->setChecked(false);

        }
        else if(ui->radioButton_girl->isChecked())
        {
            gender = "Female";
            ui->radioButton_girl->setAutoExclusive(false);
            ui->radioButton_girl->setChecked(false);
        }

        age.setNum(ui->spinBox_child_age->value(),10);
        ui->spinBox_child_age->clear();

        if(ui->radioButton_tp_yes->isChecked())
        {
            td = "Yes";
            ui->radioButton_tp_yes->setAutoExclusive(false);
            ui->radioButton_tp_yes->setChecked(false);
        }
        else if(ui->radioButton_tp_no->isChecked())
        {
            td = "No";
            ui->radioButton_tp_no->setAutoExclusive(false);
            ui->radioButton_tp_no->setChecked(false);
        }

        pChild = new CChild_Info(code, name, gender, age, td);

//        if(child.addNewChild(code, name, gender, age, td))
        if(pChild->addNewChild())
        {
            QMessageBox::information(this, "", "Child Successfully Added\n");

            ui->label_code_profile->setText(code);
            ui->label_name_profile->setText(name);
            ui->label_gender_profile->setText(gender);
            ui->label_age_profile->setText(age);
            ui->label_td_profile->setText(td);

            pChild->loadChildtoTable(model2);
        }
        else
        {
            QMessageBox::critical(this, "", "ERROR: Child was not Added\n");
        }
    }
    else
    {
        QMessageBox::critical(this, "", "ERROR: Fill the fields\n");
    }
}

/**************************************************************
                          LOAD CHILD INFORMATION TO TABLE
**************************************************************/
void MainWindow::on_pushButton_loadChildtoTable_clicked()
{
    pChild->loadChildtoTable(model2);
}

/**************************************************************
                            SHOW PROFILE'S CHILD WITH CLICK
**************************************************************/
void MainWindow::on_tableView_childs_clicked(const QModelIndex &index)
{
    QStringList lineInfo;

    if(index.isValid())
    {
        for(int col = 0; col < model2->columnCount(); col++)
        {
            lineInfo.append(index.sibling(index.row(), col).data().toStringList());
        }

        ui->label_code_profile->setText(lineInfo[0]);
        ui->label_name_profile->setText(lineInfo[1]);
        ui->label_gender_profile->setText(lineInfo[2]);
        ui->label_age_profile->setText(lineInfo[3]);
        ui->label_td_profile->setText(lineInfo[4]);

        if(lineInfo[2] == "Male")
        {
            QPixmap pixmap("assets/Little_Boy_Blue_128x128.png");
            ui->label_icon_child->setPixmap(pixmap);
        }
        else if(lineInfo[2] == "Female")
        {
            QPixmap pixmap("assets/Little_Girl_Pink_128x128.png");
            ui->label_icon_child->setPixmap(pixmap);
        }
    }
}

/**************************************************************
               SELECT A CHILD FROM TABLE CHILD WITH DOUBLE CLICK
**************************************************************/
void MainWindow::on_tableView_childs_doubleClicked(const QModelIndex &index)
{
    QStringList lineInfo;
    QString sendZeca;

    for(int col = 0; col < model2->columnCount(); col++)
    {
        lineInfo.append(index.sibling(index.row(), col).data().toStringList());
    }

    statusBar()->showMessage("Select Child: " + lineInfo[1]);

    ///lineInfo[5] - nSessions
    ///lineInfo[1] - Child name
    /// lineInfo[0] - Child Code
    sendZeca = lineInfo[0] + ';' + lineInfo[1] + ';' + lineInfo[5];

    pClient->startTransfer(sendZeca);

    pChild = new CChild_Info(lineInfo);

    if(ui->radioButton_graphF1->isChecked())
    {
        pPerformance = new CPerformance(lineInfo[0], CActivityType::F1);

        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::F1, ui->customPlot))
        {
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
    else if(ui->radioButton_graphF2->isChecked())
    {
        pPerformance = new CPerformance(lineInfo[0], CActivityType::F2);

        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::F2, ui->customPlot))
        {
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
    else if(ui->radioButton_graphC1->isChecked())
    {
        pPerformance = new CPerformance(lineInfo[0], CActivityType::C1);

        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::C1, ui->customPlot))
        {
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
    else if(ui->radioButton_graphC2->isChecked())
    {
        pPerformance = new CPerformance(lineInfo[0], CActivityType::C2);

        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::C2, ui->customPlot))
        {
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
}

void MainWindow::on_checkBox_square_clicked()
{
    if(ui->checkBox_square->isChecked())
    {
        statusBar()->showMessage("Square in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_triangle_clicked()
{
    if(ui->checkBox_triangle->isChecked())
    {
        statusBar()->showMessage("Triangle in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_rectangle_clicked()
{
    if(ui->checkBox_rectangle->isChecked())
    {
        statusBar()->showMessage("Rectangle in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_circle_clicked()
{
    if(ui->checkBox_circle->isChecked())
    {
        statusBar()->showMessage("Circle in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_blue_clicked()
{
    if(ui->checkBox_blue->isChecked())
    {
        statusBar()->showMessage("Color blue in the right place", 3000);
        //Send a comand to robot
    }

}

void MainWindow::on_checkBox_red_clicked()
{
    if(ui->checkBox_red->isChecked())
    {
        statusBar()->showMessage("Color red in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_green_clicked()
{
    if(ui->checkBox_green->isChecked())
    {
        statusBar()->showMessage("Color green in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_yellow_clicked()
{
    if(ui->checkBox_yellow->isChecked())
    {
        statusBar()->showMessage("Color yellow in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_orange_clicked()
{
    if(ui->checkBox_orange->isChecked())
    {
        statusBar()->showMessage("Color orange in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_black_clicked()
{
    if(ui->checkBox_black->isChecked())
    {
        statusBar()->showMessage("Color black in the right place", 3000);
        //Send a comand to robot
    }
}

void MainWindow::on_checkBox_white_clicked()
{
    if(ui->checkBox_white->isChecked())
    {
        statusBar()->showMessage("Color white in the right place", 3000);
        //Send a comand to robot
    }
}


void MainWindow::on_radioButton_tp_yes_clicked()
{
    if(ui->radioButton_tp_no->isChecked())
    {
        ui->radioButton_tp_no->setAutoExclusive(false);
        ui->radioButton_tp_no->setChecked(false);
     }
}

void MainWindow::on_radioButton_tp_no_clicked()
{
    if(ui->radioButton_tp_yes->isChecked())
    {
        ui->radioButton_tp_yes->setAutoExclusive(false);
        ui->radioButton_tp_yes->setChecked(false);
     }
}

void MainWindow::on_radioButton_graphF1_clicked()
{
    if(pChild->getChildCode() != "")
    {
        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::F1, ui->customPlot))
        {
            ///If no information clear the graphBar
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
}

void MainWindow::on_radioButton_graphF2_clicked()
{
    if(pChild->getChildCode() != "")
    {
        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::F2, ui->customPlot))
        {
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
}

void MainWindow::on_radioButton_graphC1_clicked()
{
    if(pChild->getChildCode() != "")
    {
        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::C1, ui->customPlot))
        {
            ///If no information clear the graphBar
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
}

void MainWindow::on_radioButton_graphC2_clicked()
{
    if(pChild->getChildCode() != "")
    {
        if(!pPerformance->updateGraph(pChild->getChildCode(), CActivityType::C2, ui->customPlot))
        {
            ///If no information clear the graphBar
            ui->customPlot->clearPlottables();
            ui->customPlot->replot();
        }
    }
}

void MainWindow::UpdateSlider()
{
    ui->slider_maxH->setSliderPosition(pColor->getiHighH());
    ui->slider_minH->setSliderPosition(pColor->getiLowH());

    ui->slider_maxS->setSliderPosition(pColor->getiHighS());
    ui->slider_minS->setSliderPosition(pColor->getiLowS());

    ui->slider_maxV->setSliderPosition(pColor->getiHighV());
    ui->slider_minV->setSliderPosition(pColor->getiLowV());
}

void MainWindow::SetHSV()
{
    UpdateSlider();

        if(ui->comboBox_colors->currentText() == "BLUE")
        {
            pColor->SetColor(CColorsType::BLUE); //Azul
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "RED") {
            pColor->SetColor(CColorsType::RED); //Vermelho
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "GREEN") {
            pColor->SetColor(CColorsType::GREEN); //Verde
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "YELLOW") {
            pColor->SetColor(CColorsType::YELLOW); //Amarelo
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "BLACK") {
            pColor->SetColor(CColorsType::BLACK); //Preto
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "WHITE") {
            pColor->SetColor(CColorsType::WHITE); // Branco
            UpdateSlider();
        }
        else if( ui->comboBox_colors->currentText() == "NOT WHITE") {
            pColor->SetColor(CColorsType::NOTWHITE); //Anular o Branco
            UpdateSlider();
        }
        else {
            pColor->SetColor(CColorsType::NONE); //Ajustes vair servir para ajustar os parametros HSV
        }
}


void MainWindow::ImageProcessing()
{
    ///Claro
//    Mat kernel = (Mat_<float>(5, 5) << 1, 1, 1, 1, 1, /**/ 1, 1, 1, 1, 1, /**/ 1, 1, 80, 1, 1, /**/ 1, 1, 1, 1, 1, /**/ 1, 1, 1, 1, 1  ) / (float)(8*8);
    ///Escuro
    Mat kernel = (Mat_<float>(5, 5) << 1, 1, 1, 1, 1, /**/ 1, 1, 1, 1, 1, /**/ 1, 1, -80, 1, 1, /**/ 1, 1, 1, 1, 1, /**/ 1, 1, 1, 1, 1  ) / (float)(-8*8);

    bool blnimgFrameReadSuccessfully = capWebcam.read(imgFrame);  // get next frame from the webcam

    if (!blnimgFrameReadSuccessfully || imgFrame.empty())  // if we did not get a frame
    {
        QMessageBox::information(this, "", "unable to read from webcam \n\n exiting program\n");
        exitProgram();  // and exit program
        return;
    }

    //cvtColor(imgFrame, imgGray, CV_BGR2GRAY);  // convert to grayscale

    //filtrar imagem
    filter2D(imgFrame, imgSharp, CV_32F, kernel,Point(-1,-1),0,BORDER_DEFAULT);
    imgSharp.convertTo(imgSharp, CV_8U);

    cvtColor(imgSharp, imgGray, CV_BGR2GRAY);  // convert to grayscale

    GaussianBlur(imgGray, imgBlurred, Size(5, 5), 1.6);  // blur
    adaptiveThreshold(imgBlurred, adapt_tresh, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 13, 0.01);

    Canny(adapt_tresh, imgCanny, 180, 120); // get Canny edges
}

void MainWindow::GetBoardFigureCoordenates()
{
    ImageProcessing();
    pFigure->Set_imgSharp(imgSharp);
    pFigure->SetBoardFigurePosition(imgCanny);
    imgSharp = pFigure->Get_imgSharp();
}

void MainWindow::GetBoardColorsCoordenates()
{
    ImageProcessing();
    pColor->set_imgSharp(imgSharp);
    pColor->setALLBoardColorPosition();
    imgSharp = pColor->get_imgSharp();
}

void MainWindow::delay(int seconds)
{
    QTime dieTime = QTime::currentTime().addSecs(seconds);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::showFramesWebcam()
{
    QImage qimgFrame = convertOpenCVMatToQtQImage(imgSharp);//(imgFrame);  // convert from OpenCV Mat to Qt QImage
    QImage qimgCanny = convertOpenCVMatToQtQImage(imgCanny);
    QImage qimgFHSV = convertOpenCVMatToQtQImage(imgFHSV); // (adapt_tresh);//
    QImage qimgFComper = convertOpenCVMatToQtQImage(imgFComper);

    if(ui->radioButton_webcam_original->isChecked())
    {
        ui->lb_webCam->setPixmap(QPixmap::fromImage(qimgFrame));  // show images on form labels
    }
    else if(ui->radioButton_webcam_canny->isChecked())
    {
        ui->lb_webCam->setPixmap(QPixmap::fromImage(qimgCanny));
    }
    else if(ui->radioButton_webcam_colors->isChecked())
    {
        ui->lb_webCam->setPixmap(QPixmap::fromImage(qimgFHSV)); //(qimgFComper)); //
    }
}

void MainWindow::on_radioButton_f1_clicked()
{
    pClient->startTransfer("F1\n");
}

void MainWindow::on_radioButton_f2_clicked()
{
    pClient->startTransfer("F2\n");
}

void MainWindow::on_radioButton_c1_clicked()
{
    pClient->startTransfer("C1\n");
}

void MainWindow::on_radioButton_c2_clicked()
{
    pClient->startTransfer("C2\n");
}
