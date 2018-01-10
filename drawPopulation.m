function drawPopulation(ax, time, animals, plants, width)


% if isempty(get(ax, 'Children'))
%     plot(animals(1:time), 'b--', 'parent', ax);
%     hold(ax, 'on');
%     plot(plants(1:time), 'r--', 'parent', ax);
%      plot(animals(1:time), 'b+', 'parent', ax);
%      plot(plants(1:time), 'r+', 'parent', ax);
%     xlabel('$t$', 'parent', ax);
%     ylabel('Number of specimen', 'parent', ax);
%     set(ax, 'ylim', [0 max(max(animals(:)), max(plants(:)))]);    
%     set(ax,'xtick',[]);
%     set(ax, 'xlim', [1 width+5]);
%     title('Population', 'parent', ax);    
% else
%     ps = get(ax, 'Children');
%     if time >= 2 && time <= width
%         t = [1:time];
%         set(ps(4), 'Xdata', t);
%         set(ps(4), 'Ydata', animals(1:time));
%         set(ps(3), 'Xdata', t);
%         set(ps(3), 'Ydata', plants(1:time));
%         set(ps(2), 'Xdata', t(time));
%         set(ps(2), 'Ydata', animals(time:time));
%         set(ps(1), 'Xdata', t(time));
%         set(ps(1), 'Ydata', plants(time:time));
%         %plot(t, animals(1:time), 'b--', 'parent', ax);
%         %hold(ax, 'on');
%         %plot(t, plants(1:time), 'r--', 'parent', ax);
%         %plot(t(time), animals(time:time), 'b+', 'parent', ax);
%         %plot(t(time), plants(time:time), 'r+', 'parent', ax);
%         
%     else
%         if time > width && time <= size(animals,1)
%         t = [1:width+1];
%         set(ps(4), 'Xdata', t);
%         set(ps(4), 'Ydata', animals(time-width:time));
%         set(ps(3), 'Xdata', t);
%         set(ps(3), 'Ydata', plants(time-width:time));
%         set(ps(2), 'Xdata', [width+1]);
%         set(ps(2), 'Ydata', animals(time:time));
%         set(ps(1), 'Xdata', [width+1]);
%         set(ps(1), 'Ydata', plants(time:time));
% %         plot(animals(time-width:time), 'b--', 'parent', ax);
% %         hold(ax, 'on');
% %         plot(plants(time-width:time), 'r--', 'parent', ax);
% %         plot([width+1], animals(time:time), 'b+', 'parent', ax);
% %         plot([width+1], plants(time:time), 'r+', 'parent', ax);
%        
%         end
%     end
% end

tfin = size(plants, 1);
if isempty(get(ax, 'Children'))
    plot(animals(1:time), 'b--', 'parent', ax);
    hold(ax, 'on');
    plot(plants(1:time), 'r--', 'parent', ax);
    plot(animals(1:time), 'b+', 'parent', ax);
    plot(plants(1:time), 'r+', 'parent', ax);
    xlabel('t', 'parent', ax);
    ylabel('Number of specimen', 'parent', ax);
    set(ax, 'ylim', [0 max(max(animals(:)), max(plants(:)))]);    
    set(ax, 'xlim', [1 tfin]);
    title('Population', 'parent', ax);  
    grid(ax, 'on');
else
    ps = get(ax, 'Children');
    t = [1:time];
    set(ps(4), 'Xdata', t);
    set(ps(4), 'Ydata', animals(1:time));
    set(ps(3), 'Xdata', t);
    set(ps(3), 'Ydata', plants(1:time));
    set(ps(2), 'Xdata', t(time));
    set(ps(2), 'Ydata', animals(time:time));
    set(ps(1), 'Xdata', t(time));
    set(ps(1), 'Ydata', plants(time:time));
        %plot(t, animals(1:time), 'b--', 'parent', ax);
        %hold(ax, 'on');
        %plot(t, plants(1:time), 'r--', 'parent', ax);
        %plot(t(time), animals(time:time), 'b+', 'parent', ax);
        %plot(t(time), plants(time:time), 'r+', 'parent', ax);
end
 set(ax, 'tag', 'population');
