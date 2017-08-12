# coding=utf-8
# 524774 993021
# writer: su
import json
import sys

num = 0
picture_num = 0
file_prefix='/media/vehicle_org/wengdeng'
# argv[1] : json file;
# argv[2] : wendeng data path: 1 2 3
# 523
print len(sys.argv), sys.argv[0]
if len(sys.argv) >= 1:
    json_file = sys.argv[1]
    print json_file.split('.')[0].split('/')[-1]
    save_file = json_file.split('.')[0].split('/')[-1] + "_res.txt"
    save_title_file = json_file.split('.')[0].split('/')[-1] + "_title.txt"
    save_data_info = json_file.split('.')[0].split('/')[-1] + "_info.txt"

    # redefine file prefix
    file_prefix=file_prefix + '/' + sys.argv[2] + '/'
totalpic = 0
with open(json_file, 'r') as file, \
        open(save_file, 'w') as out, \
        open(save_title_file, 'w') as out1:
    while True:
        first_line = file.readline()
        if not first_line:
            break
        img_path = file_prefix + '/'.join(first_line.strip().split('\\')[-2:])

        second_line = file.readline()
        data = json.loads(second_line)

        if data is None:
            print 'open json failed'
            continue

        if num % 10000 == 0:
            print num

        if 'Vehicles' not in data['Result']:
            continue
        vehicles = data['Result']['Vehicles']
        img = data['Result']['Image']['Data']
        numOfObject = 0
        for j in range(len(vehicles)):
            if len(vehicles[j]['Plate']['PlateText']) > 2:
                roi = vehicles[j]['Img']['Cutboard']
                PosX = roi['X']
                PosY = roi['Y']
                Width = roi['Width']
                Height = roi['Height']
                totalpic += 1
                out.write("%d %d %d %d %d %d\n" % (PosX, PosY, Width, Height, j,totalpic))
                num += 1
                numOfObject += 1
        if numOfObject > 0:
            picture_num += 1
            out1.write("%s %d %d %d\n" % (img_path, numOfObject, img['Width'], img['Height']))

print picture_num, num

with open(save_data_info, 'w') as out2:
    out2.write("%d %d\n" % (picture_num, num))
