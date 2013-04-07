#ifndef GAMEGRAPHIC_HH
#define GAMEGRAPHIC_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>

#include <vector>

#include "gameio.hh"

//! GameGraphic struct.
/*!
GameGraphic struct contains and initializes all necessary graphics and sounds for the game.
*/

struct GameGraphic {

public:

	//! GameGraphic constructor.
	/*!
	Initializes all necessary graphics and sounds. All paths for graphics and sound are hard-coded here.
	
	\param gameio GameIO object containing the I/O objects needed in the game.
	 */
	
	GameGraphic(GameIO& gameio) : gameio(gameio) {
		
		// Load background stuff
		CL_PixelBuffer bg_pb(CL_PNGProvider::load("images/bg.png"));
 		background = CL_Texture(gameio.getGC(), cl_texture_2d);
		background.set_image(bg_pb);
		
		bg_music = CL_SoundBuffer("sounds/bg_music.ogg").prepare();
		
		
		std::vector<CL_String> leftPipePaths;
		leftPipePaths.push_back("images/vasenputki.png");
		leftPipeSprite = loadSprite(leftPipePaths);
		
		std::vector<CL_String> rightPipePaths;
		rightPipePaths.push_back("images/oikeaputki.png");
		rightPipeSprite = loadSprite(rightPipePaths);
			
		// Load menu background stuff
		CL_PixelBuffer menu_bg_pb(CL_PNGProvider::load("images/menu_bg.png"));
 		menu_background = CL_Texture(gameio.getGC(), cl_texture_2d);
		menu_background.set_image(menu_bg_pb);
		
		menu_bg_music = CL_SoundBuffer("sounds/menu_bg_music.ogg").prepare();
		
		// Load Fabio images
		std::vector<CL_String> stillFabioPaths;
		stillFabioPaths.push_back("images/fabio.png");
		stillFabioSprite = loadSprite(stillFabioPaths);
		
		std::vector<CL_String> stillSuperFabioPaths;
		stillSuperFabioPaths.push_back("images/superfabio.png");
		stillSuperFabioSprite = loadSprite(stillSuperFabioPaths);
		
		std::vector<CL_String> movingFabioPaths;
		movingFabioPaths.push_back("images/fabio1.png");
		movingFabioPaths.push_back("images/fabio2.png");
		movingFabioSprite = loadSprite(movingFabioPaths);
		
		std::vector<CL_String> movingSuperFabioPaths;
		movingSuperFabioPaths.push_back("images/superfabio1.png");
		movingSuperFabioPaths.push_back("images/superfabio2.png");
		movingSuperFabioSprite = loadSprite(movingSuperFabioPaths);
		
		std::vector<CL_String> jumpingSuperFabioPaths;
		jumpingSuperFabioPaths.push_back("images/superfabio2.png");
		jumpingSuperFabioSprite = loadSprite(jumpingSuperFabioPaths);
		
		std::vector<CL_String> jumpingFabioPaths;
		jumpingFabioPaths.push_back("images/fabio2.png");
		jumpingFabioSprite = loadSprite(jumpingFabioPaths);
		
		// Load Uolevi images
		std::vector<CL_String> stillUoleviPaths;
		stillUoleviPaths.push_back("images/uolevi.png");
		stillUoleviSprite = loadSprite(stillUoleviPaths);
		
		std::vector<CL_String> stillSuperUoleviPaths;
		stillSuperUoleviPaths.push_back("images/superuolevi.png");
		stillSuperUoleviSprite = loadSprite(stillSuperUoleviPaths);
		
		std::vector<CL_String> movingUoleviPaths;
		movingUoleviPaths.push_back("images/uolevi1.png");
		movingUoleviPaths.push_back("images/uolevi2.png");
		movingUoleviSprite = loadSprite(movingUoleviPaths);
		
		std::vector<CL_String> movingSuperUoleviPaths;
		movingSuperUoleviPaths.push_back("images/superuolevi1.png");
		movingSuperUoleviPaths.push_back("images/superuolevi2.png");
		movingSuperUoleviSprite = loadSprite(movingSuperUoleviPaths);
		
		std::vector<CL_String> jumpingSuperUoleviPaths;
		jumpingSuperUoleviPaths.push_back("images/superuolevi2.png");
		jumpingSuperUoleviSprite = loadSprite(jumpingSuperUoleviPaths);
		
		std::vector<CL_String> jumpingUoleviPaths;
		jumpingUoleviPaths.push_back("images/uolevi2.png");
		jumpingUoleviSprite = loadSprite(jumpingUoleviPaths);
		
		// Load goomba images
		std::vector<CL_String> stillGoombaPaths;
		stillGoombaPaths.push_back("images/goomba.png");
		stillGoombaSprite = loadSprite(stillGoombaPaths);
		
		std::vector<CL_String> movingGoombaPathsl;
		movingGoombaPathsl.push_back("images/goomba1l.png");
		movingGoombaPathsl.push_back("images/goomba2l.png");
		movingGoombaSpritel = loadSprite(movingGoombaPathsl);
		
		std::vector<CL_String> movingGoombaPathsr;
		movingGoombaPathsr.push_back("images/goomba1r.png");
		movingGoombaPathsr.push_back("images/goomba2r.png");
		movingGoombaSpriter = loadSprite(movingGoombaPathsr);
		
		// Load koopa images
		std::vector<CL_String> stillKoopaPaths;
		stillKoopaPaths.push_back("images/koopa.png");
		stillKoopaSprite = loadSprite(stillKoopaPaths);
		
		std::vector<CL_String> movingKoopaPathsl;
		movingKoopaPathsl.push_back("images/koopa1l.png");
		movingKoopaPathsl.push_back("images/koopa2l.png");
		movingKoopaSpritel = loadSprite(movingKoopaPathsl);
		
		std::vector<CL_String> movingKoopaPathsr;
		movingKoopaPathsr.push_back("images/koopa1r.png");
		movingKoopaPathsr.push_back("images/koopa2r.png");
		movingKoopaSpriter = loadSprite(movingKoopaPathsr);
		
		// Load tile images
		std::vector<CL_String> stillTilePaths;
		stillTilePaths.push_back("images/tile.png");
		stillTileSprite = loadSprite(stillTilePaths);
		
		std::vector<CL_String> movingTilePaths;
		movingTilePaths.push_back("images/tile1.png");
		movingTilePaths.push_back("images/tile2.png");
		movingTileSprite = loadSprite(movingTilePaths);
		
		// Load shroom images
		std::vector<CL_String> shroomPaths;
		shroomPaths.push_back("images/shroom.png");
		shroomSprite = loadSprite(shroomPaths);
		
		// Load coin images
		std::vector<CL_String> coinPaths;
		coinPaths.push_back("images/coin.png");
		coinSprite = loadSprite(coinPaths);		
		
		// Load dead image
		std::vector<CL_String> deadPaths;
		deadPaths.push_back("images/dead.png");
		deadSprite = loadSprite(deadPaths);
		
		// Load sound effects
		std::vector<CL_String> effectsPaths;
		effectsPaths.push_back("sounds/effect1.ogg");
		effectsPaths.push_back("sounds/effect2.ogg");
		effects = initSoundBuffer_Session(effectsPaths);
		
		// Load menu sound effects
		std::vector<CL_String> menu_effectsPaths;
		menu_effectsPaths.push_back("sounds/menu_effect1.ogg");
		menu_effectsPaths.push_back("sounds/menu_effect2.ogg");
		menu_effects = initSoundBuffer_Session(menu_effectsPaths);
		
	 
	}
	
