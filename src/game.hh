#include <string>
#include <vector>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/core.h>
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <algorithm>
#include "options.hh"
#include "gameio.hh"
#include "gamegraphic.hh"
#include "movingobject.hh"
#include "player.hh"
#include "monster.hh"
#include "staticobject.hh"
#include "tile.hh"
#include "koopa.hh"
#include "shroom.hh"

//! Game logic.
class Game {

public:

	//! Constructs a new Game.
	/*!
		\param options Game options for this game.
		\param gameio GameIO object containing the I/O objects needed in the game.
		\param gameGraphic Struct for the graphical part used in the game.
	 */
	Game(Options& options, GameIO& gameio, GameGraphic& gameGraphic);

	//! Copy-constructor.
	/*!
	 * \param other Game to copy.
	 */
	Game(const Game &other);

	//! Destructor.
	/*!	Frees all the resources initialized in the constructor.
	 */
	~Game();

	//! Initializes tiles.
	/*!	Initializes tiles.
	 */
	void init_tiles();


	//! Generates a new monster to the field when the time is right.
	/*!	Initializes monsters of the game.
	 */
	void init_monsters();

	//! Sets the game paused.
	/*!	Sets the game paused, used e.g. if we enter the menu.
	 */
	void pause();

	//! Function to find out if game is paused or not.
	/*!
		\return true if game is pause, false otherwise.
	 */
	bool isPaused();

	//! Function to find out if game is paused or not.
	/*!
		\return false if game is initialized but never started, true otherwise.
	 */
	bool isStarted();


	//! Function to find out if game is paused or not.
	/*!
		\return false if game is initialized but never started, true otherwise.
	 */
	bool isOver();

	//! Handles the input from the users.
	/*!
		\param t Time.
	 */
	void handleInput(float t);

	  //! Moves all the monsters.
	  /*! Moving is done by calling move() function
	   *  of each monster one by one.
	   * \param time Time.
	   * \param total_time Total time passed from the beginning of the game.
	   */
	 void moveMonsters(float time, float totalTime);

	 //! Adds acceleration down if object is in the air.
	 /*!
	  *  \param t Time
	  * \param mo Object.
	  */
	 void addGravity(float t, MovingObject& mo);

	 //! Moves players according to user input.
	 /*!
	  *  \param t Time.
	  */
	 void movePlayers(float t);

	 //! Check the collisions to tiles.
	 /*!
	  *  \param mo Object to check.
	  */
	 void checkCollisionToTiles(MovingObject& mo);

	  //! Draws all the Tiles stored to vector 'tiles'.
	  void drawTiles();

	  //! Draws pipes to the game field.
	  void drawPipes();

	  //! Draws monsters to the game field.
	  void drawMonsters();
	  
	  //! Draws shrooms currently on the game field.
	  void drawShrooms();

	//! Runs the game.
	void runGame();

	//! assignment operator.
	Game& operator=(const Game& other);

	//! Checks the collisions to of given player to other elements of the game.
	void checkCollisions(Player& p1);

	//! Draws coins.
	void drawCoins();
	
	//! Draws the coins player have gathered to the up bar of the window.
	void drawGatheredCoins();


private:

	//! Tells if the game is created but never started.
	bool game_started;

	//! Tells if the game is paused or not.
	bool game_paused;

	//! Tells if the game is over.
	bool game_over;

	//! Game options.
	Options& options;

	// Game IO.
	GameIO& gameio;

	// Graphics used in the game.
	GameGraphic& game_graphic;

	//! Player 1.
	Player p1;
	//! Player 2.
	Player p2;

	//! Variables to tell that players jumped on this round.
	bool p1Jumped, p2Jumped;

	//! acceleration of P1.
	float p1_ax, p1_ay;

	//! acceleration of P2.
	float p2_ax, p2_ay;


	//! List of monsters.
	/*! List of all the monsters of this game round.
	*/
	std::vector<Monster*> monsters;

	//! List of tiles.
	std::vector<Tile> tiles;
	
	//! List of coins.
	std::vector<Coin> coins;
	
	//! Gathered coins.
	std::vector<Coin> gatheredCoins;
	
	//! Shrooms.
	std::vector<Shroom> shrooms;
};
