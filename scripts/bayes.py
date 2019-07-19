import pandas as pd
import subprocess
import os
from gaussian_process import Space, GaussianProcess, TQDMGaussianProcess
from multiprocessing import cpu_count
from notipy_me import Notipy
from random import randint
from skopt.callbacks import DeltaYStopper

def score(oblivion:float, mu_memory:float, mu_data:float):
    data = "data/14matrizn400m80.dat"
    os.makedirs("logs", exist_ok=True)
    filename = "logs/{random}.csv".format(
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
        ),
        "--ant_system"        
        ])
    df = pd.read_csv(filename, index_col=0)
    score = int(-df["mean"].values.flatten()[0])
    return score


space = Space({
    "oblivion":(0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0),
    "mu_memory":[0, 100],
    "mu_data":[0, 100]
})

n_calls = 1000
gp = GaussianProcess(score, space)
results = gp.minimize(
    n_calls=n_calls,
    n_random_starts=10,
    callback=[
        TQDMGaussianProcess(n_calls=n_calls),
        DeltaYStopper(**{
            "delta":1,
            "n_best":100
        })
    ],
    random_state=42,
    n_jobs=cpu_count()
)

print(gp.best_parameters)
pd.DataFrame(dict(gp.best_parameters), index=[0]).to_json("best_parameters.json")
