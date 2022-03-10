//James Rogers Jan 2021 (c) Plymouth University
//Student ID: 10609827
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    //Path to image file
    string Path = "../Task3/PCB Images/";

    //Loop through component images
    for(int n=0; n<10; ++n){

        //Read PCB and Component images, create Mats
        Mat PCB = imread(Path+"PCB.png");
        Mat Component = imread(Path+"Component"+to_string(n)+".png");
        Mat Mask, Result;

        //Establish match method
        int matchMethod = TM_SQDIFF_NORMED;

        //Find error
        matchTemplate(PCB, Component, Result, matchMethod);

        //Return positions and values of min/max pixels on image
        double minVal, maxVal; //Doubles for min/max values
        Point minLoc, maxLoc; //Points for min/max positions

        //Find min/max error points on match output and print to terminal
        minMaxLoc(Result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        cout << "Minimum error: " << minVal << ", Maximum error: " << maxVal << "." << endl;

        //If error too high, print error message, else, draw rectangle around component
        if (minVal > 0.04){
             cout << "Error value too high, component placement failed." << endl;
        }
        else
            rectangle(PCB, minLoc, Point(minLoc.x + Component.cols, minLoc.y + Component.rows), Scalar(0, 255, 50), 4);

        //Display the result until x is pressed
        while(waitKey(10)!='x'){
            imshow("Target", Component);
            imshow("PCB", PCB);
        }

    }

}
