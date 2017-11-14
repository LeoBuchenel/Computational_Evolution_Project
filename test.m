%Read and display the file fgetl.m one line at a time:

animalX = fopen('animal_x_.out');
animalY = fopen('animal_y_.out');

x = str2num(fgetl(animalX));
y = str2num(fgetl(animalY));

h = plot(x, y, 'gx', 'linewidth', 2);

grid on 
grid minor
ax = gca;
ax.GridAlpha = 0.5;

xlim([0,20]);
ylim([0,20]);

xlabel('x')
ylabel('y')
ht = title('t=0 s');

t = 0;

x = str2num(fgetl(animalX));
y = str2num(fgetl(animalY));

while ~isempty(x) && ~isempty(y)
    t = t+1;
    pause(.2)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
    set(h,'XData',x);
    set(h,'YData', y);
    set(ht,'String',sprintf('t=%0.2f s',t));
    
   x = str2num(fgetl(animalX));
   y = str2num(fgetl(animalY));
end
fclose(animalX);
fclose(animalY);





