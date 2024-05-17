#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <SDL.h>
#include <unordered_map>

class InputManager
{
private:

    static InputManager* sInstance;

    Uint8* mPrevKeyboardtates;
    const Uint8* mKeyboardStates;
    int mKeyLength;

    Uint32 mPrevMouseState;
    Uint32 mMouseState;

public:

    static InputManager* Instance();

    static void Release();

    bool KeyDown(SDL_Scancode scanCode);
    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);

    void Update();

private:

    InputManager();

    ~InputManager();
};

#endif // _INPUTMANAGER_H
