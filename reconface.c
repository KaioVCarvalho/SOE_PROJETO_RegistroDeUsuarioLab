#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

int main(int argc, char** argv)
{
    // Load the registered images and labels
    vector<Mat> images;
    vector<int> labels;
    vector<string> names;
    ifstream file("images.txt");
    string line;
    while (getline(file, line))
    {
        images.push_back(imread(line, IMREAD_GRAYSCALE));
        labels.push_back(line[0] - '0');
    }

    // Load the user names
    ifstream usersFile("users.txt");
    while (getline(usersFile, line))
    {
        string name;
        int label;
        stringstream ss(line);
        ss >> label;
        getline(ss, name, ',');
        getline(ss, name);
        names.push_back(name);
    }

    // Create the face recognizer
    Ptr<FaceRecognizer> model = FisherFaceRecognizer::create();
    model->train(images, labels);

    // Load the test image
    Mat testImage = imread("test.jpg", IMREAD_GRAYSCALE);

    // Predict the label of the test image
    int predictedLabel = model->predict(testImage);

    cout << "Predicted label: " << names[predictedLabel] << endl;

    return 0;
}