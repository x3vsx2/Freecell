#include "pch.h"
#include "Carte.h"


Carte::Carte(TypeCouleur Couleur, TypeHauteur Hauteur)
{
	Couleur_ = Couleur;
	Hauteur_ = Hauteur;
}


Carte::~Carte()
{
}

void Carte::display() {
	std::cout << "Le couleur est : " <<Couleur_ << std::endl;
	std::cout << "La hauteur est : " << Hauteur_ << std::endl;
 }