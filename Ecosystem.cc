#include "Ecosystem.h"


Ecosystem::~Ecosystem(){
								for(size_t i(0); i<animal_list.size(); ++i)
								{
																delete animal_list[i];
								}
}


Ecosystem::Ecosystem(Grid* grid, Zone const& animal_zone, Zone const& plant_zone,
																					unsigned int animals, unsigned int plants)
								: plant_zone(plant_zone), animal_zone(animal_zone), grid(grid)
{
								unsigned int animal_zone_size(animal_zone.size());
								unsigned int plant_zone_size(plant_zone.size());
								for (size_t i(0); i < animals; ++i) {
																unsigned int n(std::rand() % animal_zone_size);
																Animal* ptr(new Animal(animal_zone[n]));
																animal_list.push_back(ptr);
								}

								for(size_t i(0); i < plants; ++i) {
																unsigned int n(std::rand() % plant_zone_size);
																plant_zone[n]->addFood();
								}

								for(size_t i(0); i < plant_zone.size(); ++i) {
																plant_zone[i]->set_exist_food(true);
																// gives the cell the right to reproduce food
																// (cell is marked as "food can exist here")
								}


}

void Ecosystem::move()
{
								for(auto const& obj:animal_list) {
																if(obj->isAlive()) {
																								Cell* oldCell(obj->get_Position());
																								oldCell->removeAnimal(obj);
																								std::vector<unsigned int> newPosition(obj->move(grid));
																								Cell* newCell(grid->getCell(newPosition[0], newPosition[1]));
																								newCell->addAnimal(obj);
																								obj->changeCell(newCell);
																}
								}
}

void Ecosystem::animal_reproduce()
{
								std::size_t n(animal_list.size()); //loop over the existing animals
								for(std::size_t i(0); i<n; ++i) {
																if(animal_list[i]->isAlive()) {
																								std::vector<Animal*> newborns(animal_list[i]->reproduce());
																								for(auto const& newborn:newborns) {
																																animal_list.push_back(newborn);
																								}
																}

								}

}

std::ostream& Ecosystem::write_animalX(std::ostream& os) const
{
								for(auto const& org : animal_list) {
																if(org->isAlive()) {
																								os << org->getX();
																} else {
																								os << "NaN";
																}
																os << " ";
								}
								return os;
}
std::ostream& Ecosystem::write_animalY(std::ostream& os) const
{
								for(auto const& org : animal_list) {
																if(org->isAlive()) {
																								os << org->getY();
																} else {
																								os << "NaN";
																}
																os << " ";
								}
								return os;
}


std::ostream &Ecosystem::write_systParam(std::ostream &os) const
{
								unsigned int Animals(0);
								double meanForce(0.), meanEnergy(0.);
								for (auto const org : animal_list) {
																if (org->isAlive()) {
																								Animals++;
																								meanEnergy+= org->get_energy();
																								meanForce += org->get_force();
																}
								}

								os << Animals << " " << grid->getNbFood() << " " << meanForce/ (Animals * 1.)
											<< " " << meanEnergy / (Animals * 1.);

								return os;
}

std::ostream& Ecosystem::write_AnimalParam(std::ostream& os) const
{
								for(auto const& org:animal_list) {
																if(org->isAlive()) {
																								os << org->get_force() << " " << org->get_nb_moves ()<< " "
																											<< org->get_nb_offspring() << " " << org->get_rep_threshold() << std::endl;
																}
								}
								return os;
}

std::ostream& Ecosystem::write_Plant(std::ostream& os) const
{
								return grid->write_Plant(os);
}


void Ecosystem::food_reproduce()
{
								reproduce(plant_zone, 0.2, grid->getNbFood());
}


void Ecosystem::iteration(std::ostream& osX, std::ostream& osY, std::ostream& osP, std::ostream& osS){
								this->write(osX, osY, osP, osS); //writes the position of every animal, the plant density per cell and the system parameters
								this->move();
								this->die();
								this->animal_reproduce();
								grid->sortAnimals();
								this->animal_eat();
								this->food_reproduce();
}

void Ecosystem::write(std::ostream& osX, std::ostream& osY, std::ostream& osP, std::ostream& osS){
								this->write_animalX(osX);
								osX << std::endl;
								this->write_animalY(osY);
								osY << std::endl;
								this->write_Plant(osP);
								osP << std::endl;
								this->write_systParam(osS);
								osS << std::endl;
}


void Ecosystem::animal_eat(){
								for(size_t i(0); i<animal_list.size(); ++i) {
																if(animal_list[i]->isAlive()) {
																								animal_list[i]->eat();
																}
								}
}

void Ecosystem::die(){
								size_t L = animal_list.size();
								size_t first_dead = L;
								for(size_t i(0); i < L; ++i) {
																if(!(animal_list[i]->isAlive())) {
																								Animal* nextAlive = animal_list[i];
																								for(size_t j(i+1); j < L; ++j) {
																																if(animal_list[j]->isAlive()) {
																																								nextAlive = animal_list[j];
																																								animal_list[j] = animal_list[i];
																																								animal_list[i] = nextAlive;
																																								j = L;
																																}
																								}
																								//next Alive animal is found
																								if(nextAlive==animal_list[i]) { // All animals after i are dead
																																first_dead = i;
																																i = L;
																								}
																}
								}
								//loop to delete every dead animal§
								for(size_t i(L-1); i>=first_dead && !animal_list.empty(); --i) {
																delete animal_list[i];
																animal_list.pop_back();
								}


}
