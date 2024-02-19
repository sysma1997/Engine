#include "../Include/Audio.h"

Audio::Audio() {
	soloud.init();
}
Audio::~Audio() {
	soloud.deinit();
}

void Audio::load(std::string path) {
	sample.load(path.c_str());
}
void Audio::play() {
	handle = soloud.play(sample);
}
//void Audio::pause() {
//	soloud.setPause(handle, true);
//}
//void Audio::stop() {
//	soloud.stop(handle);
//}