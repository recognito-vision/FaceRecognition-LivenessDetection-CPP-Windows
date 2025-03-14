#pragma once

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

#include <opencv2/opencv.hpp>

#ifndef MYLIBRARY_EXPORTS
struct FaceBox {
    float x1;
    float y1;
    float x2;
    float y2;
    float landmark[136];
    float liveness;
    float yaw;
    float roll;
    float pitch;
    float face_occlusion;
    float left_eye;
    float right_eye;
    float face_quality;
};
#else
#include "definition.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

	MYLIBRARY_API const char* ttv_get_hwid();
	MYLIBRARY_API int ttv_set_activation(char* license);
    MYLIBRARY_API int ttv_init(char* dictPath);

    // C++ APIs
    MYLIBRARY_API int ttv_detect_face(cv::Mat img, std::vector<FaceBox>& faceBoxes, bool check_liveness, bool check_eye_closeness, bool check_face_occlusion);
    MYLIBRARY_API int ttv_feature_extract(cv::Mat img, float* landmark, std::vector<float>& feature);
    MYLIBRARY_API float ttv_compare_feature(std::vector<float> feature1, std::vector<float> feature2);
    
    // C-Sharp APIs
    MYLIBRARY_API int ttv_detect_face_c_sharp(const unsigned char* imageData, int width, int height, int stride, FaceBox* boxes, int maxCount, bool check_liveness, bool check_eye_closeness, bool check_face_occlusion);
    MYLIBRARY_API int ttv_feature_extract_c_sharp(const unsigned char* imageData, int width, int height, int stride, float* landmark, float* feature);
    MYLIBRARY_API float ttv_compare_feature_c_sharp(const float* feature1, const float* feature2, int vectorLength);
#ifdef __cplusplus
}
#endif