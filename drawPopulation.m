function drawPopulation(figure_handle, time, animals, plants, width)

if time == 1
    plot(animals(1:1), 'b', 'Parent', figure_handle);
    hold on;
    plot(plants(1:1), 'r','Parent', figure_handle);
    plot([1], animals(1:1), 'b+', 'Parent', figure_handle);
    plot([1], plants(1:1), 'r+','Parent', figure_handle);
    xlabel('$t$', 'Parent', figure_handle);
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim',[0 max(max(animals(:)), max(plants(:)))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'Xlim', [1 width+5]);
    %title('Population');
else
if time >= 2 & time <= width
    t = [1:time];
    plot(t, animals(1:time), 'b--','Parent', figure_handle);
    hold on;
    plot(t, plants(1:time), 'r--','Parent', figure_handle);
    plot(t(time), animals(time:time), 'b+','Parent', figure_handle);
    plot(t(time), plants(time:time), 'r+','Parent', figure_handle);
    xlabel('$t$', 'Parent', figure_handle);
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim', [0 max(max(animals(:)), max(plants(:)))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'xlim', [1 width+5]);
else
    if time > width & time <= size(animals,1)
    plot(animals(time-width:time), 'b--','Parent', figure_handle);
    hold on;
    plot(plants(time-width:time), 'r--','Parent', figure_handle);
    plot([width+1], animals(time:time), 'b+','Parent', figure_handle);
    plot([width+1], plants(time:time), 'r+','Parent', figure_handle);
    xlabel('$t$');
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim', [0 max(max(animals(:)), max(plants(:)))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'Xlim', [1 width+5]);
    end
end
end