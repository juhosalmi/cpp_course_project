#ifndef MOVINGOBJECT_HH
#define MOVINGOBJECT_HH


#include "gameobject.hh"
#include "gamegraphic.hh"

//! An abstract class for all moving objects.
/*!
	An abstract class for moving GameObjects.
	Includes pure virtual function Move().
*/
class MovingObject : public GameObject
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO the reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	\param init_velocity initial velocity.
	*/
	MovingObject(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef, std::pair<float, float> init_velocity) : 
	gameGraphicRef(gameGraphicRef), 
	GameObject(init_x, init_y, gameIO), 
	inAir(false), 
	velocity(init_velocity)
	{}

	//! A pure virtual destructor.
	//virtual ~MovingObject();

	//! A virtual move.
	/*!
	\return the new coordinates.
	*/
	virtual std::pair<float, float> move()
	{}
		
	//! Virtual setter for velocity.
	/*!
	\param newVelo new velocity.
	*/
	virtual void setVelocity(std::pair<float, float> newVelo){}

	//! Virtual getter for velocity.
	/*!
	\return velocity.
	*/
	virtual std::pair<float, float> getVelocity(){}
	

	//! Is object falling.
	/*!
		\return in air status.
	*/
	bool getInAir(){
		return inAir;
	}
	
	//! set object falling status.
	/*!
		\param newAirStatus new in air status.
	*/
	void setInAir(bool newAirStatus){
		inAir = newAirStatus;
	}

	
protected:

	//! Object velocity.
	std::pair<float, float> velocity;

	//! objects in air status.
	bool inAir;
	
	//! Game graphic struct.
	GameGraphic& gameGraphicRef;
};

#endif
