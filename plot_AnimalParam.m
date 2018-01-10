%% Data Loading


tfin = 500;

animal_force = fopen('animal_force_test.out');
animal_nb_moves = fopen('animal_nb_moves_test.out');
animal_nb_offspring = fopen('animal_nb_offspring_test.out');
animal_repro_threshold = fopen('animal_repro_threshold_test.out');

force = str2num(fgetl(animal_force));
nb_moves = str2num(fgetl(animal_nb_moves));
nb_offspring = str2num(fgetl(animal_nb_offspring));
repro_threshold = str2num(fgetl(animal_repro_threshold));

% force_median(1) = median(force);
% nb_moves_median(1) = median(nb_moves);
% nb_offspring_median(1) = median(nb_offspring);
% repro_threshold_median(1) = median(repro_threshold);

figure
h = histogram(force, 'Binwidth', 1);
ylim([0,100])
% grid on 
% grid minor
% ax = gca;
% ax.GridAlpha = 0.5;
% 
% xlim([0,200]);

% xlabel('x')
% ylabel('y')
 ht = title('t=0 s');
% 
 t = 0;
% 
% x = str2num(fgetl(animal_force));
% y = str2num(fgetl(animalY));
 
t=0;

while ~isempty(force) && ~isempty(nb_moves) && ~isempty(nb_offspring)...
        && ~isempty(repro_threshold)
    t = t+1;
    pause(.1)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
    set(h,'Data',force);
    set(ht,'String',sprintf('t=%0.2f s',t));
    
    force = str2num(fgetl(animal_force));
    nb_moves = str2num(fgetl(animal_nb_moves));
    nb_offspring = str2num(fgetl(animal_nb_offspring));
    repro_threshold = str2num(fgetl(animal_repro_threshold));
    
    
%     force_median(t) = median(force);
%     nb_moves_median(t) = median(nb_moves);
%     nb_offspring_median(t) = median(nb_offspring);
%     repro_threshold_median(t) = median(repro_threshold);
end

fclose(animal_force);
fclose(animal_nb_moves);
fclose(animal_nb_offspring);
fclose(animal_repro_threshold);

