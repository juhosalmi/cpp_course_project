#ifndef PLAYER_HH
#define PLAYER_HH


#include <string>
#include <vector>
#include <ClanLib/display.h>
#include "movingobject.hh"

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

class Player : public MovingObject  {

public:

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
	Player(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity, std::string normalSpritePath, std::string superSpritePath, bool isFabio);
	

	//! Copy-constructor.
	/*!
	 * \param other Player to copy.
	 */
	Player(const Player &other);

	//! A destructor.
	/*!
	RO3.
	*/
	~Player(){}

	//! Moves the player.
	/*!
	Moves the player.
	\return new coordinates.
	*/
	std::pair<float, float> move();
	
	//! Which way the player is facing.
	/*!
	\param val true = left.
	*/
	void facingLeft(bool val);
	
	//! Sets new velocity for player.
	/*!
	Sets new velocity.
	\param newVelo new velocity.
	*/
	void setVelocity(std::pair<float, float> newVelo);
	
	//! Getter for the velocity of the player.
	/*!
		\return Velocity of the player.
	*/
	std::pair<float, float> getVelocity();

	//! Grow into Super Fabio.
	void growSuper();
	
	//! Decrease into normal Fabio.
	void growNormal();

	//! Get one more coin.
	void addCoin();
	
	//! getter for coin number.
	int getCoins();
	
	//! Player is hit by monster.
	void hitByMonster();
	
	//! Getter for death-status.
	/*!
	\return isDead.
	*/
	bool getIsDead();
	
	//! Getter for is the player fabio or not.
	/*!
	\return isfabio
	*/
	bool getIsFabio();
	
	//! Getter for starTime.
	/*!
	\return starTime.
	*/
	float getStarTime();
	
	//! Setter for starTime.
	/*!
	 \param newTime new startime.
	*/
	void setStarTime(float newTime);

	//! assignment operator.
	/*!
	\param orig Reference to player-object to be assigned.
	\return this.
	*/
	Player& operator=(const Player& orig);

private:

	//! Player velocity.
	std::pair<float, float> velocity;
	
	//! Player acceleration.
	float acceleration;

	//! Player maximum speed.
	float maxSpeedX;
	
	//! Player maximum speed.
	float maxSpeedY;
	
	//! Is the player super Fabio.
	/*!
	True if super.
	False if normal.
	*/
	bool isSuper;
	
	//! Is player in immortal mode.
	/*!
	When the player is in super mode and hit by monster, player doesn't die but grows normal and becomes immune for few seconds.
	*/
	float starTime;
	
	//! tag which player the player is.
	bool isFabio;
		
	//! Sprite for still normal fabio.
	CL_Sprite stillSprite;
	
	//! Sprite for moving normal fabio.
	CL_Sprite animatedSprite;
	
	//! Sprite for jumping fabio.
	CL_Sprite jumpingSprite;
	
	//! Sprite path.
	std::string normalSpritePath;
	
	//! Sprite path.
	std::string superSpritePath;
	

	//! How many coins fabio has.
	int coins;
	
	//! Is fabio dead.
	bool isDead;
	
	//! Collision outline for normal fabio.
	CL_CollisionOutline normalOutline;
	
	//! Collision outline for hyper fabio.
	CL_CollisionOutline superOutline;
};


#endif
