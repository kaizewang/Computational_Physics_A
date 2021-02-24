import numpy as np
import matplotlib.pyplot as plt


data1=np.loadtxt("16807(N=100).txt")
data2=np.loadtxt("16807(N=1000).txt")
data3=np.loadtxt("16807(N=10000).txt")
data4=np.loadtxt("16807(N=10000000).txt")
data5=np.loadtxt("other(N=10000).txt")

plt.scatter(data1[:,0],data1[:,1],linewidths=0.1)
plt.xlabel("x")
plt.ylabel("y")
plt.savefig("N=100")
plt.figure()
plt.scatter(data2[:,0],data2[:,1],linewidths=0.1)
plt.savefig("N=1000")
plt.figure()
plt.scatter(data3[:,0],data3[:,1],linewidths=0.1)
plt.savefig("N=10000")
'''plt.scatter(data5[:,0],data5[:,1],linewidths=0.1)
plt.xlabel("x")
plt.ylabel("y")
plt.savefig("N_=10000")
plt.show()'''
