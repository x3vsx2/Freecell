#pragma once
#include "Carte.h"
#include <iostream>
#include <list>

using namespace std;


class Liste
{
private:
	int taille_;
	list <Carte> LaListe_;


public:
	Liste(list<Carte> LaListe, int taille);
	Liste();
	~Liste();
	void add(Carte macarte) {LaListe_.push_back(macarte);}
	void pop() { LaListe_.pop_back(); }
	void display();
};

