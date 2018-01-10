#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


int main(){

        //probability with evolution 54.0 % without 53.5%
        ofstream ProbaFile;
        ProbaFile.open("probability.out");

        vector<int> plants, animals;
        int plantbegin = 450, animalbegin = 270;

        for(size_t i(0); i < 20; ++i) {
                plants.push_back(plantbegin+i*5);
                animals.push_back(animalbegin+i*3);
        }

        size_t Nprob = 10;

        vector<vector<double> > p (plants.size(), vector<double>(animals.size(), 0.));

        for(size_t i(0); i < plants.size(); ++i) {
                for(size_t j(0); j < animals.size(); ++j) {
                        for(size_t k(0); k < Nprob; ++k) {
                                string strPlants = to_string(plants[i]), strAnimals = to_string(animals[j]);
                                string cmd = "./Projectv2 configuration.in animals="+strAnimals+" plants="+strPlants;
                                int a = system(cmd.c_str());
                                ifstream fichier;
                                string nom_fichier("tfin.out");
                                fichier.open(nom_fichier.c_str());
                                fichier >> a;
                                p[i][j]+=a*1.0/Nprob;
                                fichier.close();
                        }
                        ProbaFile << p[i][j] << " ";
                }
                ProbaFile << endl;
        }
        ProbaFile.close();

        return 0;
}
