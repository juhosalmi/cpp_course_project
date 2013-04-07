#ifndef MONSTER_HH
#define MONSTER_HH

#include "item.hh"
#include "coin.hh"
#include "gameio.hh"
#include "gamegraphic.hh"
#include "movingobject.hh"
#include <string>

//! An abstract class for monsters.
/*!
abstract super class for all the monsters
*/

class Monster : public MovingObject {

public:
	
	//! A constructor.
	/*!
	\param init_x initial x coordinate.
	\param init_y initial y coordinate.
	\param gameIO reference to gameIO.
	\param gameGraphicRef reference to gameGraphic.
	\param init_velocity initial velocity.
	*/
	Monster(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity) : MovingObject(init_x, init_y, gameIO, gameGraphicRef, init_velocity)
	{};
	
	//! A pure virtual destructor.
	//virtual ~Monster() = 0;
	
	//! A pure virtual reward.
	virtual Coin& reward() = 0;

	//! A pure virtual get next coords.
	virtual std::pair<float, float> getNextCoordinates() = 0;
	
	//! Virtual setter for velocity.
	/*!
	\param newVelo new velocity.
	*/
	virtual void setVelocity(std::pair<float, float> newVelo) = 0;

	//! Virtual getter for velocity.
	/*!
	\return velocity.
	*/
	virtual std::pair<float, float> getVelocity() = 0;
	
	//! Getter for outline that kills the monster.
	/*!
	\return the outline.
	*/
	CL_CollisionOutline& getWinOutline(){
		return winOutline;
	}
	
	//! Getter for outline that kills the player.
	/*!
	\return the outline.
	*/
	CL_CollisionOutline& getLoseOutline(){
		return loseOutline;
	}
		
	//! A pure virtual move.
	//virtual void move() = 0;//TODO:remove?
	
	//! A pure virtual hitwall.
	virtual void hitWall() = 0;//TODO:remove?
	
	//! A pure virtual hitbyfloor.
	virtual void hitFloor() = 0;//TODO:remove?
	
	//! A pure virtual hitbyplayer.
	virtual void hitByPlayer() = 0;//TODO:remove?
	
	//! getter for is dead.
	/*!
	\return isDead.
	*/
	bool getIsDead(){
		return isDead;
	}
	
	//! function to kill the monster.
	void kill(){
	isDead = true;
	winOutline.set_translation(0,0);
	loseOutline.set_translation(0,0);
	objectSprite = gameGraphicRef.getDeadSprite();
	}

protected:

	//! Is the monster dead or alive.
	bool isDead;

	//! Outline that kills the monster.
	CL_CollisionOutline winOutline;
	
	//! Outline that kills the player.
	CL_CollisionOutline loseOutline;

};

#endif

