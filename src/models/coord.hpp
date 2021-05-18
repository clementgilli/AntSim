#ifndef COORD_HPP
#define COORD_HPP

#include <vector>
#include<iostream>

using namespace std;


const int TAILLEGRILLE = 30;

class Coord {

    //Attributs
    int _lig;
    int _col;

    public :
    //Constructeurs
    /**
     * Constructor for Coord, giving line and column
     * 
     * @param int ,int 
     * 
     * @return Coord
     * 
     * @confidence 5
     **/
    Coord (int l, int c);

    //Méthodes
    /**
     * Getter of line
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 5
     **/
    int ligne() const;
    /**
     * Getter of column
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 5
     **/
    int colonne() const;

};

class EnsCoord {

	//Attributs
	vector<Coord> _ens;
	
	public :
	//Constructeurs
    /**
     * Constructor for EnsCoord using a vector of Coord
     * 
     * @param vector<Coord>
     * 
     * @return EnsCoord
     * 
     * @confidence 5
     **/
    EnsCoord(vector<Coord> tab);

	//Méthode
    /**
     * Getter, size of the set
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 4
     **/
    int taille() const;
    /**
     * Get at the i-th place in the set (if possible)
     * 
     * @param int
     * 
     * @return Coord
     * 
     * @confidence 5
     **/
	Coord get_coord(int i) const;
    /**
     * Check if the set owns the element <a>
     * 
     * @param Coord
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool contient(Coord a) const;
    /**
     * Add the elem <a> to the set (if it doesn't already owns it)
     * 
     * @param Coord
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void ajoute(Coord a);
    /**
     * remove the elem <a> from the set (if it owns it)
     * 
     * @param Coord
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void supprime(Coord a);
    /**
     * Check if the set is empty
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    bool estVide() const;
    /**
     * Get a random element in the set
     * 
     * @param 
     * 
     * @return Coord
     * 
     * @confidence 5
     **/
    Coord choixHasard() const;

    private :
    /**
     * Get the position of the elem <a> in the set
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 
     **/
    int position(Coord a) const;

};
//Fonctions
/**
     * Get the nearest neighbours valid Coord around the <n> one.
     * 
     * @param Coord
     * 
     * @return EnsCoord
     * 
     * @confidence 5
     **/
EnsCoord voisines(Coord n);
/**
     * Get the max of 2 ints
     * 
     * @param int,int
     * 
     * @return int
     * 
     * @confidence 5
     **/
int maxi(int a,int b);
/**
     * Get the min of 2 ints
     * 
     * @param int,int
     * 
     * @return int
     * 
     * @confidence 5
     **/
int mini(int a,int b);

//Opérateurs
/**
     * Concatenate 2 sets
     * 
     * @param EnsCoord,EnsCoord
     * 
     * @return EnsCoord
     * 
     * @confidence 5
     **/
EnsCoord operator+(EnsCoord a, EnsCoord b);
/**
     * Print a Coord
     * 
     * @param Coord
     * 
     * @return 
     * 
     * @confidence 3
     **/
ostream &operator<<(ostream &out, const Coord &c);
/**
     * Check if two Coords are equals
     * 
     * @param Coord, Coord
     * 
     * @return bool
     * 
     * @confidence 5
     **/
bool operator==(const Coord a, const Coord b);
/**
     * Check if two elems are differents
     * 
     * @param Coord,Coord
     * 
     * @return bool
     * 
     * @confidence 5
     **/
bool operator!=(const Coord a, const Coord b);
/**
     * Print a set
     * 
     * @param EnsCoord
     * 
     * @return 
     * 
     * @confidence 5
     **/
ostream &operator<<(ostream &out, const EnsCoord &e);
/**
     * Check is two sets are differents
     * 
     * @param EnsCoord, EnsCoord
     * 
     * @return bool
     * 
     * @confidence 5
     **/
bool operator!=(const EnsCoord a, const EnsCoord b);
/**
     * Check if two sets are equals
     * 
     * @param EnsCoord, EnsCoord
     * 
     * @return bool
     * 
     * @confidence 5
     **/
bool operator==(const EnsCoord a, const EnsCoord b);

#endif