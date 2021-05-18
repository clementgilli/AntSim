#ifndef FOURMI_HPP
#define FOURMI_HPP

#include <vector>
#include<iostream>
#include <array>
using namespace std;

#include "coord.hpp"

enum class Colonie {Red,Green,Blue,Yellow};

class Fourmi {

    //Attributs
    Coord position;
    array<int,2> rotation;
    int num;
    Colonie color;
    int fatigue;
    bool sucre;

    public :
    //Constructeurs
    /**
     * Constructor for Fourmi
     * 
     * @param Coord, int, enum class Colonie
     * 
     * @return Fourmi
     * 
     * @confidence 5
     **/
    Fourmi(Coord a, int n, Colonie col);

    //Accès
    /**
     * getter coord de la fourmi
     * 
     * @param 
     * 
     * @return Coord 
     * 
     * @confidence 5
     **/
    Coord coord() const;
    /**
     * Getter numéro de fourmi
     * 
     * @param 
     * 
     * @return int
     * 
     * @confidence 5
     **/
    int numero() const;
    /**
     * Getter couleur de la colonie
     * 
     * @param 
     * 
     * @return type enum Colonie 
     * 
     * @confidence 5
     **/
    Colonie couleur() const;
     /**
     * Getter energie
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 
     **/
    int energie() const;
    /**
     * Getter oriented angle vector
     * 
     * @param 
     * 
     * @return array<int,2>
     * 
     * @confidence 2
     **/
    array<int,2> getRotation() const;

    //Prédicats
    /**
     * Predict if ant is holding sugar
     * 
     * @param 
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool porteSucre() const;
    /**
     * Predict if ant is looking for sugar
     * 
     * @param 
     * 
     * @return bool
     * 
     * @confidence 5
     **/
    bool chercheSucre() const;

    //Modifications
    /**
     * Setter, makes the ant held a sugar (if possible)
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void prendSucre();
    /**
     * Setter, make the ant throw a sugar (if possible)
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void poseSucre();
    /**
     *  Moove ant to a certain coord
     * 
     * @param Coord 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void deplace(Coord a);
    /**
     * rise ant's exhaust 
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void augmenteFatigue();
    /**
     * reset ant's exhaust
     * 
     * @param 
     * 
     * @return 
     * 
     * @confidence 5
     **/
    void repos();
    /**
     * Setter, oriented angle 
     * 
     * @param array<int,2>
     * 
     * @return 
     * 
     * @confidence 2
     **/
    void setRotation(array<int,2> rot);
    
};
#endif