	//! Copy-constructor.
	/*!
		\param other reference to the object to be copied.
	*/
	GameGraphic(GameGraphic& other) : gameio(other.gameio)
	{
	}
	
	//! Assignment-operator.
	/*!
		\param other reference to the object to be assigned.
	*/
	GameGraphic& operator=(GameGraphic& other){
		GameGraphic newgg(other);
		GameGraphic& ggref = newgg;
		
		return ggref;
	}
	
	//! Destructor.
	/*!
	RO3.
	*/
	~GameGraphic(){}
	
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getStillFabioSprite() { return stillFabioSprite; }
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getStillSuperFabioSprite() { return stillSuperFabioSprite; }
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getMovingFabioSprite() { return movingFabioSprite; }
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getMovingSuperFabioSprite() { return movingSuperFabioSprite; }
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getJumpingFabioSprite() { return jumpingFabioSprite; }
	//! Getter for fabio sprite.
	/*!
	\return fabio sprite.
	*/
	CL_Sprite getJumpingSuperFabioSprite() { return jumpingSuperFabioSprite; }
	//! Getter for uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getStillUoleviSprite() { return stillUoleviSprite; }
	//! Getter for  uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getStillSuperUoleviSprite() { return stillSuperUoleviSprite; }
	//! Getter for uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getMovingUoleviSprite() { return movingUoleviSprite; }
	//! Getter for uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getMovingSuperUoleviSprite() { return movingSuperUoleviSprite; }
	//! Getter for uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getJumpingUoleviSprite() { return jumpingUoleviSprite; }
	//! Getter for uolevi sprite.
	/*!
	\return uolevi sprite.
	*/
	CL_Sprite getJumpingSuperUoleviSprite() { return jumpingSuperUoleviSprite; }
	//! Getter for goomba sprite.
	/*!
	\return goomba.
	*/
	CL_Sprite getStillGoombaSprite() { return stillGoombaSprite; }
	//! Getter for goomba sprite.
	/*!
	\return goomba.
	*/
	CL_Sprite getMovingGoombaSpriteL() { return movingGoombaSpritel; }
	//! Getter for goomba sprite.
	/*!
	\return goomba.
	*/
	CL_Sprite getMovingGoombaSpriteR() { return movingGoombaSpriter; }
	//! Getter for koopa sprite.
	/*!
	\return koopa.
	*/
	CL_Sprite getStillKoopaSprite() { return stillKoopaSprite; }
	//! Getter for koopa sprite.
	/*!
	\return koopa.
	*/
	CL_Sprite getMovingKoopaSpriteL() { return movingKoopaSpritel; }
	//! Getter for koopa.
	/*!
	\return koopa.
	*/
	CL_Sprite getMovingKoopaSpriteR() { return movingKoopaSpriter; }
	//! Getter for koopa sprite.
	/*!
	\return koopa.
	*/
	CL_Sprite getStillTileSprite() { return stillTileSprite; }
	//! Getter for tile sprite.
	/*!
	\return tile.
	*/
	CL_Sprite getMovingTileSprite() { return movingTileSprite; }
	//! Getter for shroom sprite.
	/*!
	\return shroom.
	*/
	CL_Sprite getShroomSprite() { return shroomSprite; }
	//! Getter for coin sprite.
	/*!
	\return coin.
	*/
	CL_Sprite getCoinSprite() { return coinSprite; }
	//! Getter for background texture.
	/*!
	\return background texture.
	*/
	CL_Texture& getBackground() { return background; }
	//! Getter for menu background texture.
	/*!
	\return background texture.
	*/
	CL_Texture& getMenuBackground() { return menu_background; }
	//! Getter for pipe sprite.
	/*!
	\return pipe sprite.
	*/
	CL_Sprite getLeftPipeSprite() { return leftPipeSprite; }
	//! Getter for pipe sprite.
	/*!
	\return pipe sprite.
	*/
	CL_Sprite getRightPipeSprite() { return rightPipeSprite; }
	//! Getter for dead sprite.
	/*!
	\return dead sprite.
	*/
	CL_Sprite getDeadSprite() { return deadSprite; }
	//! Getter for background music.
	/*!
	\return background music.
	*/
	CL_SoundBuffer_Session getBgMusic() { return bg_music; }
	//! Getter for menu background music.
	/*!
	\return menu background music.
	*/
	CL_SoundBuffer_Session getMenuBgMusic() { return menu_bg_music; }
	//! Getter for effect sounds.
	/*!
	\return effect sounds.
	*/
	std::vector<CL_SoundBuffer_Session> getFx() { return effects; }
	//! Getter for menu effect sounds.
	/*!
	\return menu effect sounds.
	*/
	std::vector<CL_SoundBuffer_Session> getMenuFx() { return menu_effects; }
	
	

private:
	//! gameio.
	GameIO& gameio;
	
