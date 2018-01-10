function plotEcosystem(hObject, eventdata, file)

if(strcmp(get(hObject, 'tag'),'restart'))
    fclose('all');
end

if(strcmp(get(hObject, 'tag'),'start') || strcmp(get(hObject, 'tag'), 'restart'))
filename = get(file, 'String');
data = load(['system_param', filename]);
xFile = fopen(['animal_x', filename]);
yFile = fopen(['animal_y', filename]);
plant = load(['plant', filename]);
%forceFile = fopen(['animal_force', filename]);
%movesFile = fopen(['animal_nb_moves', filename]);
%offspringFile = fopen(['animal_nb_offspring', filename]);
%reproThrFile = fopen(['animal_repro_threshold', filename]);


x = str2num(fgetl(xFile));
y = str2num(fgetl(yFile));
animalPop = data(:,1);
plantPop = data(:,2);
%force = getl(forceFile);
%moves = getl(movesFile);
%offspring = getl(offspringFile);
%reproThr = getl(reproThrFile);

tfin = size(data,1);
N = sqrt(size(plant,2));
MaxDensity = max(plant(:));
t = [0:tfin-1];


%axPop = axes(findobj('tag', 'population'));
speed= 10/tfin;

axes(findobj('tag', 'simulation'));

for i = 1 : tfin
    Density(:,:, i) = reshape(plant(i,:), [N,N]);
end

hPlant=imagesc(Density(:,:,1));
set(gca, 'YDir', 'Normal');
ht = title('t=0 s');

hold on;
hAnimal = plot(x,y, '.', 'markersize', 17);

c = colorbar;
c.Label.String = 'Number of plants on cell';
colormap(flipud(hot));
caxis([0, MaxDensity]);


ax = gca;
ax.GridAlpha = 0.5;

xlabel('x');
ylabel('y');


axes(findobj('tag', 'population'));
width = 50;

h1 = plot(t(1:1), animalPop(1:1), 'b--');
hold on;
h2 = plot(t(1:1), plantPop(1:1), 'r--');
h3 = plot(t(1:1), animalPop(1:1), 'b+');
h4 = plot(t(1:1), plantPop(1:1), 'r+');
xlabel('$t$');

ylabel('Number of specimen');

ylim([0 max(max(animalPop(:)), max(plantPop(:)))]);
set(gca,'xtick',[]);
xlim([1 width+5]);
title('Population');

for i = 2 : tfin   


if(strcmp(get(hObject, 'tag'), 'pause'))
    speed = 100000000000000000;
end    
    
pause(speed)
    if ~ishandle(hPlant) || ~ishandle(hAnimal) || ~ishandle(h1)...
            || ~ishandle(h2) || ~ishandle(h3) || ~ishandle(h4)
        break % Arrete l'animation si la fenetre est fermee
    end
    
    x = str2num(fgetl(xFile));
    y = str2num(fgetl(yFile));
    
    set(hPlant,'CData',Density(:,:,i));
    set(ht,'String',sprintf('t=%0.2f s',i));
    
    set(hAnimal, 'XData', x);
    set(hAnimal, 'YData', y);
    
    
    if (2<=i) && (i<= width)    
        set(h1, 'xData', t(1:i));
        set(h1, 'yData', animalPop(1:i));

        set(h2, 'xData', t(1:i));
        set(h2, 'yData', plantPop(1:i));

        set(h3, 'xData', t(i:i));
        set(h3, 'yData', animalPop(i:i));

        set(h4, 'xData', t(i:i));
        set(h4, 'yData', plantPop(i:i));

        xlim([1 width+5]);
        grid on
    end
    
    if (width+1<=i) && (i<=tfin)
        pause(0.1);

        set(h1, 'xData', t(i-width:i));
        set(h1, 'yData', animalPop(i-width:i));

        set(h2, 'xData', t(i-width:i));
        set(h2, 'yData', plantPop(i-width:i));

        set(h3, 'xData', t(i:i));
        set(h3, 'yData', animalPop(i:i));

        set(h4, 'xData', t(i:i));
        set(h4, 'yData', plantPop(i:i));

        xlim([t(i-width) t(i)+5]);
        grid on
    end
end

fclose(xFile);
fclose(yFile);







end



