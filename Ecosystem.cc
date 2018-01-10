#include "Ecosystem.h"

//enum Impact{HalveRate, DoubleRate}; 

Ecosystem::~Ecosystem(){
								for(size_t i(0); i<animal_list.size(); ++i)
								{
																delete animal_list[i];
								}
}


Ecosystem::Ecosystem(Grid* grid, Zone const& animal_zone, Zone const& plant_zone,
																					unsigned int animals, unsigned int plants,
																					double rate)
								: plant_zone(plant_zone), animal_zone(animal_zone), grid(grid), FeedRate(rate)
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

void Ecosystem::animal_reproduce(bool Evolution)
{
								std::size_t n(animal_list.size()); //loop over the existing animals
								for(std::size_t i(0); i<n; ++i) {
																if(animal_list[i]->isAlive()) {
																								std::vector<Animal*> newborns(animal_list[i]->reproduce(Evolution));
																								for(auto const& newborn:newborns) {
																																animal_list.push_back(newborn);
																								}
																}

								}

}

std::ostream& Ecosystem::write_animalX(std::ostream& os) const
{
								// to optimize, turn on the grid
								for(auto const& org : animal_list) {
																if(org->isAlive()) {
																								os << org->getX();
																								os << " ";
																}

								}
								return os;
}
std::ostream& Ecosystem::write_animalY(std::ostream& os) const
{
								// to optimize, turn on the grid
								for(auto const& org : animal_list) {
																if(org->isAlive()) {
																								os << org->getY();
																								os << " ";
																}
								}
								return os;
}

void Ecosystem::write_animal(std::ostream& osX, std::ostream& osY) const
{
								size_t L = grid->size();
								for(size_t i(0); i<L; ++i) {
																for(size_t j(0); j<L; ++j) {
																								if(grid->getCell(i,j)->exist_animal_on_cell()) {
																																osX << i << " ";
																																osY << j << " ";
																								}
																}
								}
}

