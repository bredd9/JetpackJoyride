#include <Game.h>

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    sf::Clock clock;
    Game game;

    clock.restart();

    while(game.running()) {

        float deltaTime = clock.restart().asSeconds();

        if (deltaTime > 1.0f / 30.0f) deltaTime = 1.0f / 30.0f;

        game.update(deltaTime);
        game.render();
    }

    return 0;
}