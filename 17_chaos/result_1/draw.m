scatter(lambda7,x7,1)
xlabel('$\lambda$','interpreter','latex');
ylabel('$x$','interpreter','latex')
set(gcf,'color','w')
set(gca,'fontsize',12)

a1=a(1:6);
a2=a(2:7);
A=a1-a2;
A1=A(1:5);
A2=A(2:6);
A1./A2

b1=b(1:6);
b2=b(2:7);
B=b1-b2;
B1=B(1:5);
B2=B(2:6);
B1./B2
