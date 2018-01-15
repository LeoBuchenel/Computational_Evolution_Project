#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include "Grid.h"
#include "Animal.h"


enum Impact {HalveRate, DoubleRate,MultiplyRate};

class Ecosystem
{
private:
Zone plant_zone;
Zone animal_zone;
Grid* grid;
std::vector<Animal*> animal_list;
double FeedRate;
double shock_parameter;

public:

//last two doubles in the constructors stand for rate and shock

//old version, if we want to inialize plants and animals randomly directly, better use next one and add_random function
Ecosystem(Grid*, Zone const&, Zone const&,unsigned int, unsigned int, double, double);
Ecosystem(Grid*, Zone const&, Zone const&,double, double);
~Ecosystem();
void move();

//adds randomly a given number of plants and animals to the grid
void add_random(unsigned int, unsigned int);

//adds animals and plants as given in a external file
std::ifstream& add_from_file(std::ifstream&);

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
//writes the distribution of plants and animals on the grid with their genetic data
std::ostream& write_ecosystem_data(std::ostream & ) const;

//saves the ecosystem so it can be reloaded later
std::ostream& save_ecosystem(std::vector<std::string>, std::vector<unsigned int>, std::ostream &, unsigned int) const;

void write(std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&);


void animal_eat();
void envImpact(Impact impact);

void iteration(std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&, bool, bool, std::string);
};

#endif //ECOSYSTEM_H
