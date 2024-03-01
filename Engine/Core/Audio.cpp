#include "../Include/Audio.h"

Audio::Audio() : soloud{ new SoLoud::Soloud } {
	soloud->init();
}
Audio::~Audio() {
	soloud->deinit();
}

void Audio::load(std::string path) {
	sample.load(path.c_str());
}
void Audio::play() {
	soloud->play(sample);
}

void Audio::load(std::string name, std::string path) {
	samples[name] = SoLoud::Wav{};
	samples[name].load(path.c_str());
}
SoLoud::handle Audio::play(std::string name) {
	return soloud->play(samples[name]);
}
SoLoud::handle Audio::playInLoop(std::string name) {
	SoLoud::handle han{ soloud->play(samples[name]) };
	soloud->setLooping(han, true);

	return han;
}
void Audio::pause(SoLoud::handle handle, bool isPause) {
	soloud->setPause(handle, isPause);
}
void Audio::stop(SoLoud::handle handle) {
	soloud->stop(handle);
}
void Audio::terminate() {
	soloud->deinit();
}