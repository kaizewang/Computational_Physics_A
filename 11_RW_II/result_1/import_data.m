p1_ideal=importdata('1d_ideal.txt');
p2_ideal=importdata('2d_ideal.txt');
p3_ideal=importdata('3d_ideal.txt');
p1=importdata('1d_random_walk_P1.txt');
p2=importdata('2d_random_walk_P2.txt');
p3=importdata('3d_random_walk_P3.txt');
N=p1(2:2:1000,1);
p1=p1(2:2:1000,2);
p2=p2(2:2:1000,2);
p3=p3(2:2:1000,2);
p1_ideal=p1_ideal(:,2);
p2_ideal=p2_ideal(:,2);
p3_ideal=p3_ideal(:,2);
a=log(N);
b1=log(p1);
b2=log(p2);
b3=log(p3);

