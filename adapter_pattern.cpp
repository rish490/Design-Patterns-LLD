#include <iostream>
using namespace std;

/*
    ============================================================
       🎧 ADAPTER DESIGN PATTERN — Real-World + C++ Example
    ============================================================

    🔹 Intent:
       The Adapter Pattern allows incompatible classes to work together.
       It acts as a bridge between two interfaces that otherwise can’t communicate.

    🔹 Real-world analogies:
       ----------------------------------------------------------
       1️⃣ **Charging Adapter** — Converts a USB-C plug to a Lightning port.
       2️⃣ **Card Reader** — Lets an SD card (Adaptee) be used through a USB interface (Target).
       3️⃣ **Language Translator** — Converts your English into Japanese for a Japanese listener.
       4️⃣ **HDMI to VGA Converter** — Connects a new laptop (HDMI output) to an old projector (VGA input).
       ----------------------------------------------------------

    🔹 In this example:
       - The system expects to use `AudioPlayer::play()` (Target interface).
       - The existing class `WAVPlayer` has a different method `playWAV()` (Adaptee).
       - The `WAVToMP3Adapter` converts one interface into the other.

    🔹 Key participants:
       - Target → AudioPlayer
       - Adaptee → WAVPlayer
       - Adapter → WAVToMP3Adapter
       - Client → main()
*/

// =======================================================
// 🎯 TARGET INTERFACE — defines what the client expects
// =======================================================
class AudioPlayer {
public:
    virtual void play() = 0; // Expected interface
    virtual ~AudioPlayer() {}
};

// =======================================================
// 🎵 CONCRETE CLASS — already compatible with AudioPlayer
// =======================================================
class MP3Player : public AudioPlayer {
public:
    void play() override {
        cout << "Playing MP3 audio..." << endl;
    }
};

// =======================================================
// ⚙️ ADAPTEE — legacy or external class with incompatible API
// =======================================================
class WAVPlayer {
public:
    void playWAV() {
        cout << "Playing WAV audio..." << endl;
    }
};

// =======================================================
// 🔌 ADAPTER — bridges AudioPlayer and WAVPlayer
// =======================================================
class WAVToMP3Adapter : public AudioPlayer {
private:
    WAVPlayer* wavPlayer; // composition: adapter has a WAVPlayer
public:
    WAVToMP3Adapter(WAVPlayer* wp) : wavPlayer(wp) {}

    void play() override {
        cout << "Adapter converting MP3 play request to WAV format..." << endl;
        wavPlayer->playWAV(); // delegate to adaptee
    }
};

// =======================================================
// 🧠 CLIENT CODE — works only with AudioPlayer interface
// =======================================================
int main() {
    // Create an MP3 player (already compatible)
    AudioPlayer* mp3Player = new MP3Player();
    mp3Player->play();

    // Create a WAV player (incompatible with AudioPlayer)
    WAVPlayer* wav = new WAVPlayer();

    // Use an adapter to make WAVPlayer work through AudioPlayer interface
    AudioPlayer* adapter = new WAVToMP3Adapter(wav);
    adapter->play();

    // 🧹 Clean up memory
    delete mp3Player;
    delete wav;
    delete adapter;

    return 0;
}

/*
    =========================================================
        📚 QUICK RECAP & REVISION NOTES
    =========================================================

    🔸 STRUCTURE SUMMARY:
        [Client] ---> [Target Interface] ---> [Adapter] ---> [Adaptee]

    🔸 CLASSES:
        1️⃣ AudioPlayer (Target) - interface client uses.
        2️⃣ MP3Player (Concrete Target) - already supports play().
        3️⃣ WAVPlayer (Adaptee) - legacy class with playWAV().
        4️⃣ WAVToMP3Adapter (Adapter) - converts play() → playWAV().

    🔸 BEHAVIOR:
        - Client calls play() on AudioPlayer.
        - Adapter intercepts and redirects to WAVPlayer’s playWAV().

    🔸 WHY IT’S USEFUL:
        ✅ Integrate old code with new systems.
        ✅ Avoid modifying stable/legacy code.
        ✅ Promotes Open/Closed Principle (open to extension, closed to modification).
        ✅ Helps plug incompatible APIs together seamlessly.

    =========================================================
       🌍 MORE REAL-WORLD USE CASES FOR ADAPTER PATTERN
    =========================================================

    🧩 Software Examples:
        - **Java I/O Streams** → InputStreamReader adapts byte streams to character streams.
        - **C++ STL Iterators** → std::back_inserter adapts containers to output iterators.
        - **Spring Framework (Java)** → adapters connect old interfaces with new controllers.
        - **Payment Gateways** → unify different APIs like PayPal, Stripe, Razorpay under one interface.
        - **Logging frameworks** → adapt different log libraries into a single Logger interface.

    🧰 Hardware Examples:
        - HDMI-to-VGA adapter
        - Type-C to headphone jack adapter
        - Multi-country travel power adapter

    =========================================================
        💬 ONE-LINE SUMMARY:
        “Adapter Pattern converts one interface into another
         so classes can work together that couldn’t otherwise.”
    =========================================================
*/
