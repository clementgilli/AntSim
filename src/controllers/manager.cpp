#include <iostream>    
#include <sstream>   
#include <iomanip>    
#include <string>
#include <vector>
#include <array>
#include <stdexcept>   
#include <cmath>      
#include <ctime>
#include <cstdlib> 
#include <chrono>

#include "controllers/manager.hpp"


Manager::Manager() {}

Data Manager::get_donnees() const { return DONNEES;}

int randomNumber(int a, int b) {
    return rand()%(b-a+1) + a;
}

Coord Manager::genereCoordVide(EnsCoord present){
    Coord c{rand()%(TAILLEGRILLE),rand()%(TAILLEGRILLE)};
    while (present.contient(c)){
        c = Coord(rand()%(TAILLEGRILLE),rand()%(TAILLEGRILLE));
    }
    return c;
}

EnsCoord Manager::genereCoordNid() {

    int tmid = TAILLEGRILLE/2;

    Coord a = Coord(randomNumber(2,tmid-2),randomNumber(2,tmid-2));
    Coord b = Coord(randomNumber(tmid+2,TAILLEGRILLE-2),randomNumber(2,tmid-2));
    Coord c = Coord(randomNumber(2,tmid-2),randomNumber(tmid+2,TAILLEGRILLE-2));
    Coord d = Coord(randomNumber(tmid+2,TAILLEGRILLE-2),randomNumber(tmid+2,TAILLEGRILLE-2));
    return EnsCoord({a,b,c,d});
}

EnsCoord Manager::genereCoordFourmi(Nid n){
    EnsCoord vois = voisines(n.pos);
    int size= vois.taille();
    EnsCoord fourmis({});
    for (int i =0;i<4;i++){
        fourmis.ajoute(vois.get_coord(2*i));
    }
    return vois;
}

bool Manager::peutChargerSucre(Fourmi f, Place p1, Place p2) {
    return f.chercheSucre() and p2.contientSucre();
}

void Manager::chargeSucre(Fourmi &f, Place &p1, Place &p2) {
    f.prendSucre();
    p1.posePheroSucre(f.couleur());
}

void Manager::mortFourmi(Fourmi f) {
	vector<Fourmi> &maison = DONNEES.nids[int(f.couleur())].famille;
	int i = DONNEES.nids[int(f.couleur())].indiceFourmi(f.numero());
    int j = maison.size()-1;
    Fourmi tmp = maison[j];
    maison[j] = maison[i];
    maison[i] = tmp;
    maison.pop_back(); 
}

void Manager::majEnsFourmi() {
    int nbNids = DONNEES.nids.size();
    int nbFourmis;
    for (int i = 0; i < nbNids; i++) {
        nbFourmis = DONNEES.nids[i].famille.size();
        for (int j = 0; j < nbFourmis; j++) {
            majUneFourmi(DONNEES.nids[i].famille[j],DONNEES.grille);
        }
    }
}


bool Manager::regle1(Fourmi &f, Place &p1, Place &p2) {
    if (p2.numFourmi() == -1) return false;
    int n = p2.numFourmi();
    int coul = int(p2.couleurFourmi());
    int indice = DONNEES.nids[coul].indiceFourmi(n);
    Fourmi g = DONNEES.nids[coul].famille[indice];
    if ((f.energie() < g.energie()) and (f.couleur() != g.couleur())) {
            p2.enleveFourmi(DONNEES.nids[coul].famille[indice]);
            mortFourmi(DONNEES.nids[coul].famille[indice]);
            return true;
        }
        return false;
}


bool Manager::regle2(Fourmi &f, Place &p1, Place &p2) {
        
    if (f.chercheSucre() and p2.contientSucre()) {
        f.prendSucre();
        p1.posePheroSucre(f.couleur());
        p2.enleveSucre();
        supprimeSucre(p2);
        return true;
    }
    return false;
}


bool Manager::regle3(Fourmi &f, Place &p1, Place &p2) {
    Nid &n = DONNEES.nids[int(f.couleur())];
    if (f.porteSucre() and p2.contientNid() and (p2.pheroNid(f.couleur()) == 1)) {
        f.poseSucre();
        f.repos();
        n.augmenteScore(1);
        if (n.score()%20 == 0)
            SummonFourmi(n);
        return true;
    }
    return false;
}


bool Manager::regle4(Fourmi &f, Place &p1, Place &p2) {
   
    Nid n = DONNEES.nids[int(f.couleur())];
    if ( f.porteSucre() and p2.estVide() and p2.estPlusProcheNid(p1,n) ) {
        bougeFourmi(f,p1,p2);
        p2.posePheroSucre(f.couleur());
        return true;
    }
    return false;
}


bool Manager::regle5(Fourmi &f, Place &p1, Place &p2) {
    Nid n = DONNEES.nids[int(f.couleur())];
    if (f.chercheSucre() and p1.estSurUnePiste(f.couleur()) 
       and p2.estVide() and p2.estPlusLoinNid(p1,n) and p2.estSurUnePiste(f.couleur())) {
           bougeFourmi(f,p1,p2);
           return true;
       }
       return false;
}


