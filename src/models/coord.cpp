#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

#include "coord.hpp"


//Constructeurs
Coord::Coord (int l, int c) {
    if (l > TAILLEGRILLE or c > TAILLEGRILLE or l < 0 or c < 0) {
        throw invalid_argument("Coordonnées invalides");
    }
    _lig = l;
    _col = c;
}

EnsCoord::EnsCoord(vector<Coord> tab): _ens{tab} {}


//Méthodes
int Coord::ligne() const { return _lig;}

int Coord::colonne() const{ return _col;}

int EnsCoord::taille() const { return _ens.size(); }

Coord EnsCoord::get_coord(int i) const {
    if (i < 0 or i > taille()) {
        throw invalid_argument("Indice incorrect");
    }
    return _ens[i];
}

int EnsCoord::position(Coord a) const {
    for (int i = 0; i < taille(); i++)
        if (get_coord(i) == a) return i;
    return -1;
}

bool EnsCoord::contient(Coord a) const {
    return position(a) != -1;
}

void EnsCoord::ajoute(Coord a) {
    if (contient(a))
        throw invalid_argument("Déjà présent dans l'ensemble");
    _ens.push_back(a);
}

void EnsCoord::supprime(Coord a) {
    if (not contient(a))
        throw invalid_argument("On ne peut pas supprimer un élément qui n'est pas dans l'ensemble");
    int i = position(a);
    int j = taille()-1;
    Coord tmp = get_coord(j);
    _ens[j] = a;
    _ens[i] = tmp;
    _ens.pop_back(); 
}

bool EnsCoord::estVide() const {
    return taille() == 0;
}

Coord EnsCoord::choixHasard() const{
    if (estVide())
        throw runtime_error("Ensemble vide !");
    int n= rand()%(taille()+1);
    return get_coord(n);
}

//Fonctions

int maxi(int a,int b){return (a > b) ? a : b;}

int mini(int a,int b){return (a > b) ? b : a;}

EnsCoord voisines(Coord n){
    int l = n.ligne();
    int c = n.colonne();
    int imin = maxi(l-1,0);
    int imax = mini(l+1,TAILLEGRILLE-1);
    int jmin = maxi(c-1,0);
    int jmax = mini(c+1,TAILLEGRILLE-1);
    EnsCoord ev({});
    for (int i = imin; i <= imax; i++){
        for (int j = jmin; j <= jmax; j++){
            ev.ajoute(Coord(i,j));
        }
    }
    if (ev.contient(n)) ev.supprime(n);
    return ev;
}


/* EnsCoord voisines(Coord n){
    int l = n.ligne();
    int c = n.colonne();
    int imin = maxi(l-1,0);
    int imax = mini(l+1,TAILLEGRILLE-1);
    int jmin = maxi(c-1,0);
    int jmax = mini(c+1,TAILLEGRILLE-1);
    EnsCoord ev({});
    for (int i = imin; i <= imax; i++){
        for (int j = jmin; j <= jmax; j++){
            if(i ==l or j==c){
                ev.ajoute(Coord(i,j));
            }
        }
    }
    if (ev.contient(n)) ev.supprime(n);
    return ev;
} */
//Opérateur
ostream &operator<<(ostream &out, const Coord &c) {
    out << "(" << c.ligne() << "," << c.colonne() << ")";
    return out;
}

bool operator==(const Coord a, const Coord b) {
    return a.ligne() == b.ligne() and a.colonne() == b.colonne();
}

bool operator!=(const Coord a, const Coord b) {
    return not (a == b);
}

ostream &operator<<(ostream &out, const EnsCoord &e) {
    out << "{";
    for (int i = 0; i < e.taille()-1; i++)
        out << e.get_coord(i) << ",";  
    out<< e.get_coord(e.taille()-1) << "}";
    return out;
}

bool operator==(const EnsCoord a,const EnsCoord b) {
    if (a.taille() != b.taille()) return false;
    EnsCoord t = a;
    for (int i = 0; i < a.taille(); i++) {
        Coord elem = a.get_coord(i);
        if (b.contient(elem)) t.supprime(elem);
    }
    return t.estVide();
}

bool operator!=(const EnsCoord a, const EnsCoord b){
    return not (a == b);
}

EnsCoord operator+(EnsCoord a, EnsCoord b){
    for (int i =0;i<b.taille();i++){
        a.ajoute(b.get_coord(i));
    }
    return a;
}