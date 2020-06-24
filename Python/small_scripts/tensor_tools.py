import torch as T


def save_tensor(x, fname, path):
    sizes = x.size()

    with open(path + fname + '.txt', "w+") as f:

        if len(sizes) == 1:
            f.write(str(sizes[0]) + '\n')

            for a in range(sizes[0]):
                f.write(str(x[a].item()) + '\n')

        elif len(sizes) == 2:
            f.write(str(sizes[0]) + '\n')
            f.write(str(sizes[1]) + '\n')

            for a in range(sizes[0]):
                for b in range(sizes[1]):
                    f.write(str(x[a][b].item()) + '\n')

        elif len(sizes) == 3:
            f.write(str(sizes[0]) + '\n')
            f.write(str(sizes[1]) + '\n')
            f.write(str(sizes[2]) + '\n')

            for a in range(sizes[0]):
                for b in range(sizes[1]):
                    for c in range(sizes[2]):
                        f.write(str(x[a][b][c].item()) + '\n')

        elif len(sizes) == 4:
            f.write(str(sizes[0]) + '\n')
            f.write(str(sizes[1]) + '\n')
            f.write(str(sizes[2]) + '\n')
            f.write(str(sizes[3]) + '\n')

            for a in range(sizes[0]):
                for b in range(sizes[1]):
                    for c in range(sizes[2]):
                        for d in range(sizes[3]):
                            f.write(str(x[a][b][c][d].item()) + '\n')

        else:
            print('Unsupported layer size')

def save_fig_as_pdf(filepath, fig=None):
    import matplotlib.pyplot as plt
    if not fig:
        fig = plt.gcf()

    plt.subplots_adjust(0,0,1,1,0,0)
    for ax in fig.axes:
        ax.axis('off')
        ax.margins(0,0)
        ax.xaxis.set_major_locator(plt.NullLocator())
        ax.yaxis.set_major_locator(plt.NullLocator())
    fig.savefig(filepath, pad_inches = 0, bbox_inches='tight')