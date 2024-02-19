#pragma once

#include <string>
#include <SoLoud/soloud.h>
#include <SoLoud/soloud_wav.h>

class Audio {
private:
	static SoLoud::Soloud Soloud;
	static SoLoud::Wav Sample;
	static SoLoud::handle Handle;

public:
	static void Load(std::string path);
	static void Play();
	static void Pause();
	static void Stop();
};