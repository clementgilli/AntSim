#include "../models/place.hpp"
#include "../views/affichage.hpp"

struct Manager {

    Data DONNEES;
    Display Fenetre;
    bool SEPAREMUR = false;
    
    /**
     * genere des coordonnées aléatoires pour les 4 nids
     * repartis dans 4 zones définies équitablement
     * 
     * @return EnsCoord 
     * 
     * @confidence 2
     **/
    EnsCoord genereCoordNid();

    /**
     * genere des coordonnées qui ne sont pas dans l'ensemble donnée
     * 
     * @param present un EnsCoord
     * 
     * @return EnsCoord
     * 
     * @confidence 2
     **/
    Coord genereCoordVide(EnsCoord present);

    /**
     * genere les coordonnes des fourmis autour d'un nid
     * 
     * @param n un nid
     * 
     * @return EnsCoord
     * 
     * @confidence 2
     **/
    EnsCoord genereCoordFourmi(Nid n);

    /**
     * regarde si une fourmi pour charger un sucre
     * 
     * @param f une fourmi
     * 
     * @param p1 une place
     * 
     * @param p2 une autre place
     * 
     * @return bool
     * 
     * @confidence 2
     **/
    bool peutChargerSucre(Fourmi f, Place p1, Place p2);

    /**
     * fourmi charge sucre
     * 
     * @param f &une fourmi
     * 
     * @param p1 &une place
     * 
     * @param p2 &une autre place
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void chargeSucre(Fourmi &f, Place &p1, Place &p2);

    /**
     * supprime une fourmi des données
     * 
     * @param f une fourmi
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void mortFourmi(Fourmi f);

    /**
     * met à jour les données d'une fourmi
     * 
     * @param f &une fourmi
     * 
     * @param g &la grille
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void majUneFourmi(Fourmi &f, Grille &g);

    /**
     * met à jour toutes les fourmis
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void majEnsFourmi();

    /**
     * regarde si une fourmi peut tuer une fourmi sur une place adjacente
     * si oui, elle le fait
     * 
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 1
     **/    
    bool regle1(Fourmi &f, Place &p1, Place &p2);

    /**
     * regarde si une fourmi cherche du sucre et la place adjacente contient du sucre
     * si oui, elle charge le sucre et pose un phero sucre de sa couleur
     * 
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle2(Fourmi &f, Place &p1, Place &p2);

    /**
     * regarde si une fourmi rentre au nid et la place adjacente contient un nid
     * si oui, elle pose son sucre
     * 
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle3(Fourmi &f, Place &p1, Place &p2);

    /**
     * permet à la fourmi de rentrer au nid en suivant phero nid
     *
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle4(Fourmi &f, Place &p1, Place &p2);

    /**
     * la fourmi cherche une sucre et est sur une piste (elle suit la piste)
     *
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle5(Fourmi &f, Place &p1, Place &p2);

    /**
     * la fourmi cherche une sucre et est sur une piste (elle suit la piste)
     * 
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle6(Fourmi &f, Place &p1, Place &p2);

    /**
     * la fourmi se deplace aleatoirement pour essayer de trouver un sucre
     * 
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool regle7(Fourmi &f, Place &p1, Place &p2);

    /**
     * regarde si une fourmi valide une regle par ordre de priorité et l'applique (de 1 à 7)
     * 
     * @param r &un nombre correspondant à une regle
     * @param f &une fourmi
     * @param p1 &une place
     * @param p2 &une autre place
     * @return bool
     * 
     * @confidence 2
     **/    
    bool condition_n(int r, Fourmi &f, Place &p1, Place &p2);


    void afficheColonies() const;
    void affiche_nids();
    void affiche_pheroNid();
    void affiche_pheroSucre();
    void manageNidEtSucre();
    void SummonFourmi(Nid &n);
    void rajouteSucre(EnsCoord objets);
    void supprimeSucre(Place &p);
    void majSucre();
    void majWall();
    void supprimeNid(Nid &n);

    public:
    
    Manager();
    
    Data get_donnees() const;
    
    void start();

};

int randomNumber(int a, int b);