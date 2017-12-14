function plotDensity(ax,time, animalPosition, plantDensity)
global maxCharac charac

if isempty(get(ax, 'Children'))
    MaxDensity = max(plantDensity(:));
    [y,x] = find(animalPosition(:,:,time) > 0);
    imagesc(plantDensity(:,:,time), 'parent', ax);
    set(ax,'YDir', 'Normal');
    title(strcat('t=', num2str(time), 's'), 'parent', ax);
    
    
    hold(ax, 'on');
    cdata = autumn;
    data = [];
    for i = 1:length(x)
        data(i) = charac(y(i),x(i),time);
    end
    sz = size(autumn,1);
    cdata = cdata(sz - ceil(sz*data/maxCharac) +1,:);
    scatter(x,y,  [],cdata,'filled','parent', ax);

    c = colorbar;
    c.Label.Interpreter = 'latex';
    c.Label.String = 'Number of plants on cell';
    mymap = summer;
    mymap(size(mymap,1),:) = [1 1 1];
    colormap(flipud(mymap));
    set(c, 'Limits', [0, MaxDensity]);

    ax.GridAlpha = 0.5;

    xlabel('x', 'parent', ax);
    ylabel('y', 'parent', ax);
    set(ax, 'fontweight', 'bold');
else
    ps = get(ax, 'children');
    [y,x] = find(animalPosition(:,:,time) > 0);
    
    cdata = autumn;
    data = [];
    for i = 1:length(x)
        data(i) = charac(y(i),x(i),time);
    end
    sz = size(autumn,1);
    cdata = cdata(sz - ceil(sz*data/maxCharac) +1,:);
    
    set(ps(2), 'cData', plantDensity(:,:,time)); 
    set(ps(1), 'cData', cdata);
    set(ps(1), 'xData', x);
    set(ps(1), 'yData', y);
    title(strcat('t=', num2str(time), 's'), 'parent', ax);
end
set(ax, 'tag', 'simulation');
end
