close all; 
clear all;

%% Data Loading

ft = fittype( 'a*x-b*x*y', ...
    'independent', {'x', 'y'}, 'dependent', 'z',...,
    'coefficients', {'a','b'} );

data = load('plant_test.out');
N = sqrt(size(data,2)); % N = L-1
tfin = size(data,1);

sys_param = load('system_param_test.out');
animal_param_begin = load('animal_param_begin_test.out');
animal_param_end = load('animal_param_end_test.out');
t = [0:tfin-1];

N1 = sys_param(:,1);
N1fit = N1(1:end-1);
N2 = sys_param(:,2);
N2fit = N2(1:end-1);

for i = 1 : size(N1, 1)-1
   N1dot(i) = N1(i+1)-N1(i); 
   N2dot(i) = N2(i+1)-N2(i);
end

MaxDensity = max(data(:));

%% Lotka Volterra fit
f1 = fit([N1fit N2fit], N1dot', ft);
f2 = fit([N2fit N1fit], N2dot',ft);
alpha = f2.a
beta = f2.b
gamma = -f1.a
delta = -f1.b
N1dotFit = f1.a*N1fit-f1.b*N1fit.*N2fit;
N2dotFit = f2.a.*N2fit-f2.b*N1fit.*N2fit;

N1LV(1) = N1(1);
N2LV(1) = N2(1);

for i = 1 : tfin-1
   N1LV(i+1) = N1dotFit(i)+N1LV(i); 
   N2LV(i+1) = N2dotFit(i)+N2LV(i); 
end



%% Derivatives plot

figure
plot(N1dot,'b.', 'MarkerSize', 17);
hold on;
plot(N2dot,'r.', 'MarkerSize', 17);
plot(t(1:end-1),N1dotFit);
plot(t(1:end-1), N2dotFit);
xlim([0, tfin-1]);
xlabel('$t$');
ylabel('$\dot{N_i}(t)$');
legend({'Animals (simulation)',  'Plants (simulation)','Animals (LV fit)', 'Plants (LV fit)'}, 'location', 'best');


 %% Animal/plant plot
figure
plot(t,N1, 'b');
hold on;
plot(t,N2, 'r');
%plot(t, N1LV, 'b--');
%plot(t, N2LV, 'r--');
xlabel('$t$');
ylabel('Number of specimens');
legend({'Animals', 'Plants'},'location', 'best');


%% Histogram plot
figure
histogram(animal_param_begin(:,1));
xlabel('force (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_begin(:,2));
xlabel('Number of moves (beginning)');
ylabel('Number of animals');

figure

histogram(animal_param_begin(:,3));
xlabel('Number of offsprings (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_begin(:,4));
xlabel('Reproduction threshold (beginning)');
ylabel('Number of animals');

figure

histogram(animal_param_end(:,1));
xlabel('Force (end)');
ylabel('Number of animals');

histogram(animal_param_end(:,2));
xlabel('Number of moves (end)');
ylabel('Number of animals');


figure
histogram(animal_param_end(:,3));
xlabel('Number of offsprings (end)');
ylabel('Number of animals');

histogram(animal_param_end(:,4));
xlabel('Reproduction threshold (end)');
ylabel('Number of animals');



%% Density plotting
for i = 1 : tfin
    Density(:,:, i) = transpose(reshape(data(i,:), [N,N]));
end

figure
for i = 1 : tfin
    
h=imagesc(Density(:,:,i));
set(gca,'YDir', 'Normal');

c = colorbar;
c.Label.Interpreter = 'latex';
c.Label.String = 'Number of plants on cell';
colormap(flipud(hot));
caxis([0, MaxDensity]);


ax = gca;
ax.GridAlpha = 0.5;

xlabel('$x$');
ylabel('$y$');
title(sprintf('$t$=%0.2f s',t(i)));
pause(.1)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
end

