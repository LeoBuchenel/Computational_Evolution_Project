function setTime(hObject, eventdata)
global time

timeMax = get(findobj('tag', 'timeSlider'), 'Max');
timeMin = get(findobj('tag', 'timeSlider'), 'Min');

%data = get(findobj('tag', 'run'), 'userdata');
%val = data.pauseCounter;
if strcmp(get(hObject, 'tag'), 'timeSlider')
    val = floor(get(hObject, 'Value'));
    set(hObject, 'Value', val);
    set(findobj('tag', 'timeEdit'), 'String', num2str(val));
elseif strcmp(get(hObject, 'tag'), 'timeEdit')
    
    val = floor(str2num(get(hObject, 'String')));
    
    if(val < timeMin)
        val = timeMin;
    elseif(val > timeMax)
        val = time;
    end
    set(hObject, 'String', num2str(val));
    set(findobj('tag', 'timeSlider'), 'Value', val);
    
end

time = val; 
%set(findobj('tag', 'run'), 'userdata', data);

end