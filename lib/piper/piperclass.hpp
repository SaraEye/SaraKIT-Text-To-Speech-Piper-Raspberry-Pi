#ifndef PIPERCLASS_HPP
#define PIPERCLASS_HPP

#include "src/cpp/piper.hpp"

namespace piper {

class PiperClass {
private:
    PiperConfig piperConfig;
    Voice voice;

    void playAudioAlsa(void* audioBuffer, size_t bufferSizeInSamples);
public:
    PiperClass(const std::string& modelPath, const std::string& dataPath);
    ~PiperClass();
    void say(const std::string& text);
};

} // namespace piper


#endif // PIPER_HPP
