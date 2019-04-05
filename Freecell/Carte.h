#pragma once
#include <iostream>
#include "CImg.h"
#include <string>

typedef enum { Coeur, Pique, Carreau ,Trefle}TypeCouleur;
typedef enum { As,Roi, Dame, Valet, Dix, Neuf, Huit, Sept, Six, Cinq, Quatre, Trois, Deux}TypeHauteur;

using namespace cimg_library;

class Carte: public CImg<unsigned char>

{
private:
	TypeCouleur Couleur_;
	TypeHauteur Hauteur_;
	int positionX;
	int positionY;


public:
	Carte(TypeCouleur Couleur, TypeHauteur Hauteur,std::string fileName);
	~Carte();
	void display();
	int getPosX();
	int getPosY();

};

