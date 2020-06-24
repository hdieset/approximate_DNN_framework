import torch as T 

from paths import get_inference_path

def load(dataset = 'ImageNet', model = 'VGG16', img_nb = 0):

    PATH = get_inference_path()

    with open(PATH + '\\' + dataset + '\\' + model + '\\' + str(img_nb) + '.txt') as f:
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