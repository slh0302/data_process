import sys
import os
import json

exec_prefix = sys.argv[1]
data_file_prefix = sys.argv[2]
json_file_prefix = sys.argv[3]
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
    context = ""
    first_line = ""
    second_line = ""
    data = ""
    with open(file_path, 'r') as file_list, \
         open(json_file_prefix + handle + "_json.txt", 'r') as json_data, \
         open(handle + ".out", 'w') as out:
        while True:
            # JSON process
            first_line = json_data.readline()
            second_line = json_data.readline()
            data = json.loads(second_line)
            while True:
                context = file_list.readline()
                line_num += 1
                Name = context.split(' ')[0].split('.')[0]
                OriginName = context.split(' ')[1]
                NumOfPic = context.split(' ')[-1]
                json_pic_name = first_line.strip().split('\\')[-1]

                if json_pic_name != OriginName:
                    print "[Line]: ", line_num, " Json Not Found: ", OriginName
                    break
                # Json
                # TODO: Null Data process
                Cars = data['Result']['Vehicles'][int(NumOfPic)]

                CarType = Cars['ModelType']['Type']
                CarColor = Cars['Color']['ColorName']
                CarBrand = Cars['ModelType']['brand']
                CarIsHead = Cars['ModelType']['IsHead']
                CarSubBrand = Cars['ModelType']['SubBrand']
                CarModelYear = Cars['ModelType']['ModelYear']
                CarPlateName = Cars['Plate']['PlateText']
                CarPlateColor = Cars['Plate']['TypeName']

            # if int(Name) != int(res_name):
            #     print "[Line]: ", line_num, " File Not Found: ", res
            #     isContext = False
            # else:
            #     isContext = True

