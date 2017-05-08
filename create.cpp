#include <fstream>
#include <iostream>
#include <string>
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
using namespace std;
int main(int args, char** argv) {
	//open file
	std::string info_file_name = argv[1];
	std::string res_file_name = argv[2];
	std::string title_file_name = argv[3];
	int FileNum = 0;
	int PicNum = 0;
	std::ifstream inRes(res_file_name.c_str(), std::ios::in);
	std::ifstream inTitle(title_file_name.c_str(), std::ios::in);

	std::ifstream inInfo(info_file_name.c_str(), std::ios::in);
	inInfo >> FileNum >> PicNum;
	inInfo.close();

	if (args < 2) {
		cout << "args not enough" << endl;
		return 0;
	}
	//inital
	pic* totalPic = new pic[PicNum];
	file_info* totalFile = new file_info[FileNum];
	//trans
	int k = 0;
	string fileName;
	int pic_num = 0, totalProcess = 0, height = 0, width = 0;
	while (k < FileNum) {
		inTitle >> fileName >> pic_num >> width >> height;
		int j = 0;
		for (; j < fileName.length(); j++) {
			totalFile[k].FilePath[j] = fileName[j];
		}
		totalFile[k].FilePath[j] = '\0';
		totalFile[k].numOfObject = pic_num;
		totalFile[k].width = width;
		totalFile[k].height = height;
		int i = 0;
		for (; i < pic_num; i++) {
			inRes >> totalPic[totalProcess + i].x >> totalPic[totalProcess + i].y
				>> totalPic[totalProcess + i].width >> totalPic[totalProcess + i].height
				>> totalPic[totalProcess + i].num	>>  totalPic[totalProcess + i].name;
		}
		totalProcess += i;
		k++;
	}
	//output
	std::string name_prefix = "./result/";
	//get res_file_name
	int index_end = res_file_name.find_last_of(".");
	int index_slash = res_file_name.find_last_of("/");
	res_file_name = res_file_name.substr(index_slash + 1, index_end - index_slash - 1);
	std::string res_out_name = name_prefix + res_file_name + ".data";

	//get title_file_name
	index_end = title_file_name.find_last_of(".");
	index_slash = title_file_name.find_last_of("/");
	title_file_name = title_file_name.substr(index_slash + 1, index_end - index_slash - 1);
	std::string title_out_name = name_prefix + title_file_name + ".data";

	FILE* outfile = fopen(res_out_name.c_str(), "wb");
	fwrite(totalPic, sizeof(pic), PicNum, outfile);


	FILE* outfile2 = fopen(title_out_name.c_str(), "wb");
	fwrite(totalFile, sizeof(file_info), FileNum, outfile2);


	fclose(outfile2);
	fclose(outfile);
	return 0;
}