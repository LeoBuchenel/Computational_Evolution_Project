function varargout = GUI(varargin)
% GUI MATLAB code for GUI.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI

% Last Modified by GUIDE v2.5 06-Dec-2017 16:03:20

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI is made visible.
function GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI (see VARARGIN)
% Choose default command line output for GUI

handles.output = hObject;

% counts where the simulation stopped for pause
handles.pause_counter = 1; 
handles.width = 50;


set(handles.axes1, 'visible', 'on');
set(handles.axes2, 'visible', 'on');

% Update handles structure
guidata(hObject, handles);



% UIWAIT makes GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Moves_PushButton.
function Moves_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Moves_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of Moves_PushButton


% --- Executes on button press in Offspring_PushButton.
function Offspring_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Offspring_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of Offspring_PushButton


% --- Executes on button press in Force_PushButton.
function Force_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Force_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Force_PushButton


% --- Executes on button press in Force_RadioButton.
function Force_RadioButton_Callback(hObject, eventdata, handles)
% hObject    handle to Force_RadioButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Force_RadioButton




function Extension_Name_edit_Callback(hObject, eventdata, handles)
% hObject    handle to Extension_Name_edit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Extension_Name_edit as text
%        str2double(get(hObject,'String')) returns contents of Extension_Name_edit as a double


% --- Executes during object creation, after setting all properties.
function Extension_Name_edit_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Extension_Name_edit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in LoadFiles_PushButton.
function LoadFiles_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to LoadFiles_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% when LoadFiles button is pressed, it loads every data the program needs
extension = get(handles.Extension_Name_edit', 'string');
data = load(strcat('system_param_',extension,'.out'));
handles.animalPopulation = data(:,1);
handles.plantPopulation = data(:,2);
handles.meanForce= data(:,3)';
handles.meanEnergy = data(:,4)';
handles.meanNbMoves = data(:,5)';
handles.meanOffsprings = data(:,6)';
handles.meanReprThr = data(:,7)';
handles.tfin = size(data,1);
handles.width = handles.tfin;
data = load(strcat('animal_pos_', extension, '.out'));
handles.grid_size = sqrt(size(data,2));
handles.animal_position = data;
data = load(strcat('plant_', extension, '.out'));
handles.plant_density = data;
handles.animal_force = load(strcat('animal_force_', extension, '.out'));

populationdata(1,:) = handles.animalPopulation';
populationdata(2,:) = handles.plantPopulation';

handles.populationtab = populationdata;

tablecolor(1,:) = [0 0 0];
tablecolor(2,:) = [0.4 1 0];

handles.axes2data{1} = handles.populationtab;
handles.axes2data{2} = handles.meanForce;
handles.axes2data{3} = handles.meanEnergy;
handles.axes2data{4} = handles.meanNbMoves;
handles.axes2data{5} = handles.meanOffsprings;
handles.axes2data{6} = handles.meanReprThr;

handles.currentaxes2tablecolor = tablecolor;

handles.choice = 'Population';


cla;

axes(handles.axes1);
drawEcosystem(handles.axes1, 1, handles.animal_position, handles.plant_density, handles.grid_size);
set(handles.axes1,'YDir', 'Normal');
set(handles.axes1, 'Xlim', [0 handles.grid_size]);
set(handles.axes1, 'Ylim', [0 handles.grid_size]);
c1 = colorbar('westoutside');
c2 = colorbar('southoutside');
c1.Label.Interpreter = 'latex';
c2.Label.Interpreter = 'latex';
c1.Label.String = 'Number of plants on cell';
c2.Label.String = 'Genetic data';
colormap(flipud(hot));
caxis([0, max(data(:))]);

axes(handles.axes2);
drawdata(handles.axes2, 1, handles.populationtab, handles.currentaxes2tablecolor, handles.width);

handles.pause_counter = 2;

guidata(hObject, handles);





% --- Executes on button press in Run_PushButton.
function Run_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Run_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(hObject, 'value')
    set(hObject, 'string', 'Run');
    for i = handles.pause_counter : handles.tfin 
        if get(hObject, 'value')
            %clears all axes
            handles = guidata(hObject);
            cla(handles.axes1);
            cla(handles.axes2);
            %draw ecosystem grid on axes 1
            drawEcosystem(handles.axes1, i, handles.animal_position, handles.plant_density, handles.grid_size);
            %draw population plot on axes 2
            choice = get(handles.Characteristic_Menu, 'Value');
            drawdata(handles.axes2, i, handles.axes2data{choice}, handles.currentaxes2tablecolor,handles.width);
            pause(min([1/handles.tfin 0.02]));
            guidata(hObject, handles);
        else
            handles.pause_counter = i;
            guidata(hObject, handles);
            break;
        end
    end
end


% --- Executes on button press in pause_PushButton.
function pause_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to pause_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(hObject, 'value')
    set(handles.Run_PushButton, 'value', false);
    set(handles.Run_PushButton, 'String', 'Resume');
    guidata(hObject, handles);
end



% --- Executes during object creation, after setting all properties.
function Width_Slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Width_Slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in Characteristic_Menu.
function Characteristic_Menu_Callback(hObject, eventdata, handles)
% hObject    handle to Characteristic_Menu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: contents = cellstr(get(hObject,'String')) returns Characteristic_Menu contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Characteristic_Menu


% --- Executes during object creation, after setting all properties.
function Characteristic_Menu_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Characteristic_Menu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
c1 = colorbar('westoutside');
c2 = colorbar('southoutside');
mymap = summer;
mymap(size(mymap,1),:) = [1 1 1];
colormap(flipud(mymap));
set(gca,'xtick',[]);
set(gca,'ytick',[]);
set(c1,'YTick',[]);
set(c2,'YTick',[]);

% Hint: place code in OpeningFcn to populate axes1


% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
set(gca,'xtick',[]);
set(gca,'ytick',[]);
% Hint: place code in OpeningFcn to populate axes2
