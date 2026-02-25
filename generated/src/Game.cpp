// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initMenu();
    this->initBackground();
    this->initPlayer();
    this->initTextures();
    this->initMissileAlert();
    this->initMissile();
    this->initScoreboard();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->missile;
    delete this->missileAlert;
    delete this->mainMenu;
    for (auto* coin : this->coins) {
        delete coin;
    }
    this->coins.clear();
    delete this->scoreboard;

}



void Game::initVariables(){
    this->endGame = false;
    this->spawnTimer=0.f;
    this->spawnTimerMax=10.f;
    this->coinSpawnTimerMax = 4.0f;
    this->coinSpawnTimer = 0.f;
    this->coinScore = 0;
}

void Game::initWindow() {
    this->videoMode=sf::VideoMode(windowWidth,windowHeight);
    this->window=new sf::RenderWindow(this->videoMode,"JetpackJoyride",sf::Style::Default);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initMenu() {
    this->mainMenu = new MainMenu(this->window,
                                  "../resources/GameMenu.png",
                                  "../resources/Logo.png",
                                  "../resources/ButtonMenu.png",
                                  "../resources/New Athletic M54.ttf");
    this->isMenu = true; // Start in the menu phase
}

void Game::initBackground() {
    this->background = new Background();
    constexpr float backgroundSpeed = 300.f; // Scrolling speed for the background
    if (!this->background->initialize("../resources/Background.png", backgroundSpeed, windowWidth, windowHeight)) {
        throw std::runtime_error("Failed to initialize background");
         // Close the game if initialization fails
    }
}




void Game::initPlayer() {
    this->player = new Player();
}

void Game::initTextures() {
    // 1. Missile
    if (!this->missileTexture.loadFromFile("../resources/Missile.png")) {
        std::cout << "ERROR: Missile texture not found!\n";
    }

    // 2. Alert
    if (!this->missileAlertTexture.loadFromFile("../resources/MissileAlert.png")) {
        std::cout << "ERROR: Alert texture not found!\n";
    }

    // 3. Coin
    if (!this->coinTexture.loadFromFile("../resources/Coin.png")) {
        std::cout << "ERROR: Coin texture not found!\n";
    }
}

void Game::initMissileAlert() {
    this->missileAlert = new MissileAlert(this->missileAlertTexture, this->player);
}
void Game::initMissile() {
    this->missile = new Missile(this->missileTexture);
}


void Game::initScoreboard(){
    this->scoreboard = new Scoreboard("../resources/New Athletic M54.ttf", "../resources/record_distance.txt");
}

void Game::spawnCoinPattern() {
    float startY = static_cast<float>(rand() % (windowHeight - 200) + 50);
    float startX = windowWidth + 50.f;
    int patternType = rand() % 4;
    float spacing = 45.f;
    
    switch(patternType) {
        case 0: // Horizontal line
            for (int i = 0; i < 5; i++) {
                spawnSingleCoin(startX + (i * spacing), startY);
            }
            break;

        // Block
        case 1:
            for (int col = 0; col < 3; col++) {
                for (int row = 0; row < 3; row++) {
                    spawnSingleCoin(startX + (col * spacing), startY + (row * spacing));
                }
            }
        break;

        // Diagonal
        case 2:

                if (rand() % 2 == 0) {
                    // Up
                    for (int i = 0; i < 5; i++) {
                        spawnSingleCoin(startX + (i * spacing), startY - (i * spacing));
                    }
                } else {
                    // Down
                    for (int i = 0; i < 5; i++) {
                        spawnSingleCoin(startX + (i * spacing), startY + (i * spacing));
                    }
                }
        break;

        // Zig-zag
        case 3:
            //Down
                for (int i = 0; i < 3; i++) {
                    spawnSingleCoin(startX + (i * spacing), startY + (i * spacing));
                }

        for (int i = 0; i < 3; i++) {
            //Up
            // Offset of 3 spaces + i spaces
            spawnSingleCoin(startX + ((3 + i) * spacing), startY + ((2 - i) * spacing));
        }
        break;
    }

    // If the type of coins was long, increase the pause before the next spawn
    this->coinSpawnTimerMax = static_cast<float>(rand() % 2 + 2); // Pauză între 2 și 3 secunde
    }


void Game::spawnSingleCoin(float x, float y) {
    if (y < 0) y = 0;
    if (y > windowHeight - 40) y = windowHeight - 40;

    Coin* coin = new Coin(this->coinTexture, x, y);
    this->coins.push_back(coin);
}

void Game::updateCoins(float deltaTime) {
    this->coinSpawnTimer += deltaTime;
    if (this->coinSpawnTimer >= this->coinSpawnTimerMax) {
        this->spawnCoinPattern();
        this->coinSpawnTimer = 0.f;
        this->coinSpawnTimerMax = static_cast<float>(rand() % 2 + 1);
    }

    for (auto it = this->coins.begin(); it != this->coins.end();) {
        Coin* coin = *it;
        coin->update(deltaTime);

        // Check for collision with player
        if (Collision::checkCollision(this->player->getSprite(), coin->getSprite())) {
            this->coinScore++; // Increase score by 10 for each coin collected
            delete *it;
            it = this->coins.erase(it);
        } else if ((*it)->getX() + (*it)->getWidth() < 0) {
            // Remove coin if it goes off-screen
            delete *it; // Free memory
            it = this->coins.erase(it);

        } else {
            ++it;
        }
    }

}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
            break;
            case sf::Event::MouseButtonPressed:
                if (this->isMenu) {
                    int buttonIndex = this->mainMenu->handleInput(this->event);
                    switch (buttonIndex) {
                        case 0: // PLAY button
                            this->isMenu = false; // Start the gameplay
                        break;
                        case 1: // SCOREBOARD button
                            this->mainMenu->showScoreboard(this->scoreboard->getHighScore()); // Pass the high score
                        break;
                        default:
                            break;
                    }
                }
            break;
            default:
                break;
        }
    }
}


void Game::update(float deltaTime) {
    this->pollEvents();
    if (this->isMenu) {
        // Skip gameplay updates when in the menu
        return;
    }

    this->background->update(deltaTime);
    this->player->update(deltaTime);
    this->updateCoins(deltaTime);
    this->scoreboard->update(coinScore); // Update the scoreboard with the player's speed

    // Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else
        player->useJetpack(false);

    auto* missile = dynamic_cast<Missile*>(this->missile);
    auto* missileAlert = dynamic_cast<MissileAlert*>(this->missileAlert);

    if(missileAlert->isAlerting()) {
       missileAlert->update(deltaTime);
       if(!missileAlert->isAlerting()) {
           missile->launch(missileAlert->getY());
       }
    }
    else if(missile->isLaunched()) {
        missile->update(deltaTime);
    }
    else {
        this->spawnTimer += deltaTime;
        if (this->spawnTimer >= this->spawnTimerMax) {
            missileAlert->alert();
            this->spawnTimer = 0.f;
        }
    }

    if (Collision::checkCollision(player->getSprite(), missile->getSprite())) {
        std::cout << "Collision detected! Closing game..." << std::endl;
        this->endGame = true; // Set endGame to true
        this->window->close(); // Close the game window
    }
}



void Game::render() const {
    this->window->clear();

    if (this->isMenu) {
        this->mainMenu->render(); // Render the main menu
    } else {
        this->background->render(*this->window);
        this->player->render(*this->window);
        this->missileAlert->render(*this->window);
        this->missile->render(*this->window);
        for (auto* coin : this->coins) {
            coin->render(*this->window);
        }
        this->scoreboard->draw(*this->window);
    }

    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}