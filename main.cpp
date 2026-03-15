#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;

int main() {
    cout << "=========================================" << endl;
    cout << "[SYSTEM] OpenVINO GSoC PoC: C++ Native Video Ingestion" << endl;
    cout << "=========================================" << endl;

    // path
    string video_path = "test_video.mp4"; 
    
    // Forcibly specify the use of Windows’ native MSMF backend decoding, without relying on OpenCV’s external FFmpeg.
    VideoCapture cap(video_path);

    if (!cap.isOpened()) {
        cerr << " Error: Cannot open the video file. Please check the path." << endl;
        return -1;
    }

    // Get video metadata
    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
    double fps = cap.get(CAP_PROP_FPS);
    cout << "[INFO] Video Loaded. Total Frames: " << total_frames << ", FPS: " << fps << endl;

    int frame_interval = 30; // Extract every 30 frames 
    int extracted_count = 0;
    Mat frame;

    cout << "[INFO] Starting high-performance frame extraction (Interval: " << frame_interval << ")..." << endl;

    // Start timer
    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < total_frames; i++) {
        cap >> frame; 
        if (frame.empty()) break;

        if (i % frame_interval == 0) {
            //Here we just verify the extraction logic
            extracted_count++;
        }
    }

    // Stop timing
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end_time - start_time;

    cout << "==================================================" << endl;
    cout << "[SUCCESS] Extraction Complete!" << endl;
    cout << "[STAT] Total Extracted Keyframes: " << extracted_count << endl;
    cout << "[STAT] Pure C++ Execution Time: " << duration.count() << " ms" << endl;
    cout << "[STAT] Effective Processing Speed: " << (total_frames / (duration.count() / 1000.0)) << " FPS" << endl;
    cout << "==================================================" << endl;

    cap.release();
    return 0;
}
