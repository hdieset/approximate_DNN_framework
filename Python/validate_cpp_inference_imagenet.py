# The original script was obtained from the PyTorch repository

# Runs validation on output produced by c++ VGG16 model on ImageNet

import torch as T
import torchvision.transforms as transforms
import torchvision.datasets as datasets
import time

from validation_tools import AverageMeter, ProgressMeter, accuracy

import sys
sys.path.insert(0, './small_scripts/')
from small_scripts import paths
from small_scripts import load_inference_output


def validate(val_loader, criterion, images_to_validate=1, modelname='VGG16'):
    batch_time = AverageMeter('Time', ':6.3f')
    losses     = AverageMeter('Loss', ':.4e')
    top1       = AverageMeter('Acc@1', ':6.2f')
    top5       = AverageMeter('Acc@5', ':6.2f')
    progress   = ProgressMeter(
        len(val_loader),
        [batch_time, losses, top1, top5],
        prefix='Test: ')

    # switch to evaluate mode

    end = time.time()
    for i, (images, target) in enumerate(val_loader):
        if i == images_to_validate: break

        # load output
        output = load_inference_output.load(img_nb = i, model=modelname).view(1,-1)
        loss = criterion(output, target)

        # measure accuracy and record loss
        acc1, acc5 = accuracy(output, target, topk=(1, 5))
        losses.update(loss.item(), images.size(0))
        top1.update(acc1[0], images.size(0))
        top5.update(acc5[0], images.size(0))

        # measure elapsed time
        batch_time.update(time.time() - end)
        end = time.time()

        # if i % 5 == 0:
        progress.display(i)

    print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f}'
            .format(top1=top1, top5=top5))

    return top1.avg

#! ###################################################################
run = True
images_to_validate = 2046
modelname = 'AlexNet_d' # VGG16, AlexNet
#! ###################################################################

if run:
    # Load validation dataset
    print(modelname)
    valdir = paths.get_raw_imagenet_path()

    normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                     std =[0.229, 0.224, 0.225])
    val_loader = T.utils.data.DataLoader(
            datasets.ImageFolder(valdir, transforms.Compose([
                transforms.Resize(256),
                transforms.CenterCrop(224),
                transforms.ToTensor(),
                normalize,
            ])),
            batch_size=1, shuffle=False, pin_memory=True)

    #* Load model

    criterion = T.nn.CrossEntropyLoss()

    #! Higher batch size -> eats more RAM
    validate(val_loader, criterion, images_to_validate, modelname)