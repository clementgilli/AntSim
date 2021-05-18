#include "controllers/manager.hpp"
#include "models/coord.hpp"
#include "doctest.h"

DOCTEST_TEST_SUITE_BEGIN("Mananger tests");

TEST_CASE ("") {

    /*
    Manager test;

    for (int i = 0; i <= 3; i++) {  //In dept test of start function
        Coord coordNid = test.genereCoordVide();
        Nid n = {coordNid,Colonie(i),{}};
        test.DONNEES.nids.push_back(n);
        for (int j = 0; j < 5; j++) {
            Coord cF = test.genereCoordFourmi(n);        //Intitialisaton des fourmis
            Fourmi fou = Fourmi(cF,j,Colonie(i));
            test.DONNEES.nids[i].famille.push_back(fou);
        }    
    }
	test.DONNEES.grille.initialiseGrille(test.DONNEES.nids,test.DONNEES.sucres,test.DONNEES.coordNids());
    EnsCoord e = test.DONNEES.coordNids();
    Coord c = e.get_coord(0);
    Place p1 = test.DONNEES.grille.chargePlace(c);
    
    CHECK(not p1.estVide());
    */
}
DOCTEST_TEST_SUITE_END();