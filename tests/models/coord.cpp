#include "models/coord.hpp"
#include "doctest.h"

DOCTEST_TEST_SUITE_BEGIN("Coord tests");

TEST_CASE("Classe Coord") {
    Coord origine = Coord(0,0);
    CHECK(origine.ligne() == 0);
    CHECK(origine.colonne() == 0);
    CHECK_THROWS_AS(Coord(0, 50), invalid_argument);
    CHECK_THROWS_AS(Coord(41, 0), invalid_argument);
    CHECK_THROWS_AS(Coord(0, -5), invalid_argument);
    CHECK(Coord(1,0) == Coord(1,0));
    CHECK(Coord(1,0) != origine);
}

TEST_CASE("Classe EnsCoord") {
    EnsCoord e = EnsCoord({});
    CHECK(e.estVide());
    e.ajoute(Coord(0,0));
    e.ajoute(Coord(1,0));
    e.ajoute(Coord(2,0));
    CHECK(e.taille() == 3);
    CHECK(e.contient(Coord(1,0)));
    CHECK_FALSE(e.contient(Coord(0,1)));
    CHECK(e.get_coord(0) == Coord(0,0));
    CHECK_THROWS_AS(e.get_coord(-1), invalid_argument);
    CHECK_THROWS_AS(e.ajoute(Coord(0,0)), invalid_argument);
    CHECK_THROWS_AS(e.supprime(Coord(0,56)), invalid_argument);
    e.supprime(Coord(0,0));
    CHECK_FALSE(e.contient(Coord(0,0)));
    e.supprime(Coord(1,0));
    e.supprime(Coord(2,0));
    CHECK(e.estVide());
}

TEST_CASE("Grille"){
    SUBCASE("voisines"){
        CHECK(voisines(Coord(0,0))==EnsCoord({Coord(1,1),Coord(0,1),Coord(1,0)}));
        CHECK(voisines(Coord(0,TAILLEGRILLE-1))==EnsCoord({Coord(0,TAILLEGRILLE-2),Coord(1,TAILLEGRILLE-2),Coord(1,TAILLEGRILLE-1)}));
        CHECK(voisines(Coord(TAILLEGRILLE-1,0))==EnsCoord({Coord(TAILLEGRILLE-2,1),Coord(TAILLEGRILLE-1,1),Coord(TAILLEGRILLE-2,0)}));
        CHECK(voisines(Coord(TAILLEGRILLE-1,TAILLEGRILLE-1))==EnsCoord({Coord(TAILLEGRILLE-2,TAILLEGRILLE-2),Coord(TAILLEGRILLE-1,TAILLEGRILLE-2),Coord(TAILLEGRILLE-2,TAILLEGRILLE-1)}));
        CHECK(voisines(Coord(2,1)) == EnsCoord({Coord(1,0),Coord(1,1),Coord(1,2),Coord(2,2),Coord(3,2),Coord(3,1),Coord(3,0),Coord(2,0)}));
        CHECK(voisines(Coord(3,4)) == EnsCoord({Coord(2,3),Coord(2,4),Coord(3,3),Coord(4,3),Coord(4,4),Coord(2,5),Coord(3,5),Coord(4,5)}));
        CHECK(voisines(Coord(2,0)) == EnsCoord({Coord(1,0),Coord(3,0),Coord(1,1),Coord(3,1),Coord(2,1)}));
        CHECK(voisines(Coord(0,2)) == EnsCoord({Coord(0,1),Coord(0,3),Coord(1,1),Coord(1,2),Coord(1,3)}));
        CHECK(voisines(Coord(2,TAILLEGRILLE-1)) == EnsCoord({Coord(1,TAILLEGRILLE-1),Coord(1,TAILLEGRILLE-2),Coord(2,TAILLEGRILLE-2),Coord(3,TAILLEGRILLE-2),Coord(3,TAILLEGRILLE-1)}));
        CHECK(voisines(Coord(TAILLEGRILLE-1,2)) == EnsCoord({Coord(TAILLEGRILLE-1,1),Coord(TAILLEGRILLE-1,3),Coord(TAILLEGRILLE-2,1),Coord(TAILLEGRILLE-2,2),Coord(TAILLEGRILLE-2,3)}));
    }
    SUBCASE("choixHasard"){
        CHECK_THROWS_AS(EnsCoord({}).choixHasard(),runtime_error);
        EnsCoord E{{Coord(1,0),Coord(1,1),Coord(1,2),Coord(2,2),Coord(3,2),Coord(3,1),Coord(3,0),Coord(2,0)}};
    }
}
DOCTEST_TEST_SUITE_END();