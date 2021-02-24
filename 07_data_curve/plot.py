import matplotlib.pyplot as plt
import numpy as np
import matplotlib 

# 设置matplotlib正常显示中文和负号
matplotlib.rcParams['font.sans-serif']=['SimHei']   # 用黑体显示中文
matplotlib.rcParams['axes.unicode_minus']=False     # 正常显示负号

data=np.loadtxt("reject_sampling.txt")
plt.hist(data, bins=114,density=True,facecolor="blue", edgecolor="black", alpha=0.7)
# 显示横轴标签
plt.xlabel(r"$x$")
# 显示纵轴标签
plt.ylabel(r"probability density")
plt.show()