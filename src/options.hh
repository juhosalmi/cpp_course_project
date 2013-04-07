#ifndef OPTIONS_HH
#define OPTIONS_HH


//! Menu class.
/*!
Data container class for game options.
*/
class Options {

public:

	Options() :
		p1KeyLeft(CL_KEY_LEFT),
		p1KeyRight(CL_KEY_RIGHT),
		p1KeyUp(CL_KEY_UP),
		p2KeyLeft(CL_KEY_A),
		p2KeyRight(CL_KEY_D),
		p2KeyUp(CL_KEY_W)
	{ }




	// P1 KEYS
	
	//! Get P1 key left.
	/*!
	\return P1 key left.
	*/
	int getP1KeyLeft() {
		return p1KeyLeft;
	}
	
	//! Set P1 key left.
	/*!
	 \param key P1 key left.
	*/
	void setP1KeyLeft(int key) {
		p1KeyLeft = key;
	}
	
	//! Get P1 key right.
	/*!
	\return P1 key right.
	*/
	int getP1KeyRight() {
		return p1KeyRight;
	}
	
	//! Set P1 key right.
	/*!
	 \param key P1 key right.
	*/
	void setP1KeyRight(int key) {
		p1KeyRight = key;
	}
	
	//! Get P1 key up.
	/*!
	\return P1 key up.
	*/
	int getP1KeyUp() {
		return p1KeyUp;
	}
	
	//! Set P1 key up.
	/*!
	 \param key P1 key up.
	*/
	void setP1KeyUp(int key) {
		p1KeyUp = key;
	}
	
	
	// P2 KEYS
	
	//! Get P2 key left.
	/*!
	\return P2 key left.
	*/
	int getP2KeyLeft() {
		return p2KeyLeft;
	}
	
	//! Set P2 key left.
	/*!
	 \param key P2 key left.
	*/
	void setP2KeyLeft(int key) {
		p2KeyLeft = key;
	}
	
	//! Get P2 key right.
	/*!
	\return P2 key right.
	*/
	int getP2KeyRight() {
		return p2KeyRight;
	}
	
	//! Set P2 key right.
	/*!
	 \param key P2 key right.
	*/
	void setP2KeyRight(int key) {
		p2KeyRight = key;
	}
	
	//! Get P2 key up.
	/*!
	\return P2 key up.
	*/
	int getP2KeyUp() {
		return p2KeyUp;
	}
	
	//! Set P2 key up.
	/*!
	 \param key P2 key up.
	*/
	void setP2KeyUp(int key) {
		p2KeyUp = key;
	}
	
	/* Something that could have been done...
	// SETTINGS
	void saveSettings() { //TODO
		
	}
	
	void loadSettings(CL_String path) { // TODO
		
	}
	*/

private:
	//! Player 1 - Left
	int p1KeyLeft;
	//! Player 1 - Right
	int p1KeyRight;
	//! Player 1 - Up
	int p1KeyUp;

	//! Player 2 - Left
	int p2KeyLeft;
	//! Player 2 - Right
	int p2KeyRight;
	//! Player 2 - Up
	int p2KeyUp;

};

#endif
