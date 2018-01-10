function radioButtonCallback(hObject, eventdata)
global force animalNb nbMoves nbOffspring reproThreshold charac maxCharac

if strcmp(get(hObject, 'tag'), 'forceButton')
    charac = animalNb;
elseif strcmp(get(hObject, 'tag'), 'forceButton')
    charac = force;
elseif strcmp(get(hObject, 'tag'), 'nbMovesButton')
    charac = nbMoves;
elseif strcmp(get(hObject, 'tag'), 'nbOffspringButton')
    charac = nbOffspring;
elseif strcmp(get(hObject, 'tag'), 'reproThrButton')
    charac = reproThreshold;
end
maxCharac = max(charac(:));
end