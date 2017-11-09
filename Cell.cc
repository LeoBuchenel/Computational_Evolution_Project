#include "Cell.h"
#include "Animal.h"
#include <vector>
#include <iostream>


Cell::Cell(unsigned int x_, unsigned int y_)
								: x(x_), y(y_), food_density(1), nb_food(0), exist_food(false)
{
}

void Cell::initialiseFood(unsigned int density, unsigned int nb)
{
								food_density = density;
								nb_food = nb;
}

void Cell::addAnimal(std::vector<Animal*> const& objs)
{
								for(auto const& obj:objs) {
																if(obj != nullptr) {
																								animal_list.push_back(obj);
																}
								}
}

void Cell::addAnimal(Animal* const& obj)
{
								if(obj != nullptr) {
																animal_list.push_back(obj);
								}
}

void Cell::removeAnimal(Animal* const obj)
{
								if(obj != nullptr) {
																std::size_t n(animal_list.size());
																for(std::size_t i(0); i < n; ++i) {
																								if(animal_list[i] == obj) {
																																animal_list[i] = animal_list[n-1];
																																animal_list.pop_back();
																																return;
																								}
																}
								}
}

void Cell::food_reproduce(double proba)
{
								if(exist_food) {
																// old code
																double prob = (std::rand()/(RAND_MAX*1.));
																if(prob < proba) {
																								addFood(food_density);
																}
																//
																/*test code
																   int a = rate*nb_food;
																   std::cout << a << std::endl;
																   addFood(a);
																 */
								}

}
//std::cout << "Tout va bien " << std::endl;



void Cell::addFood(unsigned int food)
{
								nb_food +=food;
}

unsigned int Cell::decreaseFood(unsigned int a)
{
								unsigned int nbEaten(0);

								if(nb_food >= a) {
																nb_food -=a;
																nbEaten = a;
								} else {
																nbEaten = nb_food;
																nb_food = 0;
								}
								return nbEaten;
}

void Cell::sortAnimals()
{
								std::size_t n(animal_list.size());
								if(n>1) {
																for(std::size_t i(0); i < n-1; ++i) {
																								Animal* strongest(animal_list[i]);
																								unsigned int maxIndex(i);
																								double maxForce(strongest->get_force());
																								for(std::size_t j(i+1); j < n; ++j) {
																																if(maxForce < animal_list[j]->get_force()) {
																																								strongest = animal_list[j];
																																								maxForce = animal_list[j]->get_force();
																																								maxIndex = j;
																																}
																								}
																								animal_list[maxIndex] = animal_list[i];
																								animal_list[i] = strongest;
																}
								}
}


void Cell::set_exist_food(bool new_value){
								exist_food = new_value;
}

bool Cell::exist_food_on_cell() const {
								return (nb_food!=0);
}
