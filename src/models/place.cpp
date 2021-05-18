#include "place.hpp"



// Constructeur 


Data::Data(): nids{}, sucres({}), grille() {}

Place::Place(): pos{Coord(0,0)}{
	qteSucre = 0;
	nid = NULL;
	phS = {0,0,0,0};
	phN = array<float,4>();
	for (int i=0;i<4;i++){
		phN[i]=0;
	}
	f = NULL;
}
Place::Place(Coord coo): pos{coo} {
	qteSucre = 0;
	nid = NULL;
	phS = {0,0,0,0};
	phN = array<float,4>();
	for (int i=0;i<4;i++){
		phN[i]=0;
	}
	f = NULL;
}

Grille::Grille():g{{}}{
	for (int i=0;i<TAILLEGRILLE;i++){
		for (int j=0;j<TAILLEGRILLE;j++){
			g[j*TAILLEGRILLE+i]=Place(Coord(i,j));
		}
	}
}

//Getters :

Coord Place::coord() const {return pos;}

int Place::pheroSucre(Colonie color) const {return phS[int(color)];}

float Place::pheroNid(Colonie color) const {return phN[int(color)];}

int Place::numFourmi() const {
	if (f == NULL) return -1;
	return f->numero();
}

Colonie Place::couleurFourmi() const {
	if (f == NULL)
		throw runtime_error("La fourmi n'existe pas");
	return f->couleur();
}

bool Place::contientMur() const { return wall;}

Place Grille::chargePlace(Coord c) const {
	return g[c.colonne()*TAILLEGRILLE+c.ligne()];
}


//Prédicats :

bool Place::contientSucre() const {return qteSucre > 0;}

bool Place::contientNid() const {return nid != NULL;}

bool Place::estVide() const {return not(contientMur()) and not(contientSucre()) and not(contientNid()) and numFourmi()==-1;}

bool Place::estSurUnePiste(Colonie color) const {return pheroSucre(color)>0 ;}

bool Place::estPlusProcheNid(Place p2, Nid n) const {
	return pheroNid(n.color) > p2.pheroNid(n.color);
}

bool Place::estPlusLoinNid(Place p2, Nid n) const {
	return not estPlusProcheNid(p2,n);
}

//Modifications :

void Place::poseSucre(){
	if (not (estVide())) {
		throw runtime_error("Case non vide !");
	}
	qteSucre=1;
	//DONNEES.sucres.ajoute(pos);
}

void Place::enleveSucre(){
	if (not(contientSucre())){
		throw runtime_error("il n y a pas de sucre dans la case !");
	}
	qteSucre-=0.04;
	//DONNEES.sucres.supprime(pos);
}

void Place::setWall() {
	wall = true;
}

Nid *initialiseNid(Coord p, Colonie c) {
    Nid *n = (Nid *)malloc(sizeof(Nid));
	n->pos = p;
	n->color = c;
	n->famille = {};
	n->pts =0;
	return n;
}

void Place::poseNid(Colonie couleur){
	if (not(estVide())){
		throw runtime_error("la case n'est pas vide !");
	}
	nid = initialiseNid(pos,couleur);
	//DONNEES.nids.push_back(*nid);
}

void Place::supprimeNid(){
	if (not contientNid()){
		throw runtime_error("Il n'y a aucun nid à supprimer !");
	}
	//int j = DONNEES.nids.size()-1;
	//Nid tmp = DONNEES.nids[DONNEES.numNid(pos)];
	//DONNEES.nids[DONNEES.numNid(pos)]=DONNEES.nids[j];
    //DONNEES.nids[j] =tmp;
    //DONNEES.nids.pop_back(); 
	free(nid);
	nid=NULL;
}



void Place::poseFourmi(Fourmi &fou){
	if(not estVide()){
		throw runtime_error("La place n'est pas vide !");
	}
	f = &fou;
	fou.deplace(coord());
}

void Place::enleveFourmi(Fourmi &fou){
	//if (f==NULL)
	//	throw runtime_error("Il n y a pas de fourmi");
	f=NULL;
}

void Place::posePheroNid(float intensite, Colonie couleur) {
	phN[int(couleur)] = intensite;
}

void Place::posePheroSucre(Colonie color) {
	phS[int(color)] = 255;
}

void Place::diminuePheroSucre(Colonie color) {
	if (phS[int(color)] >= int(2.5*TAILLEGRILLE/20))
		phS[int(color)] -= int(2.5*TAILLEGRILLE/20);
	else phS[int(color)] = 0;
}

