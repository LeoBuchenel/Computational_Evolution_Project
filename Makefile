CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11  # C++11

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall         # pour les purs et durs
CXXFLAGS += -g                      # pour debugger
# CXXFLAGS += -pg                   # pour profiler
# LDFLAGS  += -pg                   # pour profiler
CXXFLAGS += -O2                   # pour optimiser la vitesse


all: Projectv2
clean:
	$(RM) $(TARGET) *.o *.out

Cell.o : Cell.cc Cell.h

GeneticData.o : GeneticData.cc GeneticData.h

Animal.o : Animal.cc Animal.h GeneticData.h Cell.h

Grid.o : Grid.cc Grid.h Cell.h

Ecosystem.o : Ecosystem.cc Ecosystem.h Grid.h Animal.h

Projectv2.o : Projectv2.cc Animal.h Ecosystem.h Grid.h Cell.h GeneticData.h 
 
Projectv2 : Projectv2.o Animal.o Ecosystem.o Grid.o Cell.o GeneticData.o


