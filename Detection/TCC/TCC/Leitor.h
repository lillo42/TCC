#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#pragma endregion

#pragma region std

#include <windows.h> 
#include <stdio.h>
#include <vector>
#include <iostream>

#pragma endregion

using namespace cv;
using namespace std;

class Leitor
{
public:
	Leitor();
	~Leitor();

	void LerImagemPasta(vector<Mat>& retorno, string pasta);
private:
	vector<string> GetAllFilesNamesWithinFolder(string folder);
};

