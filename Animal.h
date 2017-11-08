#ifndef PROJ_ANIMAL_H
#define PROJ_ANIMAL_H

//That's a comment

#include "GeneticData.h"
#include "Cell.h"
#include <vector>

class Grid;

class Animal {
public:

Animal(Cell*);                        // initializes animal with random genetic data
Animal(Cell*, GeneticData, double);   // constructor with position, genetic_data and energy
void eat();
std::vector<Animal*> reproduce();
//void update_energy();
std::vector<unsigned int> move(Grid*);
void changeCell(Cell*);

unsigned int getX() const;
unsigned int getY() const;


Cell* get_Position() const;

bool isAlive() const;
double get_force() const;
double get_rep_threshold() const;
unsigned int get_nb_moves() const;
unsigned int get_nb_offspring() const;
double get_energy() const;

protected:
Cell* position;
GeneticData genetic_data;   //maybe change to a pointer to see who belongs to same GeneticData
double energy;

};



#endif //PROJ_ANIMAL_H
