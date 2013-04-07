#include "item.hh"
#include "coin.hh"
//! A normal class for coins.
/*!
coin class is example of item subclasses
*/


	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO reference to gameio struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Coin::Coin(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef) : Item(init_x, init_y, gameIO, gameGraphicRef)
	{
	
    	objectSprite = gameGraphicRef.getCoinSprite();
    	
    	//Creates the collision outline.
	outline = CL_CollisionOutline("images/coin.png");
	outline.set_translation(init_x, init_y);
	outline.set_angle(CL_Angle::from_radians(0));
    	
	}
		
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Coin::Coin(const Coin& other) : Item(other.coordinates.first, other.coordinates.second, other.gameIO, other.gameGraphicRef)
	{
	objectSprite = other.objectSprite;

	outline = other.outline;
	}
	
	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Coin& Coin::operator=(const Coin& other){ 
		Coin uus(other);
		Coin& uusref = uus;
		return uusref;
	}
	
	//! gathers the coin.
	void Coin::gather(){
	outline.set_translation(0,0);
	objectSprite = gameGraphicRef.getDeadSprite();
	}
	
	
	//! A destructor.
	Coin::~Coin() {}


