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


void neighbors_update(Mat& array, int radius, int row_index, int column_index){

    for (int j = column_index - radius; j < column_index + 1 + radius; j++) {
        for (int i = row_index - radius; i < row_index + 1 + radius; i++) {
            if (i >= 0 && i < array.rows && j >= 0 and j < array.cols) {
                array.at<uchar>(i, j) = 255;
            }
        }
    }
}



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
    Mat img = imread("space.jpg");
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    threshold(img_gray, img_bin, 127, 255, THRESH_BINARY);






    for (int i = 0; i < 30; i++) {
        start = clock();

        img_dilate = img_bin.clone();
                      
        for (int x = 0; x < img_bin.rows; x++) {
            for (int y = 0; y < img_bin.cols; y++) {
                if (img_bin.at<uchar>(x, y)==255) {
                    neighbors_update(img_dilate, 1, x, y);
                }
            }
        }
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

    imwrite("c++_native_res.jpg", img_dilate);

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