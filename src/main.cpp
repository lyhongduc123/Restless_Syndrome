#include "Game.h"

const char* title = "Restless Syndrome - Leko -- RECREATED by Duck";
Game* game = nullptr;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

int main(int argc, char* argv[])
{
    game = new Game();
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);

    game->createGame(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    
    while (game->Running()) 
    {
        Game::time.start();
        game->hanbleInput();
        game->Update();
        game->Render();
        
        //frameTime = SDL_GetTicks() - frameStart;  //frameTime = frameEnd ticks - frameStart ticks
        if (Game::time.getTicks() < frameDelay) {
            SDL_Delay(frameDelay - Game::time.getTicks());
        }
    }
    game->Clean();
    return 0;
}
