
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>  
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#define NUM_OF_THREADS 50
//343 MB (360,086,024 字节) 1000
#pragma omp parallel shared
using namespace cv;
struct pic {
	int x;
	int y;
	int width;
	int height;
	int num;
	int name;
};
struct file_info {
	char FilePath[50];
	int numOfObject;
	int height;
	int width;
};
std::string file_prefix = "";
int FileNamePlus = 0;
void thread_crop(pic* tempPic, file_info* tempFile, int num);

char* Pic_read(char* file_name) {
	FILE * fpPhoto;
	int     iRead;
	char    szBuf[100];
	struct stat st1;
	stat(file_name, &st1);
	fpPhoto = fopen(file_name, "rb");
	//fwrite1 = fopen("test1.jpg", "wb");
	if (!fpPhoto)
	{
		std::cout << "打开文件失败  " << file_name << std::endl;
		//printf("打开文件失败！%s\n",file_name);
		return NULL;
	}
	char* buff = new char[st1.st_size];
	long long total = 0;
	fread(buff, 1, st1.st_size, fpPhoto);
	fclose(fpPhoto);
	return buff;
}

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
	FileNamePlus = atoi(argv[7]);
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
	boost::thread_group threads;
	FileNum = end_file;
	int tempNumOfFile = (FileNum - begin_file) / NUM_OF_THREADS + 1;//500000,上取整
	int DoneNum = begin_file, handleNum = 0, handlePic = startpic;
	for (int i = 0; i < NUM_OF_THREADS; i++) {
		if (DoneNum + tempNumOfFile < FileNum) {
			int temp = handlePic; // last value
			for (int j = DoneNum; j < DoneNum + tempNumOfFile; j++) {
				handlePic += totalFile[j].numOfObject;
			}
			threads.create_thread(boost::bind(&thread_crop, &totalPic[temp], &totalFile[DoneNum], tempNumOfFile));
			DoneNum += tempNumOfFile;
		}
		else {
			handleNum = FileNum - DoneNum;
			threads.create_thread(boost::bind(&thread_crop, &totalPic[handlePic], &totalFile[DoneNum], handleNum));
		}
	}
	for (int j = DoneNum; j < DoneNum + handleNum; j++) {
		handlePic += totalFile[j].numOfObject;
	}
	threads.join_all();//14957 614819ms 8000  20-296-14154 100-277-37593 30-438-15098 50-875-13066 60-612-22715
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
		char* temp = Pic_read(tempFile[k].FilePath);
		if (temp == NULL) {
			totalProcess += tempFile[k].numOfObject;
			k++;
			continue;
		}
		CvMat mat = cvMat(tempFile[k].height, tempFile[k].width, CV_8UC1, temp);
		IplImage *p = cvDecodeImage(&mat, 1);
		cv::Mat image = cv::cvarrToMat(p);
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
			std::stringstream ss1;
			ss1 << tempPic[totalProcess + i].name + FileNamePlus;
			std::string outname1 = file_name + "_" + ss1.str() + "_" + ss.str() + ".jpg";
			cvSaveImage(std::string("/media/result/" + file_prefix + "/" + outname1).c_str(), &qImg);
		}
		cvReleaseImage(&p);
		delete[] temp;
		totalProcess += i;
		k++;
	}//2622197 ms debug 8000 
}
