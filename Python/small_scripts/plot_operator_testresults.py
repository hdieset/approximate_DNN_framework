import matplotlib.pyplot as plt 
import csv
from paths import get_operator_test_path

filelist = {"TruA.csv" : "TA",
            "LOA.csv"  : "LOA",
            "MedA.csv" : "MA",
            "APA2.csv"  : "APAII",
            "APA.csv"  : "APA",
            "ETAI.csv" : "ETAI",
            # "ESA.csv"  : "ESA"
}
nmed = {i : [] for i in range(len(filelist.keys()))}
mred = {i : [] for i in range(len(filelist.keys()))}
er   = {i : [] for i in range(len(filelist.keys()))}
mse  = {i : [] for i in range(len(filelist.keys()))}

for n,file in enumerate(filelist.keys()):
    path = get_operator_test_path() + file
    with open(path, 'r') as f:
        newdata = csv.reader(f, delimiter=',')
        for i,row in enumerate(newdata):
            if i != 0:
                nmed[n].append(float(row[1]))
                mred[n].append(float(row[2]))
                er[n].append(float(row[3]))
                mse[n].append(float(row[4]))

x = [i for i in range(1,len(nmed[0])+1)]

fig, axes = plt.subplots(nrows=2, ncols=2)
ax = axes.flatten()

for y0,y1,y2,y3 in zip(nmed.values(), mred.values(), er.values(), mse.values()):
    ax[0].plot(x,y0, marker = 'o')
    ax[1].plot(x,y1, marker = 'o')
    ax[2].plot(x,y2, marker = 'o')
    ax[3].plot(x,y3, marker = 'o')


ax[2].set_xlabel("Parameter")
ax[3].set_xlabel("Parameter")

ax[0].set_title("NMED")
ax[1].set_title("MRED")
ax[2].set_title("ER")
ax[3].set_title("MSE")

for i in range(len(ax)):
    if i != 2:
        ax[i].set_yscale('log')

ax[2].legend(filelist.values())

fig.suptitle("Approximate Adder comparison", fontsize=14)

plt.show()