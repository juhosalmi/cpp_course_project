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
#include "menu.hh"

//! Constructor.
/*!
Sets game IO, graphics, sounds, options and signal handling for the menu
\param options Game options.
\param gameio Game IO.
\param gameGraphic Game graphics.
*/
Menu::Menu (Options& options, GameIO& gameio, GameGraphic& gameGraphic) : 
	gameio(gameio), 
	gameGraphic(gameGraphic), 
	options(options), 
	input(0)
	{ }


//! Destructor.
/*!
Placeholder. We may be needing this with the signals because now it segfaults.
*/
Menu::~Menu() { }


//! Keyboard input reader.
/*! 
Reads keyboard signals. Sets the variable "input" to the key pressed. Used to set key bindings.
\param event Tells which key is pressed.
\param state State.
*/
void Menu::key(const CL_InputEvent &event, const CL_InputState &state)
{
	input = event.id;
}

//! Draws main menu.
/*! Draws main menu.
\param showContinue If game is started, draw menu with a continue button.
\return MenuSelection of whether to continue or start a new game or to quit.
*/
Menu::MenuSelection Menu::drawMain(bool showContinue) {
	
	CL_System::sleep(SLEEP_TIEM); // Let the user release the buttons
	
	gameGraphic.getMenuBgMusic().set_looping(true);
	gameGraphic.getMenuBgMusic().play();
	
	int dy = 50; // Space between menu buttons.
	int x = 600; // X-coordinate for the menu buttons.
	
	if (showContinue) { // Shows continue button only if game is started already.
		
		
		while (true) {
			
			gameio.getGC().clear(CL_Colorf::white); // Clear the screen.
			CL_Font font(gameio.getGC(), "Tahoma", 30); // Set font.
			CL_Texture& bg = gameGraphic.getMenuBackground(); // Get menu BG.
			CL_Draw::texture(gameio.getGC(), bg, CL_Quadf(bg.get_size())); // Draw menu BG.
			
			// Draw menu buttons.
			font.draw_text(gameio.getGC(), x, dy, "1. Continue" , CL_Colorf::black);
			font.draw_text(gameio.getGC(), x, 2*dy, "2. New game" , CL_Colorf::black);
			font.draw_text(gameio.getGC(), x, 3*dy, "3. Options" , CL_Colorf::black);
			font.draw_text(gameio.getGC(), x, 4*dy, "4. Quit" , CL_Colorf::black);
			
			CL_KeepAlive::process(); // Read messages from the windowing system message queue, if any are available
			
			// Navigating with the number keys.
			if (gameio.getKeyboard().get_keycode(CL_KEY_1)) {
				gameGraphic.getMenuBgMusic().stop();			
				return Menu::CONTINUE;
			}
			else if (gameio.getKeyboard().get_keycode(CL_KEY_2)) {
				gameGraphic.getMenuBgMusic().stop();
				return Menu::NEW_GAME;
			}
			else if (gameio.getKeyboard().get_keycode(CL_KEY_3)) {
				drawOptions();
			}
			else if (gameio.getKeyboard().get_keycode(CL_KEY_4) || gameio.getKeyboard().get_keycode(CL_KEY_ESCAPE)) {
				gameGraphic.getMenuBgMusic().stop();
				return Menu::QUIT;
			}
			
			// Navigating with the mouse. Mouse hover turns button grey.
			if (gameio.getMouse().get_y() > 0.5*dy && gameio.getMouse().get_y() < 1.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					gameGraphic.getMenuBgMusic().stop();
					return Menu::CONTINUE;
				}
				font.draw_text(gameio.getGC(), x, 1*dy, "1. Continue" , CL_Colorf::grey);
			}
			else if (gameio.getMouse().get_y() > 1.5*dy-50 && gameio.getMouse().get_y() < 2.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					gameGraphic.getMenuBgMusic().stop();
					return Menu::NEW_GAME;
				}
				font.draw_text(gameio.getGC(), x, 2*dy, "2. New game" , CL_Colorf::grey);
			}
			else if (gameio.getMouse().get_y() > 2.5*dy-50 && gameio.getMouse().get_y() < 3.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					drawOptions();
				}
				font.draw_text(gameio.getGC(), x, 3*dy, "3. Options" , CL_Colorf::grey);
			}
			else if (gameio.getMouse().get_y() > 3.5*dy-50 && gameio.getMouse().get_y() < 4.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					gameGraphic.getMenuBgMusic().stop();
					return Menu::QUIT;
				}
				font.draw_text(gameio.getGC(), x, 4*dy, "4. Quit" , CL_Colorf::grey);
			}
			
			gameio.getWindow().flip(); // Make the stuff visible.
			CL_System::sleep(MENU_SLEEP); // Sleep to prevent over processing.
			
		}
		
	} else {
		
		while (true) {
			
			gameio.getGC().clear(CL_Colorf::white); // Clear the screen.
			CL_Font font(gameio.getGC(), "Tahoma", 30); // Set font.
			CL_Texture& bg = gameGraphic.getMenuBackground(); // Get menu BG.
			CL_Draw::texture(gameio.getGC(), bg, CL_Quadf(bg.get_size())); // Draw menu BG.
			
			// Draw menu buttons.
			font.draw_text(gameio.getGC(), x, dy*2, "1. New game" , CL_Colorf::black);
			font.draw_text(gameio.getGC(), x, dy*3, "2. Options" , CL_Colorf::black);
			font.draw_text(gameio.getGC(), x, dy*4, "3. Quit" , CL_Colorf::black);
			
			CL_KeepAlive::process(); // Read messages from the windowing system message queue, if any are available
			
			// Navigating with the number keys.
			if (gameio.getKeyboard().get_keycode(CL_KEY_1)) {
				gameGraphic.getMenuBgMusic().stop();
				return Menu::NEW_GAME;
			}
			else if (gameio.getKeyboard().get_keycode(CL_KEY_2)) drawOptions();
			else if (gameio.getKeyboard().get_keycode(CL_KEY_3) || gameio.getKeyboard().get_keycode(CL_KEY_ESCAPE)) return QUIT;
			
			// Navigating with the mouse. Mouse hover turns button grey.
			if (gameio.getMouse().get_y() > 1.5*dy && gameio.getMouse().get_y() < 2.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					gameGraphic.getMenuBgMusic().stop();
					return Menu::NEW_GAME;
				}
				font.draw_text(gameio.getGC(), x, 2*dy, "1. New game" , CL_Colorf::grey);
			}
			else if (gameio.getMouse().get_y() > 2.5*dy && gameio.getMouse().get_y() < 3.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					drawOptions();
				}
				font.draw_text(gameio.getGC(), x, 3*dy, "2. Options" , CL_Colorf::grey);
			}
			else if (gameio.getMouse().get_y() > 3.5*dy && gameio.getMouse().get_y() < 4.5*dy) {
				if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
					gameGraphic.getMenuBgMusic().stop();
					return Menu::QUIT; 
				}
				font.draw_text(gameio.getGC(), x, 4*dy, "3. Quit" , CL_Colorf::grey);
			}
			
			gameio.getWindow().flip(); // Make the stuff visible.
			CL_System::sleep(MENU_SLEEP); // Sleep to prevent over processing.
			
		}
		
	}
	
}

