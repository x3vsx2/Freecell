#include "pch.h"
#include "Liste.h"


Liste::Liste( int taille)
{
	taille_ = taille;
}

Liste::Liste() : CImgList<unsigned char>() {
}

Liste::~Liste()
{
}
 

//void Liste::display() {
//	
//}