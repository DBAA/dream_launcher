# dream_launcher

Being developped in openFrameworks 0.9.8 using Visual Studio 2015

Games and launcher can all be found here (you need access to the DBAA drive): https://drive.google.com/file/d/1FU0trKjiFTmyVm3DkcyMQJSRTVrT1XmZ/view?usp=drive_link

You may need to run some of the installers in files_to_install when deploying on a new machine

Most of the relevant files (the launcher etc) can be found in dream_launcher/bin

Use dream_launcher.exe NOT dream_launcher_debug.exe

If you move the EXE, bring all the .dll files with it. Your best bet is to just copy the whole bin folder.

You need to edit dream_launcher/bin/data/games.xml to math the file locations of the games


I hid the console with this:
https://www.youtube.com/watch?v=o_BB5-Z65dc

Probably need to undo it if you want the console.
To turn it back on go to:
Project->dream_launcher properties

Then in the configuration window go to
Linker->System and change the SubSystem value

Windows (/SUBSYSTEM:WINDOWS)	=	no console
Console (/SUBSYSTEM:CONSOLE)	= console