#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sound.h>
#include <ClanLib/application.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/gui.h>
#include <iostream>

bool quit = false;

void my_callback(const CL_InputEvent &event, const CL_InputState &state)
{
	if (event.id == CL_KEY_ESCAPE)
		quit = true;
	std::cout << event.id << std::endl;
}
 
int main(int, char**)
{
	try
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;
 
		CL_DisplayWindow window("Hyper Fabio Brothers", 1000, 750);
		CL_InputContext ic = window.get_ic();
		CL_InputDevice keyboard = ic.get_keyboard();
		CL_Slot slot = keyboard.sig_key_up().connect(&my_callback);
 
		while (!quit)
		{
			CL_KeepAlive::process();
			window.get_gc().clear(CL_Colorf::white);
			window.flip();
			CL_System::sleep(10);
		}
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();
 
		return -1;
	}
 
	return 0;
}

	
	

