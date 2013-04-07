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

#include "koopa.hh"
#include "monster.hh"
#include "coin.hh"
#include "movingobject.hh"
#include <ClanLib/display.h>



	//! A constructor.
	/*!
	\param init_x initial x coordinate.
	\param init_y initial y coordinate.
	\param gameIO reference to gameIO.
	\param gameGraphicRef reference to gameGraphic.
	\param init_velocity initial velocity.
	Also loads the image by the image path into the objectSprite.
	*/
	Koopa::Koopa(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity) : 
	Monster(init_x, init_y, gameIO, gameGraphicRef, init_velocity),  
	isDead(false)
	{
	
		//Loads the image of koopa
	
		normalSprite = gameGraphicRef.getStillKoopaSprite();
		
		if(init_x > 500.0f)
    			animatedSprite = gameGraphicRef.getMovingKoopaSpriteL();
    		else if(init_x < 500.0f)
    			animatedSprite = gameGraphicRef.getMovingKoopaSpriteR();
    	
	    	objectSprite = animatedSprite;
	    	    	
	    	//Creates the collision outlines.
		rightWin = CL_CollisionOutline("images/koopawinoutlineright.png");
		rightWin.set_translation(init_x, init_y);
		rightWin.set_angle(CL_Angle::from_radians(0));
		
		rightLose = CL_CollisionOutline("images/koopaloseoutlineright.png");
		rightLose.set_translation(init_x, init_y);
		rightLose.set_angle(CL_Angle::from_radians(0));
		
		leftWin = CL_CollisionOutline("images/koopawinoutlineleft.png");
		leftWin.set_translation(init_x, init_y);
		leftWin.set_angle(CL_Angle::from_radians(0));
		
		leftLose = CL_CollisionOutline("images/koopaloseoutlineleft.png");
		leftLose.set_translation(init_x, init_y);
		leftLose.set_angle(CL_Angle::from_radians(0));
		
		
		objectSprite.set_play_loop(true);
	/*
		if(init_x < 500)
			objectSprite.set_angle_yaw(CL_Angle::from_radians(3.14));
		else if(init_x > 500)
			objectSprite.set_angle_yaw(CL_Angle::from_radians(0));
	*/
		
	}
	
	
	//! A copy constructor.
	/*!
	\param other reference to koopa to be copied.
	*/
	Koopa::Koopa(Koopa& other) : 
	Monster(other.getVelocity().first, other.getVelocity().second, other.gameIO, other.gameGraphicRef, other.getVelocity()), 
	isDead(false)
	{
	normalSprite = other.normalSprite;
	animatedSprite = other.animatedSprite;
	objectSprite = other.objectSprite;
	leftWin = other.leftWin;
	leftLose = other.leftLose;
	rightWin = other.rightWin;
	rightLose = other.rightLose;
	outline = other.outline;
	}
	
	
	
	//! A destructor.
	Koopa::~Koopa(){}

	//! A reward.
	/*!
	Creates a coin and returns a reference to it.
	\return a reference to a coin.
	*/
	Coin& Koopa::reward(){
		Coin coin(0,0,gameIO,gameGraphicRef);
		Coin& output = coin;
		return output;
	}
	
	//! Setter for velocity.
	/*!
	Sets koopa's velocity.
	\param newVelo new velocity.
	*/
	void Koopa::setVelocity(std::pair<float, float> newVelo){
		velocity = newVelo;
		
		
		
		if(velocity.first > 0){
			winOutline = rightWin;
			loseOutline = rightLose;
		}else{
			winOutline = leftWin;
			loseOutline = leftLose;
		}
		
		outline = loseOutline;
			
	}
	
	//! getter for velocity.
	/*!
	\return the velocity.
	*/
	std::pair<float, float> Koopa::getVelocity(){
		return velocity;
	}

	//! A get next coords.
	/*!
	\return next coordinates.
	*/
	std::pair<float, float> Koopa::getNextCoordinates(){
			return std::pair<float, float>(coordinates.first+velocity.first, coordinates.second+velocity.second);
	
	}
	
	//! moves the monster.
	/*!
	\return new coordinates.
	*/
	std::pair<float, float> Koopa::move(){
		
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
	void Koopa::hitWall(){ //TODO:remove?
		// maybe needed, maybe not
	}
	
	//! A pure virtual hitbyfloor.
	void Koopa::hitFloor(){ //FIXME: we need something like "bool goingDown" here (Riku 21.11)
		// maybe needed, maybe not
	}
	
	//! A pure virtual hitbyplayer.
	void Koopa::hitByPlayer(){//TODO:remove?
		isDead = true;
		objectSprite = normalSprite;
	}
	
	//! Assignment operator.
	/*!
	\param other reference to the koopa to be assigned.
	\return reference to the new koopa. 
	*/
	Koopa& Koopa::operator=(Koopa& other){
		Koopa uus(other);
		Koopa& uusref = uus;
		return uusref;
	}

