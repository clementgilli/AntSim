#include "views/affichage.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


//si pb lors de executer, faire commande suivante :
// export DISPLAY=:0


Display::Display() {
    tex.loadFromFile("./Images/ant.png");
    tex.setSmooth(true);
    sprite.setTexture(tex);
	sprite.setScale(0.2,0.2);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}

int Display::sourisX() { return positionX; }
int Display::sourisY() { return positionY; }

bool Display::sucreR_on() { return sucreR; }
bool Display::nidR_on() { return nidR; }

bool Display::sucreG_on() { return sucreG; }
bool Display::nidG_on() { return nidG; }

bool Display::sucreB_on() { return sucreB; }
bool Display::nidB_on() { return nidB; }

bool Display::sucreY_on() { return sucreY; }
bool Display::nidY_on() { return nidY; }

long Display::delais() { return delayMax; }

void Display::cercle(int x, int y,sf::Color coul)
{
    sf::CircleShape forme(3);
    forme.setFillColor(coul);
    forme.setPosition(x,y);
    fenetre.draw(forme);
}

void Display::carre(int x, int y,sf::Color coul)
{
    sf::RectangleShape forme;
    forme.setSize(sf::Vector2f(24, 24));
    forme.setFillColor(coul);
    forme.setPosition(x,y);
    fenetre.draw(forme);
}

void Display::carre2(int x, int y,sf::Color coul)
{
    sf::RectangleShape forme;
    forme.setSize(sf::Vector2f(int(35), int(35)));
    forme.setFillColor(coul);
    forme.setPosition(x,y);
    fenetre.draw(forme);
}

void Display::carre3(int x, int y,sf::Color coul)
{
    sf::RectangleShape forme;
    forme.setSize(sf::Vector2f(int(47), int(47)));
    forme.setFillColor(coul);
    forme.setPosition(x,y);
    fenetre.draw(forme);
}

void Display::grille() 
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(1, 700));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineThickness(1);
    sf::Vector2u t = fenetre.getSize();
    rectangle.setPosition(700,0);
    fenetre.draw(rectangle);
}

void Display::afficheTour(int i) {
    sf::Font font;
    font.loadFromFile("./Fonts/police.ttf");
    string tour = "Tour " + std::to_string(i);
    sf::Text texte(tour,font,30);
    int s = texte.getLocalBounds().width;
    texte.setPosition(850 - s/2,30);
    texte.setFillColor(sf::Color::White);
    texte.setStyle(sf::Text::Bold);
    fenetre.draw(texte);
}

void Display::afficheStat(Nid n) {
    int fourmis = n.famille.size();
    int sucres = n.score();
    int coul = int(n.color);
    sf::Font font;
    font.loadFromFile("./Fonts/police.ttf");
    string stats = "fourmis : " + std::to_string(fourmis) + "    sucres : " + std::to_string(sucres);
    sf::Text texte(stats,font,15);
    texte.setFillColor(sf::Color::White);
    sf::Text rouge("Rouge",font,20);
    sf::Text vert("Vert",font,20);
    sf::Text bleu("Bleu",font,20);
    sf::Text jaune("Jaune",font,20);
    switch (coul)
        {
        case 0:
        rouge.setPosition(730,120);
        rouge.setFillColor(sf::Color::Red);
        rouge.setStyle(sf::Text::Bold);
        texte.setPosition(730,150);
        fenetre.draw(texte);
        fenetre.draw(rouge);
            break;
        case 1:
        vert.setPosition(730,250);
        vert.setFillColor(sf::Color::Green);
        vert.setStyle(sf::Text::Bold);
        texte.setPosition(730,280);
        fenetre.draw(texte);
        fenetre.draw(vert);
            break;
        case 2:
        bleu.setPosition(730,380);
        bleu.setFillColor(sf::Color::Blue);
        bleu.setStyle(sf::Text::Bold);
        texte.setPosition(730,410);
        fenetre.draw(texte);
        fenetre.draw(bleu);
            break;
        case 3:
        jaune.setPosition(730,510);
        jaune.setFillColor(sf::Color::Yellow);
        jaune.setStyle(sf::Text::Bold);
        texte.setPosition(730,540);
        fenetre.draw(texte);
        fenetre.draw(jaune);
            break;
        }
}



void Display::manageEvent()
{
    sf::Event _event;
    sf::Vector2i localPosition;
    sf::Vector2u t = fenetre.getSize();
    while (fenetre.pollEvent(_event))
        switch (_event.type)
        {
        case sf::Event::Closed:
            fenetre.close();
            break; 
        case sf::Event::MouseButtonPressed:
            localPosition = sf::Mouse::getPosition(fenetre);
            positionX = localPosition.x * TAILLEGRILLE/700;
            positionY = localPosition.y * TAILLEGRILLE/700;
            break;
        case sf::Event::KeyPressed:
            switch (_event.key.code)
            {
            case sf::Keyboard::A:
                sucreR = not(sucreR);
                break;
            case sf::Keyboard::Q:
                nidR = not(nidR);
                break;
            case sf::Keyboard::Z:
                sucreG = not(sucreG);
                break;
            case sf::Keyboard::S:
                nidG = not(nidG);
                break;
            case sf::Keyboard::E:
                sucreB = not(sucreB);
                break;
            case sf::Keyboard::D:
                nidB = not(nidB);
                break;
            case sf::Keyboard::R:
                sucreY = not(sucreY);
                break;
            case sf::Keyboard::F:
                nidY = not(nidY);
                break;
            case sf::Keyboard::Up:
                delayMax /= 10;
                break;
            case sf::Keyboard::Down:
                delayMax *= 10;
                break;
            }
        }
}

