import pandas as pd
import time

#url = 'https://raw.githubusercontent.com/ravennaras/FinalProject/master/ComplementaryData.csv'
df = pd.read_csv('KalmanData.csv', sep='\;', engine='python')
df.head()
for index, row in df.iterrows():
    R1X = df.loc[row,'R1X']
    print(" ")
    time.sleep(0.5)

