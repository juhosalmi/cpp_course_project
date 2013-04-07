#ifndef COIN_HH
#define COIN_HH


#include "item.hh"

//! A header for coins.
class Coin : public Item
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Coin(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef);
	
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Coin(const Coin& other);
	
	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Coin& operator=(const Coin& other);
		
	//! A destructor.
	~Coin();

	//! gathers the coin.
	void gather();

private:

};

#endif