float Display::vectToRot(array<int,2> vec) {
    if (vec[0] == 1) return 90 - vec[1]*45 +90;
    if (vec[0] == 0) return 90 - vec[1]*90 +90;
    else return 270 + vec[1]*45 + 90;   
}




void Display::affiche_grille() {
    grille();
    //sf::sleep(sf::Time(sf::milliseconds(60)));
    fenetre.display();
}

void Display::init_affichage() {
    fenetre.create(sf::VideoMode(1000, 700), "ant_sim");
}

void Display::affiche_fourmi(Fourmi f) {
    int coul = int(f.couleur());
    int x = f.coord().colonne()*700/TAILLEGRILLE;
    int y = f.coord().ligne()*700/TAILLEGRILLE;
    x += 700/60;
    y += 700/60;
    switch (coul)
        {
        case 0:
            sprite.setPosition(x,y);
            sprite.setColor(sf::Color::Red);
            sprite.setRotation(vectToRot(f.getRotation()));
            fenetre.draw(sprite);
            //cercle(x,y,sf::Color::Red);
            break;
        case 1:
            sprite.setPosition(x,y);
            sprite.setColor(sf::Color::Green);
            sprite.setRotation(vectToRot(f.getRotation()));
            fenetre.draw(sprite);
            //cercle(x,y,sf::Color::Green);
            break;
        case 2: 
            sprite.setPosition(x,y);
            sprite.setColor(sf::Color::Blue);
            sprite.setRotation(vectToRot(f.getRotation()));
            fenetre.draw(sprite);  
            //cercle(x,y,sf::Color::Blue);
            break;
        case 3: 
            sprite.setPosition(x,y);
            sprite.setColor(sf::Color::Yellow);
            sprite.setRotation(vectToRot(f.getRotation()));
            fenetre.draw(sprite);  
            //cercle(x,y,sf::Color::Yellow);
            break;
        }
}

void Display::dessine_nid(Nid m) {
    int coul = int(m.color);
    int x = m.pos.colonne()*700/TAILLEGRILLE;
    int y = m.pos.ligne()*700/TAILLEGRILLE;
    switch (coul)
        {
        case 0: carre2(x,y,sf::Color::Red);
            break;
        case 1: carre2(x,y,sf::Color::Green);
            break;
        case 2: carre2(x,y,sf::Color::Blue);
            break;
        case 3: carre2(x,y,sf::Color::Yellow);
            break;
        }
}

void Display::affiche_sucre(EnsCoord s) {
    int x,y;
    for (int i = 0; i < s.taille(); i++) {
        x = s.get_coord(i).colonne()*700/TAILLEGRILLE;
        y = s.get_coord(i).ligne()*700/TAILLEGRILLE;
        carre(x,y,sf::Color::White);
    }   
}


void Display::dessine_pheroNid(Nid n, Grille g) {
    int coul = int(n.color);
    float pheroNid;
    int x,y;
    sf::Color rouge2(255,0,0,150);
    sf::Color vert2(0,255,0,150);
    sf::Color bleu2(0,0,255,150);
    sf::Color jaune2(255,255,0,150);
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            pheroNid = g.chargePlace(Coord(i,j)).pheroNid(Colonie(coul));
            x = i*700/TAILLEGRILLE;
            y = j*700/TAILLEGRILLE;
            switch (coul)
            {
            case 0:
                rouge2.r = 255*pheroNid;
                rouge2.a = 70*pheroNid;
                carre3(y,x,rouge2);
                break;
            case 1:
                vert2.a = 80*pheroNid;
                carre3(y,x,vert2);
                break;
            case 2:
                bleu2.b = 255*pheroNid;
                bleu2.a = 70*pheroNid;
                carre3(y,x,bleu2);
                break;
            case 3: 
                jaune2.a = 80*pheroNid;
                carre3(y,x,jaune2);
                break;
            }
        }
    }    
}

void Display::dessine_pheroSucre(Colonie c, Grille g) {
    int coul = int(c);
    int pheroSucre;
    int x,y;
    sf::Color color(0,0,0,150);
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.a = 150;
            pheroSucre = g.chargePlace(Coord(i,j)).pheroSucre(c);
            x = i*700/TAILLEGRILLE + 700/60;
            y = j*700/TAILLEGRILLE + 700/60;
            if (pheroSucre == 0) {
                color.a = 0;
                carre(y,x,color);
            }
            switch (coul)
            {
            case 0:
                color.r = pheroSucre;
                color.a = 155;
                carre(y,x,color);
                break;
            case 1:
                color.g = pheroSucre;
                carre(y,x,color);
                break;
            case 2: 
                color.b = pheroSucre;
                carre(y,x,color);
                break;
            case 3: 
                color.r = pheroSucre;
                color.g = pheroSucre;
                carre(y,x,color);
                break;
            }
        }
    }
}

void Display::dessine_murs(Grille g) {
    bool mur;
    sf::Color grey(169,169,169);
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            mur = g.chargePlace(Coord(j,i)).contientMur();
            if (mur) {
                int x = i*700/TAILLEGRILLE;
                int y = j*700/TAILLEGRILLE;
                carre(x,y,grey);
            }
        }
    }
}

void Display::nettoye() {
    fenetre.clear();
}

bool Display::estOuverte() {
    return fenetre.isOpen();
}