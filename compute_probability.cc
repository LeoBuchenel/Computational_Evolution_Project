#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


int main(){

        //probability with evolution 54.0 % without 53.5%
        ofstream ProbaFile;
        ProbaFile.open("Results/SurvivalTime.out");

        size_t Nprob = 2;
        unsigned int Mnumber = 10;

        vector<double> mutrate (Mnumber, 0.);

        for(size_t i(0); i< Mnumber; ++i) {
                mutrate[i] = (i*1.0)/((Mnumber-1)*1.0);
        }

        cout << endl;

        vector<double> p (mutrate.size(), 0.);

        for(size_t i(0); i < p.size(); ++i) {
                string mutation = to_string(mutrate[i]);
                for(size_t k(0); k < Nprob; ++k) {
                        string cmd = "./Projectv2 configuration.in Mutation_rate="+mutation;
                        int a = system(cmd.c_str());
                        ifstream fichier;
                        string nom_fichier("Results/tfin.out");
                        fichier.open(nom_fichier.c_str());
                        fichier >> a;
                        p[i]+=(a*1.0)/(Nprob*1.0);
                        fichier.close();
                }
                ProbaFile << p[i] << " ";
        }
        ProbaFile.close();

        return 0;
}
