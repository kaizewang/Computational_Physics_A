plot(N,p2,'linewidth',1);
set(gcf,'color','w');
set(gca,'fontsize',14);
xlabel('step N');
ylabel('p(N)');
xlim([1,400])
title('2d random walk p(N)');
grid on
grid minor
print(gcf,'-djpeg','./result/2d.jpg');
