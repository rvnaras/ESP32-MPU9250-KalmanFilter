import pandas as pd
import time

df = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R1X', 'R1Y', 'R1Z', 'R2X', 'R2Y', 'R2Z', 'R3X', 'R3Y', 'R3Z', 'R4X', 'R4Y', 'R4Z', 'R5X', 'R5Y', 'R5Z', 'R6X', 'R6Y', 'R6Z', 'R7X', 'R7Y', 'R7Z', 'L1X', 'L1Y', 'L1Z', 'L2X', 'L2Y', 'L2Z', 'L3X', 'L3Y', 'L3Z', 'L4X', 'L4Y', 'L4Z', 'L5X', 'L5Y', 'L5Z', 'L6X', 'L6Y', 'L6Z', 'L7X', 'L7Y', 'L7Z'], engine='python')
df.head()
for index, row in df.iterrows():
    print(row)
    print(" ")
    time.sleep(0.5)

