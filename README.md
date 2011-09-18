spacemouse
==========
A simple utility for converting input from a 3dconnexion 3d mouse to mouse and keyboard events.
Uses `libspnav` from the [spacenav open source driver project](http://spacenav.sourceforge.net/) and `libxdo` from the [xdotool project](http://www.semicomplete.com/projects/xdotool/).

Project status
--------------
This is the first release, which means the project is in it's infancy. The mouse and keyboard events are hardcoded atm. They are mapped with 'wasd' games in mind, i.e. first person type games with the `w`, `a`, `s` and `d` keys for movement and mouse for looking around. I'm planning to develop this further to at least use a config file for the bindings.

Installation
------------

Assuming Ubuntu, the following command should install dependencies and the open source driver:

	apt-get install libx11-dev libxdo-dev libspnav-dev spacenavd

Then clone this repository:

	git clone https://github.com/niklasekman/spacemouse.git

Compile and run:

	make
	./spacemouse


