import matplotlib.pyplot as plt
import numpy as np
import matplotlib 

# 设置matplotlib正常显示中文和负号
matplotlib.rcParams['font.sans-serif']=['SimHei']   # 用黑体显示中文
matplotlib.rcParams['axes.unicode_minus']=False     # 正常显示负号

data=np.loadtxt("p_1(x).txt")
x=np.arange(-1,1,0.001);
y=1/3.1415926*np.reciprocal(np.power((1-np.power(x,2)),1/2));
fig, ax = plt.subplots(1, 1)
ax.plot(x, y, color="r", ls="--", lw=2)
plt.hist(data, bins=500,density=True,facecolor="blue", edgecolor="black", alpha=0.7);
# 显示横轴标签
plt.xlabel(r"$x$")
# 显示纵轴标签
plt.ylabel(r"probability density")
plt.show()