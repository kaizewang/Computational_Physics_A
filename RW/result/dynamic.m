Y2=importdata('rw_1particle_1000steps.txt');
X2=Y2.data;
hp=plot(X2(1,1),X2(1,2),'marker','o','markersize',6, ...
    'markerfacecolor','r');
xlabel('x','interpreter','LaTex','Fontsize',14);
ylabel('y','interpreter','LaTex','Fontsize',14);
title('Simulation of random walk','interpreter','LaTex','Fontsize',14)
axis equal
axis([min(X2(:,1))*1.1 max(X2(:,1))*1.1 ...
    min(X2(:,2))*1.1 max(X2(:,2))*1.1])
grid on
grid minor
hold on
set(gcf,'color','w');
for k=1:200
   F=getframe(gcf);
   I=frame2im(F);
   [I,map]=rgb2ind(I,256);
    if k==1
        imwrite(I,map,'rw.gif','gif', 'Loopcount',inf,'DelayTime',0.1);
    else
        set(hp,'xdata',X2(k,1),'ydata',X2(k,2),'Markersize',6);
        plot(X2(2:k,1),X2(2:k,2),'b');
        pause(0.1);
        imwrite(I,map,'rw.gif','gif','WriteMode','append','DelayTime',0.1);
    end
end
