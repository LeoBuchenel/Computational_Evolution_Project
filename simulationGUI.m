global time force nbMoves nbOffspring reproThreshold 

%
%Check whether the GUI window is already opn
h = findall(0,'tag','ecosystem');

if(~isempty(h))
    
    %
    %If GUI window is already open, inform the user
     msgbox('The window is already open');  

else
    time = 1;
    force = [];
    nbMoves = [];
    nbOffspring = [];
    reproThreshold = [];
    %
    %Else create the GUI window
    fig         =   figure( 'Name',             'Ecosystem',...
                            'Numbertitle',      'off',...
                            'tag',              'ecosystem',...
                            'units',            'normalized',...
                            'outerposition',    [0 0 1 1]);
    
    
    %
    %Get the screen size in order to adjust the fonts with repect to the
    %screen size
    scrsz       = get(groot, 'screensize');
    
    title_font  = scrsz(3)*15/1920;
    text_font   = scrsz(3)*13/1920;
    
%     inputs      = uipanel(  fig,...
%                             'title',            'Inputs',...
%                             'fontsize',         title_font,...
%                             'fontweight',       'bold',...
%                             'position',         [0.65 0.18 0.3 0.8]);
%     
    
    horzalign     = 0.63;
%     characPanel   = uipanel(  fig,...
%                               'title',          'Characteristic to display',...
%                               'fontsize',       title_font,...
%                               'fontweight',     'bold',...
%                               'position',       [horzalign, 0.2, 0.35, 0.28]);
    filePanel     = uipanel(  fig,...
                            'title',            'File to import',...
                            'fontsize',         title_font,...
                            'fontweight',       'bold',...
                            'position',         [horzalign 0.1 0.35 0.07]);
%     
%                     
%                  
%     
%     
%                     
%     %----------Equation panel
%     
%     
%     %
    %Create a panel to display the equation of harmonic oscillator motion                    
                            
    extension    =   uicontrol(  filePanel,...
                                'style',            'edit',...
                                'string',           'untitled.out',...
                                'fontsize',         text_font,...
                                'unit',             'normalized',...
                                'fontweight',       'bold',...
                                'position',         [0.05 0.2 0.9 0.8]);
                            
   startData    =   struct('pauseCounter', 1, 'animalPopulation', [],...
                            'plantPopulation', [],...
                            'Force', [], 'NbMoves', [],...
                            'NbOffspring', [], 'ReproThr', [],...
                            'meanEnergy', [],...
                            'meanForce', [], 'meanNbMoves', [],...
                            'meanNbOffspring', [], 'meanReproThr',[],...
                            'animalPosition', [],...
                            'plantDensity', []);
   run        =   uicontrol(  fig,... 
                                    'style',            'pushbutton',...
                                    'String',           'Start',...
                                    'units',            'normalized',...
                                    'fontsize',         title_font,...
                                    'fontweight',       'bold',...
                                    'Userdata',             startData,...
                                    'tag',              'run',...
                                    'position',         [0.63, 0.05, 0.1, 0.035],...
                                    'callback',         {@buttonsCallback, extension});
                                %'userdata',         struct('inputs', [], 'outputs', []),...    

   pause        =   uicontrol(  fig,... 
                                    'style',            'pushbutton',...
                                    'String',           'Pause',...
                                    'units',            'normalized',...
                                    'value',            false,...
                                    'fontsize',         title_font,...
                                    'fontweight',       'bold',...
                                    'tag',              'pause',...
                                    'position',         [0.755, 0.05, 0.1, 0.035],...
                                    'callback',         {@buttonsCallback, extension});
                                    
                                    %'userdata',         struct('inputs', [], 'outputs', []),...    
                                    %'callback',         {@oscillation,...
                                   % mass, k, l0, x0, v0, b, w, A, time, equation, simulation});                               
                                   
   load      =   uicontrol(  fig,... 
                                    'style',            'pushbutton',...
                                    'String',           'Load files',...
                                    'units',            'normalized',...
                                    'fontsize',         title_font,...
                                    'fontweight',       'bold',...
                                    'tag',              'load',...
                                    'position',         [0.88, 0.05, 0.1, 0.035],...
                                    'callback',         {@buttonsCallback, extension});
                                    %'userdata',         struct('inputs', [], 'outputs', []),...    
                                    %'callback',         {@oscillation,...
                                   % mass, k, l0, x0, v0, b, w, A, time, equation, simulation});

  characButtons = uibuttongroup(  fig,...
                                'Visible',  'on',...
                                'Title',    'Characteristic to display',...
                                'units',    'normalized',...
                                'fontsize',  title_font,...
                                'fontweight', 'bold',...
                                'position',       [horzalign, 0.2, 0.35, 0.28]);
        
  radioInfo     = struct( 'style',     'radiobutton',...
                    'units',    'normalized',...
                    'fontsize', title_font,...
                    'fontweight', 'bold');
  
 animalNbButton   = uicontrol(    'Parent', characButtons,...
                                radioInfo,...
                                'String',       'Number of animals',...
                                'units',        'normalized',...
                                'tag',          'forceButton',...
                                'position',     [0.06 0.85 0.7 0.1],...
                                'callback',     @radioButtonCallback);
  forceButton   = uicontrol(    'Parent', characButtons,...
                                radioInfo,...
                                'String',       'Force',...
                                'units',        'normalized',...
                                'tag',          'forceButton',...
                                'position',     [0.06 0.65 0.7 0.1],...
                                'callback',     @radioButtonCallback);
                            
  movesButton   = uicontrol(    'Parent', characButtons,...
                                radioInfo,...
                                'String',       'Number of moves',...
                                'units',        'normalized',...
                                'tag',          'nbMovesButton',...
                                'position',     [0.06 0.45 0.7 0.1],...
                                'callback',     @radioButtonCallback);                           
  
  offspringButton   = uicontrol(    'Parent', characButtons,...
                                radioInfo,...
                                'String',       'Number of offspring',...
                                'units',        'normalized',...
                                'tag',          'nbOffspringButton',...
                                'position',     [0.06 0.25 0.7 0.1],...
                                'callback',     @radioButtonCallback);
                            
 reproButton   = uicontrol(    'Parent', characButtons,...
                                radioInfo,...
                                'String',       'Reproduction threshold',...
                                'units',        'normalized',...
                                'tag',          'reproThrButton',...
                                'position',     [0.06 0.05 0.7 0.1],...
                                'callback',     @radioButtonCallback);                            
