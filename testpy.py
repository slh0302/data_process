import os
import time
from subprocess import Popen, PIPE

handle = "20160515"
co = 524774
NumFile = 0
File_Handle = 100
startPic = 0
FileResultPrefix = "/media/result/"

result_dir = FileResultPrefix + handle
if not os.path.isdir(result_dir):
    os.mkdir(result_dir)

if not os.path.isfile("./data/" + handle + "_title.txt"):
    exit()
elif not os.path.isfile("./result/" + handle + "_title.data"):
    ChangeScript = "sed -i 's/F:/\/media\/data/g' ./data/" + handle + "_title.txt"
    Popen(ChangeScript, shell=True, stdout=PIPE, stderr=PIPE)

if not os.path.isfile("./result/" + handle + "_title.data"):
    CreateScript = "./create " + "./data/" + handle + "_info.txt " + "./data/" + \
                   handle + "_res.txt " + "./data/" + handle + "_title.txt "
    print CreateScript
    resp = Popen(CreateScript, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
    print os.path.isfile("./result/" + handle + "_title.data"), resp
    if not os.path.isfile("./result/" + handle + "_title.data"):
        exit()

print "next"
with open("./data/" + handle + "_info.txt", 'r') as f:
    ans = f.readline()
    NumFile = ans.split(' ')[0]
    print "NumFile: ", NumFile

if NumFile == 0:
    exit()

NumFile = 300
handle_script = "./test_8000 " + "./data/" + handle + "_info.txt " + "./result/" + \
                handle + "_res.data " + "./result/" + handle + "_title.data " + \
                "0 " + str(NumFile) + " 0"
print handle_script

resp = Popen(handle_script, shell=True, stdout=PIPE, stderr=PIPE).stdout.readlines()
end_time = time.clock()
print resp
print "read: %f s" % (end_time - begin_time)
