%% Setup
plantbegin = 400;
animalbegin = 200;

for i = 0 : 49
     plants(i+1) = plantbegin+i*5;
     animals(i+1) = animalbegin+i*3;
end

p1 = load('probability_evolution.out');
p2 = load('probability_no_evolution.out');

minp = min([min(p1(:)) min(p2(:))]);

%% Plots
figure
[X Y] = meshgrid(plants, animals);
pcolor(X,Y,p1);
xlabel('plants');
ylabel('animals');
colormap default

caxis([minp max(p1(:))]);
 c = colorbar;
% set(c, 'ylim', [0 1]);
 ylabel(c,'Steady state probability', 'interpreter', 'latex') 


figure
pcolor(X,Y,p2);
xlabel('plants');
ylabel('animals');
colormap default
% c = colorbar;
%set(c, caxis, [0 max(p1(:))]);
%set(c, 'DisplayRange', [0 1]);
caxis([minp max(p1(:))]);
c = colorbar
ylabel(c,'Steady state probability', 'interpreter', 'latex') 


