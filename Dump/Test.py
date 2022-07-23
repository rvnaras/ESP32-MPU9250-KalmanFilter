import pandas as pd
import time

df0 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R1X', 'R1Y', 'R1Z'], engine='python')
df1 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R2X', 'R2Y', 'R2Z'], engine='python') 
df2 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R3X', 'R3Y', 'R3Z'], engine='python') 
df3 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R4X', 'R4Y', 'R4Z'], engine='python')
df4 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R5X', 'R5Y', 'R5Z'], engine='python')
df5 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R6X', 'R6Y', 'R6Z'], engine='python')
df6 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['R7X', 'R7Y', 'R7Z'], engine='python')
df7 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L1X', 'L1Y', 'L1Z'], engine='python')
df8 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L2X', 'L2Y', 'L2Z'], engine='python') 
df9 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L3X', 'L3Y', 'L3Z'], engine='python')
df10 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L4X', 'L4Y', 'L4Z'], engine='python') 
df11 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L5X', 'L5Y', 'L5Z'], engine='python') 
df12 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L6X', 'L6Y', 'L6Z'], engine='python') 
df13 = pd.read_csv("KalmanData.csv", sep='\;', usecols=['L7X', 'L7Y', 'L7Z'], engine='python') 

df0.head()
for item0, frame0 in df0.iteritems():
    print(item0, frame0[0])

print(" ")

df1.head()
for item1, frame1 in df1.iteritems():
    print(item1, frame1[0])

print(" ")

df2.head()
for item2, frame2 in df2.iteritems():
    print(item2, frame2[0])

print(" ")

df3.head()
for item3, frame3 in df3.iteritems():
    print(item3, frame3[0])

print(" ")

df4.head()
for item4, frame4 in df4.iteritems():
    print(item4, frame4[0])

print(" ")

df5.head()
for item5, frame5 in df5.iteritems():
    print(item5, frame5[0])

print(" ")

df6.head()
for item6, frame6 in df6.iteritems():
    print(item6, frame6[0])

print(" ")
 
df7.head()
for item7, frame7 in df7.iteritems():
    print(item7, frame7[0])

print(" ")

df8.head()
for item8, frame8 in df8.iteritems():
    print(item8, frame8[0])

print(" ")
 
df9.head()
for item9, frame9 in df9.iteritems():
    print(item9, frame9[0])

print(" ")

df10.head()
for item10, frame10 in df10.iteritems():
    print(item10, frame10[0])

print(" ")

df11.head()
for item11, frame11 in df11.iteritems():
    print(item11, frame11[0])

print(" ")

df12.head()
for item12, frame12 in df12.iteritems():
    print(item12, frame12[0])

print(" ")

df13.head()
for item13, frame13 in df13.iteritems():
    print(item13, frame13[0])