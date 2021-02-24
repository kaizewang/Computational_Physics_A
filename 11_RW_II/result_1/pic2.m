plot(N,p2,'linewidth',2);
set(gcf,'color','w');
set(gca,'fontsize',14);
xlabel('step N');
ylabel('p(N)');
title('2d random walk p(N)');
hold on
scatter(N(1:51)-2,p2_ideal(1:51));
xlim([1 100])
grid on
grid minor
print(gcf,'-djpeg','./result/2d_2.jpg');