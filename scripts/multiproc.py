import os
import pandas as pd
import subprocess
from multiprocessing import cpu_count, Pool
from auto_tqdm import tqdm

def score(data):
    csv = "{data}.csv".format(data=data)
    subprocess.run([
        "./linux/greedy_grasp_ant",
        "data/{data}".format(data=data),
        csv,
	"0"
    ])
    df = pd.read_csv(csv, index_col=0)
    df.columns = [data]
    return df.T

data = os.listdir("data")

with Pool(cpu_count()) as p:
    df = pd.concat(list(tqdm(p.imap(score, data), total=len(data))))

df.to_csv("concat.csv")

