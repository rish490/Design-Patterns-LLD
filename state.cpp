/*
    ============================================
                STATE DESIGN PATTERN
    ============================================

    📘 PURPOSE:
    The State Design Pattern allows an object to change its behavior
    when its internal state changes — without using complex if-else or switch statements.

    📦 REAL-WORLD ANALOGY:
    Think of a Music Player.
    - When stopped → pressing play starts the music.
    - When playing → pressing pause pauses it, pressing stop stops it.
    - When paused  → pressing play resumes, pressing stop stops it.
    The behavior changes depending on the current *state*.

    🧠 WHY USE THIS PATTERN:
    - Avoids large chains of if/else or switch statements.
    - Makes it easy to add new states later (e.g., LoadingState, ErrorState).
    - Encapsulates state-specific behavior inside dedicated classes.

    🚫 WITHOUT STATE PATTERN:
    We’d have code like:

        if (state == "stopped") { ... }
        else if (state == "playing") { ... }
        else if (state == "paused") { ... }

    This becomes messy and hard to maintain as the number of states grows.

    ✅ WITH STATE PATTERN:
    Each state is a class that defines its own behavior for actions like
    play, pause, and stop. The MusicPlayer delegates to its current state object.

    ============================================
*/

#include <bits/stdc++.h>
using namespace std;

// Forward declaration for circular dependency
class MusicPlayer;

/* 
    🎵 Abstract Base Class (State Interface)
    Defines the common actions all states must handle.
*/
class MusicPlayerState {
public:
    virtual void describe() = 0;
    virtual void pressPlay(MusicPlayer* musicPlayer) = 0;
    virtual void pressPause(MusicPlayer* musicPlayer) = 0;
    virtual void pressStop(MusicPlayer* musicPlayer) = 0;
    virtual ~MusicPlayerState() = default;
};

/*
    ========================
       Concrete States
    ========================
*/

// 🎵 Stopped State
class StoppedState : public MusicPlayerState {
public:
    void describe() override {
        cout << "Currently: Music Player is stopped." << endl;
    }

    void pressPlay(MusicPlayer* musicPlayer) override;  // defined later
    void pressPause(MusicPlayer* musicPlayer) override {
        cout << "Cannot pause — music is not playing." << endl;
    }
    void pressStop(MusicPlayer* musicPlayer) override {
        cout << "Already stopped." << endl;
    }
};

// 🎵 Playing State
class PlayState : public MusicPlayerState {
public:
    void describe() override {
        cout << "Currently: Music Player is playing." << endl;
    }

    void pressPlay(MusicPlayer* musicPlayer) override {
        cout << "Already playing." << endl;
    }
    void pressPause(MusicPlayer* musicPlayer) override;
    void pressStop(MusicPlayer* musicPlayer) override;
};

// 🎵 Paused State
class PausedState : public MusicPlayerState {
public:
    void describe() override {
        cout << "Currently: Music Player is paused." << endl;
    }

    void pressPlay(MusicPlayer* musicPlayer) override;
    void pressPause(MusicPlayer* musicPlayer) override {
        cout << "Already paused." << endl;
    }
    void pressStop(MusicPlayer* musicPlayer) override;
};

/*
    ========================
        Context Class
    ========================

    🎮 The MusicPlayer holds a reference to the current state.
    Each button press is delegated to the current state's implementation.
*/
class MusicPlayer {
public:
    MusicPlayerState* pauseState;
    MusicPlayerState* playState;
    MusicPlayerState* stopState;

    MusicPlayerState* musicPlayerState; // current state

    MusicPlayer() {
        pauseState = new PausedState();
        playState  = new PlayState();
        stopState  = new StoppedState();

        // Initial state is stopped
        musicPlayerState = stopState;
        musicPlayerState->describe();
    }

    void changeState(MusicPlayerState* state) {
        musicPlayerState = state;
        musicPlayerState->describe();
    }

    // Delegate button presses to current state
    void pressPlay()  { musicPlayerState->pressPlay(this); }
    void pressPause() { musicPlayerState->pressPause(this); }
    void pressStop()  { musicPlayerState->pressStop(this); }

    ~MusicPlayer() {
        delete pauseState;
        delete playState;
        delete stopState;
    }
};

/*
    ========================
        State Transitions
    ========================
    Each state's method defines what happens next.
*/

// --- Stopped → Play ---
void StoppedState::pressPlay(MusicPlayer* musicPlayer) {
    cout << "Playing music..." << endl;
    musicPlayer->changeState(musicPlayer->playState);
}

// --- Play → Pause ---
void PlayState::pressPause(MusicPlayer* musicPlayer) {
    cout << "Music paused." << endl;
    musicPlayer->changeState(musicPlayer->pauseState);
}

// --- Play → Stop ---
void PlayState::pressStop(MusicPlayer* musicPlayer) {
    cout << "Music stopped." << endl;
    musicPlayer->changeState(musicPlayer->stopState);
}

// --- Pause → Play ---
void PausedState::pressPlay(MusicPlayer* musicPlayer) {
    cout << "Resuming music..." << endl;
    musicPlayer->changeState(musicPlayer->playState);
}

// --- Pause → Stop ---
void PausedState::pressStop(MusicPlayer* musicPlayer) {
    cout << "Music stopped." << endl;
    musicPlayer->changeState(musicPlayer->stopState);
}

/*
    ========================
            Demo
    ========================
*/

int main() {
    MusicPlayer player;

    player.pressPlay();   // stopped → playing
    player.pressPause();  // playing → paused
    player.pressPlay();   // paused → playing
    player.pressStop();   // playing → stopped

    return 0;
}

/*
    🧾 OUTPUT (Expected):

    Currently: Music Player is stopped.
    Playing music...
    Currently: Music Player is playing.
    Music paused.
    Currently: Music Player is paused.
    Resuming music...
    Currently: Music Player is playing.
    Music stopped.
    Currently: Music Player is stopped.

    ============================================

    🧩 TAKEAWAY:
    - Each state knows how to handle actions and when to transition.
    - Adding a new state (e.g., LoadingState, ErrorState) only requires:
        1️⃣ Creating a new class implementing MusicPlayerState
        2️⃣ Adding transition logic in existing states.
    - No need to touch the MusicPlayer logic itself!

    This makes the system flexible, maintainable, and easier to extend.
*/
