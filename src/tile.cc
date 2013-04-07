//! A normal class for tiles.
/*!
tile class is for tiles and maybe later on for moving tiles or POW-tiles

inherits the GameObject class
inherited functionalities:
	-drawing
	-collisions
	-virtual move()
	
own functionalities:
	-sprite
	-move() when collided with

*/

#include "tile.hh"
#include "staticobject.hh"
#include "gameio.hh"
#include "gamegraphic.hh"
#include "gameobject.hh"


	//! A constructor.
	/*!
	\param init_x initial x.
	\param init_y initial y.
	\param gameIO the reference to gameIO struct.
	\param gameGraphicRef reference to gamegraphic struct.
	*/
	Tile::Tile(float init_x, float init_y, GameIO& gameIO, GameGraphic& gameGraphicRef) :
		StaticObject(init_x, init_y, gameIO, gameGraphicRef),
		initPosition(init_x, init_y)
	{
		
		
		
		objectSprite = gameGraphicRef.getStillTileSprite();
		
	
		//Creates the collision outline.
		CL_CollisionOutline collisionOutline("images/tile.png");
		collisionOutline.set_translation(init_x, init_y+10);
		collisionOutline.set_angle(CL_Angle::from_radians(0));
		outline = collisionOutline;
	}
	
	//! Copy-constructor.
	/*!
	\param other reference to the object to be copied.
	*/
	Tile::Tile(const Tile& other) :
			StaticObject(other.coordinates.first, other.coordinates.second, other.gameIO, other.gameGraphicRef),
			initPosition(other.coordinates.first, other.coordinates.second)
	{
			objectSprite = other.objectSprite;
			outline = other.outline;

	}
	
	//! Draws the object.
	/*!
	Draws the object into the game's graphic context into its own coordinates.
	*/
	void Tile::drawObject(){
		objectSprite.draw(gameIO.getGC(), coordinates.first, coordinates.second);
		objectSprite.update();
		if(objectSprite.is_finished()){
			objectSprite = gameGraphicRef.getStillTileSprite();			
			}
	}
	
	//! A destructor.
	Tile::~Tile()
	{}
	
	//! Function for player hitting the tile.
	/*!
	Animates the tile.
	*/
	void Tile::hitByPlayer(){
		objectSprite = gameGraphicRef.getMovingTileSprite();	
		objectSprite.restart();
		objectSprite.set_play_loop(false);
	}
	
	//! Returns the tile to initial position.
	void Tile::returnToInitPos(){
		coordinates = initPosition;
	}

	//! assignment operator.
	/*!
	\param other reference to player-object to be assigned.
	\return this.
	*/
	Tile& Tile::operator=(const Tile& other){
		Tile uus(other);
		Tile& uusref = uus;
		return uusref;
	}
