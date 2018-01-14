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

        bool load = configFile.get<bool>("load");
        double FeedRate = configFile.get<double>("feeding rate");
        double shock_parameter = configFile.get<double>("shock parameter");
        unsigned int shock_time = configFile.get<unsigned int>("shock at t");
        unsigned int tfin = configFile.get<unsigned int>("tfin");
        unsigned int nb_plants = configFile.get<unsigned int>("plants");
        unsigned int nb_animals = configFile.get<unsigned int>("animals");
        bool DataWrite = configFile.get<bool>("write data");
        bool Evolution = configFile.get<bool>("evolution");
        string food_reproduce = configFile.get<string>("feeding");
        string loadfile = configFile.get<string>("file to load");
        string extension = configFile.get<string>("output");


        string animalForm, plantForm;
        unsigned int L(0), AnimalParam1, AnimalParam2, AnimalParam3, AnimalParam4,
        PlantParam1,PlantParam2, PlantParam3, PlantParam4;

        ifstream eco_to_load;
        eco_to_load.open(loadfile);
        string test;


        if(load) {
                if(eco_to_load.fail()) {
                        cerr << "Please enter a valid load file name!" << endl;
                        return 1;
                }
                else{
                        cout << "Loading parameters from external savefile..." << endl;
                        getline(eco_to_load,test);
                        eco_to_load >> animalForm >> plantForm >> AnimalParam1
                        >> AnimalParam2 >> AnimalParam3 >> AnimalParam4
                        >> PlantParam1>> PlantParam2>> PlantParam3>> PlantParam4
                        >> L;

                        test.clear();
                }
        }else{
                L = configFile.get<unsigned int>("L");

                animalForm = configFile.get<string>("Animal zone");
                AnimalParam1 = configFile.get<unsigned int>("Animal zone parameter 1");
                AnimalParam2 = configFile.get<unsigned int>("Animal zone parameter 2");
                AnimalParam3 = configFile.get<unsigned int>("Animal zone parameter 3");
                AnimalParam4 = configFile.get<unsigned int>("Animal zone parameter 4");

                plantForm = configFile.get<string>("Plant zone");
                PlantParam1 = configFile.get<unsigned int>("Plant zone parameter 1");
                PlantParam2 = configFile.get<unsigned int>("Plant zone parameter 2");
                PlantParam3 = configFile.get<unsigned int>("Plant zone parameter 3");
                PlantParam4 = configFile.get<unsigned int>("Plant zone parameter 4");

                cout << "Creating new simulation from scratch ... " << endl;
        }

        string path = "Results/";
        string savepath = "Saves/";



        srand(time(NULL) +clock());        // seeds the random number generator
        //(added clock() in the case of multiple simulations at the same second)

        Grid grid(L);
        Zone animalZone = grid.getZone(animalForm, AnimalParam1, AnimalParam2, AnimalParam3, AnimalParam4);
        Zone plantZone = grid.getZone(plantForm, PlantParam1, PlantParam2, PlantParam3, PlantParam4);


        Ecosystem ecosystem(&grid, animalZone, plantZone, FeedRate, shock_parameter);

        if(load) {

                //skip two lines in order to get at the appropriate line with getline
                for(size_t i(2); i!=0; --i) {
                        getline(eco_to_load, test);
                        test.clear();
                }

                ecosystem.add_from_file(eco_to_load);
        }else{
                ecosystem.add_random(nb_animals, nb_plants);
        }


        ofstream write_AnimalPos, write_Plant, write_SystemParam,
                 write_AnimalParamBegin, write_AnimalParamEnd, write_AnimalForce,
                 write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr,
                 write_AnimalMouthSize, write_Ecosystem, endTime, savefile;

        write_AnimalPos.open(path+"animal_pos_"+extension+".out");
        write_Plant.open(path+"plant_"+extension+".out");
        write_SystemParam.open(path+"system_param_"+extension+".out");
        write_AnimalParamBegin.open(path+"animal_param_begin_"+extension+".out");
        write_AnimalParamEnd.open(path+"animal_param_end_"+extension+".out");
        write_AnimalForce.open(path+"animal_force_"+extension+".out");
        write_AnimalNbMoves.open(path+"animal_nb_moves_"+extension+".out");
        write_AnimalNbOff.open(path+"animal_nb_offspring_"+extension+".out");
        write_AnimalReproThr.open(path+"animal_repro_threshold_"+extension+".out");
        write_AnimalMouthSize.open(path+"animal_mouth_size_"+extension+".out");
        write_Ecosystem.open(path+"ecosystem_data_"+extension+".out");
        endTime.open(path+"tfin.out");

        savefile.open(savepath+"ecosystemSave.out");


        ecosystem.write_AnimalParam(write_AnimalParamBegin);

        for(size_t t(0); t<tfin; ++t) {

                if(t == shock_time) {
                        ecosystem.envImpact(MultiplyRate);
                }

                // if(t == 600){
                //ecosystem.envImpact(DoubleRate);
                //}

                if(t == 100) {
                        vector<string> strings = {animalForm, plantForm};

                        vector<unsigned int> numbers={AnimalParam1, AnimalParam2,
                                                      AnimalParam3, AnimalParam4,
                                                      PlantParam1, PlantParam2,
                                                      PlantParam3, PlantParam4, L};
                        ecosystem.save_ecosystem(strings, numbers, savefile, t);
                }



                ecosystem.iteration(write_AnimalPos, write_Plant, write_SystemParam, write_AnimalForce, write_AnimalNbMoves,
                                    write_AnimalNbOff, write_AnimalReproThr, write_AnimalMouthSize, DataWrite, Evolution, food_reproduce);
                if(ecosystem.died_out()) {
                        std::cout << "Ecosystem died out at t = " << t+1 << std::endl;
                        endTime << t+1;
                        return 1;
                }
                ecosystem.write_ecosystem_data(write_Ecosystem);
        }
        endTime << tfin;
        ecosystem.write(write_AnimalPos, write_Plant, write_SystemParam, write_AnimalForce, write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr, write_AnimalMouthSize);
        ecosystem.write_AnimalParam(write_AnimalParamEnd);

        //write_AnimalX.close();
        //write_AnimalY.close();
        write_AnimalPos.close();
        write_Plant.close();
        write_SystemParam.close();
        write_AnimalParamBegin.close();
        write_AnimalParamEnd.close();
        write_AnimalForce.close();
        write_AnimalNbMoves.close();
        write_AnimalNbOff.close();
        write_AnimalReproThr.close();
        write_AnimalMouthSize.close();
        write_Ecosystem.close();

        savefile.close();
        eco_to_load.close();
        endTime.close();






        return 0;
}
