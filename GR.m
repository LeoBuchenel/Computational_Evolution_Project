M = 100;
delta = M/10;
[r, T] = meshgrid(linspace(0,2*M-delta,10), linspace(0, 2*M, 10));
v = (2*1./(1-2*M./r)-1)./sqrt(1+((2*1./(1-2*M./r)-1)).^2);
u = 1./sqrt(1+((2*1./(1-2*M./r)-1)).^2);

[r2, T2] = meshgrid(linspace(2*M+delta,5*M,10), linspace(0, 2*M, 10));
v2 = (2*1./(1-2*M./r2)-1)./sqrt(1+((2*1./(1-2*M./r2)-1)).^2);
u2 = 1./sqrt(1+((2*1./(1-2*M./r2)-1)).^2);

figure
quiver(r, T, u,v);
hold on;
quiver(r2, T2, u2,v2);
daspect([1 1 1])

