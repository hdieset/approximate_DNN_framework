# Creates histograms of the parameters of the networks

import torch as T 
import torchvision.models as models
import matplotlib.pyplot as plt
import numpy as np 

#! Set Network type here
vgg         = True # if false, then AlexNet
find_minmax = False # prints min/max to console
save_csv    = False # saves to cwd

if vgg:
    model = models.vgg16(pretrained=True)
else:
    model = models.alexnet(pretrained=True)

# Conv layers
data_conv_w = []
data_conv_b = []
legend_conv = []
for n,layer in enumerate(model.features):
    if isinstance(layer,T.nn.Conv2d):
        data_conv_w.append(layer.weight.detach().view(-1,1).numpy())
        data_conv_b.append(layer.bias.detach().view(-1,1).numpy())
        legend_conv.append(str(n))

if find_minmax:
    print('Conv w min', min([min(data) for data in data_conv_w]))
    print('Conv w max', max([max(data) for data in data_conv_w]))
    print('Conv b min', min([min(data) for data in data_conv_b]))
    print('Conv b max', max([max(data) for data in data_conv_b]))

# Linear layers
data_lin_w = []
data_lin_b = []
legend_lin = []
for n,layer in enumerate(model.classifier, len(model.features)+1):
    if isinstance(layer, T.nn.Linear):
        data_lin_w.append(layer.weight.detach().view(-1,1).numpy())
        data_lin_b.append(layer.bias.detach().view(-1,1).numpy())
        legend_lin.append(str(n))

if find_minmax:
    print('Linear w min', min([min(data) for data in data_lin_w]))
    print('Linear w max', max([max(data) for data in data_lin_w]))
    print('Linear b min', min([min(data) for data in data_lin_b]))
    print('Linear b max', max([max(data) for data in data_lin_b]))

# Plots
fig, axes = plt.subplots(nrows=2, ncols=2)
ax = axes.flatten()

ax[0].hist(data_conv_w, bins=40, histtype='bar', stacked=True)
ax[1].hist(data_conv_b, bins=40, histtype='bar', stacked=True)
ax[2].hist(data_lin_w, bins=40, histtype='bar', stacked=True)
ax[3].hist(data_lin_b, bins=40, histtype='bar', stacked=True)

ax[0].legend(legend_conv)
ax[1].legend(legend_conv)
ax[2].legend(legend_lin)
ax[3].legend(legend_lin)

ax[0].set_title('Conv2d weights')
ax[1].set_title('Conv2d biases')
ax[2].set_title('Linear weights')
ax[3].set_title('Linear biases')

[a.set_yscale('log') for a in ax]
fig.suptitle("VGG16" if vgg else "AlexNet", fontsize=14)
plt.show()

#* Saving histograms as .csv for report

def save_hist(data, legends, fname):
    from os import getcwd
    counts, bins, _ = plt.hist(data, bins=40, histtype='bar', stacked=True)
    fname = getcwd() + "/" + fname
    with open(fname + '.csv', "w+") as f:
        # header
        header = 'bin'
        for legend in legends:
            header += ',l' + str(legend)
        f.write(header + '\n')

        # values
        for bin, count in zip(bins, np.transpose(counts)):
            line = str(bin) + ','
            for i,c in enumerate(count):
                line += str(c)
                if i is not len(counts)-1: line += ','
            f.write(line + '\n')

if save_csv:
    print("Saving")
    save_hist(data_conv_w, legend_conv, "hist_conv_w_" + ("vgg16" if vgg else "alexnet"))
    save_hist(data_conv_b, legend_conv, "hist_conv_b_" + ("vgg16" if vgg else "alexnet"))
    save_hist(data_lin_w, legend_lin, "hist_lin_w_" + ("vgg16" if vgg else "alexnet"))
    save_hist(data_lin_b, legend_lin, "hist_lin_b_" + ("vgg16" if vgg else "alexnet"))