import torch
import torchvision.transforms as transforms
import torchvision.datasets as datasets

from paths import get_raw_imagenet_path

def get_val_loader(batch_size = 1):

    valdir = get_raw_imagenet_path()
    normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                     std =[0.229, 0.224, 0.225])
    val_loader = torch.utils.data.DataLoader(
            datasets.ImageFolder(valdir, transforms.Compose([
                transforms.Resize(256),
                transforms.CenterCrop(224),
                transforms.ToTensor(),
                normalize,
            ])),
            batch_size=batch_size, shuffle=False, pin_memory=True)

    return val_loader