bool Manager::regle6(Fourmi &f, Place &p1, Place &p2) {
    if (f.chercheSucre() and p2.estSurUnePiste(f.couleur()) and p2.estVide()) {
        bougeFourmi(f,p1,p2);
        return true;
    }
    return false;
}


bool Manager::regle7(Fourmi &f, Place &p1, Place &p2) {
    
    if (f.chercheSucre() and p2.estVide()) {
        bougeFourmi(f,p1,p2);
        return true;
    }
    return false;
}


bool Manager::condition_n(int r, Fourmi &f, Place &p1, Place &p2) {
    switch(r) {
        case 1: return regle1(f,p1,p2);
        case 2: return regle2(f,p1,p2);
        case 3: return regle3(f,p1,p2);
        case 4: return regle4(f,p1,p2); 
        case 5: return regle5(f,p1,p2);
        case 6: return regle6(f,p1,p2);
        case 7: return regle7(f,p1,p2);
        default: return false;
    }
}


void Manager::majUneFourmi(Fourmi &f, Grille &g) {
    Coord cf = f.coord();
    Fenetre.affiche_fourmi(f);
    Place pf = g.chargePlace(cf);
    EnsCoord voisCoord = voisines(cf);
    for (int i=1; i < 8; i++) {
        for (int j = 0; j < voisCoord.taille(); j++) {
            Place vois = g.chargePlace(voisCoord.get_coord(rand()%voisCoord.taille()));
            if (condition_n(i,f,pf,vois)) {
                condition_n(i,f,pf,vois);
                g.rangePlace(pf);
                g.rangePlace(vois);
                return;
            }
        }
    }
}


void Manager::afficheColonies() const {
    for (int i = 0; i <= 3; i++) {
            std::cout << "Colonie : " << int(DONNEES.nids[i].color) <<endl;
            int taille = DONNEES.nids[i].famille.size();
            for (int j = 0; j < taille; j++) {
                std::cout << DONNEES.nids[i].famille[j].numero() << " ";
            }
            std::cout << endl;
        }
}

void Manager::affiche_nids() {
    for (int i = 0; i < 4; i++) {
        Nid n = DONNEES.nids[i];
        Fenetre.dessine_nid(n);
    }  
}

void Manager::affiche_pheroNid() {
    for (int i = 0; i <= 3; i++) {
        Fenetre.dessine_pheroNid(DONNEES.nids[i],DONNEES.grille);
    }
}

void Manager::affiche_pheroSucre() {
    for (int i = 0; i <= 3; i++)
        Fenetre.dessine_pheroSucre(DONNEES.nids[i].color,DONNEES.grille);
}

void Manager::manageNidEtSucre() {
    if (Fenetre.sucreR_on())
        Fenetre.dessine_pheroSucre(DONNEES.nids[0].color,DONNEES.grille);
    if (Fenetre.nidR_on()) 
        Fenetre.dessine_pheroNid(DONNEES.nids[0],DONNEES.grille);
    
    if (Fenetre.sucreG_on())
        Fenetre.dessine_pheroSucre(DONNEES.nids[1].color,DONNEES.grille);
    if (Fenetre.nidG_on()) 
        Fenetre.dessine_pheroNid(DONNEES.nids[1],DONNEES.grille);
    
    if (Fenetre.sucreB_on())
        Fenetre.dessine_pheroSucre(DONNEES.nids[2].color,DONNEES.grille);
    if (Fenetre.nidB_on()) 
        Fenetre.dessine_pheroNid(DONNEES.nids[2],DONNEES.grille);
    
    if (Fenetre.sucreY_on())
        Fenetre.dessine_pheroSucre(DONNEES.nids[3].color,DONNEES.grille);
    if (Fenetre.nidY_on()) 
        Fenetre.dessine_pheroNid(DONNEES.nids[3],DONNEES.grille);
}


void Manager::SummonFourmi(Nid &n){
	Fourmi f{ genereCoordFourmi(n).get_coord(0),n.indiceMax()+1,n.color};
    n.famille.push_back(f);
}

void Manager::rajouteSucre(EnsCoord objets) {
    if (DONNEES.sucres.taille() == 2) return;
    
    int nbNids = DONNEES.nids.size();
    int nbFourmis;
    for (int i = 0; i < nbNids; i++) {
        nbFourmis = DONNEES.nids[i].famille.size();
        for (int j = 0; j < nbFourmis; j++) {
            objets.ajoute(DONNEES.nids[i].famille[j].coord());
        }
    }
    if (DONNEES.sucres.taille() == 1) {
        Coord coordSucre = genereCoordVide(objets);
        while(objets.contient(coordSucre) or DONNEES.sucres.contient(coordSucre)) {
            coordSucre = genereCoordVide(objets);
        }
        DONNEES.sucres.ajoute(coordSucre);
        Place p = DONNEES.grille.chargePlace(coordSucre);
        p.poseSucre();
        DONNEES.grille.rangePlace(p);
    }
    if (DONNEES.sucres.taille() == 0) {
        for (int i = 0; i < 2; i++) {
            Coord coordSucre = genereCoordVide(objets);
            while(objets.contient(coordSucre) or DONNEES.sucres.contient(coordSucre)) {
                coordSucre = genereCoordVide(objets);
            }
            objets.ajoute(coordSucre);
            DONNEES.sucres.ajoute(coordSucre);
            Place p = DONNEES.grille.chargePlace(coordSucre);
            p.poseSucre();
            DONNEES.grille.rangePlace(p);
        }
    }
}

