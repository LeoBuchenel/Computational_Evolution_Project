function drawCharac(ax,time, charac, width, tag)

str = [];
if strcmp(tag, 'MeanEnergy') 
    str = 'Mean Energy';
elseif strcmp(tag, 'MeanForce')
    str = 'Mean Force';
elseif strcmp(tag, 'MeanNbMoves')
    str = 'Mean Number of Moves';
elseif strcmp(tag, 'MeanNbOffspring')
    str = 'Mean Number of Offspring';
elseif strcmp(tag, 'MeanReproThr')
    str = 'Mean Reproduction Threshold';
end
% 
% if isempty(get(ax, 'Children'))
%     plot(charac(1:time), 'b--', 'parent', ax);
%     hold(ax, 'on');
%     plot(charac(1:time), 'b+', 'parent', ax);
%     xlabel('$t$', 'parent', ax);
%     ylabel(str, 'parent', ax);
%     set(ax, 'ylim', [0,max(charac(:))]);    
%     set(ax,'xtick',[]);
%     set(ax, 'xlim', [1 width+5]);
%     title(str, 'parent', ax);    
% else
%     ps = get(ax, 'Children');
%     if time >= 2 && time <= width
%         t = [1:time];
%         set(ps(2), 'Xdata', t);
%         set(ps(2), 'Ydata', charac(1:time));
%         set(ps(1), 'Xdata', t(time));
%         set(ps(1), 'Ydata', charac(time:time));
%         %plot(t, charac(1:time), 'b--', 'parent', ax);
%         %hold(ax, 'on');
%         %plot(t, plants(1:time), 'r--', 'parent', ax);
%         %plot(t(time), charac(time:time), 'b+', 'parent', ax);
%         %plot(t(time), plants(time:time), 'r+', 'parent', ax);
%         
%     else
%         if time > width && time <= size(charac,1)
%         t = [1:width+1];
%         set(ps(2), 'Xdata', t);
%         set(ps(2), 'Ydata', charac(time-width:time));
%         set(ps(1), 'Xdata', [width+1]);
%         set(ps(1), 'Ydata', charac(time:time));
% %         plot(charac(time-width:time), 'b--', 'parent', ax);
% %         hold(ax, 'on');
% %         plot(plants(time-width:time), 'r--', 'parent', ax);
% %         plot([width+1], charac(time:time), 'b+', 'parent', ax);
% %         plot([width+1], plants(time:time), 'r+', 'parent', ax);
%        
%         end
%     end
% 
% 
% end

tfin = size(charac,1);
if isempty(get(ax, 'Children'))
    plot(charac(1:time), 'b--', 'parent', ax);
    hold(ax, 'on');
     plot(charac(1:time), 'b+', 'parent', ax);
    xlabel('t', 'fontweight', 'bold', 'parent', ax);
    ylabel(str, 'fontweight', 'bold', 'parent', ax);
    set(ax, 'xlim', [0,tfin]);
    set(ax, 'ylim', [0,max(charac(:))]);    
    title(str, 'parent', ax); 
    grid(ax, 'on')
else
   ps = get(ax, 'Children');
   t = [1:time];
   set(ps(2), 'Xdata', t);
   set(ps(2), 'Ydata', charac(1:time));
   set(ps(1), 'Xdata', t(time));
   set(ps(1), 'Ydata', charac(time:time));
end
 set(ax, 'tag', tag);