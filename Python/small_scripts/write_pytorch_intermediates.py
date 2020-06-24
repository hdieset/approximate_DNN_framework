# Does inference with accurate PyTorch model and saves intermediate tensors to file

import torch as T 
import torchvision.models as models

from tensor_tools import save_tensor
from imagenet_loader import get_val_loader
from paths import get_intermediate_path

#! Get network model
modelname = 'AlexNet_ref'
model = models.alexnet(pretrained=True)
model.eval()

#! setup image loader
nb_images = 4
img_loader = get_val_loader()

path = get_intermediate_path() + 'ImageNet' + '\\' + modelname + '\\'

#! Do inference
for img_nb,(img,_) in enumerate(img_loader):
    if img_nb >= nb_images: break

    for l_nb,layer in enumerate(model.features):
        img = layer.forward(img)
        save_tensor(img, str(img_nb)+'_'+str(l_nb), path)

    # Squeeze layer
    img = T.flatten(img,1)
    save_tensor(img, str(img_nb)+'_'+str(len(model.features)), path)

    for l_nb,layer in enumerate(model.classifier, len(model.features)+1):
        img = layer.forward(img)
        save_tensor(img, str(img_nb)+'_'+str(l_nb), path)

    print("completed image", img_nb+1, "of", nb_images)