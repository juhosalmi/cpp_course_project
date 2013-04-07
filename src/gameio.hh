#ifndef GAMEIO_HH
#define GAMEIO_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>

//! GameIO struct.
/*!
GameIO struct is a container for all game IO.
*/
struct GameIO {

public:
	//! Constuctor.
	GameIO() :
		win("Hyper Fabio Brothers", 1000, 750),
		gc(win.get_gc()),
		keyboard(win.get_ic().get_keyboard()),
		mouse(win.get_ic().get_mouse())
		{ }
	
	//! Copy constructor.
	/*!
	\param gameio Other gameIO.
	*/
	GameIO(GameIO& gameio) : 
		win(gameio.getWindow()),
		gc(gameio.getGC()), 
		keyboard(gameio.getKeyboard()), 
		mouse(gameio.getMouse())
		{ }
	
	//! Destructor.
	~GameIO() { }
	
	//! Assignment operator.
	/*!
	\param other Other gameIO.
	*/
	GameIO& operator=(GameIO& other){
		
		GameIO newgio(other);
		GameIO& gioref = newgio;
		return gioref;
	}
	
	//! Get GC pointer.
	/*!
	\return GC pointer.
	*/
	CL_GraphicContext* getGCptr() {
		return &gc;
	}
	
	//! Get GC.
	/*!
	\return GC reference.
	*/
	CL_GraphicContext& getGC() {
		return gc;
	}
	
	//! Get keyboard.
	/*!
	\return Reference to keyboard ID.
	*/
	CL_InputDevice& getKeyboard() { 
		return keyboard;
	}
	
	//! Get mouse.
	/*!
	\return Reference to mouse ID.
	*/
	CL_InputDevice& getMouse() {
		return mouse;
	}
	
	//! Get window.
	/*!
	\return Reference to the game window.
	*/
	CL_DisplayWindow& getWindow() {
		return win;
	}

private:

	//! Game window.
	CL_DisplayWindow win;
	//! Graphic context.
	CL_GraphicContext gc;
	//! Keyboard ID.
	CL_InputDevice keyboard;
	//! Mouse ID.
	CL_InputDevice mouse;
	
};

#endif
