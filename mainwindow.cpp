#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout> 
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>

#include "mainwindow.h"

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
  using namespace cv;

  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
    qDebug() << "ERROR: Could not open camera";
    return; 
  }

  // create a window to display the images from the webcam
  // cv::namedWindow("Webcam", WINDOW_AUTOSIZE);

  // this will contain the image from the webcam
  cv::Mat frame;
        
  // capture the next frame from the webcam
  camera >> frame;

  QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_BGR888));
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
