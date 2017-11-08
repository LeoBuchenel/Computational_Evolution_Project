#include "Grid.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

Zone operator+(Zone zone1, Zone const& zone2)
{
								for(auto const& obj:zone2) {
																bool exist(false);
																unsigned int j(0);
																while(!exist&& j < zone1.size()) {
																								if(obj == zone1[j]) {
																																exist = true;
																								}
																								++j;
																}
																if(!exist) {
																								zone1.push_back(obj);
																}
								}

								return zone1;
}

Grid::Grid(unsigned int L)
								: grid(std::vector<std::vector<Cell*> > (L+1, std::vector<Cell*>(L+1)))
{
								for(unsigned int x(0); x < L+1; ++x) {
																for(unsigned int y(0); y < L+1; ++y) {
																								grid[x][y] = new Cell(x,y);
																}
								}
}

Cell* Grid::getCell(unsigned int x, unsigned int y) const
{
								if(x < grid.size() && y < grid.size()) {
																return grid[x][y];
								}
								return NULL;
}

Grid::~Grid()
{
								for(auto& line:grid) {
																for(auto& obj:line) {
																								delete obj;
																}
								}
}

Zone Grid::getZone(std::string form, unsigned int param1, unsigned int param2, unsigned int param3, unsigned int param4) const {
								Zone zone;
								if(form == "rectangle") {
																//A below and behind B : rearranges that
																unsigned int xA = std::min(param1,param3);
																unsigned int yA = 0;
																unsigned int xB = 0;
																unsigned int yB = 0;

																if(xA == param1) {
																								yA = param2;
																								xB = param3;
																								yB = param4;
																}else{
																								yA = param4;
																								xB = param1;
																								yB = param2;
																}

/*
                std::cout << "xA = " << xA << std::endl;
                std::cout << "yA = " << yA << std::endl;
                std::cout << "xB = " << xB << std::endl;
                std::cout << "yB = " << yB << std::endl;
 */

																size_t L = grid.size();

																if(xA < L+1 and xB > xA and xB < L+1 and yA < L+1 and yB<L+1) {
																								for(size_t x(xA); x < xB+1; ++x) {
																																for(size_t y(yA); y< yB+1; ++y) {
																																								zone.push_back(grid[x][y]);
																																}
																								}
																}
								}
								if(form=="whole") {
																for(size_t x(0); x < grid.size(); ++x) {
																								for(size_t y(0); y< grid.size(); ++y) {
																																zone.push_back(grid[x][y]);
																								}
																}

								}

								return zone;
}


void Grid::food_reproduce(size_t possible_cells) const
{
								/*
								       unsigned int nbFood = this->getNbFood();
								       double alpha = 1; // dN/dt = alpha*N
								       for(auto const& line:grid) {
								               for(auto const& cell:line) {
								                       cell->food_reproduce(proba);
								               }
								       }
								 */
}

unsigned int Grid::getNbFood() const
{
								unsigned int nbFood(0);
								for(auto const& line:grid) {
																for(auto const& cell:line) {
																								nbFood+=cell->getNbFood();
																}
								}

								return nbFood;
}

void Grid::sortAnimals() const
{
								for(auto const& line:grid) {
																for(auto const& cell:line) {
																								cell->sortAnimals();
																}
								}
}

std::ostream& Grid::write_Plant(std::ostream& os) const
{
								for(auto const line:grid) {
																for(auto const cell:line) {
																								os << cell->getNbFood() <<" ";
																}
								}

								return os;
}

std::size_t Grid::size() const {
								return grid.size();
}

void reproduce(const Zone& zone, double alpha, unsigned int food){
								unsigned int N = zone.size();
								for(size_t i(0); i < alpha*food; ++i) {
																unsigned int pick = std::rand() % N;
																zone[pick]->addFood(1);
								}
}
