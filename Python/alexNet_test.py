# This script prints all layer information and image sizes

import torch as T
import torchvision.models as models

import sys
sys.path.insert(0, './small_scripts/')
from small_scripts import imagenet_loader

alexnet = models.alexnet(pretrained=True)
alexnet.eval()

val_loader = imagenet_loader.get_val_loader(1)
# (image, _) = next(iter(val_loader))

for m,(image,_) in enumerate(val_loader):
    if m > 1: break
    do_print_layers = True

    for n,layer in enumerate(alexnet.features):
        if do_print_layers:
            print('----------------', n, '----------------')
            print('Input :', image.shape)
        image = layer.forward(image)
        if do_print_layers:
            print('Output:', image.shape)
            print(layer)

    # # AvgPool layer
    if do_print_layers:
        print('----------------', len(alexnet.features), '----------------')
        print('Input :', image.shape)
    pre = image
    image = alexnet.avgpool(image)
    if do_print_layers:
        print('Output:', image.shape)
        print("Adaptive avgpool2d layer")

    # a = pre - image
    # print(a.sum())

    # # Squeeze layer
    if do_print_layers:
        print('----------------', len(alexnet.features)+1, '----------------')
        print('Input :', image.shape)
    image = T.flatten(image,1)
    if do_print_layers:
        print('Output:', image.shape)
        print("Flatten layer")

    for n,layer in enumerate(alexnet.classifier, len(alexnet.features)+2):
        if do_print_layers:
            print('----------------', n, '----------------')
            print('Input :', image.shape)
        image = layer.forward(image)
        if do_print_layers:
            print('Output:', image.shape)
            print(layer)
