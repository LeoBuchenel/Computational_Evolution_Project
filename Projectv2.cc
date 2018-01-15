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

        unsigned int L = configFile.get<unsigned int>("L");
        unsigned int nb_plants = configFile.get<unsigned int>("plants");
        unsigned int nb_animals = configFile.get<unsigned int>("animals");
        unsigned int tfin = configFile.get<unsigned int>("tfin");
        double FeedRate = configFile.get<double>("Feeding rate");
        double MutationRate = configFile.get<double>("Mutation rate");
        string writeCharac =  configFile.get<string>("write characteristics");
		
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

        bool DataWrite = configFile.get<bool>("write data");
        bool Evolution = configFile.get<bool>("evolution");
        string food_reproduce = configFile.get<string>("feeding");

        string extension = configFile.get<string>("output");

        srand(time(NULL) +clock()); // seeds the random number generator
        //(added clock() in the case of multiple simulations at the same second)

        Grid grid(L);

        Zone animalZone = grid.getZone(animalForm, AnimalParam1, AnimalParam2, AnimalParam3, AnimalParam4);
        Zone plantZone = grid.getZone(plantForm, PlantParam1, PlantParam2, PlantParam3, PlantParam4);


        Ecosystem ecosystem(&grid, animalZone, plantZone, nb_animals, nb_plants, FeedRate, MutationRate);
		
	   //ofstream write_AnimalParamBegin;
       //ofstream write_AnimalParamEnd; 
       //write_AnimalParamBegin.open("animal_param_begin_"+extension+".out");
       //write_AnimalParamEnd.open("animal_param_end_"+extension+".out");
        
       ofstream write_AnimalPos;
       ofstream write_Plant;
       ofstream write_SystemParam;
       ofstream write_AnimalForce, write_AnimalNbMoves, write_AnimalNbOff, write_AnimalReproThr, write_AnimalMouthSize;
       ofstream write_CellForce, write_CellNbMoves, write_CellNbOff, write_CellReproThr, write_CellMouthSize;
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
                
                //if(t == 500){
					//ecosystem.envImpact(HalveRate);
				//}
				
				// if(t == 600){
					//ecosystem.envImpact(DoubleRate);
				//}
                
                ecosystem.iteration(os_tab, DataWrite, Evolution, food_reproduce, writeCharac);
                if(ecosystem.died_out()) {
                        std::cout << "Ecosystem died out at t = " << t+1 << std::endl;
                        endTime << t+1;
                        return 1;
                }
        }
        endTime << tfin;        
        ecosystem.write(os_tab, writeCharac);
        
        //ecosystem.write_AnimalParam(write_AnimalParamEnd);

        //write_AnimalX.close();
        //write_AnimalY.close();
        //write_AnimalParamBegin.close();
        //write_AnimalParamEnd.close();
        
        write_AnimalPos.close();
        write_Plant.close();
        write_SystemParam.close();
        
        
        close_ostreams(os_tab, writeCharac);       
        //write_AnimalForce.close();
        //write_AnimalNbMoves.close();
        //write_AnimalNbOff.close();
        //write_AnimalReproThr.close();
		//write_AnimalMouthSize.close();
		
		//write_CellForce.close();
        //write_CellNbMoves.close();
        //write_CellNbOff.close();
        //write_CellReproThr.close();
		//write_CellMouthSize.close();

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
