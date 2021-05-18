#include <stdexcept>
#include <iostream>
#include <vector>
#include <array>
using namespace std;

#include "fourmi.hpp"

//Constructeurs

Fourmi::Fourmi(Coord a, int n, Colonie col):position{a}, num{n}, color{col} {
	rotation = {0,1};
    fatigue = 0;
    sucre = false;
}

//Getters

Coord Fourmi::coord() const {return position;}

int Fourmi::numero() const {return num;}

Colonie Fourmi::couleur() const {return color;}

int Fourmi::energie() const {return fatigue;}

bool Fourmi::porteSucre() const {return sucre;}

bool Fourmi::chercheSucre() const {return not sucre;}

//Setters

void Fourmi::augmenteFatigue() {
	if (porteSucre()) fatigue +=2;
	else fatigue += 1;
}

void Fourmi::repos(){fatigue=0;}

void Fourmi::prendSucre(){
	if (sucre){
		throw runtime_error("La fourmi a déja un sucre !");
	}
	sucre = true;
}

void Fourmi::poseSucre(){
	if (not(sucre))
		throw runtime_error("La fourmi n'a pas de sucre !");
	sucre =false;
}

void Fourmi::deplace(Coord a){
	position=a;
	augmenteFatigue();
}

void Fourmi::setRotation(array<int,2> rot){
	rotation = rot;
}

array<int,2> Fourmi::getRotation() const{
	return rotation;
}