# Plots intermediate output difference tensors

import matplotlib.pyplot as plt
import csv
from paths import get_intermediate_path

filelist = {
    # "AlexNet_Q10.10_accurate.csv" : "20 bit static",
    # "AlexNet_Q10.9_accurate.csv"  : "19 bit static",
    # "AlexNet_Q10.8_accurate.csv"  : "18 bit static",
    # "AlexNet_20bit_accurate.csv"  : "20 bit dynamic",
    # "AlexNet_19bit_accurate.csv"  : "19 bit dynamic",
    # "AlexNet_18bit_accurate.csv"  : "18 bit dynamic",
    # "AlexNet_17bit_accurate.csv"  : "17 bit dynamic",
    # "AlexNet_16bit_accurate.csv"  : "16 bit dynamic",
    # "AlexNet_20bit_APA_1.csv"     : "APA-1",
    # "AlexNet_20bit_APA_2.csv"     : "APA-2",
    # "AlexNet_20bit_APA_3.csv"     : "APA-3",
    # "AlexNet_20bit_APA_4.csv"     : "APA-4",
    # "AlexNet_20bit_APAII_1.csv"   : "APAII-1",
    # "AlexNet_20bit_APAII_2.csv"   : "APAII-2",
    # "AlexNet_20bit_APAII_3.csv"   : "APAII-3",
    # "AlexNet_20bit_APAII_4.csv"   : "APAII-4",
    # "AlexNet_20bit_ETAI_1.csv"    : "ETAI-1",
    # "AlexNet_20bit_ETAI_2.csv"    : "ETAI-2",
    # "AlexNet_20bit_ETAI_3.csv"    : "ETAI-3",
    # "AlexNet_20bit_ETAI_4.csv"    : "ETAI-4",
    # "AlexNet_20bit_LOA_1.csv"     : "LOA-1",
    # "AlexNet_20bit_LOA_2.csv"     : "LOA-2",
    # "AlexNet_20bit_LOA_3.csv"     : "LOA-3",
    # "AlexNet_20bit_LOA_4.csv"     : "LOA-4",
    # "AlexNet_20bit_LOA_5.csv"     : "LOA-5",
    # "AlexNet_20bit_LOA_6.csv"     : "LOA-6",
    # "AlexNet_20bit_LOA_7.csv"     : "LOA-7",
    # "AlexNet_20bit_LOA_8.csv"     : "LOA-8",
    # "AlexNet_20bit_LOA_9.csv"     : "LOA-9",
    # "AlexNet_20bit_MA_1.csv"      : "MA-1",
    # "AlexNet_20bit_MA_2.csv"      : "MA-2",
    # "AlexNet_20bit_MA_3.csv"      : "MA-3",
    # "AlexNet_20bit_TA_1.csv"      : "TA-1",
    # "AlexNet_20bit_TA_2.csv"      : "TA-2",
    # "AlexNet_20bit_TA_3.csv"      : "TA-3",
    # "AlexNet_20bit_TA_4.csv"      : "TA-4",
    "VGG16_20bit_APA_1.csv"  : "APA-1",
    # "VGG16_20bit_APA_2.csv"  : "APA-2",
    # "VGG16_20bit_APA_3.csv"  : "APA-3",
    # "VGG16_20bit_APA_4.csv"  : "APA-4",
    "VGG16_20bit_APAII_1.csv": "APAII-1",
    # "VGG16_20bit_APAII_2.csv": "APAII-2",
    # "VGG16_20bit_APAII_3.csv": "APAII-3",
    # "VGG16_20bit_APAII_4.csv": "APAII-4",
    "VGG16_20bit_ETAI_1.csv" : "ETAI-1",
    # "VGG16_20bit_ETAI_2.csv" : "ETAI-2",
    # "VGG16_20bit_ETAI_3.csv" : "ETAI-3",
    # "VGG16_20bit_ETAI_4.csv" : "ETAI-4",
    "VGG16_20bit_LOA_1.csv"  : "LOA-1",
    # "VGG16_20bit_LOA_2.csv"  : "LOA-2",
    # "VGG16_20bit_LOA_3.csv"  : "LOA-3",
    # "VGG16_20bit_LOA_4.csv"  : "LOA-4",
    # "VGG16_20bit_LOA_5.csv"  : "LOA-5",
    # "VGG16_20bit_LOA_6.csv"  : "LOA-6",
    # "VGG16_20bit_LOA_7.csv"  : "LOA-7",
    # "VGG16_20bit_LOA_8.csv"  : "LOA-8",
    # "VGG16_20bit_LOA_9.csv"  : "LOA-9",
    "VGG16_20bit_MA_1.csv"   : "MA-1",
    # "VGG16_20bit_MA_2.csv"   : "MA-2",
    # "VGG16_20bit_MA_3.csv"   : "MA-3",
    "VGG16_20bit_TA_1.csv"   : "TA-1",
    # "VGG16_20bit_TA_2.csv"   : "TA-2",
    # "VGG16_20bit_TA_3.csv"   : "TA-3",

}

data = {i : [] for i in range(len(filelist.keys()))}

for n,file in enumerate(filelist.keys()):
    path = get_intermediate_path() + 'ImageNet/' + file
    with open(path, 'r') as f:
        newdata = csv.reader(f, delimiter=',')
        for i,row in enumerate(newdata):
            if i != 0:
                data[n].append(float(row[2]))

x = [i for i in range(0,len(data[0]))]

sep = 4
for n,y in enumerate(data.values()):
    if n < sep:
        plt.plot(x,y, marker = 'o')
    else:
        plt.plot(x,y, marker = 'x')

plt.legend(filelist.values())
plt.xlabel("Layer number")
plt.xticks(x)
plt.ylabel("MSE loss")
plt.yscale('log')
plt.title('MSE difference due to approximate adders per layer (AlexNet).')
# plt.title("AlexNet quantization error, compared to double")
plt.show()