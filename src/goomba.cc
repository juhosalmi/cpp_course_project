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

#include "goomba.hh"
#include "gameio.hh"
#include "gamegraphic.hh"
#include "movingobject.hh"
#include "monster.hh"
#include "coin.hh"


	//! A constructor.
	/*!
	\param init_x initial x coordinate.
	\param init_y initial y coordinate.
	\param gameIO reference to gameIO.
	\param gameGraphicRef reference to gameGraphic.
	\param init_velocity initial velocity.
	Also loads the image by the image path into the objectSprite.
	*/
	Goomba::Goomba(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity) : 
	Monster(init_x, init_y, gameIO, gameGraphicRef, init_velocity), 
	isDead(false)
	{
	//Loads the image of goomba
	if(init_x > 500.0f)
    		animatedSprite = gameGraphicRef.getMovingGoombaSpriteL();
    	else if(init_x < 500.0f)
    		animatedSprite = gameGraphicRef.getMovingGoombaSpriteR();
    	
    	normalSprite = gameGraphicRef.getStillGoombaSprite();
    	
    	objectSprite = animatedSprite;
	
	objectSprite.set_play_loop(true);
	
	
	//Creates the collision outline.
	winOutline = CL_CollisionOutline("images/goombawinoutline.png");
	winOutline.set_translation(init_x, init_y);
	winOutline.set_angle(CL_Angle::from_radians(0));
		
	loseOutline = CL_CollisionOutline("images/goombaloseoutline.png");
	loseOutline.set_translation(init_x, init_y);
	loseOutline.set_angle(CL_Angle::from_radians(0));

	outline = loseOutline;

	}
	
	
	//! A copy constructor.
	/*!
	\param other reference to goomba to be copied.
	*/
	Goomba::Goomba(Goomba& other) : 
	Monster(other.getVelocity().first, other.getVelocity().second, other.gameIO, other.gameGraphicRef, other.getVelocity()), 
	isDead(false)
	{
	normalSprite = other.normalSprite;
	animatedSprite = other.animatedSprite;
	objectSprite = other.objectSprite;
	winOutline = other.winOutline;
	loseOutline = other.loseOutline;
	outline = other.outline;
	}
	
	
	
	//! A destructor.
	/*!
	RO3.
	*/
	Goomba::~Goomba() {}
	
	//! A reward.
	/*!
	\return reference to a coin.
	*/
	Coin& Goomba::reward(){
		Coin coin(0,0,gameIO, gameGraphicRef);
		Coin& output = coin;
		return output;
	}
	

	//! Setter for velocity.
	/*!
	Sets goomba's velocity.
	\param newVelo new velocity.
	*/
	void Goomba::setVelocity(std::pair<float, float> newVelo){
		velocity = newVelo;
		
			
	}

	//! getter for velocity.
	/*!
	\return the velocity.
	*/
	std::pair<float, float> Goomba::getVelocity(){
		return velocity;
	}


	//! A get next coords.
	/*!
	\return next coordinates.
	*/
	std::pair<float, float> Goomba::getNextCoordinates(){
			return std::pair<float, float>(coordinates.first+velocity.first, coordinates.second+velocity.second);
	
	}
	
	//! moves the monster.
	/*!
	\return new coordinates.
	*/
	std::pair<float, float> Goomba::move(){
		
		objectSprite.update();
		
		winOutline.set_translation(coordinates.first, coordinates.second);
		loseOutline.set_translation(coordinates.first, coordinates.second);
		
		
		coordinates.first = coordinates.first + velocity.first;
		coordinates.second = coordinates.second + velocity.second;
			
		if(coordinates.first < -50 && coordinates.second > 570){ //vasen alaputki -> oikea ylaputki
			coordinates.first = 999;
			coordinates.second = 200;
			}	
		else if(coordinates.first < -50)
			coordinates.first = 999;
		
		if(coordinates.first > 1000 && coordinates.second > 570){ //oikea alaputki -> vasen ylaputki
			coordinates.first = -49;
			coordinates.second = 200;
			}
		else if(coordinates.first > 1000)
			coordinates.first = -49;	
		
		return coordinates;
	}
	
	//! A pure virtual hitwall.
	void Goomba::hitWall(){//TODO:remove?
		// maybe needed, maybe not
	}
	
	//! A pure virtual hitbyfloor.
	void Goomba::hitFloor(){//TODO:remove?
		// maybe needed, maybe not
	}
	
	//! A pure virtual hitbyplayer.
	void Goomba::hitByPlayer(){
		isDead = true;
		objectSprite = normalSprite;
	}
	
	//! Assignment operator.
	/*!
	\param other reference to the goomba to be assigned.
	\return reference to the new goomba. 
	*/
	Goomba& Goomba::operator=(Goomba& other){
		Goomba uus(other);
		Goomba& uusref = uus;
		return uusref;
	}

