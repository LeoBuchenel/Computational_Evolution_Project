%% Simulation
repertoire = './'; % Chemin d'acces au code compile
executable = 'Projectv2'; % Nom de l'executable
input = 'configuration.in'; % Nom du fichier d'entree

paramstr = '';

nsimul = 421; % Nombre de simulations a faire



%% Simulations
for i = 1 : nsimul 
    eval(sprintf('!%s%s %s %s', repertoire, executable, input, ['output=test_' num2str(i)]))
    disp('Done.')
end



%% Results loading and computing
 data = load([['system_param_test_' num2str(1)] '.out']);
 Animals = 1/nsimul*data(:,1);
 Plants = 1/nsimul*data(:,2);
 t = [0:size(data,1)-1];
 tfin = size(data,1);

for i = 2:nsimul
    data = load([['system_param_test_' num2str(i)] '.out']);
    currentAnimals = data(:,1);
    currentPlants = data(:,2);
    Animals = Animals+1/nsimul*currentAnimals;
    Plants = Plants+1/nsimul*currentPlants;
end

%% Graphs
figure
plot(t, Animals);
hold on
plot(t, Plants);
xlabel('$t$');
ylabel('Average of specimens');
legend({'Animals', 'Plants'}, 'location', 'best');

%% Lotka-Volterra fitting
ft = fittype( 'a*x+b*x*y', ...
    'independent', {'x', 'y'}, 'dependent', 'z',...,
    'coefficients', {'a','b'} );

Animalsfit = Animals;
Plantsfit = Plants;
Animalsdot(1) = Animals(2)-Animals(1);
Plantsdot(1) = Plants(2)-Plants(1);
for i = 2 : tfin-1
   Animalsdot(i) = 0.5*(Animals(i+1)-Animals(i-1)); 
   Plantsdot(i) = 0.5*(Plants(i+1)-Plants(i-1));
end
Animalsdot(tfin)=Animals(tfin)-Animals(tfin-1);
Plantsdot(tfin) = Plants(tfin)-Plants(tfin-1);

f1 = fit([Animalsfit Plantsfit], Animalsdot', ft);
f2 = fit([Plantsfit Animalsfit], Plantsdot',ft);

alpha = f2.a
beta = -f2.b
gamma = -f1.a
delta = f1.b

AnimalsdotFit = f1.a*Animalsfit+f1.b*Animalsfit.*Plantsfit;
PlantsdotFit = f2.a.*Plantsfit+f2.b*Animalsfit.*Plantsfit;

AnimalsLV(1:2) = Animals(1:2);
PlantsLV(1:2) = Plants(1:2);

for i = 2 : tfin-1
   AnimalsLV(i+1) = 2*AnimalsdotFit(i)+AnimalsLV(i-1); 
   PlantsLV(i+1) = 2*PlantsdotFit(i)+PlantsLV(i-1); 
end

%% Derivatives plot
figure
plot(Animalsdot,'b.', 'MarkerSize', 17);
hold on;
plot(Plantsdot,'r.', 'MarkerSize', 17);
plot(t,AnimalsdotFit);
plot(t, PlantsdotFit);
xlim([0, tfin-1]);
xlabel('$t$');
ylabel('$\dot{N_i}(t)$');
legend({'Animals (simulation)',  'Plants (simulation)','Animals (LV fit)', 'Plants (LV fit)'}, 'location', 'best');
