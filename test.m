
repertoire = './'; % Chemin d'acces au code compile
executable = 'Projectv2'; % Nom de l'executable
input = 'configuration.in';

[status, result] = system(strcat(repertoire,executable)); %fait tourner l'executable dans le repertoire et retourne le code lance par l'executable