#include "Animal.h"
#include "Grid.h"
#include <random>
#include <iostream>

Animal::Animal(Cell* cell_, double mutation_rate)
: position(cell_), genetic_data(GeneticData(mutation_rate)), energy(100)
{
        //position = cell_;
        //genetic_data = GeneticData(mutation_rate);
        //energy = (std::rand()%100)+1;
        //energy = 100.;
        cell_->addAnimal(this);

}

Animal::Animal(Cell* cell_, GeneticData gd, double health)
:position(cell_), genetic_data(gd), energy(health)
{
        //position = cell_;
        //genetic_data = gd;
        //energy = health;
        position->addAnimal(this);
}

bool Animal::isAlive() const {
        return (energy>0.0);
}

double Animal::get_force() const {
        return genetic_data.GeneticData::get_force();
}


double Animal::get_rep_threshold() const {
        return genetic_data.GeneticData::get_rep_threshold();
}

unsigned int Animal::get_nb_moves() const {
        return genetic_data.GeneticData::get_nb_moves();
}

unsigned int Animal::get_nb_offspring() const {
        return genetic_data.GeneticData::get_nb_offspring();
}

unsigned int Animal::get_mouth_size() const {
        return genetic_data.GeneticData::get_mouth_size();
}

double Animal::get_energy() const {
        return energy;
}

std::vector<Animal*> Animal::reproduce(bool Evolution){
        std::vector<Animal*> newborns;
        if(energy>Animal::get_rep_threshold()) {
                double offspringEnergy
                        = energy/(Animal::get_nb_offspring()*1.0 + 1.0);
                for(std::size_t i(0); i<Animal::get_nb_offspring(); ++i) {
                        Animal* ptr = new Animal(position, genetic_data, offspringEnergy);
                        if(!this->isAlive()) {
                                std::cout << "A dead animal is reproducing" << std::endl;
                        }
                        if(Evolution) {
                                ptr->evolve();
                        }
                        newborns.push_back(ptr);

                }
                energy = offspringEnergy;
        }
        return newborns;
}

void Animal::changeCell(Cell* cell){
        position = cell;
}

std::vector<unsigned int> Animal::move(Grid* grid){


        int X = position->getX();
        int Y = position->getY();
        unsigned int Taille = grid->size();
        unsigned int X2 = 0;
        unsigned int Y2 = 0;

        for(std::size_t i(0); i<get_nb_moves(); ++i) {
                int depl_x = (rand()%3)-1;
                int depl_y = (rand()%3)-1;
                X+=depl_x;
                Y+=depl_y;
                energy-=7.0;

                int X1 = X, Y1 = Y;

                if(X1 >= Taille or X1 < 0) X1 = X1 % Taille;
                if(Y1 >=Taille or Y1 < 0) Y1 = Y1 % Taille;

                X2 = abs(X1);
                Y2 = abs(Y1);

                if(grid->getCell(X2,Y2)->exist_food_on_cell()) {
                        i = get_nb_moves();
                }
        }

        std::vector<unsigned int> new_pos;
        new_pos.push_back(X2);
        new_pos.push_back(Y2);

        return new_pos;
}

void Animal::eat() {
        //decreasefood retourne la quantité de food que l'animal mange

        // the animal eats all the food he can on the cell
        for(size_t i(0); i < this->genetic_data.get_mouth_size(); ++i) {
                if(position->decreaseFood()!=0) {
                        energy+=70.;
                }
        }
}

unsigned int Animal::getX() const
{
        return position->getX();
}

unsigned int Animal::getY() const
{
        return position->getY();
}

Cell* Animal::get_Position() const {
        return position;
}

void Animal::evolve(){
        genetic_data.mutate();
}

Animal::~Animal()
{
        position->removeAnimal(this);

}

std::ostream& Animal::write_animal_data(std::ostream& os) const
{
        genetic_data.write_genetic_data(os);
        os << " " << energy;

        return os;

}
