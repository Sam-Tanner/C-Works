#used imports
from matplotlib import pyplot as plt
import csv
import numpy as np

#sets lists up to hold Day and Individual statuses
Days=[0]
day=0
Alive=[200000]
Dead=[0]
Died=[0]
Immune=[0]
Recovered=[0]
Infected=[100]

#imports Alive.csv and copies data to a list, as well as generating day list
with open('Alive.csv') as alive:
    Alive_reader = csv.reader(alive, delimiter=',')
    for i in Alive_reader:
        for j in range(1,len(i)-1):
            Alive.append(int(i[j]))
            Dead.append(200000-int(i[j]))
            Died.append(Alive[j-1]-Alive[j])
            Days.append(day)
            day+=1
            
#imports Infected.csv and copies data to a list
with open('Infected.csv') as inf:
    Inf_reader = csv.reader(inf, delimiter=',')
    for i in Inf_reader:
        for j in range(1,len(i)-1):
            Infected.append(int(i[j]))
            
#imports Immune.csv and copies data to a list
with open('Immune.csv') as imn:
    Imn_reader = csv.reader(imn, delimiter=',')
    for i in Imn_reader:
        for j in range(1,len(i)-1):
            Immune.append(int(i[j]))
            Recovered.append(int(Immune[j])-Immune[j-1])

#find average R_0 value and calculates herd immunity needed (not used in report as a very crude approximation)
print(Died)
print(Recovered)
R=[]
Rfinite=[]
for i in range(0,len(Died)):
    R.append(Recovered[i]/np.max([Died[i]]))
    if np.isfinite(R[i]):
        Rfinite.append(R[i])
    else:
        Rfinite.append(0)
print(np.mean(Rfinite))
print((np.mean(Rfinite)-1)/np.mean(Rfinite))

print(Immune[365]/Alive[365])
#used in testing
#print(Alive)
#print(Infected)
#print(Immune)

#plots data with appropriate labeling and legend positioning
plt.figure(figsize=(16,8),dpi=120)
plt.plot(Days, Alive,'y',label="Alive Individuals")
plt.plot(Days, Infected,'b',label="Infected Individuals")
plt.plot(Days, Immune,'g',label="Immune Individuals")
plt.plot(Days, Dead,'r',label="Deceased Individuals")
plt.ylabel("Number of Individuals")
plt.xlabel("Days")
plt.title("Status of Individuals For a Year of Infections",size='xx-large')
plt.legend(title='Legend',title_fontsize='large',loc=5)
plt.show()