#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H
#include <iostream>
#include <string>
#include "Grid.h"
#include "Animal.h"


enum Impact{HalveRate, DoubleRate}; 

class Ecosystem
{
private:
Zone plant_zone;
Zone animal_zone;
Grid* grid;
std::vector<Animal*> animal_list;
double FeedRate;

public:
Ecosystem(Grid*, Zone const&, Zone const&,unsigned int, unsigned int, double, double);
~Ecosystem();
void move();
void animal_reproduce(bool);
void food_reproduce(std::string);
bool died_out() const;
void die();

std::ostream& write_animalX(std::ostream&) const;
std::ostream& write_animalY(std::ostream&) const;
std::ostream& write_animalPos(std::ostream&) const;

void write_animal(std::ostream&, std::ostream&) const;

std::ostream& write_systParam(std::ostream&) const;
std::ostream& write_AnimalParam(std::ostream&) const;
std::ostream& write_Plant(std::ostream&) const;
std::ostream& write_animalForce(std::ostream&) const;
std::ostream& write_animalNbMoves(std::ostream&) const;
std::ostream& write_animalNbOff(std::ostream&) const;
std::ostream& write_animalReproThr(std::ostream&) const;
std::ostream& write_animalMouthSize(std::ostream&) const;

void write(std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&);


void animal_eat();
void envImpact(Impact impact);

void iteration(std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, bool, bool, std::string);
};

#endif //ECOSYSTEM_H
