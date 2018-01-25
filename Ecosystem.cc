#include "Ecosystem.h"

//enum Impact{HalveRate, DoubleRate};

unsigned int numberReproduced(0);
unsigned int numberDied(0);
 
Ecosystem::~Ecosystem(){
								for(size_t i(0); i<animal_list.size(); ++i)
								{
																delete animal_list[i];
								}
}

Ecosystem::Ecosystem(Grid* grid, Zone const& animal_zone, Zone const& plant_zone,
																					double rate, double shock)
								: plant_zone(plant_zone), animal_zone(animal_zone), grid(grid), FeedRate(rate), shock_parameter(shock)
{

								for(size_t i(0); i < plant_zone.size(); ++i) {
																plant_zone[i]->set_exist_food(true);
																// gives the cell the right to reproduce food
																// (cell is marked as "food can exist here")
								}

}

Ecosystem::Ecosystem(Grid* grid, Zone const& animal_zone, Zone const& plant_zone,
					unsigned int animals, unsigned int plants, double rate, double shock, double mutation_rate)
: plant_zone(plant_zone), animal_zone(animal_zone), grid(grid), FeedRate(rate), shock_parameter(shock)
{

								unsigned int animal_zone_size(animal_zone.size());
								unsigned int plant_zone_size(plant_zone.size());

								for (size_t i(0); i < animals; ++i) {
																unsigned int n(std::rand() % animal_zone_size);
																Animal* ptr(new Animal(animal_zone[n], mutation_rate));
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

void Ecosystem::add_random(unsigned int animals, unsigned int plants, double mutationRate)
{
								unsigned int animal_zone_size(animal_zone.size());
								unsigned int plant_zone_size(plant_zone.size());

								for (size_t i(0); i < animals; ++i) {
																unsigned int n(std::rand() % animal_zone_size);
																Animal* ptr(new Animal(animal_zone[n], mutationRate));
																animal_list.push_back(ptr);
								}

								for(size_t i(0); i < plants; ++i) {
																unsigned int n(std::rand() % plant_zone_size);
																plant_zone[n]->addFood();
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
																								numberReproduced += newborns.size();
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

								os << Animals << " " << grid->getNbFood() << " " << meanEnergy/ (Animals * 1.)
											<< " " << meanForce / (Animals * 1.) << " " << meanNumberofMoves / (Animals * 1.) 
											<< " " << meanOffsprings / (Animals * 1.) << " "<< meanReprThreshold/(Animals*1.) << " " 
											<< numberReproduced << " " << numberDied;

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

void Ecosystem::iteration(std::vector<std::ofstream*> os_tab, bool DataWrite, bool Evolution,
							std::string feeding, std::string writeCharac){
								if(DataWrite) {
																this->write(os_tab, writeCharac);
								}                                                          //writes the position of every animal, the plant density per cell and the system parameters
								this->move();
								numberDied = 0;
								this->die();
								numberReproduced = 0;
								this->animal_reproduce(Evolution);
								grid->sortAnimals();
								this->animal_eat();
								this->food_reproduce(feeding);
}

void Ecosystem::write(std::vector<std::ofstream*> os_tab, std::string writeCharac){
								//this->write_animalX(osX);
								//osX << std::endl;
								//this->write_animalY(osY);
								//osY << std::endl;
								//this->write_animal(osX, osY);
								//osX << std::endl;
								//osY << std::endl;
															
								this->write_animalPos(*(os_tab[0]));
								*(os_tab[0]) << std::endl;
								this->write_Plant(*os_tab[1]);
								*os_tab[1] << std::endl;
								this->write_systParam(*os_tab[2]);
								*os_tab[2] << std::endl;
								
								switch(writeCharac[0]){
									case 'a' : this->write_animalForce(*os_tab[3]); *os_tab[3] << std::endl; break;
									case 'c' : this->write_cellForce(*os_tab[8]); *os_tab[8] << std::endl;break; 
									case 'b' : {this->write_animalForce(*os_tab[3]); *os_tab[3] << std::endl;
												this->write_cellForce(*os_tab[8]);   *os_tab[8] << std::endl; break; }
									default : break;
								} 
								
								switch(writeCharac[1]){
									case 'a' : this->write_animalNbMoves(*os_tab[4]); *os_tab[4] << std::endl; break;
									case 'c' : this->write_cellNbMoves(*os_tab[9]); *os_tab[9] << std::endl;break; 
									case 'b' : {this->write_animalNbMoves(*os_tab[4]); *os_tab[4] << std::endl;
												this->write_cellNbMoves(*os_tab[9]);   *os_tab[9] << std::endl; break; }
									default : break;
								} 
								
								switch(writeCharac[2]){
									case 'a' : this->write_animalNbOff(*os_tab[5]); *os_tab[5] << std::endl; break;
									case 'c' : this->write_cellNbOff(*os_tab[10]); *os_tab[10] << std::endl;break; 
									case 'b' : {this->write_animalNbOff(*os_tab[5]); *os_tab[5] << std::endl;
												this->write_cellNbOff(*os_tab[10]);   *os_tab[10] << std::endl; break; }
									default : break;
								} 
								
								switch(writeCharac[3]){
									case 'a' : this->write_animalReproThr(*os_tab[6]); *os_tab[6] << std::endl; break;
									case 'c' : this->write_cellReproThr(*os_tab[11]); *os_tab[11] << std::endl;break; 
									case 'b' : {this->write_animalReproThr(*os_tab[6]); *os_tab[6] << std::endl;
												this->write_cellReproThr(*os_tab[11]);   *os_tab[11] << std::endl; break; }
									default : break;
								} 
								
								switch(writeCharac[4]){
									case 'a' : this->write_animalMouthSize(*os_tab[7]); *os_tab[7] << std::endl; break;
									case 'c' : this->write_cellMouthSize(*os_tab[12]); *os_tab[12] << std::endl;break; 
									case 'b' : {this->write_animalMouthSize(*os_tab[7]); *os_tab[7] << std::endl;
												this->write_cellMouthSize(*os_tab[12]);   *os_tab[12] << std::endl; break; }
									default : break;
								} 
}

void Ecosystem::animal_eat(){
								for(size_t i(0); i<animal_list.size(); ++i) {
																if(animal_list[i]->isAlive()) {
																								animal_list[i]->eat();
																}
								}
}

std::ostream& Ecosystem::write_cellForce(std::ostream& os) const
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




std::ostream& Ecosystem::write_cellNbMoves(std::ostream& os) const
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




std::ostream& Ecosystem::write_cellNbOff(std::ostream& os) const
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


std::ostream& Ecosystem::write_cellReproThr(std::ostream& os) const
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

std::ostream& Ecosystem::write_cellMouthSize(std::ostream&  os) const {
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



std::ostream& Ecosystem::write_animalForce(std::ostream&  os) const {
	for(auto const& animal : animal_list){
		os << animal -> get_force() << " " ; 
	}
	
	return os;
}

std::ostream& Ecosystem::write_animalNbMoves(std::ostream&  os) const {
	for(auto const& animal : animal_list){
		os << animal -> get_nb_moves() << " "; 
	}
	
	return os;
}

std::ostream& Ecosystem::write_animalNbOff(std::ostream&  os) const {
	for(auto const& animal : animal_list){
		os << animal -> get_nb_offspring() << " "; 
	}
	
	return os;
}

std::ostream& Ecosystem::write_animalReproThr(std::ostream&  os) const {
	for(auto const& animal : animal_list){
		os << animal -> get_rep_threshold() << " "; 
	}
	
	return os;
}

std::ostream& Ecosystem::write_animalMouthSize(std::ostream&  os) const {
	for(auto const& animal : animal_list){
		os << animal -> get_mouth_size() << " "; 
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
																numberDied = nbDead;
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
								switch(impact) {
								case HalveRate:
																std::cout << "Halve feeding rate";
																FeedRate /= 2.0;
																break;
								case DoubleRate:
																std::cout << "Double feeding rate";
																FeedRate *= 2.0;
																break;
								case MultiplyRate:
																std::cout << "Multiply feeding rate by " << shock_parameter;
																FeedRate *= shock_parameter;
																break;
								default: break;
								}

/*
        if(impact == HalveRate) {
                std::cout << "Halve Feeding rate";
                FeedRate /= 2.0;
        } else if(impact == DoubleRate) {
                FeedRate *= 2.0;
                std::cout << "Double Feeding rate";
        }
 */

								std::cout << std::endl;



}



std::ostream& Ecosystem::write_ecosystem_data(std::ostream & os) const
{
								size_t L = grid->size();
								for(size_t x(0); x < L; ++x) {
																for(size_t y(0); y < L; ++y) {
																								grid->getCell(x,y)->write_cell_data(os);
																								os << std::endl;
																}
								}
								return os;
}

std::ostream& Ecosystem::save_ecosystem(std::vector<std::string> strings,std::vector<unsigned int> numbers,std::ostream & os, unsigned int t) const {
								//strings : 0 : animalform, 1 : plantForm
								//numbers : 0 1 2 3 : AnimalParam 1 2 3 4, 4 5 6 7 : PlantParam 1 2 3 4, 8 : grid size
								os << '%'
											<< " Savefile of the following system at time t = "
											<< t
											<<" automatically generated on ";
								std::time_t end_time =std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
								os << std::ctime(&end_time);
								os << strings[0] << " " << strings[1] << " " << std::endl;
								for(size_t i(0); i < numbers.size(); ++i)
								{
																os << numbers[i] << " ";
								}
								os << std::endl;
								os << '%' << " Cells information ======== " << std::endl;
								write_ecosystem_data(os);


								return os;
}

std::ifstream& Ecosystem::add_from_file(std::ifstream& loadfile)
{
							//IMPORTANT : THIS ASSUMES WE START RIGHT AT THE GOOD LINE
								std::string test;
								size_t L = grid->size();
								for(size_t x(0); x < L; ++x) {
																for(size_t y(0); y < L; ++y)
																{
																								Cell* currentCell = grid->getCell(x,y);
																								std::string test,a;

																								unsigned int a_food_density, a_nb_food;
																								bool a_exist_food;

																								//add plant's characteristics first
																								loadfile >> a_food_density >> a_nb_food >> a_exist_food;
																								currentCell->set_food_density(a_food_density);
																								currentCell->set_food(a_nb_food);
																								currentCell->set_exist_food(a_exist_food);


																								//get the rest of the stream
																								getline(loadfile, test, 'E');
																								std::stringstream listanimalstream(test);

																								//list each animal
																								while(!(test.empty())) {
																																getline(listanimalstream, test, ';');
																																if(!(test.empty())) {
																																								unsigned int nb_offspring, nb_moves, mouth_size;
																																								double force, repr_threshold, energy;
																																								double mutation_rate;
																																								std::stringstream(test)
																																								>> force >> nb_offspring
																																								>> repr_threshold >> nb_moves
																																								>> mouth_size >> energy >> mutation_rate;

																																								Animal* ptr(new Animal(currentCell, GeneticData(force, nb_offspring, repr_threshold, nb_moves, mouth_size, mutation_rate), energy));
																																								animal_list.push_back(ptr);

																																}
																								}
																								test.clear();
																}

								}




								return loadfile;

}