%=====================================================================
    %
    %----------------Axes to plot the results
    
    %Create tabs that will contain different axes
    graphTab        =   uitabgroup( fig,...
                                    'unit',             'normalized',...
                                    'position',         [horzalign 0.5 0.37 0.5]);
                                
    tab1            =   uitab(graphTab, 'title', 'Animal/Food Population');
     tab2           =   uitab(graphTab, 'title', 'Energy');
     tab3            =   uitab(graphTab, 'title', 'Force');
     tab4            =   uitab(graphTab, 'title', 'Number of Moves');
     tab5            =   uitab(graphTab, 'title', 'Number of Offspring');
     tab6            =   uitab(graphTab, 'title', 'Reproduction Threshold');
    
      
    %
    %--------------------------------------------------------------------
    %Axes to plot simulation
    %
    axinfo          =   struct( 'units',            'normalized',...
                                'fontweight',       'bold',...
                                'fontsize',         text_font);
    simulationAxe = axes('Parent',   fig,...
                         axinfo,...
                        'position', [0.05 0.15 0.5 0.7],...
                        'tag',      'simulation');  
    
    xlabel('y');                
    ylabel('x');
    
    grid on
 %---------------------------------------   
 %Tab1   
 
    axposition = [0.14 0.15 0.8 0.8];
    axes(       'Parent' ,         tab1,...
                axinfo,...
                'position',         axposition,...
                'tag',              'population');
        
        
    ylabel('Population');
    xlabel('t');
    grid on
%---------------------------------------------
 %Tab2   
 
    axes(       'Parent' ,         tab2,...
                axinfo,...
                'position',         axposition,...
                'tag',              'MeanEnergy');
        
        
    ylabel('Mean Energy');
    xlabel('t');
    grid on
    
%---------------------------------------------
 %Tab3   
 
    axes(       'Parent' ,         tab3,...
                axinfo,...
                'position',         axposition,...
                'tag',              'MeanForce');
        
        
    ylabel('Mean Force');
    xlabel('t');
    grid on
 
    %---------------------------------------------
 %Tab4   
 
    axes(       'Parent' ,         tab4,...
                axinfo,...
                'position',         axposition,...
                'tag',              'MeanNbMoves');
        
        
    ylabel('Mean Number of Moves');
    xlabel('t');
    grid on
    
    %---------------------------------------------
 %Tab5   
 
    axes(       'Parent' ,         tab5,...
                axinfo,...
                'position',         axposition,...
                'tag',              'MeanNbOffspring');
        
        
    ylabel('Mean Number of Offspring');
    xlabel('t');
    grid on
    
   %---------------------------------------------
 %Tab6   
 
    axes(       'Parent' ,         tab6,...
                axinfo,...
                'position',         axposition,...
                'tag',              'MeanReproThr');
        
        
    ylabel('Mean Reproduction Threshold');
    xlabel('t');
    grid on
    
    %==================================================
    
                uicontrol(fig,...
                            'style',        'text',...
                            'String',       'Time',...
                            'fontweight',   'bold',...
                            'fontsize',     title_font,...
                            'unit',         'normalized',...
                            'position',     [0.08 0.9 0.05 0.03]);
                            
    timeSlider = uicontrol(fig,...
                            'style',        'slider',...
                            'unit',         'normalized',...
                            'position',     [0.13 0.9 0.3 0.03],...
                            'BackgroundColor', 'w',...
                            'Value',        1,...
                            'min',          1,...
                            'max',          100,...
                            'tag',          'timeSlider',...
                            'SliderStep',   [1/100 5/100],...
                            'callback',     @setTime);
                        
   timeEdit    = uicontrol(fig,...
                            'style',        'edit',...
                            'string',       '1',...
                            'fontsize',     text_font,...
                            'unit',         'normalized',...
                            'position',     [0.45 0.9 0.05 0.03],...
                            'tag',          'timeEdit',...
                            'callback',     @setTime);
                        
end