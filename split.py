import sys

print len(sys.argv), sys.argv[0]
if len(sys.argv) >= 1:
    save_file = sys.argv[1]         # res
    save_title_file = sys.argv[2]  # title
    save_data_info = sys.argv[3]   # info

totalpic = 0
NumFile = 0
with open(save_data_info, 'r') as f:
    ans = f.readline()
    NumFile = ans.split(' ')[0]
    print "NumFile: ", NumFile

file_num = 0
split_file_name = '_'.join(save_file.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_res.txt"
split_file_title_name = '_'.join(save_title_file.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_title.txt"
split_file_info_name = '_'.join(save_data_info.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_info.txt"
print split_file_name, split_file_title_name
split_res = open(split_file_name, 'w')
split_title = open(split_file_title_name, 'w')
split_info = open(split_file_info_name, 'w')

info_file = 0
info_pic = 0
with open(save_file, 'r') as res, \
        open(save_title_file, 'r') as title:
    while True:
        ans = title.readline()
        if not ans:
            break
        NumPic = ans.split(' ')[1]
        if totalpic > 0 and totalpic % 500000 == 0:
            print totalpic
            print "done ", split_file_name
            split_res.close()
            split_title.close()
            split_info.write("%d %d\n" % (info_file, info_pic))
            split_info.close()
            info_pic = 0
            info_file = 0
            file_num += 1
            split_file_name = '_'.join(save_file.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_res.txt"
            split_file_title_name = '_'.join(save_title_file.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_title.txt"
            split_file_info_name = '_'.join(save_data_info.split('.')[0].split('_')[:-1]) + "_" + str(file_num) + "_info.txt"
            split_res = open(split_file_name, 'w')
            split_title = open(split_file_title_name, 'w')
            split_info = open(split_file_info_name, 'w')

        split_title.write(ans)
        for num in range(0, int(NumPic)):
            info_pic += 1
            tmp = res.readline()
            split_res.write(tmp)

        totalpic += 1
        info_file += 1

split_info.write("%d %d\n" % (info_file, info_pic))
split_info.close()
split_res.close()
split_title.close()