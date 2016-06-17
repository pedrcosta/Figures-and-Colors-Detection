#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QtCore>
#include <QString>
#include <QMessageBox>

#include "cclient.h"
#include "cchild_info.h"
#include "csession.h"
#include "cperformance.h"
#include "canswers.h"
#include "cactivitytype.h"
#include "cfigure.h"
#include "ccolor.h"
#include "cposcenter.h"

#include "qcustomplot.h"

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>

#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

#include <vector>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void processFrameAndUpdateGUI();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_close_clicked();
    void on_pushButton_send_clicked();
    void on_pushButton_send_2_clicked();

    ///START AND STOP BUTTONS
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();

    ///RIGHT AND WRONG BUTTONS
    void on_pushButton_right_clicked();
    void on_pushButton_wrong_clicked();

    ///OPEN AND CLOSE WEBCAM
    void on_pushButton_open_webcam_clicked();
    void on_pushButton_close_webcam_clicked();

    void on_radioButton_girl_clicked();
    void on_radioButton_boy_clicked();

    void on_pushButton_add_child_clicked();
    void on_pushButton_loadChildtoTable_clicked();

    void on_checkBox_square_clicked();
    void on_checkBox_triangle_clicked();
    void on_checkBox_rectangle_clicked();
    void on_checkBox_circle_clicked();
    void on_checkBox_blue_clicked();
    void on_checkBox_red_clicked();
    void on_checkBox_green_clicked();
    void on_checkBox_yellow_clicked();
    void on_checkBox_orange_clicked();
    void on_checkBox_black_clicked();
    void on_checkBox_white_clicked();

    void on_tableView_childs_clicked(const QModelIndex &index);
    void on_tableView_childs_doubleClicked(const QModelIndex &index);

    void on_radioButton_tp_yes_clicked();
    void on_radioButton_tp_no_clicked();

    ///RADIOBUTTONS TO GRAPH
    void on_radioButton_graphF1_clicked();
    void on_radioButton_graphF2_clicked();
    void on_radioButton_graphC1_clicked();
    void on_radioButton_graphC2_clicked();

    void on_radioButton_f1_clicked();

    void on_radioButton_f2_clicked();

    void on_radioButton_c1_clicked();

    void on_radioButton_c2_clicked();

private:
    Ui::MainWindow *ui;
    CClient *pClient;
    CChild_Info *pChild;
    CSession *pSession;
    CPerformance *pPerformance;
    CAnswers *pAnswers;

    CFigure *pFigure;
    CColor *pColor;
    CPosCenter *pPosCenter;

    Mat imgFrame;  // input image
    Mat imgGray;  // grayscale of input imageget feed back
    Mat imgBlurred;  // intermediate blured image
    Mat imgCanny;  // Canny edge image
    Mat imgSharp;
    Mat adapt_tresh;
    Mat imgFHSV;
    Mat imgFHSVBoard;
    Mat imgFComper;
    Mat imgInitialCanny;

    void UpdateSlider();
    void SetHSV();
    void ImageProcessing();

    void GetBoardFigureCoordenates();
    void GetBoardColorsCoordenates();

    void delay(int seconds);
    void showFramesWebcam();


    bool waitStartF1;
    bool waitStartF2;
    bool waitStartC1;
    bool waitStartC2;

    bool run;
    bool waitNoFigure;
    bool newFigure;
    bool waitNoColor;
    bool newColor;
    int countTimes;

    VideoCapture capWebcam;   /// Capture object to use with webcam
    QTimer* qtimer;  ///Timer for processFrameAndUpdateGUI()
    QStandardItemModel *model2;  ///Child's Table

    QImage convertOpenCVMatToQtQImage(Mat mat);

    void exitProgram();

    void setupTableViewChild();
    void setupGraphBar();

    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();
    Mat foregroundMask, backgroundImage, foregroundImg;
    bool detectMoviment();

};

#endif // MAINWINDOW_H
