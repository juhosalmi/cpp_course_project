#ifndef SHROOM_HH
#define SHROOM_HH


#include "item.hh"

//! A header for shrooms.

class Shroom : public Item
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Shroom(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef);
	
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Shroom(const Shroom& other);
	
	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Shroom& operator=(const Shroom& other);

	//! Gathers the mushroom.
	void gather();
	
	//! A destructor.
	~Shroom();

private:

};

#endif

