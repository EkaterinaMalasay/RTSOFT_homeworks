#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

void help(char** argv ) {
    std::cout << "\n"
    << "\nxample 2-10. The same object can load videos from a camera or a file"
    << "\nCall:\n"  
    << argv[0] <<" [path/image]\n"
    << "\nor, read from camera:\n"
    << argv[0]
    << "\nFor example:\n"
    << argv[0] << " ../tree.avi\n"
    << std::endl;
}

int main( int argc, char** argv ) {
    
    help(argv);

  cv::namedWindow( "Homework 1", cv::WINDOW_AUTOSIZE );
  cv::VideoCapture cap;

  if (argc==1) {
    cap.open(0); // open the first camera
  } else {
    cap.open(argv[1]);
  }

  if( !cap.isOpened() ) { // check if we succeeded
    std::cerr << "Couldn't open capture." << std::endl;
    return -1;
  }

  cv::Mat frame;
  int count = 0, collisions = 0;
  int x = 250, y = 250; //координаты центра круга
  int radius = 50;
  int R = 255, G = 255, B = 0;

  int speed = 10;
  float angle = 60;
  float vx = cos(angle/256*M_PI)*speed;
  float vy = sin(angle/256*M_PI)*speed;
  int width;
  int height;

  for(;;) {
    cap >> frame;
    if( frame.empty() ) break; // Ran out of film

    //границы
    cv::Size window = frame.size();
    width = window.width;
    height = window.height;

    //добавление графики

    //текст
    stringstream ss;
    ss<<count;
    string text = "count: " + ss.str();
    cv::rectangle(frame, cv::Point(0,0),cv::Point(130,20),cv::Scalar(255,255,255),CV_FILLED);
    cv::rectangle(frame, cv::Point(0,0),cv::Point(130,20),cv::Scalar(0,0,0));
    cv::putText(frame, text, cv::Point(10,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0));

    //круг
    stringstream ss2;
    ss2<<collisions;
    string circleText = ss2.str();
    cv::circle(frame, cv::Point(x,y), radius, cv::Scalar(B,G,R), CV_FILLED);
    cv::putText(frame, circleText, cv::Point(x-5,y+5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0));
    cv::imshow( "Homework 1", frame );

    //расчет новых координат
    x = x + vx;
    y = y + vy;
    if (x-radius < 0 ) {
      vx = -vx;
      collisions++;
    }
    if( x+radius > width) {
      x = 2*(width-radius)-x;
      vx = -vx;
      B = rand()%256;
      G = rand()%256;
      R = rand()%256;
      collisions++;
    }

    if (y-radius < 0 ) {
      vy = -vy;
      collisions++;
    }
    if( y+radius > height) {
      y = 2*(height-radius)-y;
      vy = -vy;
      B = rand()%256;
      G = rand()%256;
      R = rand()%256;
      collisions++;
    }
    count++;

    if( (char) cv::waitKey(33) >= 0 ) break;
  }

  return 0;
}
