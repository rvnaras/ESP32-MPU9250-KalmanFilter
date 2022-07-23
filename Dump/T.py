import pandas as pd
from itertools import islice
import time

df = pd.read_csv('KalmanData.csv', sep='\;', engine='python')
df.head()
for index, row in df.iterrows():
    print(row[5])
    time.sleep(0.5)

