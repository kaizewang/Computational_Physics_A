import matplotlib.pyplot as plt
import numpy as np
import matplotlib 

# 设置matplotlib正常显示中文和负号
matplotlib.rcParams['font.sans-serif']=['SimHei']   # 用黑体显示中文
matplotlib.rcParams['axes.unicode_minus']=False     # 正常显示负号

data=np.loadtxt("N=1000000.txt")
x=np.arange(-10,10,0.001)
y=1/np.sqrt(3.1415926)*np.exp(-np.power(x,2))
fig,ax = plt.subplots(1, 1)
ax.plot(x, y, color="r", ls="--", lw=4,label='ideal distribution')
plt.hist(data, bins=500,density=True,facecolor="blue", edgecolor="black", alpha=0.7,label='normalized histogram')
# 显示横轴标签
plt.xlabel(r"$x$")
# 显示纵轴标签
plt.ylabel(r"probability density")
plt.legend(loc='best')
plt.show()