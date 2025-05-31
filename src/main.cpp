#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat hwnd2mat(HWND hwnd) {
    HDC hwindowDC, hwindowCompatibleDC;

    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    cv::Mat src;
    BITMAPINFOHEADER bi;

    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    RECT windowsize;
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = srcheight;
    width = srcwidth;

    src.create(height, width, CV_8UC4);

    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    SelectObject(hwindowCompatibleDC, hbwindow);
    BitBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, SRCCOPY);

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // Top-down image
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

int main() {
    HWND hwnd = GetDesktopWindow(); // Capture entire desktop
    cv::Mat screenshot = hwnd2mat(hwnd);
    
    // Convert screenshot from BGRA to BGR (remove alpha channel)
    cv::Mat screenshot_bgr;
    cv::cvtColor(screenshot, screenshot_bgr, cv::COLOR_BGRA2BGR);

    cv::Mat template_img = cv::imread("template.png", cv::IMREAD_COLOR);
    if (template_img.empty()) {
        std::cerr << "Template image not found!" << std::endl;
        return -1;
    }

    // Debug: Print image information
    std::cout << "Screenshot size: " << screenshot_bgr.size() << " channels: " << screenshot_bgr.channels() << std::endl;
    std::cout << "Template size: " << template_img.size() << " channels: " << template_img.channels() << std::endl;

    // Ensure both images have the same type
    if (screenshot_bgr.type() != template_img.type()) {
        std::cerr << "Image types don't match!" << std::endl;
        std::cerr << "Screenshot type: " << screenshot_bgr.type() << std::endl;
        std::cerr << "Template type: " << template_img.type() << std::endl;
        return -1;
    }

    cv::Mat result;
    cv::matchTemplate(screenshot_bgr, template_img, result, cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    std::cout << "Best match at: " << maxLoc << " with score: " << maxVal << std::endl;

    // Draw matching rectangle on the BGR image for display
    cv::rectangle(screenshot_bgr, maxLoc, maxLoc + cv::Point(template_img.cols, template_img.rows), cv::Scalar(0,255,0), 2);
    cv::imshow("Match", screenshot_bgr);
    cv::waitKey(0);

    return 0;
}
