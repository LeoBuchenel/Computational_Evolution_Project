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

% Last Modified by GUIDE v2.5 30-Nov-2017 19:01:22

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

axes(handles.axes1);
title('Grid');
c = colorbar;
set(gca,'xtick',[]);
set(gca,'ytick',[]);
set(c,'YTick',[]);




axes(handles.axes2);
title('Population');
set(gca,'xtick',[]);
set(gca,'ytick',[]);



% Choose default command line output for GUI
handles.output = hObject;



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


% --- Executes on button press in togglebutton7.
function togglebutton7_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton7


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


% --- Executes on button press in radiobutton3.
function radiobutton3_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton3


% --- Executes on button press in radiobutton4.
function radiobutton4_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton4


% --- Executes on button press in radiobutton5.
function radiobutton5_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton5


% --- Executes on button press in LoadFile_PushButton.
function LoadFile_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to LoadFile_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
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


% --- Executes on button press in Run_PushButton.
function Run_PushButton_Callback(hObject, eventdata, handles)
% hObject    handle to Run_PushButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
data = load('system_param_test.out');
animals = data(:,1);
plants = data(:,2);

axes(handles.axes2);
tfin = size(animals,1);

t = [0:tfin-1];

width = 50;

h1 = plot(t(1:1), animals(1:1), 'b--');
hold on;
h2 = plot(t(1:1), plants(1:1), 'r--');
h3 = plot(t(1:1), animals(1:1), 'b+');
h4 = plot(t(1:1), plants(1:1), 'r+');
xlabel('$t$');
ylabel('Number of specimen');
ylim([0 max(max(animals(:)), max(plants(:)))]);
set(gca,'xtick',[]);
xlim([1 width+5]);
title('Population');


for i = 2 : width
    pause(0.1);
    set(h1, 'xData', t(1:i));
    set(h1, 'yData', animals(1:i));
    xlim([1 width+5]);
    set(h2, 'xData', t(1:i));
    set(h2, 'yData', plants(1:i));
    
    set(h3, 'xData', t(i:i));
    set(h3, 'yData', animals(i:i));
    
    set(h4, 'xData', t(i:i));
    set(h4, 'yData', plants(i:i));

end


for  i = 2 : tfin-width
    pause(0.1);
    set(h1, 'xData', t(i:i+width));
    set(h1, 'yData', animals(i:i+width));
    xlim([t(i) t(i+width)+5]);
    set(h2, 'xData', t(i:i+width));
    set(h2, 'yData', plants(i:i+width));
    
    set(h3, 'xData', t(i+width:i+width));
    set(h3, 'yData', animals(i+width:i+width));
    
    set(h4, 'xData', t(i+width:i+width));
    set(h4, 'yData', plants(i+width:i+width));
end





% --------------------------------------------------------------------
function uipushtool2_ClickedCallback(hObject, eventdata, handles)
% hObject    handle to uipushtool2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gca, 'xlimMode', 'auto');
