#pragma once
#include <iostream>
#include "CImg.h"

typedef enum { Coeur, Pique, Carreau ,Trefle}TypeCouleur;
typedef enum { As,Roi, Dame, Valet, Dix, Neuf, Huit, Sept, Six, Cinq, Quatre, Trois, Deux}TypeHauteur;

class Carte: public CImg<unsigned char>
{
private:
	TypeCouleur Couleur_;
	TypeHauteur Hauteur_;


public:
	Carte(TypeCouleur Couleur, TypeHauteur Hauteur);
	~Carte();
	void display();

};

