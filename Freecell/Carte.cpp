#include "pch.h"
#include "Carte.h"


Carte::Carte(TypeCouleur Couleur, TypeHauteur Hauteur,std::string fileName)
{
	Couleur_ = Couleur;
	Hauteur_ = Hauteur;
	(this)->assign(fileName.c_str());
}


Carte::~Carte()
{
}

void Carte::display() {
	std::cout << "Le couleur est : " <<Couleur_ << std::endl;
	std::cout << "La hauteur est : " << Hauteur_ << std::endl;
 }