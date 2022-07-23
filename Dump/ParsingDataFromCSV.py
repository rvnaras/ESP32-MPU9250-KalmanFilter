import pandas as pd

cols0 = ['R1X', 'R1Y', 'R1Z']
cols1 = ['R2X', 'R2Y', 'R2Z']
cols2 = ['R3X', 'R3Y', 'R3Z']
cols3 = ['R4X', 'R4Y', 'R4Z']
cols4 = ['R5X', 'R5Y', 'R5Z']
cols5 = ['R6X', 'R6Y', 'R6Z']
cols6 = ['R7X', 'R7Y', 'R7Z']
cols7 = ['L1X', 'L1Y', 'L1Z']
cols8 = ['L2X', 'L2Y', 'L2Z']
cols9 = ['L3X', 'L3Y', 'L3Z']
cols10 = ['L4X', 'L4Y', 'L4Z']
cols11 = ['L5X', 'L5Y', 'L5Z']
cols12 = ['L6X', 'L6Y', 'L6Z']
cols13 = ['L7X', 'L7Y', 'L7Z']

df0 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols0)
df0.head()
print (df0)

df1 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols1)
df1.head()
print (df1)

df2 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols2)
df2.head()
print (df2)

df3 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols3)
df3.head()
print (df3)

df4 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols4)
df4.head()
print (df4)

df5 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols5)
df5.head()
print (df5)

df6 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols6)
df6.head()
print (df6)

df7 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols7)
df7.head()
print (df7)

df8 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols8)
df8.head()
print (df8)

df9 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols9)
df9.head()
print (df9)

df10 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols10)
df10.head()
print (df10)

df11 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols11)
df11.head()
print (df11)

df12 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols12)
df12.head()
print (df12)

df13 = pd.read_csv('SampleDataXYZComplementary.csv', sep='\;', engine='python', index_col=0, usecols=cols13)
df13.head()
print (df13)