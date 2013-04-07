#include "player.hh"
#include "movingobject.hh"
#include "gameobject.hh"

#include <ClanLib/core.h>
#include <ClanLib/display.h>


//! A normal class for players.
/*!
class for players:
inherits GameObject abstract class so it includes:
	-drawing
	-collisions
	-virtual move() function

functionality for class:
move() implementation
health (big/small fabio)
bonuses

have-to-know info:
-own place
-own speed
-own sprite
-own bonuses
-own health state

*/


	//! Constructor.
	/*!
	Constructor. Also initializes the isSuper, isDead and coins variables.
	\param init_x Initial x.
	\param init_y Initial y.
	\param gameIO GameIO rerefence.
	\param gameGraphicRef GameGraphic rerefence.
	\param init_velocity Initial Velocity.
	\param normalSpritePath Sprite path for normal fabio.
	\param superSpritePath Sprite path for super fabio.
	\param isFabio Is this player Fabio or not.
	*/
	Player::Player(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity, std::string normalSpritePath, std::string superSpritePath, bool isFabio) : 
	MovingObject(init_x, init_y, gameIO, gameGraphicRef, init_velocity),
	velocity(init_velocity), 
	isSuper(false), 
	coins(0), 
	isDead(false), 
	isFabio(isFabio), 
	normalSpritePath(normalSpritePath), 
	superSpritePath(superSpritePath),
	maxSpeedX(2.5f),
	maxSpeedY(10.0f),
	starTime(0.0f)
	{
		
		if(isFabio){
		//normal fabio sprite loading
		stillSprite = gameGraphicRef.getStillFabioSprite();
		animatedSprite = gameGraphicRef.getMovingFabioSprite();
		jumpingSprite = gameGraphicRef.getJumpingFabioSprite();
		}
		else{
		//normal uolevi sprite loading
		stillSprite = gameGraphicRef.getStillUoleviSprite();
		animatedSprite = gameGraphicRef.getMovingUoleviSprite();
		jumpingSprite = gameGraphicRef.getJumpingUoleviSprite();
		}
		
		//objectSprite = stillSprite;
		objectSprite = animatedSprite;
		objectSprite.set_play_pingpong();
		
	    	//Creates the collision outline.
	    	CL_CollisionOutline normalOutline("images/pco.png");
		normalOutline.set_translation(init_x, init_y);
		normalOutline.set_angle(CL_Angle::from_radians(0));
	
		CL_CollisionOutline superOutline("images/pco.png");
		superOutline.set_translation(init_x, init_y);
		superOutline.set_angle(CL_Angle::from_radians(0));
		
		outline = normalOutline;
    		
	}

	//! Copy-constructor.
	/*!
	\param other reference to player-object to be copied.
	*/
	Player::Player(const Player &other) :
		MovingObject(other.coordinates.first, other.coordinates.second, other.gameIO, other.gameGraphicRef, other.velocity),
		velocity(other.velocity),
		isSuper(other.isSuper),
		coins(other.coins),
		isDead(other.isDead),
		isFabio(other.isFabio),
		normalSpritePath(other.normalSpritePath),
		superSpritePath(other.superSpritePath),
		stillSprite(other.stillSprite),
		animatedSprite(other.animatedSprite),
		jumpingSprite(other.jumpingSprite),
		maxSpeedX(other.maxSpeedX),
		maxSpeedY(other.maxSpeedY)
	{

	}

	//! Moves the player.
	/*!
	Moves the player.
	\return new coordinates.
	*/
	std::pair<float, float> Player::move()
	{
		
		outline.set_translation(coordinates.first, coordinates.second);
		
		if(velocity.first < -maxSpeedX)
			velocity.first = -maxSpeedX;
		if(velocity.second < -maxSpeedY)
			velocity.second = -maxSpeedY;
		
		if(velocity.first > maxSpeedX)
			velocity.first = maxSpeedX;
		if(velocity.second > maxSpeedY)
			velocity.second = maxSpeedY;
			
		if(coordinates.first < -50)
			coordinates.first = 999;
		
		if(coordinates.first > 1000)
			coordinates.first = -49;
			
		coordinates.first = coordinates.first + velocity.first;
		coordinates.second = coordinates.second + velocity.second;
		return coordinates;
	}
	
	//! Which way the player is facing.
	/*!
	\param val true = left.
	*/
	void Player::facingLeft(bool val){
		if(!val)
			objectSprite.set_angle_yaw(CL_Angle::from_radians(3.14));
		else
			objectSprite.set_angle_yaw(CL_Angle::from_radians(0));
	}
	
	//! Sets new velocity for player.
	/*!
	Sets new velocity.
	\param newVelo new velocity.
	*/
	void Player::setVelocity(std::pair<float, float> newVelo)
	{
		
		objectSprite.update();
		
		if(velocity.second != 0)
			objectSprite = jumpingSprite;
		else if(velocity.first == 0)
			objectSprite = stillSprite;		
		else{
			objectSprite = animatedSprite;	
			objectSprite.set_play_pingpong();	
		}
	
		
		int a = 0;
		int b = 40;
		
		if(velocity.first > 0){
			if(200-b*velocity.first <= 0)
				a = 1;
			else
				a = 200-b*velocity.first;
		}else{
			if(200+b*velocity.first <= 0)
				a = 1;
			else
				a = 200+b*velocity.first;
		}
		
		objectSprite.set_delay(a);
			
		velocity = newVelo;
		
		if(velocity.first > maxSpeedX)
			velocity.first = maxSpeedX;
		if(velocity.second > maxSpeedY)
			velocity.second = maxSpeedY;
		
	}
	
	//! Getter for the velocity of the player.
	/*!
		\return Velocity of the player.
	*/
	std::pair<float, float> Player::getVelocity() {
		return velocity;
	}


	//! Grow into Super Fabio.
	void Player::growSuper()
	{
		isSuper = true;
		
		if(isFabio){
			animatedSprite = gameGraphicRef.getMovingSuperFabioSprite();
			stillSprite = gameGraphicRef.getStillSuperFabioSprite();
			jumpingSprite = gameGraphicRef.getJumpingSuperFabioSprite();
		}else{
			animatedSprite = gameGraphicRef.getMovingSuperUoleviSprite();
			stillSprite = gameGraphicRef.getStillSuperUoleviSprite();
			jumpingSprite = gameGraphicRef.getJumpingSuperUoleviSprite();
		}	
		
				
		//outline = superOutline;
	}
	
	//! Decrease into normal Fabio.
	void Player::growNormal()
	{
		isSuper = false;
		
		if(isFabio){
			animatedSprite = gameGraphicRef.getMovingFabioSprite();
			stillSprite = gameGraphicRef.getStillFabioSprite();
			jumpingSprite = gameGraphicRef.getJumpingFabioSprite();
		}else{
			animatedSprite = gameGraphicRef.getMovingUoleviSprite();
			stillSprite = gameGraphicRef.getStillUoleviSprite();
			jumpingSprite = gameGraphicRef.getJumpingUoleviSprite();
		}
			
		//outline = normalOutline;
	}

	//! gain one more coin.
	void Player::addCoin()
	{
		coins = coins + 1;
	}
	
	//! get the number of coins.
	/*!
	\return INT the number of coins that player has.
	*/
	int Player::getCoins(){
		return coins;
	}
	
	//! Player is hit by monster.
	void Player::hitByMonster()
	{
		if(isSuper){
			setStarTime(2.0f);
			growNormal();
		} else {
			isDead = true;
		}
	}

	//! Getter for death-status.
	/*!
	\return isDead.
	*/
	bool Player::getIsDead(){
		return isDead;
	}
	
	//! Getter for is the player fabio or not.
	/*!
	\return isfabio.
	*/
	bool Player::getIsFabio(){
		return isFabio;
	}

	//! Getter for starTime.
	/*!
	\return starTime.
	*/
	float Player::getStarTime(){
		return starTime;
	}
	
	//! Setter for starTime.
	/*!
	\param newTime new startime.
	*/
	void Player::setStarTime(float newTime){
		starTime = newTime;
		if(starTime <= 0)
			starTime = 0;
	}
		

	//! assignment operator.
	/*!
	 \param orig Reference to player-object to be assigned.
	 \return this.
	*/
	Player& Player::operator=(const Player& orig){
		if (this != &orig) {
			Player tmp(orig);
			std::swap(coordinates, tmp.coordinates);
			std::swap(velocity, tmp.velocity);
			std::swap(acceleration, tmp.acceleration);
			std::swap(maxSpeedX, tmp.maxSpeedX);
			std::swap(maxSpeedY, tmp.maxSpeedY);
			std::swap(isSuper, tmp.isSuper);
			std::swap(isFabio, tmp.isFabio);
			std::swap(stillSprite, tmp.stillSprite);
			std::swap(animatedSprite, tmp.animatedSprite);
			std::swap(jumpingSprite, tmp.jumpingSprite);
			std::swap(normalSpritePath, tmp.normalSpritePath);
			std::swap(superSpritePath, tmp.superSpritePath);
			std::swap(coins, tmp.coins);
			std::swap(isDead, tmp.isDead);
			std::swap(normalOutline, tmp.normalOutline);
			std::swap(superOutline, tmp.superOutline);

		}
		return *this;
	}

