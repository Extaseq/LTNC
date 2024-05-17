#include "InputManager.h"

InputManager* InputManager::sInstance = nullptr;

InputManager* InputManager::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new InputManager();
    }
    return sInstance;
}

void InputManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

InputManager::InputManager()
{
    mKeyboardStates = SDL_GetKeyboardState(&mKeyLength);
    mPrevKeyboardtates = new Uint8[mKeyLength];
    memcpy(mPrevKeyboardtates, mKeyboardStates, mKeyLength);
}

InputManager::~InputManager()
{
    delete[] mPrevKeyboardtates;
    mPrevKeyboardtates = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
    return mKeyboardStates[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
    return (!mPrevKeyboardtates[scanCode] && mKeyboardStates[scanCode]);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
    return (mPrevKeyboardtates[scanCode] && !mKeyboardStates[scanCode]);
}


void InputManager::Update()
{
    memcpy(mPrevKeyboardtates, mKeyboardStates, mKeyLength);
}
