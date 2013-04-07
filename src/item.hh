#ifndef ITEM_HH
#define ITEM_HH

//! Abstract class for items.
/*!
Mainly for making the program more modular.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "staticobject.hh"



class Item : public StaticObject
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO the reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Item(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef) : StaticObject(init_x, init_y, gameIO, gameGraphicRef)
	{};
	

private:


};

#endif
