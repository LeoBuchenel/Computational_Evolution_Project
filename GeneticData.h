#ifndef PROJ_GENETICDATA_H
#define PROJ_GENETICDATA_H



class GeneticData {
public:
GeneticData();   //constructs genetic data randomly
double get_force() const;
double get_rep_threshold() const;
unsigned int get_nb_offspring() const;
unsigned int get_nb_moves() const;
unsigned int get_mouth_size() const;
void mutate();



protected:
double force;
unsigned int nb_offspring;
double repr_threshold;
unsigned int nb_moves;
unsigned int mouth_size; //maximum food eaten by animal
};

#endif //PROJ_GENETICDATA_H
