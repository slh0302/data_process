import sys
import os
# file name
file_prefix = sys.argv[1]
path_prefix_tmp = sys.argv[2]
FileNamePlus = 0
exec_file = ["wd_all_2_0", "wd_all_2_1", "wd_all_2_2"]
dir_name = ["wd_all_2_new_0/", "wd_all_2_new_1/", "wd_all_2_new_2/"]
# exec_file = ["wd_all_1"]
# ["wd_all_3_new_0", "wd_all_3_new_1", "wd_all_3_new_2", "wd_all_3_new_3", "wd_all_3_new_4" ,
# "wd_all_3_new_5", "wd_all_3_new_6", "wd_all_3_new_7"]
file_test = 0
print path_prefix_tmp
for handle, dname in zip(exec_file, dir_name):
    file_list_name = file_prefix + handle
    path_prefix = path_prefix_tmp + dname

    if not os.path.exists(file_list_name):
        print "file list wrong " + file_list_name
        exit()

    if not os.path.isdir(path_prefix):
        print "Dir not exist " + path_prefix
        exit()

    with open(file_list_name, 'r') as f, \
         open(file_list_name+".out", 'w') as out,\
         open(file_list_name+".wrong", 'w') as error:
        while True:
            Name = f.readline()
            if not Name:
                break

            NamePrefix = Name.split('.')[0]
            TmpArray = NamePrefix.split('_')
            lengthArray = len(TmpArray)
            OriginPic = '_'.join(TmpArray[:lengthArray-2]) + ".jpg"
            Rename = TmpArray[-2]
            Rename = str(int(Rename) - FileNamePlus) + ".jpg"
            NumInOrigin = TmpArray[-1]
            # rename
            # print path_prefix + Name[:-1]
            # print path_prefix + Rename
            if os.path.exists(path_prefix + Name[:-1]):
                file_test += 1
                # print "rename", path_prefix + Name[:-1], path_prefix + Rename
                # os.rename(path_prefix + Name[:-1], path_prefix + Rename)
            elif os.path.exists(path_prefix + Rename):
                error.write("%s %s %s\n" % (path_prefix + Name[:-1], "  Already Rename:  ", path_prefix + Rename))
            else:
                error.write("%s %s %s\n" % (path_prefix + Name[:-1], "  File Lost, Origin name: ", OriginPic))

            out.write("%s %s %d\n" % (Rename, OriginPic, int(NumInOrigin)))

    FileNamePlus += 1000000

print path_prefix+Name, path_prefix+Rename
