#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <alsa/asoundlib.h>

#include "src/cpp/piper.hpp"
#include "piperclass.hpp"

using namespace std;
using json = nlohmann::json;

namespace piper {

PiperClass::PiperClass(const std::string& modelPath, const std::string& dataPath) {
    piperConfig.eSpeakDataPath = dataPath;
    std::optional<SpeakerId> speakerId;
    loadVoice(piperConfig, modelPath, modelPath + ".json", voice, speakerId, false);
    initialize(piperConfig);
}

PiperClass::~PiperClass() {
    terminate(piperConfig);
}

void PiperClass::say(const std::string& text) {
    if (text.empty()) return;

    std::vector<int16_t> audioBuffer;
    SynthesisResult result;
    textToAudio(piperConfig, voice, text, audioBuffer, result, nullptr);
    playAudioAlsa(audioBuffer.data(), audioBuffer.size());
}

void PiperClass::playAudioAlsa(void* audioBuffer, size_t bufferSizeInSamples) {
		snd_pcm_t *handle;
		snd_pcm_sframes_t frames;

		if (snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
			std::cerr << "The audio device cannot be opened.\n";
			exit(1);
		}

		if (snd_pcm_set_params(handle,
							   SND_PCM_FORMAT_S16_LE,
							   SND_PCM_ACCESS_RW_INTERLEAVED,
							   1, // (mono)
							   22050, // 22050 Hz 
							   1, // Soft resampling
							   500000) < 0) { // 500000 us = 0.5s delay
			std::cerr << "Błąd konfiguracji PCM.\n";
			exit(1);
		}
		
		int silentSamples = 22050 * 0.6;
		size_t totalSamples = silentSamples + bufferSizeInSamples;
		int16_t* newBuffer = new int16_t[totalSamples];
		memset(newBuffer, 0, silentSamples * sizeof(int16_t)); // Fill it with silence
		memcpy(newBuffer + silentSamples, audioBuffer, bufferSizeInSamples * sizeof(int16_t)); 
		
		frames = snd_pcm_writei(handle, newBuffer, totalSamples);
		if (frames < 0) frames = snd_pcm_recover(handle, frames, 0);

		snd_pcm_drain(handle);
		snd_pcm_close(handle);
		delete[] newBuffer;
}

}