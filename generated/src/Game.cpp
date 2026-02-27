// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initSound();
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
    this->isPaused = false;
    this->endGame = false;
    this->isGameOver = false;
    this->spawnTimer=0.f;
    this->spawnTimerMax=10.f;
    this->coinSpawnTimerMax = 4.0f;
    this->coinSpawnTimer = 0.f;
    this->gameSpeedMultiplier = 1.f;
    this->gameSpeedMultiplierMax = 3.f;
    this->survivalTime=0.f;
    this->coinScore = 0;


}

void Game::initSound() {

    if (!this->backgroundMusic.openFromFile("C:/Users/Vlad/CLionProjects/JetpackJoyride2/resources/music.wav")) {
        std::cout << "EROARE: Nu gasesc music.wav!\n";
    } else {
        this->backgroundMusic.setLoop(true);
        this->backgroundMusic.setVolume(50.f); // Se va seta la 50

    }

    if (!this->missileBuffer.loadFromFile("C:/Users/Vlad/CLionProjects/JetpackJoyride2/resources/missileLaunch.wav")) {
        std::cout << "EROARE: Nu gasesc missile.wav!\n";
    } else {
        this->missileSound.setBuffer(this->missileBuffer);
        this->missileSound.setVolume(50.f);
    }

    // 1. Încărcăm sunetul pentru BĂNUȚ
    if (!this->coinBuffer.loadFromFile("../resources/coin.wav")) {
        std::cout << "EROARE: Nu gasesc coin.wav!\n";
    } else {
        this->coinSound.setBuffer(this->coinBuffer);
        this->coinSound.setVolume(50.f);
    }

    // 2. Încărcăm sunetul pentru ALERTĂ
    if (!this->alertBuffer.loadFromFile("../resources/alert.wav")) {
        std::cout << "EROARE: Nu gasesc alert.wav!\n";
    } else {
        this->alertSound.setBuffer(this->alertBuffer);
        this->alertSound.setVolume(50.f);
    }

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
            this->coinSound.play();
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

            // ==========================================
            // 1. TASTA ESC PENTRU PAUZĂ
            // ==========================================
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape) {
                    // Putem pune pauză doar dacă ne jucăm (nu suntem în meniul principal)
                    if (!this->isMenu && !this->isGameOver) {
                        this->isPaused = !this->isPaused;
                    }
                }
                break;

            // ==========================================
            // 2. APĂSARE CLICK (MENIU, PAUZĂ SAU SLIDER)
            // ==========================================
            case sf::Event::MouseButtonPressed:
                if (this->isMenu) {
                    // CODUL TĂU VECHI: Suntem în meniul principal
                    int buttonIndex = this->mainMenu->handleInput(this->event);
                    switch (buttonIndex) {
                        case 0: // PLAY button
                            this->isMenu = false;
                            this->resetGame();        // Start the gameplay
                            this->backgroundMusic.play();
                            break;
                        case 1: // SCOREBOARD button
                            this->mainMenu->showScoreboard(this->scoreboard->getHighScore());
                            break;
                        default:
                            break;
                    }
                }
                else if (this->isPaused) {
                    // NOU: Suntem în meniul de pauză
                    int action = this->mainMenu->handlePauseInput(this->event);
                    if (action == 1) { // Butonul RESUME
                        this->isPaused = false;
                    } else if (action == 2) { // Butonul MAIN MENU
                        this->isPaused = false;
                        this->isMenu = true;
                        this->backgroundMusic.stop();
                        this->resetGame();

                    }
                }
                else if (this->isGameOver) {
                    // <--- NOU: LOGICA PENTRU DEATH SCREEN
                    int action = this->mainMenu->handleDeathInput(this->event);
                    if (action == 1) { // Butonul MAIN MENU
                        this->isGameOver = false;
                        this->isMenu = true;
                        this->resetGame();
                    } else if (action == 2) { // Butonul EXIT
                        this->window->close(); // AICI închidem jocul de tot!
                    }
                }
                else {
                    // NOU: Suntem în joc. Trimitem click-ul la Scoreboard pentru Slider-ul de volum
                    this->scoreboard->handleInput(this->event);
                }
                break;

            // ==========================================
            // 3. ELIBERARE CLICK (PENTRU SLIDER)
            // ==========================================
            case sf::Event::MouseButtonReleased:
                // Când luăm degetul de pe click, anunțăm slider-ul să se oprească din "drag"
                if (!this->isMenu && !this->isPaused) {
                    this->scoreboard->handleInput(this->event);
                }
                break;

            // ==========================================
            // 4. MIȘCARE MOUSE (PENTRU SLIDER)
            // ==========================================
            case sf::Event::MouseMoved:
                // Trimitem coordonatele mouse-ului pentru ca slider-ul să se miște vizual stânga-dreapta
                if (!this->isMenu && !this->isPaused) {
                    this->scoreboard->handleInput(this->event);
                }
                break;

            default:
                break;
        }
    }
}


