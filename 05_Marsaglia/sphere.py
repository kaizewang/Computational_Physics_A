import numpy as np
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D  # 空间三维画图

data = np.loadtxt("sphere_surface.txt",delimiter=",") # load 时也要指定为逗号分隔
data=np.array(data)
x=data[:,0]
y=data[:,1]
z=data[:,2]
plt.scatter(x,y,0.3)
plt.grid(True)
plt.grid('minor')
plt.axis('equal')
plt.xlabel(r'$x-coordinate$')
plt.ylabel(r'$y-coordinate$')
plt.show()

'''fig = plt.figure()
ax = Axes3D(fig)
ax.scatter(x, y, z)
ax.set_zlabel(r'$Z$', fontdict={'size': 10, 'color': 'red'})
ax.set_ylabel(r'$Y$', fontdict={'size': 10, 'color': 'red'})
ax.set_xlabel(r'$X$', fontdict={'size': 10, 'color': 'red'})'''

plt.show()