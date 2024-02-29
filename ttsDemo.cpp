#include <functional>
#include <iostream>
#include <string>
#include <signal.h>

#include "lib/piper/piperclass.hpp"

using namespace std;

int main() {
    //Choose your language and voice	
	//piper::PiperClass piper("lib/piper/models/pl/gosia/pl_PL-gosia-medium.onnx", "lib/piper/lib/espeak-ng-data");
	piper::PiperClass piper("lib/piper/models/en/amy/en_US-amy-medium.onnx", "lib/piper/lib/espeak-ng-data");
	
    while (true) {
        string text;
        cout << "Enter the text to synthesize (CTRL+C to finish): ";
        getline(cin, text);

        piper.say(text);
    }

    return EXIT_SUCCESS;
}
