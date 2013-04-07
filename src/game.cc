#include "game.hh"
#include <string>
#include <vector>
#include <ClanLib/application.h> //TODO: check which of these can be deleted
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
#include "goomba.hh"
//#include "shroom.hh"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


	//! Constructs a new Game.
	/*!
		\param options Game options for this game.
		\param gameio GameIO object containing the I/O objects needed in the game.
		\param gameGraphic Struct for the graphical part used in the game.
	 */
	Game::Game(Options& options, GameIO& gameio, GameGraphic& gameGraphic) :
		options(options),
		gameio(gameio),
		game_graphic(gameGraphic),
		p1(125.0f, 599.9f, gameio, gameGraphic, std::pair<float, float>(0.0f, 0.0f), "images/fabio.png", "images/superfabio.png", true),
		p2(875.0f, 599.9f, gameio, gameGraphic, std::pair<float, float>(0.0f, 0.0f), "images/uolevi.png", "images/superuolevi.png", false),
		game_started(false),
		game_paused(false),
		game_over(false),
		p1Jumped(false),
		p2Jumped(false)
		{

		//tiles
		init_tiles();

		//monsters
		init_monsters();

		//music to the beginning
		//game_graphic.getBgMusic().set_position(0);

	}
	
	//! Copy-constructor.
	/*!
	 * \param other Game to copy.
	 */
	Game::Game(const Game &other) :
			options(other.options),
			gameio(other.gameio),
			game_graphic(other.game_graphic),
			p1(125.0f, 599.9f, gameio, game_graphic, std::pair<float, float>(0.0f, 0.0f), "images/fabio.png", "images/superfabio.png", true),
			p2(875.0f, 599.9f, gameio, game_graphic, std::pair<float, float>(0.0f, 0.0f), "images/uolevi.png", "images/superuolevi.png", false),
			game_started(other.game_started),
			game_paused(other.game_paused),
			game_over(other.game_over),
			p1Jumped(other.p1Jumped),
			p2Jumped(other.p2Jumped)
		{ 

		//tiles
		init_tiles();

		//monsters
		init_monsters();
		
		//music to the beginning
		//game_graphic.getBgMusic().set_position(0);
		}


	//! Destructor.
	/*!	Frees all the resources initialized in the constructor.
	 */
	Game::~Game() {
		std::vector<Monster*>::iterator iter;
		for (iter = monsters.begin(); iter!=monsters.end(); iter++) {
			delete (*iter);
		}
	}




	//! Initializes tiles.
	/*!	Initializes tiles.
	 */
	void Game::init_tiles() {
		/* We want tiles to be in the following positions:
		 *
		 *
		 * ------------			----------------			(1.)
		 *
		 * --		----------------------	  --			(2.)
		 *
		 * -----------			----------------			(3.)
		 */

		float floor=100;

		int len1=7; //number of tiles in the bars in top and bottom rows (1. & 3.)
		int len2=10; //number of tiles in the bar in the middle (2.)
		int len3=2; //number of tiles in the bar in the middle (2.)

		float level1_y = 200.0f-20.0f; //20.0f is invisible area
		float level2_y = 350.0f-20.0f;
		float level3_y = 500.0f-20.0f;

		float tile_width=50.0f;
		float win_width=1000.0f; //TODO: load these from somewhere

		//1.
		for (int i=0; i<len1; i++) { //left bar
			Tile t(i*tile_width, level1_y, gameio, game_graphic);
			tiles.push_back(t);
		}
		for (int i=0; i<len1; i++) { //right bar
			Tile t(win_width-(i+1)*tile_width, level1_y, gameio, game_graphic);
			tiles.push_back(t);
		}

		//2.
		//float start_x = (win_width/2)-(len2/2)*tile_width*1.0f;
		float start_x = 0.0f;
		for (int i=0; i<len3; i++) { //left bar
			Tile t(start_x+i*tile_width, level2_y, gameio, game_graphic);
			tiles.push_back(t);
		}
		start_x = 250.0f;
		for (int i=0; i<len2; i++) { //center
			Tile t(start_x+i*tile_width, level2_y, gameio, game_graphic);
			tiles.push_back(t);
		}
		start_x = 900.0f;
		for (int i=0; i<len3; i++) { //right bar
			Tile t(start_x+i*tile_width, level2_y, gameio, game_graphic);
			tiles.push_back(t);
		}

		//3.
		for (int i=0; i<len1; i++) { //left bar
			Tile t(i*tile_width, level3_y, gameio, game_graphic);
			tiles.push_back(t);
		}
		for (int i=0; i<len1; i++) { //right bar
			Tile t(win_width-(i+1)*tile_width, level3_y, gameio, game_graphic);
			tiles.push_back(t);
		}
	}


	//! Generates a new monster to the field when the time is right.
	/*!	Initializes monsters of the game.
	 */
	void Game::init_monsters() {

		//intial coordinates
		float init_x;
		float init_y;

		//left pipe
		float init_x_left = 50.0f;
		float init_y_left = 149.9f;

		//right pipe
		float init_x_right = 950.0f;
		float init_y_right = 149.9f;

		//init seed
		srand ( time(NULL) );

		for (int i=0; i<5; i++) {
			int number = rand() % 2;
			float direction;
			if(i%2 == 1){
				direction=-1;
				init_x = init_x_right;
				init_y = init_y_right;
			} else {
				direction=1;
				init_x = init_x_left;
				init_y = init_y_left;
			}


			if(number==1) {
				Koopa* koopa = new Koopa(init_x, init_y, gameio, game_graphic, std::make_pair(direction*1.0f, 0.0f));
				monsters.push_back(koopa);

			} else {
				Goomba* goomba = new Goomba(init_x, init_y, gameio, game_graphic, std::make_pair(direction*1.5f, 0.0f));
				monsters.push_back(goomba);

			}
		}

	}

	
	//! Sets the game paused.
	/*!	Sets the game paused, used e.g. if we enter the menu.
	 */
	void Game::pause() {
		game_paused=true;
	}


	//! Function to find out if game is paused or not.
	/*!
		\return true if game is pause, false otherwise.
	 */
	bool Game::isPaused() {
		return game_paused;
	}

	//! Function to find out if game is paused or not.
	/*!
		\return false if game is initialized but never started, true otherwise.
	 */
	bool Game::isStarted() {
		return game_started;
	}
	
	
	//! Function to find out if game is paused or not.
	/*!
		\return false if game is initialized but never started, true otherwise.
	 */
	bool Game::isOver() {
		return game_over;
	}


	//! Handles the input from the users.
	/*!
		\param t Time.
	 */
	void Game::handleInput(float t) {
		float a = 15.0f; //acceleration

		CL_InputDevice& keyboard = gameio.getKeyboard();

		std::pair<float, float> p1_v = p1.getVelocity();
		std::pair<float, float> p2_v = p2.getVelocity();


		if (keyboard.get_keycode(CL_KEY_ESCAPE)) {
			//causes runGame() to return so we end up back to the main menu
			pause();

		}

		if (keyboard.get_keycode(options.getP1KeyUp())) { 
			//act only if not in the air already
			if (!p1.getInAir()) {
				p1Jumped = true;
				p1.setInAir(true);
			}
			
			
		}

		if (keyboard.get_keycode(options.getP1KeyLeft())) { 
			p1_ax = (-1)*a;
			p1.facingLeft(true);
		}
		else if (keyboard.get_keycode(options.getP1KeyRight())) {
			p1_ax = a;
			p1.facingLeft(false);
		}
		else {
			//no left or right pressed -> slow down the horizontal speed
			float vx = p1_v.first;
			if (vx > 0.0f) {
				p1_ax = -7.5f;
			}
			else if (vx < 0.0f) { //moving left
				p1_ax = 7.5f;
			}

		}

		if (keyboard.get_keycode(options.getP2KeyUp())) { 
			if (!p2.getInAir()) {
				p2Jumped = true;
				p2.setInAir(true);
			}
		}
		if (keyboard.get_keycode(options.getP2KeyLeft())) { 
			p2_ax = (-1)*a;
			p2.facingLeft(true);
		}
		else if (keyboard.get_keycode(options.getP2KeyRight())) { 
			p2_ax = a;
			p2.facingLeft(false);
		}
		else {
			//no left or right pressed -> slow down the horizontal speed
			float vx2 = p2_v.first;
			if (vx2 > 0.0f) {
				p2_ax = -7.5f;
			}
			else if (vx2 < 0.0f) { //moving left
				p2_ax = 7.7f;
			}

		}

	}

	  //! Moves all the monsters.
	  /*! Moving is done by calling move() function
	   *  of each monster one by one.
	   * \param time Time.
	   * \param total_time Total time passed from the beginning of the game.
	   */
	 void Game::moveMonsters(float time, float total_time) {
		float bornInterval = 7;
		int numberBorn = (total_time/bornInterval);
		int i=0;

	 	std::vector<Monster*>::iterator iter;
	 	for (iter = monsters.begin(); iter!=monsters.end(); iter++, i++) {
	 		
	 		if(!((*iter)->getIsDead())){
				addGravity(time, (*(*iter)));
				checkCollisionToTiles(*(*iter));

				(*iter)->move();

			}

	 		//move only those already "born"
	 		if (i==numberBorn)
	 			break;
	 	}
	 } 
	 

	 //! Adds acceleration down if object is in the air.
	 /*!
	  *  \param t Time.
	  * \param mo Object.
	  */
	 void Game::addGravity(float t, MovingObject& mo) {
		 float gravity = 10.0f;

		 if (mo.getInAir()) {
			 std::pair<float, float> mo_v = mo.getVelocity();
			 mo_v.second = mo_v.second + t*gravity;
		 	 mo.setVelocity(mo_v);
		  }
	 }

	 //! Moves players according to user input.
	 /*!
	 *  \param t Time.
	 */
	 void Game::movePlayers(float t) {

		 //TODO: move somewhere else
		 std::vector<Tile>::iterator iter;
		 for (iter = tiles.begin(); iter!=tiles.end(); iter++) {
			 if (p1.collides(*iter) || p2.collides(*iter)){
				 (*iter).hitByPlayer();
				 
				 std::vector<Monster*>::iterator miter;
		  		 for (miter = monsters.begin(); miter!=monsters.end(); miter++) {
		  			 //player and monster hit the same tile...
		  			 if ( ( ((*(*miter)).collides((*iter)) && p1.collides(*iter)) ||
		  		 		 ((*(*miter)).collides((*iter)) && p2.collides(*iter))) &&

		  		 		//...and monster is NOT in pipe
		  		 		!( ((*(*miter)).getCoordinates().first < 100  ||
		  		 			(*(*miter)).getCoordinates().first > 860) &&
		  		 		   ((*(*miter)).getCoordinates().second < 160 ||
		  		 			(*(*miter)).getCoordinates().second > 570 ) )
		  		 	) {
		  		 		(*miter)->kill();
						Coin coin((*miter)->getCoordinates().first,(*miter)->getCoordinates().second,gameio,game_graphic);
						coins.push_back(coin);
						game_graphic.getFx()[1].set_looping(false);
						game_graphic.getFx()[1].play();
						game_graphic.getFx()[1].set_position(0);
						}
		  		 }
		  		 
			 }
		 }

		 //calculate new speeds. Use min and max functions to ensure that if we're moving e.g. to right and stop pressing
		 // a button, our player doesn't change direction but stops instead

		 //--- PLAYER 1 ---
		 float p1_vx = p1.getVelocity().first;
		 float p1_vy = p1.getVelocity().second;
		 if (p1_vx==0.0f)
			 p1_vx = 0.5f*p1_ax;
			 //p1_vx = t*p1_ax;
		 else
			 p1_vx = (p1_vx>0.0f ? std::max(0.0f, p1_vx + t*p1_ax) : std::min(0.0f, p1_vx + t*p1_ax) );


		 //jump
		 if (p1Jumped) {
			 p1_vy = -6.0f; //set constant speed up
			 game_graphic.getFx()[0].set_looping(false);
			 game_graphic.getFx()[0].play();
			 game_graphic.getFx()[0].set_position(0);
		 }
		 else {
			 p1_vy = p1.getVelocity().second;
		 }


		 //--- PLAYER 2 ---
		 float p2_vx = p2.getVelocity().first;
		 float p2_vy = p2.getVelocity().second;
		 if (p2_vx==0.0f)
			 p2_vx = 0.5f*p2_ax;
			 //p2_vx = t*p2_ax;
		 else
			 p2_vx = (p2_vx>0.0f ? std::max(0.0f, p2_vx + t*p2_ax) : std::min(0.0f, p2_vx + t*p2_ax) );


		 //jump
		 if (p2Jumped) {
			 p2_vy = -6.0f; //set constant speed up
			 game_graphic.getFx()[0].set_looping(false);
			 game_graphic.getFx()[0].play();
			 game_graphic.getFx()[0].set_position(0);
		 }
		 else {
			 p2_vy = p2.getVelocity().second;
		 }


		 //fprintf(stderr, "P1 speed: vx=%f, vy=%f\n", p1_vx, p1_vy);
		 p1.setVelocity(std::pair<float, float>(p1_vx, p1_vy));
		 p2.setVelocity(std::pair<float, float>(p2_vx, p2_vy));


		 // Add gravity except if we just jumped
		 // Done like this 'cause jump=constant speed up (NOT time dependent), gravity=acceleration down (time dependent)
		 if (!p1Jumped)
			 addGravity(t, p1);

		 if (!p2Jumped)
			 addGravity(t, p2);

		 checkCollisionToTiles(p1);
		 checkCollisionToTiles(p2);

		 p1.move();
		 p2.move();

		 //set acceleration to zero. if player presses the button corresponding acceleration is set again
		 p1_ax = 0.0f; p1_ay = 0.0f;
		 p2_ax = 0.0f; p2_ay = 0.0f;
		 p1Jumped = false;
		 p2Jumped = false;
		 p1.setStarTime(p1.getStarTime()-t);
		 p2.setStarTime(p2.getStarTime()-t);	
		 
		 	 
	 }


	 //! Check the collisions to tiles.
	 /*!
	  *  \param mo Object to check.
	  */
	 void Game::checkCollisionToTiles(MovingObject& mo) {
		 //check collisions to tiles
		 float offset = 0.1f;
		 float yo = 10.0f; //y offset to smoothen the corners of tiles
		 float x = mo.getCoordinates().first;
		 float y = mo.getCoordinates().second;

		 float mo_vx = mo.getVelocity().first;
		 float mo_vy = mo.getVelocity().second;


		 //hit to highest tile row
		 if ( (x<350 || x>600) && (y>150 && y<250)) {
			 if (x<350 && mo_vx<0 && (y>150+yo && y<250-yo) ) { //hit to the row end from right
				 mo.setCoordinates(std::make_pair(350.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (x>600 && mo_vx>0 && (y>150+yo && y<250-yo)) { //hit to the row end from left
				 mo.setCoordinates(std::make_pair(600.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (mo_vy<0) { //hit from below
				 mo.setCoordinates(std::make_pair(x, 250.0f+offset));
				 mo_vy=0;
			 }
			 else { //hit from above
				 mo.setCoordinates(std::make_pair(x, 150.0f-offset));
				 mo.setInAir(false);
				 mo_vy=0;
			 }


		 }
		 else if ( x>=350 && x<=600 && (y==(150.0f-offset))) { //hole in the highest tile row
			 mo.setInAir(true);
		 }


		 //row in the middle
		 if ( (x<100 || (x>200 && x<750) || x>850) && (y>300 && y<400)) {

			 if (x>200 && mo_vx>0 && (y>300+yo && y<400-yo) ) { //hit to the row end from left (works for all 3 rows)
				 mo.setCoordinates(x>850 ? std::make_pair(850.0f, y) : std::make_pair(200.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (x<750 && mo_vx<0 && (y>300+yo && y<400-yo)) { //hit to the row end from right (works for all 3 rows)
				 mo.setCoordinates(x<100 ? std::make_pair(100.0f, y) : std::make_pair(750.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (mo_vy<0) { //hit from below
				 mo.setCoordinates(std::make_pair(x, 400.0f+offset));
				 mo_vy=0;
			 }
			 else { //hit from above
				 mo.setCoordinates(std::make_pair(x, 300.0f-offset));
				 mo.setInAir(false);
				 mo_vy=0;
			 }

		 }
		 else if ( ((x>=100 && x<=200) || (x>=750 && x<=850)) && (y==(300.0f-offset))) { //holes in the central tile row
			 mo.setInAir(true);
		 }


		 //hit to lowest tile row
		 if ( (x<350 || x>600) && (y>450 && y<550)) {

			 if (x<350 && mo_vx<0 && (y>450+yo && y<550-yo) ) { //hit to the row end from right
				 mo.setCoordinates(std::make_pair(350.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (x>600 && mo_vx>0 && (y>450+yo && y<550-yo)) { //hit to the row end from left
				 mo.setCoordinates(std::make_pair(600.0f, y));
				 mo_vx= (-1.0f)*mo_vx;
			 }
			 else if (mo_vy<0) { //hit from below
				 mo.setCoordinates(std::make_pair(x, 550.0f+offset));
				 mo_vy=0;
			 }
			 else { //hit from above
				 mo.setCoordinates(std::make_pair(x, 450.0f-offset));
				 mo.setInAir(false);
				 mo_vy=0;
			 }


		 }
		 else if ( x>=350 && x<=600 && (y==(450.0f-offset))) { //hole in the lowest tile row
			 mo.setInAir(true);
		 }


		 if (y>601.1f) { //floor
			 mo.setCoordinates(std::make_pair(x, 600.0f-offset));
			 mo.setInAir(false);
			 mo_vy = 0;
		 }


		if (y<100.0f) { //ceiling
			mo.setCoordinates(std::make_pair(x, 100.0f+offset));
			mo_vy = 0;
		}

		 mo.setVelocity(std::pair<float, float>(mo_vx, mo_vy));
	 }


	  //! Draws all the Tiles stored to vector 'tiles'.
	  void Game::drawTiles() {
		  std::vector<Tile>::iterator iter;
		  for (iter = tiles.begin(); iter!=tiles.end(); iter++) {
			  (*iter).drawObject();
			  //(*iter).getOutline().draw(0,0,CL_Colorf::green, gameio.getGC());
		  }
	  }


	  //! Draws pipes to the game field.
	  void Game::drawPipes() {
	  //upper pipes
		game_graphic.getLeftPipeSprite().draw(gameio.getGC(), 0.0f, 100.0f);
		game_graphic.getRightPipeSprite().draw(gameio.getGC(), 900.0f, 100.0f);

		//lower pipes
		game_graphic.getLeftPipeSprite().draw(gameio.getGC(), 0.0f, 550.0f);
		game_graphic.getRightPipeSprite().draw(gameio.getGC(), 900.0f, 550.0f);

	  }
	 
	  //! Draws monsters to the game field.
	  void Game::drawMonsters() {
		  std::vector<Monster*>::iterator iter;
		  for (iter = monsters.begin(); iter!=monsters.end(); iter++) {
			  (*iter)->drawObject();
			  			  
			 //matin collision debugia	  
		  	 //(*iter)->getWinOutline().draw(0,0, CL_Colorf::red, gameio.getGC());
		 	 //(*iter)->getLoseOutline().draw(0,0, CL_Colorf::green, gameio.getGC());
		 	 //matin collision debug loppuu			  
		  }
		  
	  }

	  //! Draws coins.
	  void Game::drawCoins() {
		  std::vector<Coin>::iterator iter;
		  for (iter = coins.begin(); iter!=coins.end(); iter++) {
			 (*iter).drawObject();	
			 //(*iter).getOutline().draw(0,0,CL_Colorf::green, gameio.getGC());	  
		  }
		  
	  }
	  
	  //! Draws shrooms currently on the game field.
	  void Game::drawShrooms() {
		  std::vector<Shroom>::iterator iter;
		  for (iter = shrooms.begin(); iter!=shrooms.end(); iter++) {
			 (*iter).drawObject();	
			 //(*iter).getOutline().draw(0,0,CL_Colorf::green, gameio.getGC());	  
		  }
		  
	  }
	  
	  //! Draws the coins player have gathered to the up bar of the window.
	  void Game::drawGatheredCoins() {
	  int i = 0;
		  std::vector<Coin>::iterator iter;
		  for (iter = gatheredCoins.begin(); iter!=gatheredCoins.end(); iter++) {
			 //(*iter).setCoordinates(std::make_pair(i*50.0f, 50.0f));
			 (*iter).drawObject();	
			 i++;	  
		  }
		  
	  }


	//! Checks the collisions to of given player to other elements of the game.
	void Game::checkCollisions(Player& player){
		std::vector<Monster*>::iterator iter;
		for (iter = monsters.begin(); iter!=monsters.end(); iter++) {
			if( ( player.getOutline().collide(((*(*iter))).getWinOutline()) ) &&
			 !( ( (*iter)->getCoordinates().first < 100  || (*iter)->getCoordinates().first > 860) &&
			    ( (*iter)->getCoordinates().second < 160 || (*iter)->getCoordinates().second > 570) ) &&
			    ( player.getStarTime() == 0)) {
			    	
				(*iter)->kill();
				Coin coin((*iter)->getCoordinates().first,(*iter)->getCoordinates().second,gameio,game_graphic);
				coins.push_back(coin);
				game_graphic.getFx()[1].set_looping(false);
				game_graphic.getFx()[1].play();
				game_graphic.getFx()[1].set_position(0);
				
				int number;
				int rndx;
				int rndy;
				srand ( time(NULL) );
		  		number = rand() % 10;
		  		rndx = rand() % 1000;
		  		rndy = rand() % 3;
		  		rndy = (rndy+1) * 150;
		  		
		  		
				if(number > 5)	{
					Shroom shroom(rndx, rndy, gameio, game_graphic);
					shrooms.push_back(shroom);
				}
				
			}
			if(player.getOutline().collide(((*(*iter))).getLoseOutline()) && 
			!(((*iter)->getCoordinates().first < 100 || (*iter)->getCoordinates().first > 860) &&
			 ((*iter)->getCoordinates().second < 160 || (*iter)->getCoordinates().second > 570 )) ){
				if(player.getStarTime() == 0){
					
					player.hitByMonster();
					}
				
			}			
		}
		
		std::vector<Coin>::iterator coiniter;
		for (coiniter = coins.begin(); coiniter!=coins.end(); coiniter++) {
			if(player.getOutline().collide((*coiniter).getOutline())){
				player.addCoin();
				if(player.getIsFabio()){
					(*coiniter).setCoordinates(std::make_pair(player.getCoins()*50.0f, 25.0f));
					(*coiniter).getOutline().set_translation(player.getCoins()*50.0f, 25.0f);
				} else{
					(*coiniter).setCoordinates(std::make_pair(950-player.getCoins()*50.0f, 25.0f));
					(*coiniter).getOutline().set_translation(950-player.getCoins()*50.0f, 25.0f);
				}
				gatheredCoins.push_back((*coiniter));
			}		  
		}
		
		std::vector<Shroom>::iterator shroomiter;
		for (shroomiter = shrooms.begin(); shroomiter!=shrooms.end(); shroomiter++) {
			if(player.getOutline().collide((*shroomiter).getOutline())){
				player.growSuper();
				(*shroomiter).gather();
			}		  
		}
		
		
		
	}



	//! Runs the game.
	void Game::runGame() {	
					
		float total_time = 0.0f;
		unsigned int prev_time = CL_System::get_time();
		game_paused = false;
		game_started = true;
		game_over = false;
		game_graphic.getBgMusic().set_looping(true);
		game_graphic.getBgMusic().play();
		while (!game_over && !game_paused) {

			//check how much time has passed
			unsigned int curr_time = CL_System::get_time();
			float time = ( (unsigned int)(curr_time - prev_time)) / 1000.0f; //ms
			//fprintf(stderr, "time=%f, curr_time-prev_time=%u\n", time, (curr_time-prev_time));
			prev_time = curr_time;
			total_time += time;

			//TODO: move players here according to the input, or maybe inside handleInput?
			handleInput(time);
			if (game_paused) {
				game_graphic.getBgMusic().stop();
				break;
			}

			moveMonsters(time, total_time);
			movePlayers(time);

			//TODO: something like this:
			// Graphics: First clear the screen
			//gameio.getGC().clear(CL_Colorf::aquamarine);
			// .. then draw the background
			CL_Draw::texture(gameio.getGC(), game_graphic.getBackground(), CL_Quadf(game_graphic.getBackground().get_size()));
			//gameio.getGC().clear(CL_Colorf::white);
			//gameio.getGC().clear(CL_Colorf::aquamarine);

			//draw monsters
			drawMonsters();

			//draw pipes
			drawPipes();

			//draw coins
			drawCoins();

			drawShrooms();

			// draw players
			p1.drawObject();
			p2.drawObject();
			
			//matin collision debugia //////////////////////////////////////////////////////////////////////////
			//p1.getOutline().draw(0,0,CL_Colorf::yellow,gameio.getGC());
			//p2.getOutline().draw(0,0,CL_Colorf::yellow,gameio.getGC());
			//matin collision debug loppuu /////////////////////////////////////////////////////////////////////

			checkCollisions(p1);
			checkCollisions(p2);


			//draw tiles
			drawTiles();


			if(p1.getIsDead() || p2.getIsDead() || (p1.getCoins() + p2.getCoins()) == 5){
				game_over = true;
				game_started = false;
			}

			// Draw the window to the screen
			gameio.getWindow().flip();
			// Let ClanLib do its own processing
			CL_KeepAlive::process();
	
			//use refresh rate 100Hz
			CL_System::sleep(10);

			

		}
	
		if (game_over) {
			CL_Font font(gameio.getGC(), "Tahoma", 100);
			if(p1.getIsDead() || p2.getCoins() > p1.getCoins())
				font.draw_text(gameio.getGC(), 300, 300, "Uolevi won!", CL_Colorf::red);
			else
				font.draw_text(gameio.getGC(), 300, 300, "Fabio won!", CL_Colorf::red);
			
			drawGatheredCoins();
				
			gameio.getWindow().flip();
			
			CL_System::sleep(1500);
		}

	}


	//! assignment operator.
	Game& Game::operator=(const Game& orig){
		if (this != &orig) {
			Game gameCopy(orig);
			std::swap(p1, gameCopy.p1);
			std::swap(p2, gameCopy.p2);
			std::swap(game_started, gameCopy.game_started);
			std::swap(game_paused, gameCopy.game_paused);
			std::swap(game_over, gameCopy.game_over);
			std::swap(p1Jumped, gameCopy.p1Jumped);
			std::swap(p2Jumped, gameCopy.p2Jumped);
			std::swap(monsters, gameCopy.monsters);
			std::swap(tiles, gameCopy.tiles);
			std::swap(coins, gameCopy.coins);
			std::swap(gatheredCoins, gameCopy.gatheredCoins);
			std::swap(shrooms, gameCopy.shrooms);
		}

		return *this;
	}