void Manager::supprimeSucre(Place &p){
    if (not p.contientSucre()){
        DONNEES.sucres.supprime(p.coord());
    }
}

void Manager::majWall() {
    if (Fenetre.sourisX() >= 0 and Fenetre.sourisY() >= 0 and Fenetre.sourisX() < 700 and Fenetre.sourisY() < 700) {
        int x = Fenetre.sourisX();
        int y = Fenetre.sourisY();
        Place p = DONNEES.grille.chargePlace(Coord(y,x));
        p.setWall();
        DONNEES.grille.rangePlace(p);
    }
}

/* void Manager::supprimeNid(Nid &n){
    Place p = DONNEES.grille.g[n.pos.colonne()*TAILLEGRILLE + n.pos.ligne()];
    int j = DONNEES.nids.size()-1;
	Nid tmp = DONNEES.nids[DONNEES.numNid(p.coord())];
	DONNEES.nids[DONNEES.numNid(p.coord())]=DONNEES.nids[j];
    DONNEES.nids[j] =tmp;
    DONNEES.nids.pop_back();
    p.supprimeNid();
    DONNEES.grille.rangePlace(p);
} */

void Manager::start() {

    //on initialise les 4 sucres et 4 nids avec 5 fourmis dedans

    EnsCoord objets({});
    EnsCoord ensembleNid = genereCoordNid();
    objets = objets + ensembleNid;
    for (int i = 0; i <= 3; i++) {
        Nid n = {0,ensembleNid.get_coord(i),Colonie(i),{}};
        DONNEES.nids.push_back(n);
        EnsCoord eF = genereCoordFourmi(n);
        objets = objets + eF;        
        for (int j = 0; j < 5; j++) {
            Coord cF = eF.get_coord(j);
            Fourmi fou = Fourmi(cF,j,Colonie(i));
            DONNEES.nids[i].famille.push_back(fou);
        }    
    }
    
    for (int i = 0; i < 2; i++) {
        Coord coordSucre = genereCoordVide(objets);
        DONNEES.sucres.ajoute(coordSucre);
    }

    cout << " Nid : " << DONNEES.coordNids() << endl;
    cout << " Sucre : " << DONNEES.sucres << endl;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j < 5; j++) {
            cout << " Fourmi : " << DONNEES.nids[i].famille[j].coord() << " ";
        }
        cout << endl;
    }

    //on initialise la grille avec les nids et les sucres
    DONNEES.grille.initialiseGrille(DONNEES.nids,DONNEES.sucres,DONNEES.coordNids());

    if (SEPAREMUR) {
        for (int i = 0; i < 30; i++) {
            Place p1 = DONNEES.grille.chargePlace((Coord(i,15)));
            p1.setWall();
            DONNEES.grille.rangePlace(p1);
        }
        for (int i = 0; i < 30; i++) {
            Place p1 = DONNEES.grille.chargePlace((Coord(15,i)));
            p1.setWall();
            DONNEES.grille.rangePlace(p1);
        }
    }
    cout << SEPAREMUR << endl;
    //on initialise les pheromones de nids
    for (int i = 0; i <= 3; i++)
        DONNEES.grille.linearisePheroNid(Colonie(i));
    
    objets = DONNEES.coordNids() + DONNEES.sucres;

    int c;
    int num = 0;
    Fenetre.init_affichage();
    std::chrono::high_resolution_clock::time_point previousTime = std::chrono::high_resolution_clock::now();
    while (Fenetre.estOuverte()) {
        Fenetre.manageEvent();
        Fenetre.affiche_grille();
        Fenetre.affiche_sucre(DONNEES.sucres);
        affiche_nids();
        long delay = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - previousTime).count();
        if (delay < Fenetre.delais())
            continue;
        previousTime = std::chrono::high_resolution_clock::now();
        Fenetre.nettoye();
        Fenetre.afficheTour(num);
        for (int i =0;i<DONNEES.nids.size();i++){
            Fenetre.afficheStat(DONNEES.nids[i]);
        }
        for (int i = 0; i <= 3; i++)
            DONNEES.grille.linearisePheroNid(Colonie(i));
        //afficheColonies();
        manageNidEtSucre();
        majWall();
        Fenetre.dessine_murs(DONNEES.grille);
        Fenetre.affiche_sucre(DONNEES.sucres);
        affiche_nids();
        majEnsFourmi();
        rajouteSucre(objets);
        DONNEES.grille.diminuePheroSucre();
        num++;
    }

}