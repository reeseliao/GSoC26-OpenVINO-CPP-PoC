#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;

int main() {
    cout << "=========================================" << endl;
    cout << "[SYSTEM] OpenVINO GSoC PoC: C++ Native Video Ingestion" << endl;
    cout << "=========================================" << endl;

    // 1. 因为视频和 exe 在同一个文件夹，直接写名字，彻底消灭路径斜杠问题！
    string video_path = "test_video.mp4"; 
    
    // 2. 强行指定使用 Windows 原生的 MSMF 后端解码，不依赖 OpenCV 的外部 FFmpeg
    VideoCapture cap(video_path);

    if (!cap.isOpened()) {
        cerr << " Error: Cannot open the video file. Please check the path." << endl;
        return -1;
    }

    // 获取视频元数据
    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
    double fps = cap.get(CAP_PROP_FPS);
    cout << "[INFO] Video Loaded. Total Frames: " << total_frames << ", FPS: " << fps << endl;

    int frame_interval = 30; // 每 30 帧抽取一次 (模拟 RAG 关键帧提取)
    int extracted_count = 0;
    Mat frame;

    cout << "[INFO] Starting high-performance frame extraction (Interval: " << frame_interval << ")..." << endl;

    // 启动高精度计时器
    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < total_frames; i++) {
        cap >> frame; // 极速读取下一帧
        if (frame.empty()) break;

        if (i % frame_interval == 0) {
            // 在实际工程中，这里会把 frame 转为 Tensor 喂给 OpenVINO
            // 这里我们只是验证抽取逻辑
            extracted_count++;
        }
    }

    // 停止计时
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