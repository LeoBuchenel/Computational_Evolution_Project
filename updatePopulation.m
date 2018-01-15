function updatePopulation(figure_handle, time, animals, plants, width)
%get axes of current plot
axh = findobj(figure_handle, 'Type', 'Line');

if time >= 2 & time <= width
    t = [1:time];

    set(axh(1), 'XData',t);
    set(axh(1), 'YData', animals(1:time));
    %set(axh(1), 'LineStyle', '--');

    set(axh(2), 'XData',t);   
    set(axh(2), 'YData', plants(1:time));
    %set(axh(2), 'LineStyle', '--');

    
%     set(axh(3), 'XData', t(time));
%     set(axh(3), 'YData', animals(time:time));
%     
%     set(axh(4), 'XData', t(time));
%     set(axh(4), 'YData', plants(time:time));
    
else
    if time > width & time <= size(animals,1)       
    t = [1:width+1];
    
    set(axh(1), 'XData', t);
    set(axh(2), 'XData', t);
    
    set(axh(1), 'YData', animals(time-width:time));
    set(axh(2), 'YData', plants(time-width:time));
    
%     set(axh(3), 'XData', [width+1]);
%     set(axh(3), 'YData', animals(time:time));
%     
%     set(axh(4), 'XData', [width+1]);
%     set(axh(4), 'YData', plants(time:time));
    end
end
