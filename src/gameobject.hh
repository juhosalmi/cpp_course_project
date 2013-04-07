#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH


#include <string>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>

#include "gameio.hh"

//! An abstract class for all functional objects in the game.
/*!
ABSTRACT superclass for all functional objects in the game.
e.g players, monsters, items and tiles.
*/

class GameObject
{

	public:

		
		//! constructor.
		/*!
		\param init_x initial x.
		\param init_y initial y.
		\param gameIO reference to gameio struct.
		*/
		GameObject(float init_x, float init_y, GameIO& gameIO) : gameIO(gameIO), coordinates(init_x, init_y)
		{}
	
		//GameObject(const GameObject& o) : coordinates(o.coordinates), gameIO(o.gameIO)
		//{}
		
		//! Draws the object.
		/*!
		Draws the object into the game's graphic context into its own coordinates.
		*/
		void drawObject(){
			objectSprite.draw(gameIO.getGC(), coordinates.first, coordinates.second);
		}

		//! A pure virtual destructor.
		//virtual ~GameObject() = 0;

		//! Gets the coordinates.
		/*!
		Gets the coordiates.
		\return The coordinates.
		*/
		std::pair<float,float> getCoordinates() {
			return coordinates;
		}
		
		//! Set coodinates.
		/*!
		Sets the coordiates.
		\param newCoords new coordinates.
		*/
		void setCoordinates(std::pair<float, float> newCoords) {
			coordinates = newCoords;
		}

		//! Get sprite.
		/*!
		Gets the sprite-image of the object.
		\return The image-file.
		*/
		CL_Sprite getSprite() {
			return objectSprite;
		}
		
		//! Gets the collision outline.
		/*!
		\return collision outline.
		*/
		CL_CollisionOutline& getOutline() {
			CL_CollisionOutline& olref = outline;
			return olref;
		}
		
		//! Collision check for moving objs.
		/*!
		Collision is checked by calculating the angle of the impact.
		It is calculated by checking the relation of speed vector and the impact point. 
		\param o Moving object that is checked.
		\return boolean if the collision happened.
		*/
		bool collides(GameObject o)
		{			
			return outline.collide(o.getOutline());
		}
			
		//! virtual assignment operator.
		/*!
		\param other object to be assigned.
		\return the assigned object.
		*/
		virtual GameObject& operator=(const GameObject other){ // ei ehkä tarpeellinen, ehkä jopa haitallinen
			GameObject uus(other);
			GameObject& uusref = uus;
			return uusref;
		}
		
	protected:

		

		//! Object coordinates.
		/*!
		The coordinates of the object.
		*/
		std::pair<float, float> coordinates;
	
		//! Object sprite.
		/*!
		The image of the object.
		*/
		CL_Sprite objectSprite;
		
		
		//! Object size (rectangle).
		/*!
		The size of the sprite int int.
		*/
		std::pair<int, int> size;
		
		//! Collision outline for the object.
		CL_CollisionOutline outline;
		
		//! game io reference.
		GameIO& gameIO;
};

#endif