void Game::update(float deltaTime) {
    this->pollEvents();
    if (this->isMenu || this->isGameOver || this->isPaused) {
        // Skip gameplay updates when in the menu
        return;
    }
    if (this->isPaused) return;

    if (this->gameSpeedMultiplier < this->gameSpeedMultiplierMax) {
        this->gameSpeedMultiplier += 0.01f * deltaTime;
    }

    float scaledDeltaTime = deltaTime * this->gameSpeedMultiplier;
    this->player->update(deltaTime);
    this->background->update(scaledDeltaTime);
    this->updateCoins(scaledDeltaTime);
    float currentVol = this->scoreboard->getVolume();
    this->backgroundMusic.setVolume(currentVol);
    this->missileSound.setVolume(currentVol);
    this->coinSound.setVolume(currentVol);
    this->alertSound.setVolume(currentVol);
    this->survivalTime += deltaTime;
    this->scoreboard->update(coinScore, this->survivalTime); // Update the scoreboard with the player's speed


    // Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else
        player->useJetpack(false);

    auto* missile = dynamic_cast<Missile*>(this->missile);
    auto* missileAlert = dynamic_cast<MissileAlert*>(this->missileAlert);

    if(missileAlert->isAlerting()) {
       missileAlert->update(scaledDeltaTime);
       if(!missileAlert->isAlerting()) {
           if (!missile->isLaunched()) { // Să nu se audă de 60 de ori pe secundă
               this->missileSound.play();
           }
           missile->launch(missileAlert->getY());
       }
    }
    else if(missile->isLaunched()) {
        missile->update(scaledDeltaTime);
    }
    else {
        this->spawnTimer += scaledDeltaTime;
        if (this->spawnTimer >= this->spawnTimerMax) {
            missileAlert->alert();
            this->alertSound.play();
            this->spawnTimer = 0.f;
        }
    }

    if (Collision::checkCollision(player->getSprite(), missile->getSprite())) {
        std::cout << "Collision detected! GAME OVER." << std::endl;
        this->isGameOver=true; // Set endGame to true
        this-> backgroundMusic.stop(); // Stop background music
        this->mainMenu->setDeathScore(this->coinScore); // Update the death screen with the final score
        this->scoreboard->saveRecord();
    }
}



void Game::render() const {
    this->window->clear();

    if (this->isMenu) {
        this->mainMenu->render(); // Render the main menu
    } else {
        this->scoreboard->draw(*this->window);
        if (this->isPaused) {
            this->mainMenu->renderPause();
        } else if (this->isGameOver) {
            this->mainMenu->renderDeath(); // <--- DESENĂM DEATH SCREEN-UL
        }
        this->background->render(*this->window);
        this->player->render(*this->window);
        this->missileAlert->render(*this->window);
        this->missile->render(*this->window);
        for (auto* coin : this->coins) {
            coin->render(*this->window);
        }
        this->scoreboard->draw(*this->window);
        if (this->isPaused) {
            this->mainMenu->renderPause();
        }
        else if(this->isGameOver) {
            this->mainMenu->renderDeath();
        }
    }

    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}

void Game::resetGame() {
    // 1. Resetăm variabilele de scor și timp
    this->survivalTime = 0.f;
    this->coinScore = 0;
    this->spawnTimer = 0.f;
    this->coinSpawnTimer = 0.f;
    this->gameSpeedMultiplier = 1.f;
    this->scoreboard->reset();

    // 2. Curățăm toate monedele de pe ecran
    for (auto* coin : this->coins) {
        delete coin;
    }
    this->coins.clear();

    // 3. Recreăm Jucătorul și Rachetele de la zero
    // Ștergem obiectele vechi din runda trecută
    delete this->player;
    delete this->missileAlert;
    delete this->missile;

    // Le generăm din nou pe cele noi, la pozițiile de start
    this->initPlayer();
    this->initMissileAlert(); // (Aici trimitem noul player creat)
    this->initMissile();
}