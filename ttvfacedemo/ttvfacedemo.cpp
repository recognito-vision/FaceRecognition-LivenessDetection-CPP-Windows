// ttvfacedemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <stdio.h>
#include "ttvfaceengine.h"

std::vector<int8_t> convertToInt8Array(const std::vector<float>& input) {
    std::vector<int8_t> output(input.size() * sizeof(float));  // Allocate bytes
    memcpy(output.data(), input.data(), input.size() * sizeof(float));
    return output;
}

void printAttributes(FaceBox box) {
    printf("Face box: %d, %d, %d, %d\n", int(box.x1), int(box.y1), int(box.x2), int(box.y2));
    printf("Liveness: %f\n", box.liveness);
    printf("Yaw: %f, Roll: %f, Pitch: %f\n", box.yaw, box.roll, box.pitch);
    printf("Left_Eye: %s(%f),  Right_Eye: %s(%f)\n", (box.left_eye > 0.5) ? "Close" : "Open", box.left_eye, (box.right_eye > 0.5) ? "Close" : "Open", box.right_eye);
    printf("Face Occlusion: %s(%f)\n", (box.face_occlusion > 0.5) ? "Yes" : "No", box.face_occlusion);
    printf("Face Quality: %f\n", box.face_quality);
}

int main()
{
    std::cout << "Face Recognition - Windows\n";

    const char* hwid = ttv_get_hwid();
    printf("hwid: %s\n", hwid);
    int ret = ttv_set_activation((char*)"ajzxmuSmUNtYvVueVZH + q3jg + EUWjdcpOJUdLfZ2le7lYh7VQhW4Gmb / 9pBxlIT1Cok + J0v / BJP /\
        emEkHUsGGRbIf0HPGjQbWQCVYWWMRWM5x3BWPS2iN7Kb6G3M6M6ztKk + u2JZaAyO5W / l0BYHy0c8\
        ActgbioqIW8fcjIXnt48kUwOAfa81DYxw / 58iY2bEmxBWSeBOo4ySv7VoQ5ZokTsUskeBwbe5piV\
        qib2T8U9byAsIsnzR + UrRelqfJThL1onvakxIaCuKcx0EaMQJYDrckNrwR / fcaE81jy3kpmDFYbJ\
        kOghVVdngGQ04k1rdwgha273U9iNCoQz62wf2w ==");

    printf("set activation: %d\n\n", ret);

    ret = ttv_init((char*)".");

    printf(" --------------   Image 1  ----------------- \n");

    cv::Mat image1 = cv::imread("image1.jpg");
    printf("image1: width = %d, height = %d\n", image1.cols, image1.rows);

    std::vector<FaceBox> faceBoxes1;
    ret = ttv_detect_face(image1, faceBoxes1, false, true, true);
    printf("face1 detect: ret = %d, num = %d\n", ret, faceBoxes1.size());

    std::vector<float> feat1;
    if (faceBoxes1.size() > 0) {
        printAttributes(faceBoxes1[0]);
        ttv_feature_extract(image1, faceBoxes1[0].landmark, feat1);
    }
    
    printf("\n\n");

    printf(" --------------   Image 2  ----------------- \n");
    cv::Mat image2 = cv::imread("image2.jpg");
    printf("image2: width = %d, height = %d\n", image2.cols, image2.rows);

    std::vector<FaceBox> faceBoxes2;
    ret = ttv_detect_face(image2, faceBoxes2, false, true, true);
    printf("face2 detect: ret = %d, num = %d\n", ret, faceBoxes2.size());

    std::vector<float> feat2;
    if (faceBoxes2.size() > 0) {
        printAttributes(faceBoxes2[0]);
        ttv_feature_extract(image2, faceBoxes2[0].landmark, feat2);
    }
   
    printf("\n ==============   Matching Score  ================\n");
    float score = ttv_compare_feature(feat1, feat2);
    printf("score: %f\n %s\n", score, score >= 80 ? "Same Person": "Different Person");
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
