// Freecell.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Fonctions.h"
#include "Carte.h"
#include "Liste.h"

using namespace std;

int main()
{
	Carte MaCarte(Coeur, As);
	Liste MaListe;
	MaListe.add(MaCarte);
	MaListe.display();
	MaListe.pop();
	MaCarte.display();


	return(0);
}

