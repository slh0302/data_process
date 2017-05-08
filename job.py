import os
import time
from subprocess import Popen, PIPE

# 524774 993021
co = 524774
NumFile = 0
File_Handle = 100
startPic = 0
FileNamePlus = 2000000
FileResultPrefix = "/media/result/"
FileDataPrefix = "/media/data/"
exec_file = ["20160514", "20160515", "20160516", "20160517"
    , "20160518", "20160519", "20160520", "20160521"
    , "20160522", "20160524", "20160525"]

for handle in exec_file:
    begin_time = time.clock()
    print handle
    result_dir = FileResultPrefix + handle

    if not os.path.isdir(result_dir):
        os.mkdir(result_dir)

    if not os.path.isfile("./data/" + handle + "_title.txt"):
        exit()
    elif not os.path.isfile("./result/" + handle + "_title.data"):
        ChangeScript = "sed -i 's/F:/\/media\/data/g' ./data/" + handle + "_title.txt"
        resp = Popen(ChangeScript, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
        print "Done ChangeScript"

    if not os.path.isfile("./result/" + handle + "_title.data"):
        CreateScript = "./create " + "./data/" + handle + "_info.txt " + "./data/" + \
                       handle + "_res.txt " + "./data/" + handle + "_title.txt "
        print CreateScript
        resp = Popen(CreateScript, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
        print os.path.isfile("./result/" + handle + "_title.data"), "Done CreateScript"
        if not os.path.isfile("./result/" + handle + "_title.data"):
            exit()

    with open("./data/" + handle + "_info.txt", 'r') as f:
        ans = f.readline()
        NumFile = ans.split(' ')[0]
        print "NumFile: ", NumFile

    if NumFile == 0:
        continue

    handle_script = "./test " + "./data/" + handle + "_info.txt " + "./result/" + \
                    handle + "_res.data " + "./result/" + handle + "_title.data " + \
                    "0 " + str(NumFile) + " 0 " + str(FileNamePlus)
    print handle_script
    resp = Popen(handle_script, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
    end_time = time.clock()
    print "read: %f s" % (end_time - begin_time)
    FileNamePlus += 2000000
# print begin
# end = NumFile
# handle_script = "opencv_test.exe " + str(co) + " 993021 " + str(begin) + " " + str(end) + " " + str(startPic)
# resp = Popen(handle_script, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
# 2000 begin end startpic
