#include "Animal.h"
#include "ConfigFile.tpp"
#include "Ecosystem.h"
#include "Grid.h"
#include "Cell.h"
#include "GeneticData.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


//Points go from index 0 to L (so there are (L+1)^2 cells)

using namespace std;

int main(int argc, char *argv[]) {

        string inputPath("configuration.in"); // Fichier d'input par defaut
        if (argc > 1) // Fichier d'input specifie par l'utilisateur ("./Projectv2
                      // config_perso.in")
                inputPath = argv[1];

        ConfigFile configFile(inputPath); // Les parametres sont lus et stockes dans
                                          // une "map" de strings.

        for (int i(2); i < argc; ++i) // Input complementaires ("./Projectv2
                                      // config_perso.in input_scan=[valeur]")
                configFile.process(argv[i]);

        unsigned int L = configFile.get<unsigned int>("L");
        unsigned int nb_plants = configFile.get<unsigned int>("plants");
        unsigned int nb_animals = configFile.get<unsigned int>("animals");
        unsigned int tfin = configFile.get<unsigned int>("tfin");

        string animalForm = configFile.get<string>("Animal zone");
        unsigned int AnimalParam1 = configFile.get<unsigned int>("Animal zone parameter 1");
        unsigned int AnimalParam2 = configFile.get<unsigned int>("Animal zone parameter 2");
        unsigned int AnimalParam3 = configFile.get<unsigned int>("Animal zone parameter 3");
        unsigned int AnimalParam4 = configFile.get<unsigned int>("Animal zone parameter 4");

        string plantForm = configFile.get<string>("Plant zone");
        unsigned int PlantParam1 = configFile.get<unsigned int>("Plant zone parameter 1");
        unsigned int PlantParam2 = configFile.get<unsigned int>("Plant zone parameter 2");
        unsigned int PlantParam3 = configFile.get<unsigned int>("Plant zone parameter 3");
        unsigned int PlantParam4 = configFile.get<unsigned int>("Plant zone parameter 4");

        string extension = configFile.get<string>("output");

        srand(time(NULL) +clock()); // seeds the random number generator
        //(added clock() in the case of multiple simulations at the same second)

        Grid grid(L);

        Zone animalZone = grid.getZone(animalForm, AnimalParam1, AnimalParam2, AnimalParam3, AnimalParam4);
        Zone plantZone = grid.getZone(plantForm, PlantParam1, PlantParam2, PlantParam3, PlantParam4);


        Ecosystem ecosystem(&grid, animalZone, plantZone, nb_animals, nb_plants);

        ofstream write_AnimalX, write_AnimalY, write_Plant, write_SystemParam, write_AnimalParamBegin, write_AnimalParamEnd, write_AnimalForce, write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr;
        write_AnimalX.open("animal_x_"+extension+".out");
        write_AnimalY.open("animal_y_"+extension+".out");
        write_Plant.open("plant_"+extension+".out");
        write_SystemParam.open("system_param_"+extension+".out");
        write_AnimalParamBegin.open("animal_param_begin_"+extension+".out");
        write_AnimalParamEnd.open("animal_param_end_"+extension+".out");
        write_AnimalForce.open("animal_force_"+extension+".out");
        write_AnimalNbMoves.open("animal_nb_moves_"+extension+".out");
        write_AnimalNbOff.open("animal_nb_offspring_"+extension+".out");
        write_AnimalReproThr.open("animal_repro_threshold_"+extension+".out");

        ecosystem.write_AnimalParam(write_AnimalParamBegin);

        for(size_t t(0); t<tfin; ++t) {
                ecosystem.iteration(write_AnimalX,write_AnimalY, write_Plant, write_SystemParam, write_AnimalForce, write_AnimalNbMoves,
                                    write_AnimalNbOff, write_AnimalReproThr);
        }
        ecosystem.write(write_AnimalX, write_AnimalY, write_Plant, write_SystemParam, write_AnimalForce, write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr);
        ecosystem.write_AnimalParam(write_AnimalParamEnd);

        write_AnimalX.close();
        write_AnimalY.close();
        write_Plant.close();
        write_SystemParam.close();
        write_AnimalParamBegin.close();
        write_AnimalParamEnd.close();
        write_AnimalForce.close();
        write_AnimalNbMoves.close();
        write_AnimalNbOff.close();
        write_AnimalReproThr.close();






        return 0;
}
