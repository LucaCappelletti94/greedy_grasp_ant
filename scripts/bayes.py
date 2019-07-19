import pandas as pd
import subprocess
from gaussian_process import Space, GaussianProcess, TQDMGaussianProcess
from multiprocessing import cpu_count
from notipy_me import Notipy
from random import randint
from skopt.callbacks import DeltaYStopper

def score(oblivion:float, mu_memory:float, mu_data:float):
    data = "14matrizn400m80.dat"
    filename = "data/{random}.csv".format(
        random=randint(0, 10000000000)
    )
    subprocess.run([
        "./gga/greedy_grasp_ant",
        "--log={filename}".format(filename=filename),
        "--data={data}".format(data=data),
        "--oblivion={oblivion}".format(
            oblivion=oblivion
        ),
        "--mu_memory={mu_memory}".format(
            mu_memory=mu_memory
        ),
        "--mu_data={mu_data}".format(
            mu_data=mu_data
        )])
    df = pd.read_csv(filename, index_col=0)
    return -df["mean"].values.flatten()[0]


space = Space({
    "oblivion":(0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0),
    "mu_memory":[0, 100.0],
    "mu_data":[0, 100]
})

n_calls = 1000
gp = GaussianProcess(score, space)
with Notipy():
    results = gp.minimize(
        n_calls=n_calls,
        n_random_starts=10,
        callback=[
            TQDMGaussianProcess(n_calls=n_calls),
            DeltaYStopper({
                "delta":0.001,
                "n_best":10
            })
        ],
        random_state=42,
        n_jobs=cpu_count()
    )

print(gp.best_parameters)
pd.DataFrame(gp.best_parameters).to_json("best_parameters.json")
