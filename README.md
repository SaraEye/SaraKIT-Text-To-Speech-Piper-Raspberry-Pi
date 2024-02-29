# Text To Speech with SaraKIT

SaraKIT is equipped with three microphones and a specialized sound processor that cleans voice audio and supports speech recognition on Raspberry Pi from distances up to 5 meters, as described in our "Speech Recognition" section. However, to complete the setup, we now turn our attention to text-to-speech (TTS) processing, which can be incredibly useful for building voice assistants, talking devices, or integrating with Home Automation (HA) systems. While the best TTS systems currently available are online services like ElevenLabs (paid) which offers top-notch voice quality, or Google Text to Speech (detailed in a separate section), here we focus on offline text-to-speech processing.

After scouring the internet for the best current offline, fast, and easy-to-install option, Piper stands out as the top choice (if you find something better, please let us know).

Piper is fast, generates high-quality voice in real-time, and is optimized for Raspberry Pi 4. Although its installation is straightforward, I have further simplified it for you, and a demo with a description is provided below.

You can test Piper at:
[https://rhasspy.github.io/piper-samples/](https://rhasspy.github.io/piper-samples/)

Piper on GitHub:
[https://github.com/rhasspy/piper](https://github.com/rhasspy/piper) <br>
[https://github.com/rhasspy/piper-phonemize](https://github.com/rhasspy/piper-phonemize) (an additional component)

Voices for Piper:
[https://huggingface.co/rhasspy/piper-voices/tree/v1.0.0](https://huggingface.co/rhasspy/piper-voices/tree/v1.0.0)

## Installation on SaraKIT

Assuming the basic SaraKIT drivers are already installed ([https://sarakit.saraai.com/getting-started/software](https://sarakit.saraai.com/getting-started/software)), follow these steps to install Piper:

```bash
sudo apt-get install libasound2-dev
sudo apt-get install libfmt-dev
sudo apt-get install libspdlog-dev

git clone https://github.com/SaraEye/SaraKIT-Text-To-Speech-Piper-Raspberry-Pi piper
cd piper
make

sudo cp -r lib/piper/*.* /usr/local/lib/
sudo ldconfig
```

To use a language other than English, download the required language model from [https://huggingface.co/rhasspy/piper-voices/tree/v1.0.0](https://huggingface.co/rhasspy/piper-voices/tree/v1.0.0) and place it in a directory, e.g., `lib/piper/models`.

Start speech recognition by running:
```bash
./ttsDemo
```

Below is the text to speech script in your chosen language, available at
[https://github.com/SaraEye/SaraKIT-Text-To-Speech-Piper-Raspberry-Pi](https://github.com/SaraEye/SaraKIT-Text-To-Speech-Piper-Raspberry-Pi) :

```cpp
// Sample code
```

The effects of this simple yet powerful script can be seen in the video below:

[Video Link]

 
