function drawPopulation(time, animals, plants, width)

if time == 1
    plot(animals(1:1), 'b--');
    hold on;
    plot(plants(1:1), 'r--');
     plot(animals(1:1), 'b+');
     plot(plants(1:1), 'r+');
    xlabel('$t$');
    ylabel('Number of specimen');
    ylim([0 max(max(animals(:)), max(plants(:)))]);
    set(gca,'xtick',[]);
    xlim([1 width+5]);
    title('Population');
else
if time >= 2 & time <= width
    t = [1:time];
    plot(t, animals(1:time), 'b--');
    hold on;
    plot(t, plants(1:time), 'r--');
    plot(t(time), animals(time:time), 'b+');
    plot(t(time), plants(time:time), 'r+');
    xlabel('$t$');
    ylabel('Number of specimen');
    ylim([0 max(max(animals(:)), max(plants(:)))]);
    set(gca,'xtick',[]);
    xlim([1 width+5]);
    title('Population');
else
    if time > width & time <= size(animals,1)
    plot(animals(time-width:time), 'b--');
    hold on;
    plot(plants(time-width:time), 'r--');
    plot([width+1], animals(time:time), 'b+');
    plot([width+1], plants(time:time), 'r+');
    xlabel('$t$');
    ylabel('Number of specimen');
    ylim([0 max(max(animals(:)), max(plants(:)))]);
    set(gca,'xtick',[]);
    xlim([1 width+5]);
    title('Population');
    end
end
end