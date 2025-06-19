#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 加载图像
    cv::Mat image = cv::imread("sample.png");
    if (image.empty()) {
        std::cerr << "无法加载图像，请确认 sample.jpg 文件是否存在！" << std::endl;
        return -1;
    }

    // 转为灰度图
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 保存图像
    if (cv::imwrite("output.jpg", grayImage)) {
        std::cout << "已成功保存为 output.jpg" << std::endl;
    }
    else {
        std::cerr << "保存图像失败！" << std::endl;
        return -2;
    }

    // 显示图像（可选）
    cv::imshow("Original", image);
    cv::imshow("Gray", grayImage);
    cv::waitKey(0); // 等待按键
    return 0;
}
