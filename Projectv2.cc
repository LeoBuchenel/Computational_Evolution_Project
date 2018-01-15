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

void open_ostreams(vector<ofstream*>, string, string);
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
        double FeedRate = configFile.get<double>("feeding rate");
        double shock_parameter = configFile.get<double>("shock parameter");
        unsigned int shock_time = configFile.get<unsigned int>("shock at t");
        double MutationRate = configFile.get<double>("Mutation rate");
        string writeCharac =  configFile.get<string>("write characteristics");
        
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
                ecosystem.add_random(nb_animals, nb_plants, MutationRate);
        }


        //ofstream write_AnimalParamBegin;
       //ofstream write_AnimalParamEnd; 
       //write_AnimalParamBegin.open("animal_param_begin_"+extension+".out");
       //write_AnimalParamEnd.open("animal_param_end_"+extension+".out");
        
       ofstream write_AnimalPos;
       ofstream write_Plant;
       ofstream write_SystemParam;
       ofstream write_AnimalForce, write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr, write_AnimalMouthSize;
       ofstream write_CellForce, write_CellNbMoves, write_CellNbOff, write_CellReproThr, write_CellMouthSize;
       ofstream write_Ecosystem, savefile;
       ofstream endTime;
       
        vector<ofstream*> os_tab{&write_AnimalPos, &write_Plant, &write_SystemParam, 
								&write_AnimalForce, &write_AnimalNbMoves,
								&write_AnimalNbOff, &write_AnimalReproThr, &write_AnimalMouthSize, 
								&write_CellForce, &write_CellNbMoves,
								&write_CellNbOff, &write_CellReproThr, &write_CellMouthSize}; 
		
		write_AnimalPos.open("animal_pos_"+extension+".out");
        write_Plant.open("plant_"+extension+".out");
        write_SystemParam.open("system_param_"+extension+".out");
        endTime.open("tfin.out");
                   
        open_ostreams(os_tab, extension, writeCharac);           	
        //ecosystem.write_AnimalParam(write_AnimalParamBegin);
        
        
        for(size_t t(0); t<tfin; ++t) {

                if(t == save_time && save) {
                        vector<string> strings = {animalForm, plantForm};

                        vector<unsigned int> numbers={AnimalParam1, AnimalParam2,
                                                      AnimalParam3, AnimalParam4,
                                                      PlantParam1, PlantParam2,
                                                      PlantParam3, PlantParam4, L};
                        ecosystem.save_ecosystem(strings, numbers, savefile, t);
                }

                if(t == shock_time) {
                        ecosystem.envImpact(MultiplyRate);
                }

                // if(t == 600){
                //ecosystem.envImpact(DoubleRate);
                //}

               ecosystem.iteration(os_tab, DataWrite, Evolution, food_reproduce, writeCharac);
               
                if(ecosystem.died_out()) {
                        std::cout << "Ecosystem died out at t = " << t+1 << std::endl;
                        endTime << t+1;
                        return 1;
                }
                ecosystem.write_ecosystem_data(write_Ecosystem);
        }
        endTime << tfin;
        ecosystem.write(os_tab, writeCharac);
        
        //ecosystem.write_AnimalParam(write_AnimalParamEnd);

        //write_AnimalX.close();
        //write_AnimalY.close();
        write_AnimalPos.close();
        write_Plant.close();
        write_SystemParam.close();
        
        close_ostreams(os_tab, writeCharac);     
        
        /*write_AnimalParamBegin.close();
        write_AnimalParamEnd.close();
        write_AnimalForce.close();
        write_AnimalNbMoves.close();
        write_AnimalNbOff.close();
        write_AnimalReproThr.close();
        write_AnimalMouthSize.close();
        write_Ecosystem.close();
		*/
        savefile.close();
        eco_to_load.close();
        endTime.close();






        return 0;
}



void open_ostreams(vector<ofstream*> os_tab, string extension, string writeCharac)
{
	switch(writeCharac[0]){
		case 'a' : os_tab[3] -> open("animal_force_"+extension+".out"); break;
        case 'c' : os_tab[8] -> open("cell_force_"+extension+".out"); break;
        case 'b' : os_tab[3] -> open("animal_force_"+extension+".out"); 
				   os_tab[8] -> open("cell_force_"+extension+".out"); break;
		default : break;
	}
	
	switch(writeCharac[1]){
		case 'a' : os_tab[4] -> open("animal_nb_moves_"+extension+".out"); break;
        case 'c' : os_tab[9] -> open("cell_nb_moves_"+extension+".out"); break;
        case 'b' : os_tab[4] -> open("animal_nb_moves_"+extension+".out"); 
				   os_tab[9] -> open("cell_nb_moves_"+extension+".out"); break;
		default : break;
	}
	
	switch(writeCharac[2]){
		case 'a' : os_tab[5] -> open("animal_nb_offspring_"+extension+".out"); break;
        case 'c' : os_tab[10] -> open("cell_nb_offspring_"+extension+".out"); break;
        case 'b' : os_tab[5] -> open("animal_nb_offspring_"+extension+".out"); 
				   os_tab[10] -> open("cell_nb_offspring_"+extension+".out"); break;
		default : break;
	}
	
	switch(writeCharac[3]){
		case 'a' : os_tab[6] -> open("animal_repro_threshold_"+extension+".out"); break;
        case 'c' : os_tab[11] -> open("cell_repro_threshold_"+extension+".out"); break;
        case 'b' : os_tab[6] -> open("animal_repro_threshold_"+extension+".out"); 
				   os_tab[11] -> open("cell_repro_threshold_"+extension+".out"); break;
		default : break;
	}
	
	switch(writeCharac[4]){
		case 'a' : os_tab[7] -> open("animal_mouth_size_"+extension+".out"); break;
        case 'c' : os_tab[12] -> open("cell_mouth_size_"+extension+".out"); break;
        case 'b' : os_tab[7] -> open("animal_mouth_size_"+extension+".out"); 
				   os_tab[12] -> open("cell_mouth_size_"+extension+".out"); break;
		default : break;
	}
	
}


void close_ostreams(vector<ofstream*> os_tab, string writeCharac)
{
	switch(writeCharac[0]){
		case 'a' : os_tab[3] -> close(); break;
        case 'c' : os_tab[8] -> close(); break;
        case 'b' : os_tab[3] -> close(); 
				   os_tab[8] -> close(); break;
		default : break;
	}
	
	switch(writeCharac[1]){
		case 'a' : os_tab[4] -> close(); break;
        case 'c' : os_tab[9] -> close(); break;
        case 'b' : os_tab[4] -> close(); 
				   os_tab[9] -> close(); break;
		default : break;
	}
	
	
	switch(writeCharac[2]){
		case 'a' : os_tab[5] -> close(); break;
        case 'c' : os_tab[10] -> close(); break;
        case 'b' : os_tab[5] -> close(); 
				   os_tab[10] -> close(); break;
		default : break;
	}
	
	switch(writeCharac[3]){
		case 'a' : os_tab[6] -> close(); break;
        case 'c' : os_tab[11] -> close(); break;
        case 'b' : os_tab[6] -> close(); 
				   os_tab[11] -> close(); break;
		default : break;
	}
	
	switch(writeCharac[4]){
		case 'a' : os_tab[7] -> close(); break;
        case 'c' : os_tab[12] -> close(); break;
        case 'b' : os_tab[7] -> close(); 
				   os_tab[12] -> close(); break;
		default : break;
	}
}
