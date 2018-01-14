#include "GeneticData.h"
#include <iostream>

GeneticData::GeneticData(){
/*
        double x = (std::rand() % 100) + 1;
        force = x;
        unsigned int a = (std::rand() % 5) + 1;
        nb_moves = a;
        unsigned int y = (std::rand() % 5) + 1;
        nb_offspring = y;
        double b = (std::rand() % 100) + 1;
        repr_threshold = b;
 */
        force =  50.;
        nb_moves = 2;
        nb_offspring = 2;
        repr_threshold = 50.;
        mouth_size = 1;

}

void GeneticData::mutate(){
        double p1 = std::rand()/(RAND_MAX*1.0);
        if(p1 < 0.1) {
                unsigned int characteristic = std::rand() % 5 + 1;
                int change = std::rand() % 2;
                if(change==0) {
                        change =-1;
                }

                switch (characteristic) {
                case 1: if(force>1 || change > -1) {
                                force+=5*change;
                                //std::cout << "force mutated" << std::endl;
                }
                        break;
                case 2: if(nb_moves>1 || change > -1) {
                                //std::cout << "Moves mutated from " << nb_moves;
                                nb_moves+=change;
                                //std::cout << "Number of moves mutated" << std::endl;
                } break;
                case 3: if(nb_offspring>1 || change > -1) {
                                nb_offspring+=change;
                                //std::cout << "Number of offsprings mutated" << std::endl;
                } break;
                case 4: if(repr_threshold>1 || change > -1) {
                                repr_threshold+=5*change;
                                //std::cout << "Reproduction threshold mutated" << std::endl;
                } break;

                case 5: if(mouth_size > 1 || change > -1) {
                                mouth_size += change;
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

unsigned int GeneticData::get_mouth_size() const {
        return mouth_size;
}

std::ostream& GeneticData::write_genetic_data(std::ostream & os) const
{
        os << force << " ";
        os << nb_offspring << " ";
        os << repr_threshold << " ";
        os << nb_moves << " ";
        os << mouth_size;

        return os;

}
