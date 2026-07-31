#include <opencv2/opencv.hpp>
#include <sys/resource.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>


const char *fname = "../../../data/testimage3r1080p.jpg";
// const char *fname = "../../../data/testimage4r1080p.jpg";


//
long get_rss_kb() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;   // на Linux — в KB, на macOS — в байтах!
}

//
long get_current_rss_kb() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            return std::stol(line.substr(6));  // уже в KB
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {

    if(argc !=2) { 
        std::cerr << "File Name missed" << std::endl;
        return -1;
    }

    // 1. Загрузка изображения
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return -1;
    }

    // 2. В grayscale + бинаризация
    cv::Mat gray, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);

    // 3. Поиск контуров
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    long mem_before = get_current_rss_kb();
    auto time_start = std::chrono::high_resolution_clock::now();

    cv::findContours(binary, contours, hierarchy,
                     cv::RETR_CCOMP,           // или RETR_EXTERNAL / RETR_CCOMP / RETR_TREE
                     cv::CHAIN_APPROX_SIMPLE);

    auto time_end = std::chrono::high_resolution_clock::now();
    long mem_after = get_current_rss_kb();

    double elapsed_ms = std::chrono::duration<double, std::milli>(time_end - time_start).count();
    

    std::cout << "Найдено контуров: " << contours.size()
              << ", время: " << elapsed_ms << " ms" << std::endl;


    std::cout << "Прирост RSS: " << (mem_after - mem_before) << " KB" << std::endl;

    // 4. Рисуем контуры
    cv::Mat result = img.clone();
    cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2);

    // Memory stat

    size_t contours_memory = 0;

    // Память самих векторов точек
    for (const auto& contour : contours) {
        contours_memory += contour.capacity() * sizeof(cv::Point);
    }
    contours_memory += contours.capacity() * sizeof(std::vector<cv::Point>);

    // + hierarchy
    contours_memory += hierarchy.capacity() * sizeof(cv::Vec4i);

    std::cout << "Память контуров + hierarchy: "
            << int(contours_memory / 1024.0) << " KB" << std::endl;

    // 5. Сохраняем / показываем
    cv::imwrite("result_cv.jpg", result);
    cv::imshow("Contours", result);
    cv::waitKey(0);

    return 0;
}

