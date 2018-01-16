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

void open_ostreams(vector<ofstream*>, string, string, string);
void close_ostreams(vector<ofstream*>, string);

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
        bool save = configFile.get<bool>("save");
        unsigned int save_time = configFile.get<unsigned int>("save at t");
        double FeedRate = configFile.get<double>("feeding_rate");
        double shock_parameter = configFile.get<double>("shock parameter");
        unsigned int shock_time = configFile.get<unsigned int>("shock at t");
        double mutation_rate = configFile.get<double>("mutation_rate");
        string writeCharac = configFile.get<string>("write characteristics");

        unsigned int tfin = configFile.get<unsigned int>("tfin");
        unsigned int nb_plants = configFile.get<unsigned int>("plants");
        unsigned int nb_animals = configFile.get<unsigned int>("animals");
        bool DataWrite = configFile.get<bool>("write data");
        bool Evolution = configFile.get<bool>("evolution");
        bool shock = configFile.get<bool>("shock");

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
                ecosystem.add_random(nb_animals, nb_plants, mutation_rate);
        }


        ofstream write_AnimalPos, write_Plant, write_SystemParam,
                 write_AnimalParamBegin, write_AnimalParamEnd, write_AnimalForce,
                 write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr,
                 write_AnimalMouthSize,

                 write_CellForce, write_CellNbMoves,
                 write_CellNbOff, write_CellReproThr, write_CellMouthSize,

                 endTime, savefile;

        vector<ofstream*> os_tab {&write_AnimalPos, &write_Plant, &write_SystemParam,
                                  &write_AnimalForce, &write_AnimalNbMoves,
                                  &write_AnimalNbOff, &write_AnimalReproThr, &write_AnimalMouthSize,
                                  &write_CellForce, &write_CellNbMoves,
                                  &write_CellNbOff, &write_CellReproThr, &write_CellMouthSize};

        write_AnimalPos.open(path+"animal_pos_"+extension+".out");
        write_Plant.open(path+"plant_"+extension+".out");
        write_SystemParam.open(path+"system_param_"+extension+".out");
        endTime.open(path+"tfin.out");

        open_ostreams(os_tab, extension, writeCharac, path);

        for(size_t t(0); t<tfin; ++t) {

                //saves ecosystem
                if(t == save_time && save) {

                        savefile.open(savepath+"ecosystemSave_t="+to_string(save_time)+ ".out");
                        vector<string> strings = {animalForm, plantForm};
                        vector<unsigned int> numbers={AnimalParam1, AnimalParam2,
                                                      AnimalParam3, AnimalParam4,
                                                      PlantParam1, PlantParam2,
                                                      PlantParam3, PlantParam4, L};

                        ecosystem.save_ecosystem(strings, numbers, savefile, t);
                        savefile.close();

                }

                if(t == shock_time && shock) {
                        ecosystem.envImpact(MultiplyRate);
                }

                ecosystem.iteration(os_tab, DataWrite, Evolution, food_reproduce, writeCharac);

                if(ecosystem.died_out()) {
                        std::cout << "Ecosystem died out at t = " << t+1 << std::endl;
                        endTime << t+1;
                        return 1;
                }
        }
        endTime << tfin;

        ecosystem.write(os_tab, writeCharac);

        write_AnimalPos.close();
        write_Plant.close();
        write_SystemParam.close();

        close_ostreams(os_tab, writeCharac);

        eco_to_load.close();
        endTime.close();

        return 0;
}


void open_ostreams(vector<ofstream*> os_tab, string extension, string writeCharac, string path)
{
        switch(writeCharac[0]) {
        case 'a': os_tab[3]->open(path+"animal_force_"+extension+".out"); break;
        case 'c': os_tab[8]->open(path+"cell_force_"+extension+".out"); break;
        case 'b': os_tab[3]->open(path+"animal_force_"+extension+".out");
                os_tab[8]->open(path+"cell_force_"+extension+".out"); break;
        default: break;
        }

        switch(writeCharac[1]) {
        case 'a': os_tab[4]->open(path+"animal_nb_moves_"+extension+".out"); break;
        case 'c': os_tab[9]->open(path+"cell_nb_moves_"+extension+".out"); break;
        case 'b': os_tab[4]->open(path+"animal_nb_moves_"+extension+".out");
                os_tab[9]->open(path+"cell_nb_moves_"+extension+".out"); break;
        default: break;
        }

        switch(writeCharac[2]) {
        case 'a': os_tab[5]->open(path+"animal_nb_offspring_"+extension+".out"); break;
        case 'c': os_tab[10]->open(path+"cell_nb_offspring_"+extension+".out"); break;
        case 'b': os_tab[5]->open(path+"animal_nb_offspring_"+extension+".out");
                os_tab[10]->open(path+"cell_nb_offspring_"+extension+".out"); break;
        default: break;
        }

        switch(writeCharac[3]) {
        case 'a': os_tab[6]->open(path+"animal_repro_threshold_"+extension+".out"); break;
        case 'c': os_tab[11]->open(path+"cell_repro_threshold_"+extension+".out"); break;
        case 'b': os_tab[6]->open(path+"animal_repro_threshold_"+extension+".out");
                os_tab[11]->open(path+"cell_repro_threshold_"+extension+".out"); break;
        default: break;
        }

        switch(writeCharac[4]) {
        case 'a': os_tab[7]->open(path+"animal_mouth_size_"+extension+".out"); break;
        case 'c': os_tab[12]->open(path+"cell_mouth_size_"+extension+".out"); break;
        case 'b': os_tab[7]->open(path+"animal_mouth_size_"+extension+".out");
                os_tab[12]->open(path+"cell_mouth_size_"+extension+".out"); break;
        default: break;
        }

}


void close_ostreams(vector<ofstream*> os_tab, string writeCharac)
{
        switch(writeCharac[0]) {
        case 'a': os_tab[3]->close(); break;
        case 'c': os_tab[8]->close(); break;
        case 'b': os_tab[3]->close();
                os_tab[8]->close(); break;
        default: break;
        }

        switch(writeCharac[1]) {
        case 'a': os_tab[4]->close(); break;
        case 'c': os_tab[9]->close(); break;
        case 'b': os_tab[4]->close();
                os_tab[9]->close(); break;
        default: break;
        }


        switch(writeCharac[2]) {
        case 'a': os_tab[5]->close(); break;
        case 'c': os_tab[10]->close(); break;
        case 'b': os_tab[5]->close();
                os_tab[10]->close(); break;
        default: break;
        }

        switch(writeCharac[3]) {
        case 'a': os_tab[6]->close(); break;
        case 'c': os_tab[11]->close(); break;
        case 'b': os_tab[6]->close();
                os_tab[11]->close(); break;
        default: break;
        }

        switch(writeCharac[4]) {
        case 'a': os_tab[7]->close(); break;
        case 'c': os_tab[12]->close(); break;
        case 'b': os_tab[7]->close();
                os_tab[12]->close(); break;
        default: break;
        }
}
