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

% Last Modified by GUIDE v2.5 02-Dec-2017 17:20:10

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
axes(handles.axes1);
t = title('Grid');
c = colorbar;
set(gca,'xtick',[]);
set(gca,'ytick',[]);
set(c,'YTick',[]);




axes(handles.axes2);
title('Population');
set(gca,'xtick',[]);
set(gca,'ytick',[]);


handles.output = hObject;

% counts where the simulation stopped for pause
handles.pause_counter = 1; 

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

% --- Executes on button press in LoadFile_PushButton.
function LoadFile_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to LoadFile_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



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
guidata(hObject, handles);




% --- Executes on button press in Run_PushButton.
function Run_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Run_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(hObject, 'value')
    set(hObject, 'string', 'Run');
    handles.animalPopulation;
    for i = handles.pause_counter : 1000
        if get(hObject, 'value')
            %draw ecosystem grid on axes 1
            
            %draw population plot on axes 2
            axes(handles.axes2);
            cla reset;
            drawPopulation(i, handles.animalPopulation, handles.plantPopulation, 5);
            pause(0.05);
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