//! Get key binding.
/*!
Helper function that tells the user to press a button to set the key binding.
\return The code of the key pressed.
*/
int Menu::getKey() {
	
	CL_Font font(gameio.getGC(), "Tahoma", 50); // Set font
	int tmp = 0;
	input = 0;
	while (tmp == input) { // Wait for user input.
		CL_KeepAlive::process(); // Read messages from the windowing system message queue, if any are available
		font.draw_text(gameio.getGC(), 450, 450, "press button" , CL_Colorf::white);
		gameio.getWindow().flip(); // Make the stuff visible
		CL_System::sleep(MENU_SLEEP);
	}
	return input;
}

//! Draws options.
/*!
Draws options.
*/
void Menu::drawOptions() {
	
	CL_System::sleep(SLEEP_TIEM); // Let the user release the buttons before reading the input in options.
		
	CL_Slot slot = gameio.getKeyboard().sig_key_up().connect(this, &Menu::key); // To read keyboard input
	
	int dy = 70; // Space between menu buttons.
	int x = 450; // X-coordinate for the menu buttons.
	
	while (true) {
		
		gameio.getGC().clear(CL_Colorf::white); // Clear the screen.
		CL_Font font(gameio.getGC(), "Tahoma", 30); // Set font.
		CL_Texture& bg = gameGraphic.getMenuBackground(); // Get menu BG.
		CL_Draw::texture(gameio.getGC(), bg, CL_Quadf(bg.get_size())); // Draw menu BG.
		
		// Set menu texts. Shows also the binded key.
		CL_String P1KeyLeft = "P1KeyLeft: " + gameio.getKeyboard().keyid_to_string(options.getP1KeyLeft());
		CL_String P1KeyRight = "P1KeyRight: " + gameio.getKeyboard().keyid_to_string(options.getP1KeyRight());
		CL_String P1KeyUp = "P1KeyUp: " + gameio.getKeyboard().keyid_to_string(options.getP1KeyUp());
		CL_String P2KeyLeft = "P2KeyLeft: " + gameio.getKeyboard().keyid_to_string(options.getP2KeyLeft());
		CL_String P2KeyRight = "P2KeyRight: " + gameio.getKeyboard().keyid_to_string(options.getP2KeyRight());
		CL_String P2KeyUp = "P2KeyUp: " + gameio.getKeyboard().keyid_to_string(options.getP2KeyUp());
		
		// Draw menu buttons
		font.draw_text(gameio.getGC(), x, 1*dy, "Back" , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 2*dy, P1KeyLeft , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 3*dy, P1KeyRight , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 4*dy, P1KeyUp , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 5*dy, P2KeyLeft , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 6*dy, P2KeyRight , CL_Colorf::white);
		font.draw_text(gameio.getGC(), x, 7*dy, P2KeyUp , CL_Colorf::white);
		
		CL_KeepAlive::process(); // Read messages from the windowing system message queue, if any are available
		
		// Navigating with the keyboard. Only back can be selected with the keyboard because of keyboard input issues. This could be fixed.
		if (gameio.getKeyboard().get_keycode(CL_KEY_1) || gameio.getKeyboard().get_keycode(CL_KEY_ESCAPE)) break;
		
		// Navigating with the mouse. Mouse hover turns button grey.
		int i = 0;
		if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) break;
			font.draw_text(gameio.getGC(), x, i*dy, "Back" , CL_Colorf::grey);
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P1KeyLeft , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP1KeyLeft(getKey());
			}
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P1KeyRight , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP1KeyRight(getKey());
			}
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P1KeyUp , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP1KeyUp(getKey());
			}
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P2KeyLeft , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP2KeyLeft(getKey());
			}
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P2KeyRight , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP2KeyRight(getKey());
			}
		} else if (gameio.getMouse().get_y() > (0.5 + i)*dy && gameio.getMouse().get_y() < (1.5 + i++)*dy) {
			font.draw_text(gameio.getGC(), x, i*dy, P2KeyUp , CL_Colorf::grey);
			if (gameio.getMouse().get_keycode(CL_MOUSE_LEFT)) {
				options.setP2KeyUp(getKey());
			}
		}
		
		gameio.getWindow().flip(); // Make the stuff visible
		
		CL_System::sleep(MENU_SLEEP);
		
		
	}
	
	/* If these worked, the program would not crash and do segfaults.
	slot.disable();
	slot.destroy();
	*/
	
	CL_System::sleep(SLEEP_TIEM);  // Let the user release the buttons before entering main menu.

}


