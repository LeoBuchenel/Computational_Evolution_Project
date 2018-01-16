#ifndef PROJ_GENETICDATA_H
#define PROJ_GENETICDATA_H


#include <iostream>

class GeneticData {
public:
GeneticData(double = 0.1);   //constructs generic genetic data
GeneticData(double, double, unsigned int, double, unsigned int, unsigned int);
double get_force() const;
double get_rep_threshold() const;
unsigned int get_nb_offspring() const;
unsigned int get_nb_moves() const;
unsigned int get_mouth_size() const;
void mutate();

//writes the genetic data on an external file (all attributes below IN THAT ORDER)
std::ostream& write_genetic_data(std::ostream &) const;



protected:
double mutation_rate;
double force;
unsigned int nb_offspring;
double repr_threshold;
unsigned int nb_moves;
unsigned int mouth_size; //maximum food eaten by animal
};

#endif //PROJ_GENETICDATA_H
