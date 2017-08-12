import sys
import os

exec_prefix = sys.argv[1]
data_file_prefix = sys.argv[2]
exec_file = ["wd_all_2_new_0", "wd_all_2_new_1", "wd_all_2_new_2"]

for handle in exec_file:
    file_path = exec_prefix + handle
    if not os.path.exists(file_path):
        print "list file not exists"
        exit()

    data_file_path = data_file_prefix + handle
    if not os.path.exists(data_file_path + "_info.txt"):
        print "data file not exists"
        exit()

    line_num = 0
    isContext = True
    context = ""
    with open(file_path, 'r') as file_list, \
         open(data_file_path + "_res.txt", 'r') as res_data:
        while True:
            res = res_data.readline()
            if not res:
                break

            if isContext:
                context = file_list.readline()

            line_num += 1
            res_name = res.split(' ')[-1]
            Name = context.split(' ')[0].split('.')[0]

            if int(Name) != int(res_name):
                print "[Line]: ", line_num, " File Not Found: ", res
                isContext = False
            else:
                isContext = True