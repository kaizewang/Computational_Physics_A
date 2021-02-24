plot(log(N),log(e),'linewidth',2)
grid on
grid minor
set(gcf,'color','w')
xlabel('$log(N)$','interpreter','latex')
ylabel('$error$','interpreter','latex')
title('积分误差随参数N的变化关系(\gamma=1.4)','interpreter','tex')
set(gca,'fontsize',14)
