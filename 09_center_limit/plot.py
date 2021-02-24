import matplotlib.pyplot as plt
import numpy as np
import matplotlib 

# 设置matplotlib正常显示中文和负号
matplotlib.rcParams['font.sans-serif']=['SimHei']   # 用黑体显示中文
matplotlib.rcParams['axes.unicode_minus']=False     # 正常显示负号

data=np.loadtxt("result/self_(N=10,M=1E4).txt")
#data=np.loadtxt("result/exp_(N=1000,M=1E4).txt")
#data=np.loadtxt("poisson_(N=10000,M=1E4).txt")
x=np.arange(-3,3,0.001)
y=1/np.sqrt(2*3.1415926)*np.exp(-np.power(x,2)/2)
fig,ax = plt.subplots(1, 1)
ax.plot(x, y, color="r", ls="--", lw=2,label='normal distribution')
plt.hist(data, bins=100,density=True,facecolor="blue", edgecolor="black", alpha=0.7,label='normalized counting')
# 显示横轴标签
plt.xlabel(r"$x$",fontsize=14)
# 显示纵轴标签
plt.ylabel(r"probability density",fontsize=14)
plt.legend()
plt.show()