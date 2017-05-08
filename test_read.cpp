#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#define NUM_OF_THREADS 50
#pragma omp parallel shared
using namespace cv;
struct pic {
	int x;
	int y;
	int width;
	int height;
	int num;
};
struct file_info {
	char FilePath[50];
	int numOfObject;
};
std::string file_prefix = "";
void thread_crop(pic* tempPic, file_info* tempFile, int num);

int main(int args, char** argv) {
	if (args < 2) {
		std::cout << "args not enough" << std::endl;
		return 0;
	}
	std::cout << "done 1" << std::endl;

	std::string info_file_name = argv[1];
	std::string res_file_name = argv[2];
	std::string title_file_name = argv[3];
	//inital
	int FileNum = 0;
	int PicNum = 0;
	std::ifstream inInfo(info_file_name.c_str(), std::ios::in);
	inInfo >> FileNum >> PicNum;
	inInfo.close();

	int index_end = res_file_name.find_last_of("_");
	int index_slash = res_file_name.find_last_of("/");
	file_prefix = res_file_name.substr(index_slash + 1, index_end - index_slash - 1);

	pic* totalPic = new pic[PicNum];
	file_info* totalFile = new file_info[FileNum];
	int begin_file = atoi(argv[4]);
	int end_file = atoi(argv[5]);
	int startpic = atoi(argv[6]);
	std::cout << startpic << " " << FileNum << std::endl;

	//Open file
	FILE* inRes = fopen(res_file_name.c_str(), "rb");
	FILE* inTitle = fopen(title_file_name.c_str(), "rb");
	fread(totalPic, sizeof(pic), PicNum, inRes);
	fread(totalFile, sizeof(file_info), FileNum, inTitle);
	fclose(inRes);
	fclose(inTitle);

	//Handle
	time_t st, end;
	time(&st);
	FileNum = end_file;
	int tempNumOfFile = (FileNum - begin_file) / NUM_OF_THREADS + 1;//500000,上取整
	int DoneNum = begin_file, handleNum = 0, handlePic = startpic;
	Mat* im = new Mat[FileNum];
	int op = 0;
	for (int i = begin_file; i < FileNum; i++) {
//		std::cout<<"num: "<<i<<std::endl;
		op++;
		if(op % 100 == 0){
			std::cout<<"op: "<<op<<std::endl;
			time(&end);
			double cost = difftime(end, st);
			std::cout << cost << std::endl;
		}
		im[i] = imread(totalFile[i].FilePath);
	}
	time(&end);
	double cost = difftime(end, st);
	//printf("%f/n", cost);
	std::cout << cost << std::endl;
	//std::cin >> cost;
	std::cout << handlePic << std::endl;
	return 0;
}

void thread_crop(pic* tempPic, file_info* tempFile, int num)
{
	int k = 0, totalProcess = 0;
	while (k < num) {
		Mat image = imread(tempFile[k].FilePath);
		//file name
		std::string file_name = std::string(tempFile[k].FilePath);
		int index_end = file_name.find_last_of(".");
		int index_slash = file_name.find_last_of("/");
		file_name = file_name.substr(index_slash + 1, index_end - index_slash - 1);
		int i = 0;
		for (i = 0; i < tempFile[k].numOfObject; i++) {
			IplImage qImg;
			Rect rect(tempPic[totalProcess + i].x, tempPic[totalProcess + i].y, tempPic[totalProcess + i].width, tempPic[totalProcess + i].height);
			qImg = IplImage(image(rect)); // cv::Mat -> IplImage
			std::stringstream ss;
			ss << tempPic[totalProcess + i].num;
			std::string outname1 = file_name + "_" + ss.str() + ".jpg";
			cvSaveImage(std::string("/media/result/dataRes/" + outname1).c_str(), &qImg);
		}
		totalProcess += i;
		k++;
	}//2622197 ms debug 8000
}
