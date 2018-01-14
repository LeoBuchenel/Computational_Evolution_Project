#ifndef PROJ_ANIMAL_H
#define PROJ_ANIMAL_H

//That's a comment

#include "GeneticData.h"
#include "Cell.h"
#include <vector>
#include <iostream>

class Grid;

class Animal {
public:

Animal(Cell*);                        // initializes animal with random genetic data
Animal(Cell*, GeneticData, double);   // constructor with position, genetic_data and energy
void eat();
std::vector<Animal*> reproduce(bool);
~Animal();
//void update_energy();
std::vector<unsigned int> move(Grid*);
void changeCell(Cell*);

void evolve();

unsigned int getX() const;
unsigned int getY() const;


Cell* get_Position() const;

bool isAlive() const;
double get_force() const;
double get_rep_threshold() const;
unsigned int get_nb_moves() const;
unsigned int get_nb_offspring() const;
unsigned int get_mouth_size() const;
double get_energy() const;

std::ostream& write_animal_data(std::ostream&) const; //writes animal's genetic data and energy

protected:
Cell* position;
GeneticData genetic_data;   //maybe change to a pointer to see who belongs to same GeneticData
double energy;

};



#endif //PROJ_ANIMAL_H
