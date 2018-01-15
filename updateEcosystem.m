function updateEcosystem(figure_handle,time, animal_position, plant_density, N)
Density = reshape(plant_density(time,:), [N,N]);
animalPos = reshape(animal_position(time,:),[N,N]);

newDensity = get(figure_handle,'CData');
set(figure_handle,'CData',newDensity);

% x and y contain the position (x and y) of the animals
%plot(x,y, '.', 'markersize', 17, 'color', 'blue');

