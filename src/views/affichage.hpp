#include "models/place.hpp"
#include <SFML/Graphics.hpp>


class Display {

    sf::RenderWindow fenetre;
    sf::Texture tex;
    sf::Sprite sprite;

    int positionX = -1;
    int positionY = -1;
    
    long delayMax = 1e8;

    bool sucreR = false;
    bool nidR = false;
    bool sucreG = false;
    bool nidG = false;
    bool sucreB = false;
    bool nidB = false;
    bool sucreY = false;
    bool nidY = false;

    public:

    Display();

    /**
     * Getter position x de la souris
     * 
     * @return int
     * 
     * @confidence 4
     **/
    int sourisX();
    
    /**
     * Getter position y de la souris
     * 
     * @return int
     * 
     * @confidence 4
     **/
    int sourisY();

    /**
     * Getter delais du programme
     * 
     * @return long
     * 
     * @confidence 4
     **/
    long delais();

    /**
     * Getter pour phero sucres rouge
     * 
     * @return bool
     * 
     * @confidence 4
     **/

    bool sucreR_on();

    /**
     * Getter pour phero nid rouge
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool nidR_on();

    /**
     * Getter pour phero sucre vert
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool sucreG_on();

    /**
     * Getter pour phero nid vert
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool nidG_on();

    /**
     * Getter pour phero sucres bleu
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool sucreB_on();

    /**
     * Getter pour phero nid bleu
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool nidB_on();

    /**
     * Getter pour phero sucres jaune
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool sucreY_on();

    /**
     * Getter pour phero nid jaune
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool nidY_on();

    /**
     * dessine un cercle centré en (x,y) de couleur coul
     * 
     * @param x coord x 
     * @param y coord y
     * @param coul couleur du cercle
     * @return void
     * 
     * @confidence 4
     **/
    void cercle(int x, int y,sf::Color coul);

    /**
     * dessine un petit carré avec coin supérieur gauche en (x,y) de couleur coul
     * 
     * @param x coord x 
     * @param y coord y
     * @param coul couleur du cercle
     * @return void
     * 
     * @confidence 2
     **/
    void carre(int x, int y,sf::Color coul);

    /**
     * dessine un moyen carré avec coin supérieur gauche en (x,y) de couleur coul
     * 
     * @param x coord x 
     * @param y coord y
     * @param coul couleur du cercle
     * @return void
     * 
     * @confidence 2
     **/
    void carre2(int x, int y,sf::Color coul);

    /**
     * dessine un grand carré avec coin supérieur gauche en (x,y) de couleur coul
     * 
     * @param x coord x 
     * @param y coord y
     * @param coul couleur du cercle
     * @return void
     * 
     * @confidence 2
     **/
    void carre3(int x, int y,sf::Color coul);

    /**
     * dessine un rectangle fin pour separer les stats de la simu
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void grille();
    
    /**
     * affiche le numero du tour
     * 
     * @param i numero du tour
     * @return void
     * 
     * @confidence 2
     **/
    void afficheTour(int i);

    /**
     * affiche les stats d'un nid
     * 
     * @param n un nid
     * @return void
     * 
     * @confidence 2
     **/
    void afficheStat(Nid n);

    /**
     * gère tous les evenements claviers et souris
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void manageEvent();

    /**
     * affiche la fenetre
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void affiche_grille();

    /**
     * creer la fenetre
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void init_affichage();

    /**
     * affiche une fourmi
     * 
     * @param f une fourmi
     * @return void
     * 
     * @confidence 2
     **/
    void affiche_fourmi(Fourmi f);

    /**
     * affiche un nid
     * 
     * @param m un nid
     * @return void
     * 
     * @confidence 2
     **/
    void dessine_nid(Nid m);

    /**
     * affiche phero nid d'une colonie
     * 
     * @param n un nid
     * @param g la grille
     * @return void
     * 
     * @confidence 2
     **/
    void dessine_pheroNid(Nid n, Grille g);

    /**
     * affiches les sucres
     * 
     * @param s ensemble de coordonnées des sucres
     * @return void
     * 
     * @confidence 2
     **/
    void affiche_sucre(EnsCoord s);

    /**
     * affiche les phero sucre d'une colonie
     * 
     * @param c une colonie
     * @param g la grille
     * @return void
     * 
     * @confidence 2
     **/
    void dessine_pheroSucre(Colonie c, Grille g);

    /**
     * dessine les murs
     * 
     * @param g la grille
     * @return void
     * 
     * @confidence 2
     **/
    void dessine_murs(Grille g);

    /**
     * clean la fenetre (permet d'actualiser tous les dessins)
     * 
     * @return void
     * 
     * @confidence 2
     **/
    void nettoye();

    /**
     * test si la fenetre est ouverte
     * 
     * @return bool
     * 
     * @confidence 4
     **/
    bool estOuverte();

    /**
     * converti un vecteur en un angle de rotation
     * 
     * @param vec un vecteur de coordonnées
     * @return void
     * 
     * @confidence 4
     **/
    float vectToRot(array<int,2> vec);
};


