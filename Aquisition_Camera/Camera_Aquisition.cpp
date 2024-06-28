#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;

int main() {
    // Open the first camera
    VideoCapture cap1(0);
    if (!cap1.isOpened()) {
        cerr << "Error: Could not open camera 1" << endl;
        return -1;
    }

    // Open the second camera
    VideoCapture cap2(1);
    if (!cap2.isOpened()) {
        cerr << "Error: Could not open camera 2" << endl;
        return -1;
    }

    // Set camera resolution 
    cap1.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap2.set(CAP_PROP_FRAME_WIDTH, 1920);

    // Get the current date and time for file naming
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now_c));

    // Set the base file path for saving images
    string base_path = "/mnt/ssd/capture_";

    while (true) {
        Mat frame1, frame2;
        
        // Capture frames from each camera
        cap1 >> frame1;
        cap2 >> frame2;

        if (frame1.empty() || frame2.empty()) {
            cerr << "Error: Could not grab frames" << endl;
            break;
        }

        // Generate file names with timestamps
        string file1 = base_path + string(time_str) + "_cam1.jpg";
        string file2 = base_path + string(time_str) + "_cam2.jpg";

        // Save the frames as images
        imwrite(file1, frame1);
        imwrite(file2, frame2);

        // Wait for a key press for 30ms
        if (waitKey(30) >= 0) break;
    }

    cap1.release();
    cap2.release();
    destroyAllWindows();

    return 0;
}

