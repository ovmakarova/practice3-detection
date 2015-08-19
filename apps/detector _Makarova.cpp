#include <iostream>
#include <string>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

const char* params =
     "{ h | help     | false | print usage                                   }"
     "{   | detector |       | XML file with a cascade detector              }"
     "{   | image    |       | image to detect objects on                    }"
     "{   | video    |       | video file to detect on                       }"
     "{   | camera   | false | whether to detect on video stream from camera }";


void drawDetections(const vector<Rect>& detections,
                    const Scalar& color,
                    Mat& image)
{
    for (size_t i = 0; i < detections.size(); ++i)
    {
        rectangle(image, detections[i], color, 2);
    }
}

const Scalar red(0, 0, 255);
const Scalar green(0, 255, 0);
const Scalar blue(255, 0, 0);
const Scalar colors[] = {red, green, blue};

int main(int argc, char** argv)
{
    // Parse command line arguments.
    CommandLineParser parser(argc, argv, params);
    // If help flag is present, print help message and exit.
    if (parser.get<bool>("help"))
    {
        parser.printParams();
        return 0;
    }

    string detector_file = parser.get<string>("detector");
    CV_Assert(!detector_file.empty());
    string image_file = parser.get<string>("image");
    string video_file = parser.get<string>("video");
    bool use_camera = parser.get<bool>("camera");

    // TODO: Load detector.

    CascadeClassifier unn;
    CascadeClassifier unn_old;
    CascadeClassifier opencv;
    CascadeClassifier itseez;
    CascadeClassifier itseez_with_caption;

    if (!unn.load("C:/Temp/SS2015/clean/practice3-detection-build/bin/unn_logo_cascade/cascade.xml"))
    {
        cout << "Olya!!!!!" << endl;
    }
    
    unn_old.load("C:/Temp/SS2015/clean/practice3-detection-build/bin/unn_logo_old_cascade/cascade.xml");
    opencv.load("C:/Temp/SS2015/clean/practice3-detection-build/bin/opencv_logo_cascade/cascade.xml");
    itseez.load("C:/Temp/SS2015/clean/practice3-detection-build/bin/itseez_logo_cascade/cascade.xml");
    itseez_with_caption.load("C:/Temp/SS2015/clean/practice3-detection-build/bin/itseez_logo_w_caption_cascade/cascade.xml");

   
    

    if (!image_file.empty())
    {
       vector<Rect> unn_vector;
       vector<Rect> unn_old_vector;
       vector<Rect> opencv_vector;
       vector<Rect> itseez_vector;
       vector<Rect> itseez_w_caption_vector;

       Mat image = imread(image_file);
       unn.detectMultiScale(image, unn_vector);
       cout<<"Unn: "<< unn_vector.size()<<endl;

       unn_old.detectMultiScale(image, unn_old_vector);
       cout<<"Unn_old: "<< unn_old_vector.size()<<endl;

       opencv.detectMultiScale(image, opencv_vector);
       cout<<"Opencv: "<< opencv_vector.size()<<endl;

       itseez.detectMultiScale(image, itseez_vector);
       cout<<"Itseez: "<< itseez_vector.size()<<endl;

       itseez_with_caption.detectMultiScale(image, itseez_w_caption_vector);
       cout<<"itseez_w_caption_vector: "<< itseez_w_caption_vector.size()<<endl;

    }
    else if (!video_file.empty())
    {
        // TODO: Detect objects on every frame of a video.

    }
    else if (use_camera)
    {
        Mat frame;
        VideoCapture cap(0); // open the default camera
        if(!cap.isOpened())  // check if we succeeded
            return -1;
        namedWindow("edges",1);
        while (true)
        {
            cap >> frame;
            if (frame.empty())
                continue;
            vector<Rect> unnLogos;
            unn.detectMultiScale(frame, unnLogos);
            cout << unnLogos.size() << endl;
            imshow("edges", frame);
            waitKey(100);
        }

    }
    else
    {
        cout << "Declare a source of images to detect on." << endl;
    }

    return 0;
}



