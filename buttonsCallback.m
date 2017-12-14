function buttonsCallback(hObject, eventdata,extension)
global time animalNb force nbMoves nbOffspring reproThreshold charac maxCharac

if strcmp(get(hObject, 'tag'), 'load')
    
    ext = get(extension, 'string');
    if exist(strcat('system_param_',ext,'.out'), 'file')
        h = waitbar(0,'Loading');
        userdata = load(strcat('system_param_',ext,'.out'));
        data = load(['plant_', ext, '.out']);
        waitbar(0.15);
        data2 = load(['animal_pos_', ext, '.out']);
        waitbar(0.3);
        data3 = load(['animal_force_', ext, '.out']);
        waitbar(0.45);
        data4 = load(['animal_nb_moves_', ext, '.out']);
        waitbar(0.6);
        data5 = load(['animal_nb_offspring_', ext, '.out']);
        waitbar(0.75);
        data6 = load(['animal_repro_threshold_', ext, '.out']);
        waitbar(0.9);
        N = sqrt(size(data,2));
        tfin = size(data,1);
        
        for i = 1 : tfin
            Density(:,:, i) = reshape(data(i,:), [N,N]);
            animalPos(:,:,i) = reshape(data2(i,:),[N,N]);
            force(:,:,i) = reshape(data3(i,:),[N,N]);
            nbMoves(:,:,i) = reshape(data4(i,:),[N,N]);
            nbOffspring(:,:,i) = reshape(data5(i,:),[N,N]);
            reproThreshold(:,:,i) = reshape(data6(i,:),[N,N]);
        end
        
        animalNb = animalPos;
        charac  = animalNb;
        maxCharac = max(charac(:));
        runData = get(findobj('tag', 'run'), 'Userdata');
        runData.animalPopulation = userdata(:,1);
        runData.plantPopulation = userdata(:,2);
        %         runData.Energy = load(['animal_force_', ext, '.out']);
%         waitbar(0.3);
%         runData.Force = load(['animal_pos_', ext, '.out']);
%         waitbar(0.45);
%         runData.NbMoves = load(['animal_nb_moves_', ext, '.out']);
%         waitbar(0.6);
%         runData.NbOffspring = load(['animal_nb_offspring_', ext, '.out']); 
%         waitbar(0.75);
%         runData.ReproThr = load(['animal_repro_threshold_', ext, '.out']);
%         waitbar(0.9);
        runData.meanEnergy = userdata(:,3);
        runData.meanForce = userdata(:,4);
        runData.meanNbMoves = userdata(:,5);
        runData.meanNbOffspring = userdata(:,6);
        runData.meanReproThr = userdata(:,7);
        runData.animalPosition = animalPos;
        runData.plantDensity = Density;
        
        
        timeSlider = findobj('tag', 'timeSlider');
        set(timeSlider, 'max', tfin);
        set(timeSlider', 'SliderStep', [1/tfin, 5/tfin]);
        set(findobj('tag', 'run'), 'Userdata', runData);
        waitbar(1)
        close(h);
        msgbox('Loading Completed');
    else 
        errordlg('No file of given name exists');
    end
end

if strcmp(get(hObject, 'tag'), 'pause')
    if get(hObject, 'value')
        set(findobj('tag', 'run'), 'value', false);
        set(findobj('tag', 'run'), 'String', 'Resume');
    end
end

if strcmp(get(hObject, 'tag'), 'run')
    if get(hObject, 'value')
        set(hObject, 'string', 'Run');
        userdata = get(hObject, 'Userdata');
        tfin = size(userdata.plantPopulation, 1);
        while time <= tfin
            if get(hObject, 'value')
                %draw ecosystem grid on axes 1
                %cla reset;              
                plotDensity(findobj('tag', 'simulation'),time,...
                    userdata.animalPosition, userdata.plantDensity);
                %draw population plot on axes 2
                drawPopulation(findobj('tag', 'population'),time,...
                        userdata.animalPopulation, userdata.plantPopulation, 5);
                %set(gca, 'tag', 'population');
                %draw population plot on axes 3
                 drawCharac(findobj('tag', 'MeanEnergy'),time,...
                        userdata.meanEnergy, 5,...
                        'MeanEnergy');
                %draw population plot on axes 4
                 drawCharac(findobj('tag', 'MeanForce'),time,...
                        userdata.meanForce, 5,...
                        'MeanForce');
                %draw population plot on axes 5
                 drawCharac(findobj('tag', 'MeanNbMoves'),time,...
                        userdata.meanNbMoves, 5,...
                        'MeanNbMoves');
                 %draw population plot on axes 6
                 drawCharac(findobj('tag', 'MeanNbOffspring'),time,...
                        userdata.meanNbOffspring, 5,...
                        'MeanNbOffspring');
                  %draw population plot on axes 7
                 drawCharac(findobj('tag', 'MeanReproThr'),time,...
                        userdata.meanReproThr, 5,...
                        'MeanReproThr');   
                    
                pause(0.1);
                time = time +1;
                if time == tfin
                    time = 1;
                    break;
                    %set(hObject, 'Userdata', userdata);
                end
                
            else
               
                %set(hObject, 'Userdata', userdata);
                break;
            end
        end
    end
end

end