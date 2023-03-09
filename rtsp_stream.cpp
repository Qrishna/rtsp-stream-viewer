
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>

using namespace std;

std::string get_current_timestamp_iso() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H-%M-%S ") ;
    return ss.str();
}


int main(int argc, char **argv) {

    std::string defaultUrl = "rtsp://admin:admin@192.168.0.41/live";
    std::string url = argc > 1 ? argv[1] : defaultUrl;

    std::cout << get_current_timestamp_iso() << "Starting rtsp stream capture..." << url << std::endl;
    cv::VideoCapture cap;
    bool isConnected = false;
    bool debug = true;

    while (!isConnected) {
        isConnected = cap.open(url);
        if (!isConnected) {
            std::cerr << get_current_timestamp_iso() << "Failed to open RTSP stream. Retrying in 5 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    if (debug) {
        cv::namedWindow("RTSP Stream", cv::WINDOW_NORMAL);
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    double input_fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << get_current_timestamp_iso() << "Frame width is: " << frame_width << std::endl;
    std::cout << get_current_timestamp_iso() << "Frame height is: " << frame_height << std::endl;

    std::cout << get_current_timestamp_iso() << "Input FPS is: " << input_fps << std::endl;

    while (true) {
        cv::Mat frame;
        if (!cap.read(frame)) {
            std::cerr << get_current_timestamp_iso() << "Failed to read frame from RTSP stream. Retrying in 5 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            isConnected = false;
            while (!isConnected) {
                isConnected = cap.open(url);
                if (!isConnected) {
                    std::cerr << get_current_timestamp_iso() << "Failed to open RTSP stream. Retrying in 5 seconds..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                }
            }
            continue;
        }

        if (debug) {
            cv::imshow("RTSP Stream", frame);
        }

        int key = cv::waitKey(1);
        if (key == 27 || key == 'q') {
            break;
        }
    }

    // Release the resources
    std::cout << get_current_timestamp_iso() << "Releasing rtsp stream..." << std::endl;
    cap.release();
    cv::destroyAllWindows();
    std::cout << get_current_timestamp_iso() << "Destroyed Windows. Bye!" << std::endl;
    return 0;
}
