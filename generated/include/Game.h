//
// Created by Vlad on 03-Nov-24.
//

#ifndef GAME_H
#define GAME_H


#include <Player.h>
#include <Missile.h>
#include <MissileAlert.h>
#include <Coin.h>
#include <Background.h>
#include <Collision.h>
#include <MainMenu.h>
#include <Scoreboard.h>
#include <vector>

class Game {

private:
    const int windowWidth = 1200;
    const int windowHeight = 791;
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event event;
    sf::Clock clock;
    sf::Texture missileTexture;
    sf::Texture missileAlertTexture;
    float spawnTimer;
    float spawnTimerMax;
    bool endGame;
    bool isMenu;
    MainMenu *mainMenu;
    Player* player;
    Object *missileAlert;
    Object *missile;

    //  Coins
    sf::Texture coinTexture;
    std::vector <Coin*> coins;
    float coinSpawnTimer;
    float coinSpawnTimerMax;
    int coinScore;
    void spawnCoinPattern();
    void spawnSingleCoin(float x, float y);
    void updateCoins(float deltaTime);

    Background *background;
    Scoreboard* scoreboard;
    void initVariables();
    void initWindow();
    void initPlayer();
    void initMissile();
    void initTextures();
    void initMissileAlert();
    void initBackground();
    void initMenu();
    void initScoreboard();




public:
    Game();
    ~Game();
    bool running() const;
    void pollEvents();
    void update(float deltaTime);
    void render() const;

};

#endif //GAME_H