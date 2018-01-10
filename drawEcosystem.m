function drawEcosystem(figure_handle, time, animal_position, plant_density,...
    animal_char,max_char, min_char,N)

Density = reshape(plant_density(time,:), [N,N]);
animalPos = reshape(animal_position(time,:),[N,N]);
color = reshape(animal_char(time,:), [N,N]);

mincolor = [255 0 0]/255; % color of min data
maxcolor = [0 0 0]/255; % color of max data

A = (maxcolor-mincolor)./(max_char-min_char);

% x and y contain the position (x and y) of the animals
[y, x] = find(animalPos > 0);
imagesc(Density, 'Parent', figure_handle);
for i = 1 : size(x,1)
   colordata(i,:) = (color(y(i), x(i))-min_char)*A+mincolor;
end


title(strcat('$t=$', num2str(time-1), ' $(L=$', num2str(N),'$)$'), 'Parent', figure_handle);
hold on;
mymap = summer;
mymap(size(mymap,1),:) = [1 1 1];
colormap(flipud(mymap));

scatter(figure_handle,x,y,30,colordata, 'filled');
set(figure_handle,'xtick',[]);
set(figure_handle,'ytick',[]);