#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>

#include "gameio.hh"
#include "options.hh"
#include "gamegraphic.hh"
#include "menu.hh"
#include "game.hh"

#include <iostream>

//! Core class.
/*!
Core class does the core functionality of the game.
*/
class Core {
	
	
	
	public:
	
	//! Constructor.
	/*!
	Sets game IO and graphics, sounds and music for the game.
	\param gameio Game IO.
	\param gg Game graphics and sounds.
	*/
	
	Core(GameIO& gameio, GameGraphic& gg) : options(), gameio(gameio), gameGraphic(gg), game(options, gameio, gg)
	{ }
	

	
	
	//! Start the core program.
	/*!
	Starts the core program. Draws the menu and waits for a menu selection.
	*/
	
	void start() {
		
		// Create a new menu.
		Menu menu(options, gameio, gameGraphic);
		
		// Create a new game so that drawMenu(game.isPaused) can be checked. Kind of stupid but makes things easier.
		//game(options, gameio, game_graphic);
		
		// Set state of the menu to IN_MENU.
		//menu.setState(Menu::IN_MENU);
		
		// Loop until QUIT.
		Menu::MenuSelection selection = Menu::NOSELECTION;
		bool running = true;
		while (running) {
			
			selection = menu.drawMain(game.isPaused());

			switch(selection) {
				case Menu::CONTINUE: continue_game(); break;
				case Menu::NEW_GAME: start_new_game(); break;
				//case Menu::OPTIONS: menu.setState(Menu::IN_OPTIONS); break;
				case Menu::QUIT: running=false; break;
			default: break;
			
			
			gameio.getWindow().flip(); // Make the stuff visible:
			CL_KeepAlive::process(); // Read messages from the windowing system message queue, if any are available:
			CL_System::sleep(10); // sleep
			
			}
		}
	
	}
	
	
	//! Starts a new game.
	/*!
	Starts a new game.
	*/
	
	void start_new_game() {
		if (game.isStarted() || game.isOver()) {
			gameGraphic.getBgMusic().set_position(0);
			Game newgame(options, gameio, gameGraphic); //overwrite an existing game with a new game
			Game tmpgame = newgame;
			game = newgame;
		}
		game.runGame();
		
	}
	
	
	//! Continue the on-going game.
	/*!
	Continue the on-going game.
	*/
	void continue_game() {
		game.runGame(); 
	}
	
	
	private:
	
	Game game;
	Options options;
	GameIO& gameio;
	GameGraphic& gameGraphic;
	
	};


//! Main game function.
/*!
Starts the whole game and initializes the display and such.
\param args commandline arguments.
\return return value.
*/
int mariomain(std::vector<CL_String> const &args) {
  
	// ClanLib uses RAII to control its resources.
	// The constructors of these objects claim the resources
	// and their destructor frees them.
	// Objects are destructed automatically when the program exits (normally)
	CL_SetupCore setup1_core;
	CL_SetupDisplay setup_display;
	CL_SetupGL setup_gl;
	CL_SetupSound setup_sound;
	CL_SetupVorbis setup_vorbis;
	CL_SoundOutput output(44100);
	GameIO gameio;
	GameGraphic gg(gameio);
	Options options;
	Core core(gameio, gg);
	core.start();
	return 0;
}


CL_ClanApplication app(mariomain);
