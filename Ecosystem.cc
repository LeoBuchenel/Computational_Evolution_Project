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
								unsigned long long int Animals(0);
								double meanForce(0.), meanEnergy(0.), meanNumberofMoves(0.), meanOffsprings(0.), meanReprThreshold(0.);
								for (auto const org : animal_list) {
																if (org->isAlive()) {
																								Animals++;
																								meanEnergy+= org->get_energy();
																								meanForce += org->get_force();
																								meanNumberofMoves+=org->get_nb_moves();
																								meanOffsprings+=org->get_nb_offspring();
																								meanReprThreshold+=org->get_rep_threshold();
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


void Ecosystem::food_reproduce()
{
								//changed to have a fixed number of plant
								reproduce(plant_zone, 0.05, grid->size());
}


void Ecosystem::iteration(std::ostream& osX, std::ostream& osY, std::ostream& osP, std::ostream& osS,
							std::ostream& osF, std::ostream& osNM, std::ostream& osNO, std::ostream& osRT){
								this->write(osX, osY, osP, osS, osF, osNM, osNO, osRT); //writes the position of every animal, the plant density per cell and the system parameters
								this->move();
								this->animal_reproduce();
								grid->sortAnimals();
								this->animal_eat();
								this->food_reproduce();
}

void Ecosystem::write(std::ostream& osX, std::ostream& osY, std::ostream& osP, std::ostream& osS, std::ostream& osF, 
						std::ostream& osNM, std::ostream& osNO, std::ostream& osRT){

								//this->write_animalX(osX);
								//osX << std::endl;
								//this->write_animalY(osY);
								//osY << std::endl;
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
	for(auto const& org : animal_list) {
		if(org->isAlive()) {
			os << org->get_force();
			os << " ";
		}
	}
	return os;
}



std::ostream& Ecosystem::write_animalNbMoves(std::ostream& os) const
{
	for(auto const& org : animal_list) {
		if(org->isAlive()) {
			os << org->get_nb_moves();
			os << " ";
		}
	}
	return os;
}




std::ostream& Ecosystem::write_animalNbOff(std::ostream& os) const
{
	for(auto const& org : animal_list) {
		if(org->isAlive()) {
			os << org->get_nb_offspring();
			os << " ";
		}
	}
	return os;
}


std::ostream& Ecosystem::write_animalReproThr(std::ostream& os) const
{
	//Write repro_thresh
	//let's push
	for(auto const& org : animal_list) {
		if(org->isAlive()) {
			os << org->get_rep_threshold();
			os << " ";
		}
	}
	return os;
}

