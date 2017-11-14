#include "GeneticData.h"
#include <iostream>

GeneticData::GeneticData(){

        double x = (std::rand() % 100) + 1;
        force = x;
        unsigned int a = (std::rand() % 5) + 1;
        nb_moves = a;
        unsigned int y = (std::rand() % 5) + 1;
        nb_offspring = y;
        double b = (std::rand() % 100) + 1;
        repr_threshold = b;

}

void GeneticData::mutate(){
        double p1 = std::rand()/(RAND_MAX*1.0);
        if(p1 < 0.1) {
                unsigned int characteristic = std::rand() % 4 + 1;
                int change = std::rand() % 2 - 1;

                switch (characteristic) {
                case 1: if(force>1) {
                                force+=change;
                                std::cout << "force mutated" << std::endl;
                } break;
                case 2: if(nb_moves>1) {
                                nb_moves+=change;
                                std::cout << "Number of moves mutated" << std::endl;
                } break;
                case 3: if(nb_offspring>1) {
                                nb_offspring+=change;
                                std::cout << "Number of offsprings mutated" << std::endl;
                } break;
                case 4: if(repr_threshold>1) {
                                repr_threshold+=change;
                                std::cout << "Reproduction threshold mutated" << std::endl;
                } break;

                default: break;
                }
        }


}

double GeneticData::get_force() const {
        return force;
}

double GeneticData::get_rep_threshold() const {
        return repr_threshold;
}

unsigned int GeneticData::get_nb_offspring() const {
        return nb_offspring;
}

unsigned int GeneticData::get_nb_moves() const {
        return nb_moves;
}
