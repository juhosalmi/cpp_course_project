#include "item.hh"
#include "shroom.hh"
//! A normal class for super mushrooms.
/*!
shroom class is example of item subclasses

inherits abstract Item and GameObject classes
inherited functionalities:
	-drawing
	-collisions
	-virtual move()
	-generation

own functionalities:
	-move()
	-grant bonus


*/


	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO reference to gameio struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Shroom::Shroom(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef) :
		Item(init_x, init_y, gameIO, gameGraphicRef)
	{
 	
    	objectSprite = gameGraphicRef.getShroomSprite();
    	
    	//Creates the collision outline.
	outline = CL_CollisionOutline("images/shroom.png");
	outline.set_translation(init_x, init_y);
	outline.set_angle(CL_Angle::from_radians(0));
    	
	}
	
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Shroom::Shroom(const Shroom& other) :
			Item(other.coordinates.first,
			other.coordinates.second,
			other.gameIO, other.gameGraphicRef)
	{
	objectSprite = other.objectSprite;

	outline = other.outline;
	}
	
	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Shroom& Shroom::operator=(const Shroom& other){ 
		Shroom uus(other);
		Shroom& uusref = uus;
		return uusref;
	}
	
	//! Gathers the mushroom.
	void Shroom::gather(){
	outline.set_translation(0,0);
	objectSprite = gameGraphicRef.getDeadSprite();
	}
	
	
	//! A destructor.
	/*!
	RO3.
	*/
	Shroom::~Shroom() {}


