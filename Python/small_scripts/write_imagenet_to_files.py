import torch as T 
from tqdm import tqdm

from imagenet_loader import get_val_loader
from tensor_tools import save_tensor
from paths import get_proc_imagenet_path

num_images = 2048
batch_size = 1
path = get_proc_imagenet_path()


with tqdm(total=num_images) as pbar:
    for i,(image,_) in enumerate(get_val_loader(batch_size)):
        save_tensor(image, str(i), path)
        pbar.update(i+1)
        if i == num_images - 1:
            break


print('Saved', str(num_images), 'to folder', path)