Tc = 25;
T = linspace(0, Tc, 500);

t = (T-Tc)/Tc;

kB = 1.38e-23;

Kc = log(1+sqrt(2))/2;
J = Kc*Tc*kB;

B = (8*sqrt(2)*Kc)^(1/8);
b = 1/(8*sqrt(2))*(sqrt(2)-9*Kc);

m = (1-sinh(2*J./(kB*T)).^(-4)).^(1/8);
m1 = B*(-t).^(1/8);
m2 = m1.*(1+b*(-t));

figure
plot(T/Tc, m);
hold on;
plot(T/Tc, m1);
plot(T/Tc, m2);
legend({'Analytic', 'Leading scaling behaviour', 'First order correction'}, 'location', 'best');

figure
loglog(-t, m);
hold on;
loglog(-t, m1);
loglog(-t, m2);
legend({'Analytic', 'Leading scaling behaviour', 'First order correction'}, 'location', 'best');

figure
plot(T/Tc, abs(m-m1)./m);
hold on
plot(T/Tc, abs(m-m2)./m);
plot(T/Tc, ones(size(T))*0.02);
