#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SoLoud/soloud.h>
#include <SoLoud/soloud_wav.h>

class Audio {
private:
	std::string LOG{ "SYSMA::ENGINE::AUDIO::" };

	SoLoud::Soloud soloud;
	SoLoud::Wav sample;
	SoLoud::handle handle;

public:
	Audio();
	~Audio();

	void load(std::string path);
	void play();
	//void pause();
	//void stop();
};