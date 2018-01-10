data = load('system_param_test.out');
animals = data(:,1);
plants = data(:,2);


cla reset;
tfin = size(animals,1);

t = [0:tfin-1];

h1 = plot(t, animals, 'b--');
hold on;
h2 = plot(t, plants, 'r--');
xlabel('$t$');
ylabel('Number of specimen');
ylim([0 max(max(animals(:)), max(plants(:)))]);
title('Population');


