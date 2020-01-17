#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <io.h>
#include <stdio.h>
#include <windows.h>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <../../volume/volume/volume.h>
#include <conio.h> 
#include <Winuser.h>
#pragma comment(lib, "winmm.lib")

VolumeUnit v = VolumeUnit::Scalar;

int nVirtKey = 0xAE;
float MAX_VOLUME_LEVEL;
int VOLUME_CHANGE_TIME;
float level_per_second;
bool changing_volume = false;

namespace
{
	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t SUCCESS = 0;
	const size_t ERROR_UNHANDLED_EXCEPTION_ = 2;

}

void volume_control(float MAX_VOLUME_LEVEL, int VOLUME_CHANGE_TIME, float level_per_second)
{
	int i = 0;
	float vol = GetSystemVolume(v);
	double new_lvl;

	while (changing_volume)	{
		// This function set the correct volume level while sound is playing
		// Even if the user will decrease a system volume level, this algorithm will set the correct volume level for certain time
		// The correct volume level means the volume integer value match time interval
		// what can be calculated by MAX_VOLUME_LEVEL / VOLUME_CHANGE_TIME * i, where "i" is number of seconds from program start moment

		if (vol < MAX_VOLUME_LEVEL) {
			new_lvl = 0.02 + level_per_second * i;
			if (new_lvl > MAX_VOLUME_LEVEL) {
				new_lvl = MAX_VOLUME_LEVEL;
			}
			SetSystemVolume(new_lvl, v);
			i++;
		}
		vol = GetSystemVolume(v);
		Sleep(1000);
	}
}


void play_sound(const char *filename, int repeats)
{
	changing_volume = true;
	std::thread volume_thread(volume_control, MAX_VOLUME_LEVEL, VOLUME_CHANGE_TIME, level_per_second);

	// convert char value filename to wchar_t for PlaySound function
	size_t size = strlen(filename) + 1;
	wchar_t* ptr = new wchar_t[size];
	size_t outSize;
	mbstowcs_s(&outSize, ptr, size, filename, size - 1);

	PlaySound(ptr, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
	std::cout << "file ended";

	// stop volume changing
	changing_volume = false;
	// wait for colume changing thread is ends
	volume_thread.join();
}


int main(int argc, char** argv)
{
	namespace po = boost::program_options;
	po::options_description desc("General options");
	std::string filename;

	int volume;
	int repeats;
	int time;

	desc.add_options()
		("help,h", "Show help")
		("filename,f", po::value<std::string>(&filename)->default_value("alarm.wav"), "filename")
		("volume,v", po::value<int>(&volume)->default_value(10), "max volume 0-100")
		("repeats,r", po::value<int>(&repeats)->default_value(2), "repeats count")
		("time,t", po::value<int>(&time)->default_value(30), "volume change steps");


	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc, argv, desc),
			vm); // can throw 

		if (vm.count("help"))
		{
			std::cout << "Basic Command Line Parameter App" << std::endl
				<< desc << std::endl;
			return SUCCESS;
		}

		po::notify(vm); // throws on error, so do after help in case 
						// there are any problems 
	}
	catch (po::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << desc << std::endl;
		return ERROR_IN_COMMAND_LINE;
	}

	const char * f = filename.c_str();
	if (_access(f, 00) != 0)	{
		printf("Filename not found");
		exit(EXIT_FAILURE);
	}

	// define main variables
	MAX_VOLUME_LEVEL = float(volume) / 100;
	VOLUME_CHANGE_TIME = time;
	level_per_second = MAX_VOLUME_LEVEL / VOLUME_CHANGE_TIME;

	for (int i = 0; i < repeats; i++)
	{
		int start = 0;
		SetSystemVolume(0.02, v);
		std::thread sound_thread(play_sound, f, repeats);
		sound_thread.join();
		printf("\nplaying process %d completed", i+1);
	}
	
	return 1;
}



