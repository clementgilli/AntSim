#include "models/fourmi.hpp"
#include "doctest.h"

DOCTEST_TEST_SUITE_BEGIN("fourmi");

TEST_CASE ("classe fourmi") {
	const Coord p1{10,6};
	const Coord p2{3,4};
	const Coord origine{0,0};
	const Coord nid{12,7};
	Fourmi f {origine,3,Colonie::Red};
	const Fourmi g {p2,3,Colonie::Blue};

	CHECK_FALSE(f.porteSucre());
	CHECK(f.energie()==0);
	CHECK(f.couleur()==Colonie::Red);
	CHECK(f.numero()==3);
	CHECK(f.numero()==g.numero());
	CHECK_FALSE(f.couleur()==g.couleur());
	CHECK_FALSE(f.coord()==g.coord());

	f.deplace(p1);

	CHECK_THROWS_AS(f.poseSucre(),runtime_error);
	CHECK(f.coord()==p1);
	CHECK(f.energie()==1);
	CHECK_FALSE(f.porteSucre());
	CHECK_FALSE(f.coord()==g.coord());

	f.deplace(p2);
	f.prendSucre();
	f.augmenteFatigue();

	CHECK(f.coord()==g.coord());
	CHECK(f.energie()==4);
	CHECK(f.porteSucre());
	CHECK_THROWS_AS(f.prendSucre(),runtime_error);
	CHECK(f.coord()==p2);
	CHECK_FALSE(f.coord()==p1);

	f.deplace(nid);
	f.poseSucre();
	f.repos();

	CHECK(f.coord()==nid);
	CHECK_FALSE(f.porteSucre());
	CHECK_THROWS_AS(f.poseSucre(),runtime_error);
	CHECK(f.energie()==0);
}

DOCTEST_TEST_SUITE_END();