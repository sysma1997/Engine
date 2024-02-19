#include "../Include/Audio.h"

SoLoud::Soloud Audio::Soloud;
SoLoud::Wav Audio::Sample;
SoLoud::handle Audio::Handle;

void Audio::Load(std::string path) {
	Sample.load(path.c_str());
}
void Audio::Play() {
	Handle = Soloud.play(Sample);
}
void Audio::Pause() {
	Soloud.setPause(Handle, true);
}
void Audio::Stop() {
	Soloud.stop(Handle);
}