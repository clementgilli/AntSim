#ifndef PLACE_HPP
#define PLACE_HPP

#include <array>
#include <vector>
#include <cmath>

using namespace std;

#include "fourmi.hpp"


struct Nid {
    int pts;
    Coord pos;
    Colonie color;
    vector<Fourmi> famille;

    /**
     * Get the position of ant whith the giving number linked
     * 
     * @param int
     * 
     * @return int
     * 
     * @confidence 2
     **/
    int indiceFourmi(int numeroFourmi);
    
    /**
     * Get score of the Nest
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 2
     **/
    int score();
    
    /**
     * raise the score of the Nest by <n>
     * 
     * @param int 
     * 
     * @return 
     * 
     * @confidence 2
     **/
    void augmenteScore(int n);
    
    /**
     * Get the highest ant's number in the Nest
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 2
     **/
    int indiceMax();
};


class Place {

    //Attributs
    Coord pos;
    float qteSucre;
    Nid *nid;
    array<int,4> phS;
    array<float,4> phN;
    Fourmi *f;
    bool wall = false;
    
    public :

    //Constructeurs
    
    /**
     * Default Place constructor
     * 
     * @param 
     * 
     * @return Place with the coord (0,0)
     * 
     * @confidence 3
     **/
    Place();
    
    /**
     * Place constructor using coord
     * 
     * @param Coord
     * 
     * @return Place
     * 
     * @confidence 5
     **/
    Place (Coord coo); //t

    //Accès
    /**
     * Get the coord of the Place
     * 
     * @param 
     * 
     * @return Coord
     * 
     * @confidence 5
     **/
    Coord coord() const; //t
    
    /**
     * Get the amount of sugar pheromons of the colony <color> 
     * 
     * @param Enum class Colonie
     * 
     * @return int
     * 
     * @confidence 5
     **/
    int pheroSucre(Colonie color) const; //t
    
    /**
     * Get the amount of Nest pheromons of the colony <color>
     * 
     * @param Enum class Colonie
     * 
     * @return float
     * 
     * @confidence 5
     **/
    float pheroNid(Colonie color) const;
    
    /**
     * Get the ant's number, -1 if there is not 
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 5
     **/
    int numFourmi() const;
    
    /**
     * Get the Color of the ant if there's one
     * 
     * @param
     * 
     * @return Enum struct Colonie
     * 
     * @confidence 5
     **/
    Colonie couleurFourmi() const;
    
    /**
     * Check if the Place is a Wall
     * 
     * @param
     * 
     * @return bool
     * 
     * @confidence 2
     **/
    bool contientMur() const;

    //Prédicats
    
    /**
     * Check is the Place is empty
     * 
     * @param 
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool estVide() const; //t
    
    /**
     * Check if there is sugar on the Place
     * 
     * @param
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool contientSucre() const; //t
    
    /**
     * Check if there is a Nest on the Place
     * 
     * @param 
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool contientNid() const; //t
    
    /**
     * Check if there is sugar pheromons for the colony <color>
     * 
     * @param Enum struct Colonie 
     * 
     * @return bool
     * 
     * @confidence 
     **/
    bool estSurUnePiste(Colonie color) const; //t
   
    /**
     * Check if the current place is closer of the nest <n> than <p2>
     * 
     * @param Place p2, Nid n
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool estPlusProcheNid(Place p2, Nid n) const;
    
    /**
     *  Check if the current place is farer of the nest <n> than <p2>
     * 
     * @param Place p2, Nid n
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool estPlusLoinNid(Place p2, Nid n) const;

    //Modifications
    
    /**
     * Put sugar on the place
     * 
     * @param 
     * 
     * @return
     * 
     * @confidence 5
     **/
    void poseSucre(); //t
    
    /**
     * Remove sugar on the place
     * 
     * @param 
     * 
     * @return
     * 
     * @confidence 5
     **/
    void enleveSucre(); //t
    
    /**
     * Put a wall on the place
     * 
     * @param
     * 
     * @return
     * 
     * @confidence 2
     **/
    void setWall();
    
    /**
     * Put a nest on the place
     * 
     * @param Enum struct Colonie
     * 
     * @return
     * 
     * @confidence 5
     **/
    void poseNid(Colonie couleur); //t
    
    /**
     * Remove the nest from the place, if there is one
     * 
     * @param
     * 
     * @return
     * 
     * @confidence 5
     **/
    void supprimeNid(); //t
    