std::ostream& Ecosystem::write_animalPos(std::ostream& os) const
{
								size_t L(grid->size());
								for(size_t i(0); i<L; ++i) {
																for(size_t j(0); j<L; ++j) {
																								os << grid->getCell(i,j)->nBAnimals_on_cell() << " ";
																}
								}
								return os;
}
std::ostream &Ecosystem::write_systParam(std::ostream &os) const
{
								unsigned long long int Animals(0);
								double meanForce(0.), meanEnergy(0.), meanNumberofMoves(0.), meanOffsprings(0.), meanReprThreshold(0.), meanMouthSize(0.);
								for (auto const org : animal_list) {
																if (org->isAlive()) {
																								Animals++;
																								meanEnergy+= (org->get_energy()*1.0);
																								meanForce += (org->get_force()*1.0);
																								meanNumberofMoves+=(org->get_nb_moves()*1.0);
																								meanOffsprings+=(org->get_nb_offspring()*1.0);
																								meanReprThreshold+=(org->get_rep_threshold()*1.0);
																								meanMouthSize+=(org->get_mouth_size()*1.0);
																}else{
																								std::cout << "There is a dead organism in the animals list" << std::endl;
																}
								}

								os << Animals << " " << grid->getNbFood() << " " << meanForce/ (Animals * 1.)
											<< " " << meanEnergy / (Animals * 1.) << " " << meanNumberofMoves / (Animals * 1.) << " " << meanOffsprings / (Animals * 1.) << " "<< meanReprThreshold/(Animals*1.);

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


void Ecosystem::food_reproduce(std::string feeding)
{
								if(feeding == "exponential") {
									reproduce(plant_zone, FeedRate, grid->getNbFood());// plants reproduce exponentially
								}else{
									if(feeding == "constant") {
										reproduce(plant_zone, FeedRate, (grid->size())*(grid->size()));
									}else{
										std::cout << feeding << std::endl;
										std::cout << "Please type valid feeding"<<std::endl;
									}
								}


}

void Ecosystem::iteration(std::ostream& osXY, std::ostream& osP, std::ostream& osS, std::ostream& osF, std::ostream& osNM, std::ostream& osNO, std::ostream& osRT, std::ostream& osMS, bool DataWrite, bool Evolution, std::string feeding){
								if(DataWrite) {
																this->write(osXY, osP, osS, osF, osNM, osNO, osRT, osMS);
								}                                                          //writes the position of every animal, the plant density per cell and the system parameters
								this->move();
								this->die();
								this->animal_reproduce(Evolution);
								grid->sortAnimals();
								this->animal_eat();
								this->food_reproduce(feeding);
}

void Ecosystem::write(std::ostream& osXY, std::ostream& osP, std::ostream& osS, std::ostream& osF, std::ostream& osNM, std::ostream& osNO, std::ostream& osRT, std::ostream& osMS){
								//this->write_animalX(osX);
								//osX << std::endl;
								//this->write_animalY(osY);
								//osY << std::endl;
								//this->write_animal(osX, osY);
								//osX << std::endl;
								//osY << std::endl;
								this->write_animalPos(osXY);
								osXY << std::endl;
								this->write_Plant(osP);
								osP << std::endl;
								this->write_systParam(osS);
								osS << std::endl;
								this->write_animalForce(osF);
								osF << std::endl;
								this->write_animalNbMoves(osNM);
								osNM << std::endl;
								this->write_animalNbOff(osNO);
								osNO << std::endl;
								this->write_animalReproThr(osRT);
								osRT << std::endl;
								this->write_animalMouthSize(osMS);
								osMS << std::endl;

}

void Ecosystem::animal_eat(){
								for(size_t i(0); i<animal_list.size(); ++i) {
																if(animal_list[i]->isAlive()) {
																								animal_list[i]->eat();
																}
								}
}

std::ostream& Ecosystem::write_animalForce(std::ostream& os) const
{
								for(size_t i(0); i < (*grid).size(); ++i) {
																for(size_t j(0); j < (*grid).size(); ++j) { //works because grid is square
																								double meanForce = 0.;
																								size_t nbAnimals = grid->getCell(i,j)->nBAnimals_on_cell();
																								for(size_t k(0); k < nbAnimals; k++)
																								{
																																Animal* currentAnimal = grid->getCell(i,j)->getAnimal_on_cell(k);
																																meanForce+=1./nbAnimals*currentAnimal->get_force();
																								}

																								os << meanForce << " ";
																}
								}
								return os;
}




std::ostream& Ecosystem::write_animalNbMoves(std::ostream& os) const
{
								for(size_t i(0); i < (*grid).size(); ++i) {
																for(size_t j(0); j < (*grid).size(); ++j) { //works because grid is square
																								double meanNbMoves = 0.;
																								size_t nbAnimals = grid->getCell(i,j)->nBAnimals_on_cell();
																								for(size_t k(0); k < nbAnimals; k++)
																								{
																																Animal* currentAnimal = grid->getCell(i,j)->getAnimal_on_cell(k);
																																meanNbMoves+=1./nbAnimals*currentAnimal->get_nb_moves();
																								}

																								os << meanNbMoves << " ";
																}
								}
								return os;
}




std::ostream& Ecosystem::write_animalNbOff(std::ostream& os) const
{
								for(size_t i(0); i < (*grid).size(); ++i) {
																for(size_t j(0); j < (*grid).size(); ++j) { //works because grid is square
																								double meanNbOff = 0.;
																								size_t nbAnimals = grid->getCell(i,j)->nBAnimals_on_cell();
																								for(size_t k(0); k < nbAnimals; k++)
																								{
																																Animal* currentAnimal = grid->getCell(i,j)->getAnimal_on_cell(k);
																																meanNbOff+=1./nbAnimals*currentAnimal->get_nb_offspring();
																								}

																								os << meanNbOff << " ";
																}
								}
								return os;
}


std::ostream& Ecosystem::write_animalReproThr(std::ostream& os) const
{
								for(size_t i(0); i < (*grid).size(); ++i) {
																for(size_t j(0); j < (*grid).size(); ++j) { //works because grid is square
																								double meanThr = 0.;
																								size_t nbAnimals = grid->getCell(i,j)->nBAnimals_on_cell();
																								for(size_t k(0); k < nbAnimals; k++)
																								{
																																Animal* currentAnimal = grid->getCell(i,j)->getAnimal_on_cell(k);
																																meanThr+=1./nbAnimals*currentAnimal->get_rep_threshold();
																								}

																								os << meanThr << " ";
																}
								}
								return os;
}

std::ostream& Ecosystem::write_animalMouthSize(std::ostream&  os) const {
								for(size_t i(0); i < (*grid).size(); ++i) {
																for(size_t j(0); j < (*grid).size(); ++j) { //works because grid is square
																								double meanMS = 0.;
																								size_t nbAnimals = grid->getCell(i,j)->nBAnimals_on_cell();
																								for(size_t k(0); k < nbAnimals; k++)
																								{
																																Animal* currentAnimal = grid->getCell(i,j)->getAnimal_on_cell(k);
																																meanMS+=1./nbAnimals*currentAnimal->get_mouth_size();
																								}

																								os << meanMS << " ";
																}
								}
								return os;
}



void Ecosystem::die()
{
								if(!animal_list.empty()) {
																bool stop(false);
																size_t first_dead(animal_list.size());

																for(size_t i(0); !stop && i < animal_list.size(); ++i) {
																								if(!(animal_list[i]->isAlive())) {
																																unsigned int first_alive(i);
																																size_t j(i+1);
																																while(first_alive == i && j < animal_list.size()) {
																																								if(animal_list[j]->isAlive()) {
																																																first_alive = j;
																																								}
																																								++j;
																																}

																																Animal* tmp(animal_list[first_alive]);
																																animal_list[first_alive] = animal_list[i];
																																animal_list[i] = tmp;

																																if(first_alive == i) {
																																								stop = true;
																																								first_dead = i;
																																}
																								}
																}


																size_t nbDead(animal_list.size() - first_dead);

																for(size_t i(0); i < nbDead; ++i) {
																								delete animal_list[animal_list.size() -1];
																								animal_list[animal_list.size()-1] = nullptr;
																								animal_list.pop_back();
																}

								}

}

bool Ecosystem::died_out() const {
								return (animal_list.empty())or (grid->getNbFood()==0);
}


void Ecosystem::envImpact(Impact impact)
{
	
	std::cout << "Environmental Impact : ";
	if(impact == HalveRate){
		std::cout << "Halve Feeding rate";
		FeedRate /= 10.0;
	} else if(impact == DoubleRate){
		FeedRate *= 2.0;
		std::cout << "Double Feeding rate";
	}
	
	std::cout << std::endl;
	
	
	
}