int Data::numNid(Coord a) const {
    for (int i = 0; i < int(nids.size()); i++)
        if (nids[i].pos == a) return i;
    throw invalid_argument("Il n'y a pas de nid ici");
}

EnsCoord Data::coordNids() const {
	EnsCoord e = EnsCoord({});
	for (Nid i : nids)
		e.ajoute(i.pos);
	return e;
}


void Grille::rangePlace(Place p){ 
	g[p.coord().colonne()*TAILLEGRILLE+p.coord().ligne()] = p; 
}

void Grille::placeNid(EnsCoord e){ 
	for (int i=0; i<e.taille();i++){
		Place p = chargePlace(e.get_coord(i));
		p.poseNid(Colonie(i));
		rangePlace(p);
	}
}

void Grille::placeSucre(EnsCoord e){
	for (int i=0; i<e.taille();i++){
		Place p = chargePlace(e.get_coord(i));
		p.poseSucre();
		rangePlace(p);
	}
}

void Grille::placeFourmi(Nid &t){
	for (int i=0;i<int(t.famille.size());i++){
		Place p =chargePlace(t.famille[i].coord());
		p.poseFourmi(t.famille[i]);
		rangePlace(p);
	}
}

void Grille::initialiseGrille(vector<Nid> &t, EnsCoord sucres, EnsCoord nids){	
	for (int i = 0; i < int(t.size()); i++) {
		placeFourmi(t[i]);
		Coord c=t[i].pos;
		int k = c.colonne()*TAILLEGRILLE+c.ligne();
		g[k].posePheroNid(1.,t[i].color);
	}	
	placeNid(nids);
	placeSucre(sucres);

}



void Grille::linearisePheroNid(Colonie couleur) {
	bool stable = false;
	while (not stable) {
  		stable = true;
  		for (int i = 0; i < TAILLEGRILLE; i++) {
			for (int j = 0; j < TAILLEGRILLE; j++) {
				Coord c = Coord(i,j);
    			Place p = chargePlace(c);
				if (p.contientMur()) {
					p.posePheroNid(0.,couleur);
					rangePlace(p);
				}else {
    				if (p.pheroNid(couleur) < 1) {
      					EnsCoord coordVois = voisines(c);
      					float maxPhero = 0;
      					for (int k = 0; k < coordVois.taille(); k++) {
						  	Place voisin = chargePlace(coordVois.get_coord(k));
						  	maxPhero = max(maxPhero, voisin.pheroNid(couleur));
    					}
						maxPhero = maxPhero - 1. / TAILLEGRILLE;
						if (maxPhero > p.pheroNid(couleur)) {
							p.posePheroNid(maxPhero,couleur);
							rangePlace(p);
							stable = false;
						}
					}
  				}
			}
		}
	}
}


void Grille::diminuePheroSucre() {
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			Place p = chargePlace(Coord(i,j));
			for (int k=0;k<4;k++){
				p.diminuePheroSucre(Colonie(k));
			}
			rangePlace(p);
		}
	}
}

array<int,2> calculeRotation(Place p1, Place p2){
	int x,y;
	x = p2.coord().ligne()-p1.coord().ligne();
	y = p2.coord().colonne()-p1.coord().colonne();
	array<int,2> rot = {x,y};
	return rot;
}

void bougeFourmi(Fourmi &f, Place &p1, Place &p2) {
    if (not p2.estVide()){
		throw invalid_argument("La place d'arrivée n'est pas vide");
	}
	p1.enleveFourmi(f);
	p2.poseFourmi(f);
    f.deplace(p2.coord());
	f.setRotation(calculeRotation(p1,p2));
}


void Grille::deplaceFourmi(Fourmi &f, Place p1, Place p2){
	if (not p2.estVide())
		throw invalid_argument("La place d'arrivée n'est pas vide");
	bougeFourmi(f,p1,p2);
	rangePlace(p1);
	rangePlace(p2);	
}


int Nid::indiceFourmi(int numeroFourmi) {
	if (numeroFourmi == -1)
		throw invalid_argument("Il n'y a pas d'indice pour une fourmi qui n'existe pas");
	for (int i = 0; i < int(famille.size()); i++) {
		if (famille[i].numero() == numeroFourmi) return i;
	}
	return -1;
}

int Nid::score(){
	return pts;
}
void Nid::augmenteScore(int n){
	pts += n;
}

int Nid::indiceMax(){
	int maxi = 0;
	for (int i=0;i<famille.size();i++){
		maxi=max(maxi,famille[i].numero());
	}
	return maxi;
}