    /**
     * Put an ant on the Place(if possible)
     * 
     * @param Fourmi
     * 
     * @return
     * 
     * @confidence 5
     **/
    void poseFourmi(Fourmi &f);
    
    /**
     * Remove ant from the place (if possible)
     * 
     * @param Fourmi
     * 
     * @return
     * 
     * @confidence 5
     **/
    void enleveFourmi(Fourmi &f);
    
    /**
     * Put nest pheromon on the place
     * 
     * @param float, Enum struct Colonie
     * 
     * @return
     * 
     * @confidence 
     **/
    void posePheroNid(float intensite, Colonie couleur);
    
    /**
     * Put sugar pheromons on the place
     * 
     * @param Enum struct Colonie
     * 
     * @return
     * 
     * @confidence 5
     **/
    void posePheroSucre(Colonie couleur); //t
    
    /**
     * low the sugar pheromons on the place
     * 
     * @param Enum struct Colonie
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void diminuePheroSucre(Colonie couleur); //t
};


/**
* Born an ant on the nest
* 
* @param Nid*
* 
* @return Fourmi*
* 
* @confidence 1
**/
Fourmi *initialiseFourmi(Nid *n);
    
/**
*  malloc a nest 
* 
* @param Coord, Colonie
* 
* @return Nid*
* 
* @confidence 1
**/
Nid *initialiseNid(Coord p, Colonie c);


struct Grille {
    
    //Attributs
    array<Place,TAILLEGRILLE*TAILLEGRILLE> g;

    //Constructeurs
    
    /**
     * Default constructor of Grille
     * 
     * @param
     * 
     * @return Grille
     * 
     * @confidence 2
     **/
    Grille();

    //Méthodes
    
    /**
     * Get a copy of the place with coord <c>
     * 
     * @param Coord
     * 
     * @return Place
     * 
     * @confidence 2
     **/
    Place chargePlace(Coord c) const;
    
    /**
     * Set the place p
     * 
     * @param Place
     * 
     * @return
     * 
     * @confidence 2
     **/
    void rangePlace(Place p);
    
    /**
     * Put nests on the given coord set
     * 
     * @param EnsCoord
     * 
     * @return 
     * 
     * @confidence 2
     **/
    void placeNid(EnsCoord e);
    
    /**
     * Place sugars on the given EnsCoord
     * 
     * @param EnsCoord 
     * 
     * @return
     * 
     * @confidence 5
     **/
    void placeSucre(EnsCoord e);
    
    /**
     * Place ants living around the nest <t>
     * 
     * @param Nid&
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void placeFourmi(Nid &t);
    
    /**
     * Place all the elements on the grid
     * 
     * @param vector<nid>&, EnsCoord, EnsCoord
     * 
     * @return
     * 
     * @confidence 2
     **/
    void initialiseGrille(vector<Nid> &t, EnsCoord sucres, EnsCoord nids);
    
    /**
     * Normalise the nest pheromons on the grid of the Colonie
     * 
     * @param Enum strucytColonie 
     * 
     * @return 
     * 
     * @confidence 2
     **/
    void linearisePheroNid(Colonie couleur);
    
    /**
     * Evaporates the sugar pheromons on the grid
     * 
     * @param
     * 
     * @return
     * 
     * @confidence 2
     **/
    void diminuePheroSucre();
    
    /**
     * Moove <f> from p1 to p2
     * 
     * @param Fourmi&, Place, Place
     * 
     * @return
     * 
     * @confidence 
     **/
    void deplaceFourmi(Fourmi &f, Place p1, Place p2);
};


struct Data {
    
    //Attributs :
    vector<Nid> nids;
    EnsCoord sucres;
    Grille grille;

    Data();
    
    //Fonctions membres :
    
    /**
     * get the nest index situated at <c>
     * 
     * @param Coord
     * 
     * @return int
     * 
     * @confidence 2
     **/
    int numNid(Coord a) const;
    
    /**
     *  return the set of coords of all nests
     * 
     * @param
     * 
     * @return EnsCoord
     * 
     * @confidence 
     **/
    EnsCoord coordNids() const;
};

/**
* Compute the rotation needed between 2 vectors
* 
* @param Place, Place
* 
* @return array<int,2>
* 
* @confidence 
**/
array<int,2> calculeRotation(Place p1, Place p2);

/**
* Moove ant <f> from <p1> to <p2>
* 
* @param Fourmi&, p1&, p2&
* 
* @return
* 
* @confidence 2
**/
void bougeFourmi(Fourmi &f, Place &p1, Place &p2);

#endif