#ifndef CELL_H
#define CELL_H

#include <vector>

class Animal;

class Cell
{
public:
Cell(unsigned int, unsigned int);
bool exist_food_on_cell() const;
void initialiseFood(unsigned int, unsigned int);
void addAnimal(std::vector<Animal*> const&);
void addAnimal(Animal* const&); //places the Animal on said cell
void removeAnimal(Animal* const);
void food_reproduce(double);
void addFood(unsigned int food = 1);
unsigned int decreaseFood(unsigned int = 1);
//Return number of food eaten by the animal(energy depend on nbEaten)
void sortAnimals();

unsigned int getX() const {
								return x;
}
unsigned int getY() const {
								return y;
}
unsigned int getNbFood() const {
								return nb_food;
}

void set_exist_food(bool);

private:
unsigned int x;
unsigned int y;
std::vector<Animal*> animal_list;
unsigned int food_density;
unsigned int nb_food;
bool exist_food;

};

#endif //CELL_H
