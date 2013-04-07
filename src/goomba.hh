//! A normal class for Goombas.
/*!
goomba class for easy sample monster.
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

#include "gameio.hh"
#include "gamegraphic.hh"
#include "monster.hh"
#include "movingobject.hh"
#include "coin.hh"

class Goomba : public Monster {

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
	Goomba(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity);
		
	//! A destructor.
	~Goomba();
	
	//! A copy constructor.
	/*!
	\param other reference to goomba to be copied.
	*/
	Goomba(Goomba& other);
	
	//! A reward.
	/*!
	\return reference to a coin.
	*/
	Coin& reward();

	//! A get next coords.
	/*!
	\return next coordinates.
	*/
	std::pair<float, float> getNextCoordinates();

	//! Setter for velocity.
	/*!
	Sets goomba's velocity.
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
	\param other reference to the goomba to be assigned.
	\return reference to the new goomba. 
	*/
	Goomba& operator=(Goomba& other);


private:

	//! Is koopa dead.
	bool isDead;
	
	//! moving sprite.
	CL_Sprite animatedSprite;
	
	//! still sprite.
	CL_Sprite normalSprite;

};
