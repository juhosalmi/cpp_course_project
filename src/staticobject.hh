#ifndef STATICOBJECT_HH
#define STATICOBJECT_HH

//! An abstract class for all non-moving objects.
/*!
Abstract class for non-moving gameobjects.
Mainyl for making the program more modular.
*/

#include "gameio.hh"
#include "gameobject.hh"
#include "gamegraphic.hh"



class StaticObject : public GameObject
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO the reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	StaticObject(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef) :
		gameGraphicRef(gameGraphicRef), GameObject(init_x, init_y, gameIO)
	{}

	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	StaticObject(const StaticObject& other) :
		gameGraphicRef(other.gameGraphicRef),
		GameObject(other.coordinates.first,
		other.coordinates.second, other.gameIO)
	{}
	
	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	StaticObject& operator=(const StaticObject& other){ 
		StaticObject uus(other);
		StaticObject& uusref = uus;
		return uusref;
	}


protected:

	//! a reference to gamegraphic object.
	GameGraphic& gameGraphicRef;

};

#endif


