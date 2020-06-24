import torch as T
import torchvision.models as models

from tensor_tools import save_tensor
from paths import get_VGG16_path, get_AlexNet_path

#! VGG16
# path      = get_VGG16_path()
# nb_layers = 38
# model     = models.vgg16(pretrained=True)

#! AlexNet
path      = get_AlexNet_path()
nb_layers = 21
model     = models.alexnet(pretrained=True)

#* Saving

for n,layer in enumerate(model.features):
    print('Saving layer', str(n), 'of', str(nb_layers+1))

    fname = '{}'.format(n) + '_'

    if isinstance(layer,T.nn.Conv2d):
        fname += 'conv2d'
        save_tensor(layer.weight, fname + '_w', path)
        save_tensor(layer.bias, fname + '_b', path)

for n,layer in enumerate(model.classifier, len(model.features)+1):
    print('Saving layer', str(n), 'of', str(nb_layers+1))
    fname = '{}'.format(n) + '_'

    if isinstance(layer,T.nn.Linear):
        fname += 'linear'
        save_tensor(layer.weight, fname + '_w', path)
        save_tensor(layer.bias, fname + '_b', path)

print('Finished.')