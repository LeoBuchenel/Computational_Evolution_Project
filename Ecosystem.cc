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
								int Taille = grid->size();
								for(auto const& obj:animal_list) {
																if(obj->isAlive()) {
																								Cell* oldCell(obj->get_Position());
																								oldCell->removeAnimal(obj);
																								std::vector<int> newPosition(obj->move(grid));

																								int X = newPosition[0];
																								int Y = newPosition[1];

																								if(X >= Taille) X -= Taille;
																								if(X < 0) X+=Taille;
																								if(Y >=Taille) Y -=Taille;
																								if(Y <0) Y+=Taille;


																								unsigned int X1 = abs(X);
																								unsigned int Y1 = abs(Y);


																								Cell* newCell(grid->getCell(X1, Y1));


																								//std::cout << "New Position [0] =" << newPosition[0] << " New Position [1] =" << newPosition[1] << std::endl;

																								//std::cout << "Tout va bien 2" << std::endl;
																								newCell->addAnimal(obj);
																								obj->changeCell(newCell);
																}
								}
}

void Ecosystem::animal_reproduce()
{
								std::size_t n(animal_list.size());
								for(std::size_t i(0); i<n; ++i ) {
																//if(obj == nullptr) std::cout << "NULLPTR" << std::endl;
																if(animal_list[i]->isAlive()) {
																								//std::cout << "start of loop" << std::endl;
																								std::vector<Animal*> newborns(animal_list[i]->reproduce());
																								//std::cout << "Number of newborns = " << newborns.size() << std::endl;
																								for(auto const& newborn:newborns) {
																																//std::cout << newborn << std::endl;
																																animal_list.push_back(newborn);
																																//								std::cout << "Animal sucessfully added"<< std::endl;
																								}
																								//std::cout << "end of loop" << std::endl;
																}

								}
								//std::cout << "out of animal_reproduce()"<< std::endl;

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
								reproduce(plant_zone, 0.05, grid->getNbFood());
}


void Ecosystem::iteration(std::ostream& osX, std::ostream& osY, std::ostream& osP, std::ostream& osS){
								this->write(osX, osY, osP, osS); //writes the position of every animal, the plant density per cell and the system parameters
								this->move();
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
