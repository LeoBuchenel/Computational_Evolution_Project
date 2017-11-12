#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H
#include <iostream>
#include "Grid.h"
#include "Animal.h"

class Ecosystem
{
private:
Zone plant_zone;
Zone animal_zone;
Grid* grid;
std::vector<Animal*> animal_list;
public:
Ecosystem(Grid*, Zone const&, Zone const&,unsigned int, unsigned int);
~Ecosystem();
void move();
void animal_reproduce();
void food_reproduce();
void die(); //kills all dead animals

std::ostream& write_animalX(std::ostream&) const;
std::ostream& write_animalY(std::ostream&) const;
std::ostream& write_systParam(std::ostream&) const;
std::ostream& write_AnimalParam(std::ostream&) const;
std::ostream& write_Plant(std::ostream&) const;

void write(std::ostream&, std::ostream&, std::ostream&, std::ostream&);


void animal_eat();



void iteration(std::ostream&, std::ostream&, std::ostream&, std::ostream&);
};

#endif //ECOSYSTEM_H

