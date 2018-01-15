x = linspace(0,4*pi, 1000);
mincolor = [1 0 0];
y = cos(x);

figure
scatter(x,y, 10, mincolor, 'filled');