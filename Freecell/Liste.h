#pragma once
#include "Carte.h"
#include <iostream>
#include <list>

using namespace std;
using namespace cimg_library;

class Liste:public CImgList<unsigned char>
{
private:
	int taille_;


public:
	Liste(int taille);
	Liste();
	~Liste();
	//void display();
};

