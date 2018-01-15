function drawdata(figure_handle, time, tabledata, tablecolor, width)

if time == 1
    
    for i = 1 : size(tabledata,1)
    plot(tabledata(i,1:1), '--', 'Parent', figure_handle, 'color', tablecolor(i,:));
    hold on;
    plot([1], tabledata(i,1:1), '+', 'Parent', figure_handle, 'color', tablecolor(i,:));
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim',[0 max(tabledata(:))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'Xlim', [1 width+5]);  
    end
    %title('Population');
else
if time >= 2 & time <= width
    t = [1:time];
    for i = 1 : size(tabledata,1)
    plot(t, tabledata(i,1:time), '--','Parent', figure_handle, 'color', tablecolor(i,:));
    hold on;
    plot(t(time), tabledata(i,time:time), '+','Parent', figure_handle, 'color', tablecolor(i,:));
    xlabel('$t$', 'Parent', figure_handle);
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim', [0 max(tabledata(:))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'xlim', [1 width+5]);
    end
else
    if time > width & time <= size(tabledata,2)
    for i = 1 : size(tabledata,1)
    plot(tabledata(i,time-width:time), '--','Parent', figure_handle, 'color', tablecolor(i,:));
    hold on;
    plot([width+1], tabledata(i,time:time), '+','Parent', figure_handle, 'color', tablecolor(i,:));
    xlabel('$t$');
    %ylabel('Number of specimen');
    set(figure_handle, 'Ylim', [0 max(tabledata(:))]);
    set(figure_handle,'xtick',[]);
    set(figure_handle, 'Xlim', [1 width+5]);
    end
    end
end
end