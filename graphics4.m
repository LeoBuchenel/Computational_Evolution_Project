%% Data Loading
close all; 
clear all;

ft = fittype( 'a*x-b*x*y', ...
    'independent', {'x', 'y'}, 'dependent', 'z',...,
    'coefficients', {'a','b'} );

data = load('plant_test.out');
N = sqrt(size(data,2)); % N = L-1
tfin = size(data,1);

sys_param = load('system_param_test.out');
animal_param_begin = load('animal_param_begin_test.out');
animal_param_end = load('animal_param_end_test.out');
data2 = load('animal_pos_test.out');

t = [0:tfin-1];

N1 = sys_param(:,1);
N2 = sys_param(:,2);

MaxDensity = max(data(:));

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

%% Genetic Data evolution
figure
plot(sys_param(:,3));
xlabel('$t$');
ylabel('Mean force');
xlim([0 tfin-1]);

figure
plot(sys_param(:,4));
xlabel('$t$');
ylabel('Mean energy');
xlim([0 tfin-1]);


figure
plot(sys_param(:,5));
xlabel('$t$');
ylabel('Mean Moves');
xlim([0 tfin-1]);


figure
plot(sys_param(:,6));
xlabel('$t$');
ylabel('Mean Offsprings');
xlim([0 tfin-1]);

figure
plot(sys_param(:,7));
xlabel('$t$');
ylabel('Mean Reproduction Threshold');
xlim([0 tfin-1]);

%% Density plotting

speed= 10/tfin;

for i = 1 : tfin
    Density(:,:, i) = reshape(data(i,:), [N,N]);
    animalPos(:,:,i) = reshape(data2(i,:),[N,N]);
end

figure
[x,y] = find(animalPos(:,:,1) == 1);
h1=imagesc(Density(:,:,1));
set(gca,'YDir', 'Normal');
ht = title('t=0 s');

hold on;
h2 = plot(x,y, '.', 'markersize', 17);

c = colorbar;
c.Label.Interpreter = 'latex';
c.Label.String = 'Number of plants on cell';
colormap(flipud(hot));
caxis([0, MaxDensity]);


ax = gca;
ax.GridAlpha = 0.5;

xlabel('$x$');
ylabel('$y$');

for i = 2 : tfin   

pause(speed)
    if ~ishandle(h1)
        break % Arrete l'animation si la fenetre est fermee
    end
    
    if ~ishandle(h2)
        break % Arrete l'animation si la fenetre est fermee
    end
    
    [y,x] = find(animalPos(:,:,i) == 1);
    
    set(h1,'CData',Density(:,:,i));
    set(ht,'String',sprintf('t=%0.2f s',i));
    
    set(h2, 'XData', x);
    set(h2, 'YData', y);
    
end

%% Histogram plot

figure
histogram(animal_param_begin(:,1), size(animal_param_begin(:,1),1));
xlabel('force (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_begin(:,2), size(animal_param_begin(:,2),1));
xlabel('Number of moves (beginning)');
ylabel('Number of animals');

figure

histogram(animal_param_begin(:,3), size(animal_param_begin(:,3),1));
xlabel('Number of offsprings (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_begin(:,4), size(animal_param_begin(:,4),1));
xlabel('Reproduction threshold (beginning)');
ylabel('Number of animals');

figure

histogram(animal_param_end(:,1), size(animal_param_end(:,1),1));
xlabel('Force (end)');
ylabel('Number of animals');

histogram(animal_param_end(:,2), size(animal_param_end(:,2),1));
xlabel('Number of moves (end)');
ylabel('Number of animals');


figure
histogram(animal_param_end(:,3), size(animal_param_end(:,3),1));
xlabel('Number of offsprings (end)');
ylabel('Number of animals');

histogram(animal_param_end(:,4), size(animal_param_end(:,4),1));
xlabel('Reproduction threshold (end)');
ylabel('Number of animals');

%% Lotka Volterra fit
N1fit = N1(1:end-1);
N2fit = N2(1:end-1);

for i = 1 : size(N1, 1)-1
   N1dot(i) = N1(i+1)-N1(i); 
   N2dot(i) = N2(i+1)-N2(i);
end

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
plot(N1dot,'b.', 'MarkerSize', 9);
hold on;
plot(N2dot,'r.', 'MarkerSize', 9);
plot(t(1:end-1),N1dotFit);
plot(t(1:end-1), N2dotFit);
xlim([0, tfin-1]);
xlabel('$t$');
ylabel('$\dot{N_i}(t)$');
legend({'Animals (simulation)',  'Plants (simulation)','Animals (LV fit)', 'Plants (LV fit)'}, 'location', 'best');