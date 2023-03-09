#include <iostream>
#include <opencv2/opencv.hpp>

//"rtsp://admin:admin@192.168.0.28/live"
//"rtsp://admin:admin@192.168.0.31/live"
//"rtsp://admin:admin@192.168.0.36/live"
//"rtsp://admin:admin@192.168.0.41/live"
//"rtsp://admin:admin@192.168.0.50/live"
//"rtsp://admin:admin@192.168.0.51/live"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    std::cout << "Starting rtsp stream capture..." << std::endl;
    // Open the RTSP stream
    cv::VideoCapture cap("rtsp://admin:admin@192.168.0.51/live");
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open RTSP stream" << std::endl;
        return -1;
    }

    // Create a window to display the stream
    cv::namedWindow("RTSP Stream", cv::WINDOW_NORMAL);

    while (true)
    {
        cv::Mat frame;
        // Read a frame from the RTSP stream
        if (!cap.read(frame))
        {
            std::cerr << "Failed to read frame from RTSP stream" << std::endl;
            break;
        }

        // Display the frame in the window
        cv::imshow("RTSP Stream", frame);

        // Wait for the user to press a key
        int key = cv::waitKey(1);
        if (key == 27 || key == 'q')
        {
            // If the user pressed either ESC or Q, stop the program
            break;
        }
    }

    // Release the resources
    std::cout << "Releasing rtsp stream..." << std::endl;
    cap.release();
    cv::destroyAllWindows();
    std::cout << "Ended Bye!" << std::endl;
    return 0;
}
