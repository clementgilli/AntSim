#include "models/place.hpp"
#include "doctest.h"


DOCTEST_TEST_SUITE_BEGIN("place");

TEST_CASE("classe place") {
	Place p = Place(Coord(0,0));
	Place d = Place(Coord(10,10));
	Place q = Place(Coord(0,1));
	Fourmi f = Fourmi(p.coord(),1,Colonie::Red);

	CHECK(p.coord() == Coord(0,0));
	CHECK(p.estVide());
	CHECK(p.pheroSucre(f.couleur()) == 0);
	p.poseSucre();
	CHECK_FALSE(p.estVide());
	CHECK(p.contientSucre());
	//CHECK(DONNEES.sucres.taille() == 1 );
	//CHECK(DONNEES.sucres.get_coord(0) == Coord(0,0));
	p.posePheroSucre(f.couleur());
	for (int i = 0; i < 10; i++) p.diminuePheroSucre(f.couleur());
	CHECK(p.pheroSucre(f.couleur()) == 205);
	p.enleveSucre();
	CHECK(p.estVide());
	//CHECK(DONNEES.sucres.taille() == 0 );
	d.posePheroSucre(f.couleur());
	CHECK(d.estSurUnePiste(f.couleur()));
	CHECK_FALSE(p.contientNid());
	p.poseNid(Colonie::Red);
	CHECK(p.contientNid());
	//CHECK(q.estPlusProcheNid(d,DONNEES.nids[DONNEES.numNid(Coord(0,0))]));
	p.supprimeNid();
	CHECK_FALSE(p.contientNid());
	p.poseFourmi(f);
	CHECK(p.numFourmi() == 1);
	CHECK(p.couleurFourmi() == Colonie::Red);
	CHECK_FALSE(p.estVide());
	p.enleveFourmi(f);
	CHECK(p.estVide());
	CHECK(p.numFourmi() == -1);
	CHECK_THROWS_AS(p.couleurFourmi(),runtime_error);
	
}

TEST_CASE("Classe Grille") {
	Data dtest {};
	Grille test = Grille();
	Fourmi f1 = Fourmi(Coord(0,0),0,Colonie::Red);
	Fourmi f2 = Fourmi(Coord(0,1),1,Colonie::Red);
	Fourmi f3 = Fourmi(Coord(0,2),2,Colonie::Red);
	vector<Fourmi> lesRouges = {f1,f2,f3};
	Nid nidRouge = {0,Coord(10,10),Colonie::Red,lesRouges};
	dtest.nids.push_back(nidRouge);
	dtest.sucres.ajoute(Coord(5,5));
	dtest.sucres.ajoute(Coord(15,15));
	test.initialiseGrille(dtest.nids,dtest.sucres,dtest.coordNids());
	Place p1 = test.chargePlace(Coord(10,10));
	Place p2 = test.chargePlace(Coord(5,5));
	Place p3 = test.chargePlace(Coord(15,15));
	Place p4 = test.chargePlace(Coord(0,0));
	Place p5 = test.chargePlace(Coord(0,1));
	Place p6 = test.chargePlace(Coord(0,2));
	Place p7 = test.chargePlace(Coord(5,0));
	CHECK(p1.contientNid());
	CHECK(p2.contientSucre());
	CHECK(p3.contientSucre());
	CHECK(p4.numFourmi() == 0);
	CHECK(p4.couleurFourmi() == Colonie::Red);
	CHECK(p5.numFourmi() == 1);
	CHECK(p5.couleurFourmi() == Colonie::Red);
	CHECK(p6.numFourmi() == 2);
	CHECK(p6.couleurFourmi() == Colonie::Red);
	test.deplaceFourmi(f1,p4,p7);
	p4 = test.chargePlace(Coord(0,0));
	p7 = test.chargePlace(Coord(5,0));
	CHECK(p4.numFourmi() == -1);
	CHECK(p7.numFourmi() == 0);
	test.linearisePheroNid(Colonie::Red);
	CHECK(p1.pheroNid(Colonie::Red) == 1);
	Place p8 = test.chargePlace(Coord(10,12));
	CHECK_FALSE(p8.pheroNid(Colonie::Red) == 1);
	test.g[TAILLEGRILLE].posePheroSucre(f1.couleur());
	test.diminuePheroSucre();
	p5 = test.chargePlace(Coord(0,1));
	CHECK(p5.pheroSucre(f1.couleur()) == 250);
}

DOCTEST_TEST_SUITE_END();