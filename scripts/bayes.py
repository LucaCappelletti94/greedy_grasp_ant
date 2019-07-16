import pandas as pd
import subprocess
from gaussian_process import Space, GaussianProcess, TQDMGaussianProcess
from multiprocessing import cpu_count
from notipy_me import Notipy

def score(oblivion:float, memory_mu:float, data_mu:float):
    data = "14matrizn400m80.dat"
    subprocess.run([
        "./linux/greedy_grasp_ant",
        "data/{data}".format(data=data),
        str(oblivion),
        str(memory_mu),
        str(data_mu)])
    df = pd.read_csv("tmp.csv", index_col=0)
    return -df.values.flatten()[0]


space = Space({
    "oblivion":(0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0),
    "memory_mu":[0, 100.0],
    "data_mu":[0, 100]
})

n_calls = 1000
gp = GaussianProcess(score, space)
with Notipy():
    results = gp.minimize(
        n_calls=n_calls,
        n_random_starts=10,
        callback=[TQDMGaussianProcess(n_calls=n_calls)],
        random_state=42,
        n_jobs=cpu_count()
    )

print(gp.best_parameters)
print(gp.best_optimized_parameters)
