#include "GameManager.h"

int main(int argc, char ** argv)
{
    GameManager* game = GameManager::Instance();

    game->MainScreen();

    GameManager::Release();

    game = nullptr;

    return 0;
}
