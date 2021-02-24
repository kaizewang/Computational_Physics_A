%This a for ellipsoid moving 


%hp1=plot(x(1),y(1),'marker','o','markersize',5,'markerfacecolor','r','markeredgecolor','b');
r=4;
hold on;
p=[x(1)-r*cos(theta(1)),x(1)+r*cos(theta(1))];
q=[y(1)-r*sin(theta(1)),y(1)+r*sin(theta(1))];

hp2=plot(p,q,'linewidth',8,'color','r');
grid on
grid minor
axis equal;
xlim([-15,25])
ylim([-10 ,10])
set(gcf,'color','w');
set(gca,'color','b');


for i=1:800
    if i>1
    %set(hp1,'xdata',x(i),'ydata',y(i),'Markersize',5);
    p=[x(i)-r*cos(theta(i)),x(i)+r*cos(theta(i))];
    q=[y(i)-r*sin(theta(i)),y(i)+r*sin(theta(i))];
    end
    drawnow;
    F=getframe(gcf);
   I=frame2im(F);
   [I,map]=rgb2ind(I,256);
    if i==1
        imwrite(I,map,'rw.gif','gif', 'Loopcount',inf,'DelayTime',0.01);
    else
        set(hp2,'xdata',p,'ydata',q);
        pause(0.001)
        imwrite(I,map,'rw.gif','gif','WriteMode','append','DelayTime',0.01);
    end
end