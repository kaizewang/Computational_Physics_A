## 计算物理 实验报告X

王铠泽 PB18020766

### 第X题

设权重因子 $g(x)=e^{-ax}(a>0)$ ，用重要抽样方法计算积分 $\int_0^\pi\frac1{x^2+cos^2x}dx$ ，并求使得 $\sigma_f$ 最小的 $a$ 值。

### 算法公式

#### 权重Monte Carol积分法

当被积函数 $f(x)$ 呈现出较大的不均匀性时，为提高计算效率，常常寻找和其行为类似并且易于抽样的函数 $g(x)$ ，按 $g(x)$ 的分布进行抽样，再对 $\frac{f(x)}{g(x)}$ 做平均得到积分值:
$$
\int_a^bf(x)dx=\int_0^c\frac{f(x(y))}{g(x(y))}dy
$$
其中 $y$ 的抽样是在 $[0,c]$ 区间上的均匀分布。

一般可通过直接抽样法得到 $x(y)$，即从
$$
y(x)=\int_0^xf(x')dx'
$$
得到：
$$
x=x(y)
$$
对本题而言：$f(x)=\frac1{x^2+cos^2x},g(x)=e^{-ax}$。
$$
y(x)=\int_0^xe^{-ax'}dx'=\frac{1-e^{-ax}}{a}\Rightarrow x=-\frac{log(1-ay)}a
$$
其中 $y$ 在区间 ${\Large[}0,\Large\frac{1-e^{\pi a}}a]$ 上抽样。
$$
\int_a^b f(x)dx=\frac{1-e^{\pi a}}a\cdot\frac1N\sum_{i=1}^N\frac{f(x_i)}{g(x_i)}
$$

#### 中心极限定理和误差

中心极限定理保证了Monte Carol方法的正确性，它给出了误差的分布如下：
$$
P\{\frac{\lang f\rang-\mu}{\sigma_f/\sqrt N}<\beta\}\rightarrow\Phi(\beta)
$$
其中 $\Phi$ 为 $Guass$ 正态分布函数。由此得到：
$$
\sigma_s=|\lang f\rang-\mu|\cdot d =d\cdot\sigma_f/\sqrt{N}
$$
上式中， $d$ 代表区间长度（本题中$d=\Large\frac{1-e^{-\pi a}}a$）, $\sigma_f$ 代表 $f$ 的标准差,其定义为$\sigma_f=\sqrt{\frac1N\sum f(x_i)^2-{(\frac1N\sum f(x_i))}^2}$

#### 程式说明

* integral.cpp 

本程式使用16807随机数生成器产生随机数。利用Monte Carol权重积分算法实现如下功能：

1）筛选出使得 $\sigma_f$ 最小的 $a$ 值（精确到小数点后两位）

2）计算在不同 抽样总点数 $N$ 值下得到的积分结果

* rdm.h

带有随机数产生器函数的头文件。

#### 计算结果和分析

列出 $a-\sigma_f$ 的部分数据如下：

| $a$  | $\sigma_f$ |
| ---- | ---------- |
| 0.70 | 0.241572   |
| 0.71 | 0.234371   |
| 0.72 | 0.237643   |
| 0.73 | 0.236734   |
| 0.74 | 0.238221   |
| 0.75 | 0.23372    |
| 0.76 | 0.229242   |
| 0.77 | 0.234027   |
| 0.78 | 0.230453   |
| 0.79 | 0.236723   |

运行程序得到的 $a(min)=0.76$ ,此时函数 $\Large\frac{f(x)}{g(x)}$ 最平缓,用 ***Mathematica*** 做出可视化如下：

<img src="C:\Users\91922\AppData\Roaming\Typora\typora-user-images\image-20200609215822967.png" alt="image-20200609215822967" style="zoom:50%;" />

​                                                                                $a=0$ 

<img src="C:\Users\91922\AppData\Roaming\Typora\typora-user-images\image-20200609215922050.png" alt="image-20200609215922050" style="zoom:50%;" />

​																			$a=0.76$

<img src="C:\Users\91922\AppData\Roaming\Typora\typora-user-images\image-20200609220018426.png" alt="image-20200609220018426" style="zoom:50%;" />

​																			   $a=2$ 

进而取最优化的 $a=0.76$ ,得到的积分结果如下：

| 抽样总数 $N$ | 积分结果 $I$ | 积分标准差 $\sigma_s$ |
| ------------ | ------------ | --------------------- |
| 100          | 1.6043       | 0.0202347             |
| 1000         | 1.5759       | 0.00651431            |
| 10000        | 1.5794       | 0.00204551            |
| 1000000      | 1.5822       | 0.000647728           |
| 1000000      | 1.58147      | 0.000204608           |

利用 ***Mathematica*** 计算得到的数值结果为：$I=1.5811879708477275830$
