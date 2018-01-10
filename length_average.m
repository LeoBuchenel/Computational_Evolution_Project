%% Data loading
LWE = load('length_with_evolution.out');
LWoE = load('length_without_evolution.out');
for i = 1 : 20
   animals(i) = 270+(i-1)*3;
   plants(i) = 450 + (i-1)*5;
end

%% Plot
figure
[X Y] = meshgrid(plants, animals);
pcolor(X, Y, LWE);
xlabel('plants');
ylabel('animals');
caxis([min(LWoE(:)) max(LWE(:))]);
title('With evolution');
c=colorbar;
ylabel(c,'Average time before ecosystem dies out', 'interpreter', 'latex')
pbaspect([1 1 1]);

figure
pcolor(X, Y, LWoE);
xlabel('plants');
ylabel('animals');
caxis([min(LWoE(:)) max(LWE(:))]);
title('Without evolution');
c=colorbar;
ylabel(c,'Average time before ecosystem dies out', 'interpreter', 'latex') 
pbaspect([1 1 1]);










