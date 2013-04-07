#ifndef TILE_HH
#define TILE_HH

#include "gameio.hh"
#include "gamegraphic.hh"
#include "staticobject.hh"

//! Class for a single tile object.
class Tile : public StaticObject
{

public:

	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO the reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Tile(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef);
	
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Tile(const Tile& other);
	
	//! A destructor.
	~Tile();
	
	//! Function for player hitting the tile.
	/*!
	Animates the tile.
	*/
	void hitByPlayer();

	//! Draws the object.
	/*!
	Draws the object into the game's graphic context into its own coordinates.
	*/
	void drawObject();
	
	//! Returns the tile to initial position.
	void returnToInitPos();

	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Tile& operator=(const Tile& other);

private:

	//! initial position.
	std::pair<float, float> initPosition;

	
};

#endif
