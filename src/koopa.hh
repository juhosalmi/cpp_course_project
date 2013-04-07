#ifndef KOOPA_HH
#define KOOPA_HH

//! A normal class for Koopa Troopas.
/*!
koopa class for easy sample monster.
inherits Monster and GameObject classes
inherited funtionalities:
-drawing
-collisions
-virtual move()
-generation
-health

own functionalities:
-AI (boolean for which direction it will move)
-move() implementation
-sprite

*/

#include "monster.hh"
#include "coin.hh"
#include <ClanLib/display.h>
#include "movingobject.hh"

class Koopa : public Monster {

public:

	//! A constructor.
	/*!
	\param init_x initial x coordinate.
	\param init_y initial y coordinate.
	\param gameIO reference to gameIO.
	\param gameGraphicRef reference to gameGraphic.
	\param init_velocity initial velocity.
	Also loads the image by the image path into the objectSprite.
	*/
	Koopa(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity);
		
	//! A copy constructor.
	/*!
	\param other reference to koopa to be copied.
	*/
	Koopa(Koopa& );

	//! A destructor.
	~Koopa();
	
	//! A reward.
	/*!
	Creates a coin and returns a reference to it.
	\return a reference to a coin.
	*/
	Coin& reward();

	//! A get next coords.
	/*!
	\return next coordinates.
	*/
	std::pair<float, float> getNextCoordinates();
	
	//! Setter for velocity.
	/*!
	Sets koopa's velocity.
	\param newVelo new velocity.
	*/
	void setVelocity(std::pair<float, float> newVelo);

	//! getter for velocity.
	/*!
	\return the velocity.
	*/
	std::pair<float, float> getVelocity();
	
	
	//! moves the monster.
	/*!
	\return new coordinates.
	*/
	std::pair<float, float> move();
	
	//! A pure virtual hitwall.
	void hitWall();
	
	//! A pure virtual hitbyfloor.
	void hitFloor();
	
	//! A pure virtual hitbyplayer.
	void hitByPlayer();
	
	//! Assignment operator.
	/*!
	\param other reference to the koopa to be assigned.
	\return reference to the new koopa. 
	*/
	Koopa& operator=(Koopa& other);

private:
	
	//! Is koopa dead.
	bool isDead;
	
	//! non moving sprite.
	CL_Sprite normalSprite;
	
	//! moving sprite.
	CL_Sprite animatedSprite;
	
	//! winning collision outline for going right.
	CL_CollisionOutline rightWin;
	//! losing collision outline for going right.
	CL_CollisionOutline rightLose;
	//! winning collision outline for going left.
	CL_CollisionOutline leftWin;
	//! losing collision outline for going left.
	CL_CollisionOutline leftLose;
};

#endif
