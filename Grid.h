#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>
#include <string>

typedef std::vector<Cell*> Zone;

class Grid
{
private:
std::vector<std::vector<Cell*> > grid;
public:
Grid(unsigned int L);
~Grid();
Cell* getCell(unsigned int, unsigned int) const;
std::size_t size() const;
void food_reproduce(size_t) const;
Zone getZone(std::string, unsigned int, unsigned int, unsigned int, unsigned int = 0) const;

void sortAnimals() const;
unsigned int getNbFood() const;

std::ostream& write_Plant(std::ostream&) const;
};
#endif //GRID_H


void reproduce(const Zone&, double, unsigned int);