	//CL_PixelBuffer bg_pixbuffer;
	//CL_PixelBuffer menu_bg_pixbuffer;
	
	//! background.
	CL_Texture background;
	//! menu background.
	CL_Texture menu_background;
	//! bg_music.
	CL_SoundBuffer_Session bg_music;
	//! menu_bg_music.
	CL_SoundBuffer_Session menu_bg_music;
	//! effects.
	std::vector<CL_SoundBuffer_Session> effects;
	//! menu_effects.
	std::vector<CL_SoundBuffer_Session> menu_effects;
	//! stillFabioSprite.
	CL_Sprite stillFabioSprite;
	//! stillSuperFabioSprite.
	CL_Sprite stillSuperFabioSprite;
	//! movingFabioSprite.
	CL_Sprite movingFabioSprite;
	//! movingSuperFabioSprite.
	CL_Sprite movingSuperFabioSprite;
	//! jumpingFabioSprite.
	CL_Sprite jumpingFabioSprite;
	//! jumpingSuperFabioSprite.
	CL_Sprite jumpingSuperFabioSprite;
	//! stillUoleviSprite.
	CL_Sprite stillUoleviSprite;
	//! stillSuperUoleviSprite.
	CL_Sprite stillSuperUoleviSprite;
	//! movingUoleviSprite.
	CL_Sprite movingUoleviSprite;
	//! movingSuperUoleviSprite.
	CL_Sprite movingSuperUoleviSprite;
	//! jumpingUoleviSprite.
	CL_Sprite jumpingUoleviSprite;
	//! jumpingSuperUoleviSprite.
	CL_Sprite jumpingSuperUoleviSprite;
	//! stillGoombaSprite.
	CL_Sprite stillGoombaSprite;
	//! movingGoombaSpritel.
	CL_Sprite movingGoombaSpritel;
	//! movingGoombaSpriter.
	CL_Sprite movingGoombaSpriter;
	//! stillKoopaSprite.
	CL_Sprite stillKoopaSprite;
	//! movingKoopaSpritel.
	CL_Sprite movingKoopaSpritel;
	//! movingKoopaSpriter.
	CL_Sprite movingKoopaSpriter;
	//! stillTileSprite.
	CL_Sprite stillTileSprite;
	//! movingTileSprite.
	CL_Sprite movingTileSprite;
	//! shroomSprite.
	CL_Sprite shroomSprite;
	//! coinSprite.
	CL_Sprite coinSprite;
	//! leftPipeSprite.
	CL_Sprite leftPipeSprite;
	//! rightPipeSprite.
	CL_Sprite rightPipeSprite;
	//! deadSprite.
	CL_Sprite deadSprite;


	
	//! loads the object sprite.
	/*!
		\param path to the image.
		\return sprite.
	*/
	CL_Sprite loadSprite(std::vector<CL_String> paths){
		CL_SpriteDescription desc;
		std::vector<CL_String>::iterator iter;
		for (iter = paths.begin(); iter != paths.end(); iter++){
    			desc.add_frame(CL_PNGProvider::load( (*iter) ));
    		}  		
    	CL_Sprite sprite(gameio.getGC(), desc);
    	return sprite;
	}
	
	//! initializes the soundbuffer session.
	/*!
		\param paths the paths to the sounds.
		\return ready sound sessions.
	*/
	std::vector<CL_SoundBuffer_Session> initSoundBuffer_Session(std::vector<CL_String> paths) {
		std::vector<CL_SoundBuffer_Session> sessions;
		for (std::vector<CL_String>::iterator iter = paths.begin(); iter != paths.end(); iter++) {
			
			CL_SoundBuffer_Session effect = CL_SoundBuffer(*iter).prepare();
 			effect.set_position(0);
    			sessions.push_back(effect);
			
    		}
    		
    	return sessions;
	}
	
	
	
};

#endif
