#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "windows.h"

#include "mainwindow.h"

using namespace cv;



BITMAPINFOHEADER createBitmapHeader(int width, int height)
{
   BITMAPINFOHEADER  bi;

     // create a bitmap
     bi.biSize = sizeof(BITMAPINFOHEADER);
     bi.biWidth = width;
     bi.biHeight = -height;  //this is the line that makes it draw upside down or not
     bi.biPlanes = 1;
     bi.biBitCount = 32;
     bi.biCompression = BI_RGB;
     bi.biSizeImage = 0;
     bi.biXPelsPerMeter = 0;
     bi.biYPelsPerMeter = 0;
     bi.biClrUsed = 0;
     bi.biClrImportant = 0;

     return bi;
}

Mat captureScreenMat(HWND hwnd)
{
     Mat src;

     // get handles to a device context (DC)
     HDC hwindowDC = GetDC(hwnd);
     HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
     SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

     // define scale, height and width
     int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
     int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
     int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
     int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

     // create mat object
     src.create(height, width, CV_8UC4);

     // create a bitmap
     HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
     BITMAPINFOHEADER bi = createBitmapHeader(width, height);

     // use the previously created device context with the bitmap
     SelectObject(hwindowCompatibleDC, hbwindow);

     // copy from the window device context to the bitmap device context
     StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
     GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

     // avoid memory leak
     DeleteObject(hbwindow);
     DeleteDC(hwindowCompatibleDC);
     ReleaseDC(hwnd, hwindowDC);

     return src;
 }


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  QWidget *root = new QWidget(this);
  QWidget *top = new QWidget(this);
  QWidget *content = new QWidget(this);

  /* Top Layout */
  QHBoxLayout *topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString ("Quit"), this);
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
  topLayout->addWidget(quitButton);

  startButton = new QPushButton(QString("Start CV"), this);
  connect (startButton, &QPushButton::clicked, this, &MainWindow::onStart);
  topLayout->addWidget(startButton);

  stopButton = new QPushButton(QString("Stop CV"), this);
  connect (stopButton, &QPushButton::clicked, this, &MainWindow::onStop);
  topLayout->addWidget(stopButton);

  /* Content Layout */
  contentLayout = new QVBoxLayout(content);

  imageLabel = new QLabel();
  contentLayout->addWidget(imageLabel);


  /* Root Layout */
  QVBoxLayout *rootLayout = new QVBoxLayout(root);
  rootLayout->addWidget(top);
  rootLayout->addWidget(content);
  setCentralWidget(root);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onStart() {

  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
    qDebug() << "ERROR: Could not open camera";
    return;
  }

  // create a window to display the images from the webcam
  // cv::namedWindow("Webcam", WINDOW_AUTOSIZE);

  // this will contain the image from the webcam
  cv::Mat frame;
  cv::Mat dst;

  // capture the next frame from the webcam
  camera >> frame;

  // cv::Mat kernel = (cv::Mat_<char>(3,3) <<  0, -1,  0,
  //                                          -1,  5, -1,
  //                                           0, -1,  0);

  cv::Mat kernel = (cv::Mat_<char>(3,3) <<  0, -1,  0,
                                           -1,  4, -1,
                                            0, -1,  0);

  filter2D(frame, dst, frame.depth(), kernel);

  QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char*) dst.data, dst.cols, dst.rows, QImage::Format_BGR888));
  imageLabel->setPixmap(pixmap);

  // QImageReader reader("d:/work/qt/game_overlay/img/food.png");
  // reader.setAutoTransform(true);
  // const QImage newImage = reader.read();
  // image = newImage;
  // imageLabel->setPixmap(QPixmap::fromImage(image));


  // // display the frame until you press a key
  // while (1) {
  //   // show the image on the window
  //   cv::imshow("Webcam", frame);
  //   // wait (10ms) for a key to be pressed
  //   if (cv::waitKey(10) >= 0)
  //     break;
  // }
  // return;

  // Mat image;
  // image = imread("d:/work/qt/game_overlay/img/food.png", IMREAD_COLOR);
  //
  // if( image.empty() ) // Check for invalid input
  //   {
  //     qDebug() << "Could not open or find the image";
  //
  //   }
  //
  // namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
  // imshow( "Display window", image ); // Show our image inside it.
  // waitKey(0); // Wait for a keystroke in the window
}

void MainWindow::onStop() {

  // capture image
  HWND hwnd = GetDesktopWindow();
  Mat src = captureScreenMat(hwnd);

  // encode result
  std::vector<uchar> buf;
  cv::imencode(".png", src, buf);

  // save img
  cv::imwrite("d:/work/qt/test_cv/screenshot.png", src);

  buf.clear();

}

void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {

    }
}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select Output Image", QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        // using namespace cv;
        // Mat inpImg, outImg;
        // inpImg = imread(ui->inputLineEdit->text().toStdString());
        // if(ui->medianBlurRadioButton->isChecked())
        //     cv::medianBlur(inpImg, outImg, 5);
        // else if(ui->gaussianBlurRadioButton->isChecked())
        //     cv::GaussianBlur(inpImg, outImg, Size(5, 5), 1.25);
        // imwrite(fileName.toStdString(), outImg);
        // if(ui->displayImageCheckBox->isChecked())
        //     imshow("Output Image", outImg);
    }
}
