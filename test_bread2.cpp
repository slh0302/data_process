#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iterator>
#include <sys/stat.h>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#define NUM_OF_THREADS 50
//343 MB (360,086,024 字节) 1000
#pragma omp parallel shared
using namespace cv;
using namespace std;
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
//char point[10][2000000];
char* Pic_read(char* file_name) {
	FILE * fpPhoto;
	int     iRead;
	char    szBuf[100];
	struct stat st1;
	stat(file_name, &st1);
	fpPhoto = fopen(file_name, "rb");
	char* buff = new char[st1.st_size];
	//fwrite1 = fopen("test1.jpg", "wb");
	if (!fpPhoto)
	{
		printf("打开文件失败！\n");
		return NULL;
	}
	long long total = 0;
	fread(buff, 1, st1.st_size, fpPhoto);
	fclose(fpPhoto);
	return buff;
}
int main(int args, char** argv) {

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
	//clock_t st, end;
	time(&st);

	char* point[1000];


	for (int i = 0; i < end_file - begin_file; i++) {
	//	//	im[i] = imread(totalFile[i].FilePath);
		point[i] = Pic_read(totalFile[i + begin_file].FilePath);
		if (i % 100 == 0) {
			time(&end);
			double cost = difftime(end,st);
			std::cout << cost << " " << i << std::endl;
		}
	}


	//point[0] = Pic_read(totalFile[end_file].FilePath);
	//CvMat mat = cvMat(2104, 3392, CV_8UC1, point[0]);
	//IplImage *p = cvDecodeImage(&mat, 1);
	//	Mat image;
	//cvSaveImage("saveImage.jpg", p);
	//cv::Mat m = cv::cvarrToMat(p);
	//cvNamedWindow("a");

	//imwrite("test3.jpg", m);

	//cvReleaseImage(&p);
	//cvShowImage("a", p);
	//	cvWaitKey(0);
	//}
	time(&end);
	double cost = difftime(end, st);
	//printf("%f/n", cost);
	std::cout << cost << std::endl;
	//std::cin >> cost;
	cin >> cost;
	//	std::cout << handlePic << std::endl;
	return 0;
}
