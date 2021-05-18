#include "controllers/manager.hpp"
#include <iostream>
#include <cstring>


int main(int argv,char ** args) {

    

    srand(time(0));
    
    Manager ant_sim;

    if (argv > 1) {
        if (strcmp(args[1], "-w") == 0)
            ant_sim.SEPAREMUR = true;    
    }

    ant_sim.start();

    return 0;
}