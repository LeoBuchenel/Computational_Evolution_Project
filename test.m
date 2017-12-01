data = load('system_param_test.out');
animals = data(:,1);
plants = data(:,2);

tfin = size(animals,1);

t = [0:tfin-1];

width = 50;

figure
h1 = plot(t(1:1), animals(1:1));
hold on;
h2 = plot(t(1:1), plants(1:1));
xlabel('$t$');
ylabel('Number of specimen');
ylim([0 max(max(animals(:)), max(plants(:)))]);
set(gca,'xtick',[]);
xlim([1 width]);

for i = 2 : width
    pause(0.1);
    set(h1, 'xData', t(1:i));
    set(h1, 'yData', animals(1:i));
    xlim([1 width+5]);
    set(h2, 'xData', t(1:i));
    set(h2, 'yData', plants(1:i));

end


for  i = 2 : tfin-width
    pause(0.1);
    set(h1, 'xData', t(i:i+width));
    set(h1, 'yData', animals(i:i+width));
    xlim([t(i) t(i+width)+5]);
    set(h2, 'xData', t(i:i+width));
    set(h2, 'yData', plants(i:i+width));
end

