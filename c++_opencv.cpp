#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>




using namespace cv;
using namespace std;


int main()
{
    unsigned int start;
    unsigned int end;
    vector <float> test;
    ofstream excel;
    bool flag = true;

    Mat img_gray;
    Mat img_bin;
    Mat img_dilate;
    Mat img_show;
    Mat img = imread("C:/Users/bobti/Desktop/datascience/lab1/space.jpg");
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    threshold(img_gray, img_bin, 127, 255, THRESH_BINARY);
    
    for (int i = 0; i < 30; i++) {
        start = clock();
        dilate(img_bin, img_dilate, Mat());
        end = clock();
        test.push_back((float)(end - start) / 1000);
    }



    while (1){

        if (flag){
            img_show = img_bin;
        }
        else {
            img_show = img_dilate;
        }
        resize(img_show, img_show, Size(500, 500));
        imshow("Result", img_show);

        int key = waitKey(1);

        if (key == 27) break;

        if (key == 44 || key == 46) flag = !flag;

    }

    destroyAllWindows();


    excel.open("test.xls", fstream::app);

    excel << "C++ opencv";

    for (int i = 0; i < test.size(); i++) {
        excel << "\t" << test.at(i);
    }
    excel << "\n";

    excel.close();

    system("pause");

    return 0;
}