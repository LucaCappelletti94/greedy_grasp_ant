import os
import pandas as pd
import subprocess
from multiprocessing import cpu_count, Pool
from auto_tqdm import tqdm
from notipy_me import Notipy

def score(data):
    csv = "scores/{data}.csv".format(data=data)
    subprocess.run([
        "./gga/greedy_grasp_ant",
        "--data=data/{data}".format(data=data),
        "--log={csv}".format(csv=csv),
        "--all"
    ])
    df = pd.read_csv(csv, index_col=0)[["mean"]]
    df.columns = [data]
    return df.T

data = os.listdir("data")

with Notipy():
    with Pool(cpu_count()) as p:
        df = pd.concat(list(tqdm(p.imap(score, data), total=len(data))))

df.to_csv("scores/all_scores.csv")

