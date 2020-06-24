import matplotlib.pyplot as plt
import torch as T
import math

from paths import get_highpass_path
from tensor_tools import save_fig_as_pdf

def load_image(img_name):
    with open(get_highpass_path() + img_name + ".txt", 'r') as f:
        batches =  int(f.readline())
        channels = int(f.readline())
        height   = int(f.readline())
        width    = int(f.readline())

        res = T.zeros(batches, channels, height, width)

        for bz in range(batches):
            for ch in range(channels):
                for h in range(height):
                    for w in range(width):
                        res[bz][ch][h][w] = float(f.readline())

    return res

dpi = 100
#!§

img_names = [
    # 'TA_1',
    # 'TA_2',
    # 'TA_3',
    # 'TA_4',
    # 'TA_5',
    # 'TA_6',
    # 'TA_7',
    # 'TA_11',
    # 'TA_12',
    # 'TA_13',
    # 'MA_7_1'

]

#! Saving approximate image as pdf
img_nb = 0
img = load_image(img_names[img_nb])
img = img.view(img.size()[-1],img.size()[-1])
fig = plt.figure(figsize=(500/dpi, 500/dpi), dpi=dpi)
plt.gray()
plt.imshow(img)
save_fig_as_pdf(img_names[img_nb]+".pdf",fig)

#! Target image
# img_acc = load_image("lena_0.16_acc")
# img_acc = img_acc.view(img_acc.size()[-1],img_acc.size()[-1])
# print("loaded 1 of",len(img_names)+1)

#! Saving target image as pdf
# fig = plt.figure(figsize=(500/dpi, 500/dpi), dpi=dpi)
# plt.gray()
# plt.imshow(img_acc)
# save_fig_as_pdf("target.pdf",fig)


#! Preparing diff tensors
# img_dict = {x : T.empty(0) for x in range(len(img_names))}

# for i in img_dict.keys():
#     x = load_image(img_names[i])
#     img_dict[i] = x.view(x.size()[-1],x.size()[-1]) - img_acc
#     img_dict[i] = img_dict[i].abs()
#     print("Loaded",i+2,"of",len(img_dict)+1)


#! Calculating SNRs
# for a_img,name in zip(img_dict.values(),img_names):
#     snr = 10*math.log10( img_acc.mean() / a_img.mean() )
#     print(name,"SNR [dB] =",snr)


#! finding max and mins
# # _min = 999999
# _max = -999999
# for img in img_dict.values():
#     # if _min > img.min():
#     #     _min = img.min()
#     if _max < img.max():
#         _max = img.max()

# # _min = _min.item()
# _max = _max.item()
# if _max < 0: _max = 1
# # print("min:",_min)
# print("max:",_max)

# # limit = _max if _max > abs(_min) else -_min
# # _min = -limit
# # _max = limit

# # _min = -175
# _max = 175

#! Color bar setup
# import matplotlib.colors as colorslib
# # cvals = [_min, 0, _max]
# cvals = [0, _max]
# colors = ["black","red"]
# norm = plt.Normalize(0,_max)
# tuples = list(zip(map(norm,cvals), colors))
# cmap = colorslib.LinearSegmentedColormap.from_list("", tuples)

#! Saving as pdf
# for img,fname in zip(img_dict.values(),img_names):
#     fig = plt.figure(figsize=(500/dpi, 500/dpi), dpi=dpi)
#     plt.imshow(img, vmin=0, vmax=_max, cmap=cmap, norm=norm)
#     save_fig_as_pdf(fname+".pdf",fig)
