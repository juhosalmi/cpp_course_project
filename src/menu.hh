#ifndef MENU_HH
#define MENU_HH
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/gui.h>
#include "options.hh"
#include "gameio.hh"
#include "gamegraphic.hh"

const int SLEEP_TIEM = 200; // Variable for system sleep to prevent pushing the button between the game and the menus.
const int MENU_SLEEP = 10; // Variable for system sleep to prevent over processing.

//! Menu class.
/*!
Menu class. Drawing and using the menu.
*/
class Menu {
public:
	
	//! Enumerations for menu selections
	enum MenuSelection {
		NOSELECTION,/*!< No menu selection. */
		CONTINUE, 	/*!< Continue selection from the menu. */
		NEW_GAME, 	/*!< New game selection from the menu. */
		QUIT		/*!< Quit selection from the menu. */
	};
	
	//! Constructor.
	/*!
	Sets game IO, graphics, sounds, options and signal handling for the menu
	\param options Game options.
	\param gameio Game IO.
	\param gameGraphic Game graphics.
	*/
	Menu (Options& options, GameIO& gameio, GameGraphic& gameGraphic);
	
	//! Destructor.
	/*!
	Placeholder. We may be needing this with the signals because now it segfaults.
	*/
	~Menu();
	
	//! Keyboard input reader.
	/*! 
	Reads keyboard signals. Sets the variable "input" to the key pressed. Used to set key bindings.
	\param event Tells which key is pressed.
	\param state
	*/
	void key(const CL_InputEvent &event, const CL_InputState &state);
	
	//! Draws main menu.
	/*! Draws main menu.
	\param showContinue If game is started, draw menu with a continue button.
	\return MenuSelection of whether to continue or start a new game or to quit.
	*/
	MenuSelection drawMain(bool showContinue);
	
	//! Get key binding 
	/*!
	Helper function that tells the user to press a button to set the key binding.
	\return The code of the key pressed.
	*/
	int getKey();
	
	//! Draws options.
	/*!
	Draws options.
	*/
	void drawOptions();

private:
	
	//! Variable for the latest keyboard input.
	int input;
	//CL_Slot slot; // Slot for keyboard input signal. Alternative place for this.
	//! Options for the game.
	Options &options; 
	//! Game IO.
	GameIO &gameio;
	//! Game graphics and sounds.
	GameGraphic &gameGraphic;
	
};

#endif
