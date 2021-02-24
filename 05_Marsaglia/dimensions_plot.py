import numpy as np
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D  # 空间三维画图

data1 = np.loadtxt("ring.txt",delimiter=",") # load 时也要指定为逗号分隔
data2=np.loadtxt("4-sphere.txt",delimiter=",")

x1=data1[0:500,0]
y1=data1[0:500,1]
x2=data2[0:10000,0]
y2=data2[0:10000,1]
u2=data2[0:10000,2]
v2=data2[0:10000,3]
'''plt.scatter(x1,y1,0.5)
plt.grid(True)
plt.grid('minor')
plt.axis('equal')
plt.xlabel(r'$x-coordinate$')
plt.ylabel(r'$y-coordinate$')'''



fig = plt.figure()
ax = Axes3D(fig)
ax.scatter(x2, y2, v2,s=1)
ax.set_zlabel(r'$Z$', fontdict={'size': 10, 'color': 'blue'})
ax.set_ylabel(r'$Y$', fontdict={'size': 10, 'color': 'blue'})
ax.set_xlabel(r'$X$', fontdict={'size': 10, 'color': 'blue'})

plt.figure()
plt.scatter(x2,y2,0.1)
plt.grid(True)
plt.grid('minor')
plt.axis('equal')
plt.xlabel(r'$x-coordinate$')
plt.ylabel(r'$y-coordinate$')

plt.show()