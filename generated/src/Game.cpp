// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"
#include "../include/EntityFactory.h"

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

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
    delete this->background;

    for (auto* coin : this->coins) {
        delete coin;
    }
    this->coins.clear();

    delete this->scoreboard;

    for (auto* pb : this->piggyBanks) {
        delete pb;
    }
    this->piggyBanks.clear();

    for (auto* laser : this->lasers) {
        delete laser;
    }
    this->lasers.clear();
}

void Game::initVariables() {
    this->isPaused = false;
    this->endGame = false;
    this->isGameOver = false;
    this->spawnTimer = 0.f;
    this->spawnTimerMax = 10.f;
    this->coinSpawnTimerMax = 4.0f;
    this->coinSpawnTimer = 0.f;
    this->piggyTimer = 0.f;
    this->piggyTimerMax = 15.f;
    this->laserTimer = 0.f;
    this->laserTimerMax = 7.f;
    this->gameSpeedMultiplier = 1.f;
    this->gameSpeedMultiplierMax = 3.f;
    this->survivalTime = 0.f;
    this->coinScore = 0;
}

void Game::initSound() {
    if (!this->backgroundMusic.openFromFile("../resources/music.wav")) {
        std::cout << "ERROR: Could not find music.wav!\n";
    } else {
        this->backgroundMusic.setLoop(true);
        this->backgroundMusic.setVolume(50.f);
    }

    if (!this->missileBuffer.loadFromFile("../resources/missileLaunch.wav")) {
        std::cout << "ERROR: Could not find missileLaunch.wav!\n";
    } else {
        this->missileSound.setBuffer(this->missileBuffer);
        this->missileSound.setVolume(50.f);
    }

    if (!this->coinBuffer.loadFromFile("../resources/coin.wav")) {
        std::cout << "ERROR: Could not find coin.wav!\n";
    } else {
        this->coinSound.setBuffer(this->coinBuffer);
        this->coinSound.setVolume(50.f);
    }

    if (!this->alertBuffer.loadFromFile("../resources/alert.wav")) {
        std::cout << "ERROR: Could not find alert.wav!\n";
    } else {
        this->alertSound.setBuffer(this->alertBuffer);
        this->alertSound.setVolume(50.f);
    }

    if (!this->piggyBuffer.loadFromFile("../resources/Piggy.wav")) {
        std::cout << "ERROR: Could not find piggy.wav!\n";
    } else {
        this->piggySound.setBuffer(this->piggyBuffer);
        this->piggySound.setVolume(50.f);
    }

    if (!this->laserBuffer.loadFromFile("../resources/Laser.wav")) {
        std::cout << "ERROR: Could not find Laser.wav!\n";
    } else {
        this->laserSound.setBuffer(this->laserBuffer);
        this->laserSound.setVolume(50.f);
    }
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "JetpackJoyride", sf::Style::Default);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initMenu() {
    this->mainMenu = new MainMenu(this->window,
                                  "../resources/GameMenu.png",
                                  "../resources/Logo.png",
                                  "../resources/ButtonMenu.png",
                                  "../resources/New Athletic M54.ttf");
    this->isMenu = true;
}

void Game::initBackground() {
    this->background = new Background();
    constexpr float backgroundSpeed = 300.f;
    if (!this->background->initialize("../resources/Background.png", backgroundSpeed, windowWidth, windowHeight)) {
        throw std::runtime_error("Failed to initialize background");
    }
}

void Game::initPlayer() {
    this->player = new Player();
}

void Game::initTextures() {
    if (!this->missileTexture.loadFromFile("../resources/Missile.png")) {
        std::cout << "ERROR: Missile texture not found!\n";
    }
    if (!this->missileAlertTexture.loadFromFile("../resources/MissileAlert.png")) {
        std::cout << "ERROR: Alert texture not found!\n";
    }
    if (!this->coinTexture.loadFromFile("../resources/Coin.png")) {
        std::cout << "ERROR: Coin texture not found!\n";
    }
    if (!this->piggyBankTexture.loadFromFile("../resources/Piggy.png")) {
        std::cout << "ERROR: PiggyBank texture not found!\n";
    }
    if (!this->laserTexture.loadFromFile("../resources/Laser.png")) {
        std::cout << "ERROR: Laser texture not found!\n";
    }
}

void Game::initMissileAlert() {
    this->missileAlert = new MissileAlert(this->missileAlertTexture, this->player);
}

void Game::initMissile() {
    this->missile = new Missile(this->missileTexture);
}

void Game::initScoreboard() {
    this->scoreboard = new Scoreboard("../resources/New Athletic M54.ttf", "../resources/record_distance.txt");
}

void Game::spawnCoinPattern() {
    float startY = static_cast<float>(rand() % (windowHeight - 200) + 50);
    float startX = windowWidth + 50.f;
    int patternType = rand() % 4;
    float spacing = 45.f;

    switch (patternType) {
        case 0:
            for (int i = 0; i < 5; i++) {
                spawnSingleCoin(startX + (i * spacing), startY);
            }
            break;
        case 1:
            for (int col = 0; col < 3; col++) {
                for (int row = 0; row < 3; row++) {
                    spawnSingleCoin(startX + (col * spacing), startY + (row * spacing));
                }
            }
            break;
        case 2:
            if (rand() % 2 == 0) {
                for (int i = 0; i < 5; i++) {
                    spawnSingleCoin(startX + (i * spacing), startY - (i * spacing));
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    spawnSingleCoin(startX + (i * spacing), startY + (i * spacing));
                }
            }
            break;
        case 3:
            for (int i = 0; i < 3; i++) {
                spawnSingleCoin(startX + (i * spacing), startY + (i * spacing));
            }
            for (int i = 0; i < 3; i++) {
                spawnSingleCoin(startX + ((3 + i) * spacing), startY + ((2 - i) * spacing));
            }
            break;
    }

    this->coinSpawnTimerMax = static_cast<float>(rand() % 2 + 2);
}

void Game::spawnSingleCoin(float x, float y) {
    if (y < 0) y = 0;
    if (y > windowHeight - 40) y = windowHeight - 40;

    Coin* coin = EntityFactory::createCoin(this->coinTexture, x, y);
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

        if (Collision::checkCollision(this->player->getSprite(), coin->getSprite())) {
            this->coinScore++;
            this->coinSound.play();
            delete *it;
            it = this->coins.erase(it);
        } else if ((*it)->getX() + (*it)->getWidth() < 0) {
            delete *it;
            it = this->coins.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::updateObstaclesAndItems(float deltaTime) {
    this->piggyTimer += deltaTime;
    if (this->piggyTimer >= this->piggyTimerMax) {
        float startY = static_cast<float>(rand() % (windowHeight - 150) + 50);
        float startX = windowWidth + 50.f;

        this->piggyBanks.push_back(
            EntityFactory::createPiggyBank(this->piggyBankTexture, startX, startY, 50)
        );
        this->piggyTimer = 0.f;
    }

    for (auto it = this->piggyBanks.begin(); it != this->piggyBanks.end();) {
        (*it)->update(deltaTime);

        if (Collision::checkCollision(this->player->getSprite(), (*it)->getSprite())) {
            this->coinScore += (*it)->getValue();
            this->piggySound.play();
            delete *it;
            it = this->piggyBanks.erase(it);
        } else if ((*it)->getX() + 150.f < 0) {
            delete *it;
            it = this->piggyBanks.erase(it);
        } else {
            ++it;
        }
    }

    this->laserTimer += deltaTime;
    if (this->laserTimer >= this->laserTimerMax) {
        float possibleAngles[] = {0.f, 90.f, 45.f, 135.f};
        int randomAngleIndex = rand() % 4;
        float chosenAngle = possibleAngles[randomAngleIndex];

        int margin = 210;
        float startY = static_cast<float>(rand() % (windowHeight - 2 * margin) + margin);
        float startX = windowWidth + 200.f;

        this->lasers.push_back(
            EntityFactory::createLaser(this->laserTexture, startX, startY, 102, 420, 4, chosenAngle)
        );

        this->laserTimer = 0.f;
    }

    for (auto it = this->lasers.begin(); it != this->lasers.end();) {
        (*it)->update(deltaTime);

        if (Collision::checkRotatedCollision(this->player->getSprite(), (*it)->getSprite(), 0.6f, 0.6f, 0.3f, 0.9f)) {
            std::cout << "Hit by laser! GAME OVER." << std::endl;
            this->laserSound.play();
            this->isGameOver = true;
            this->backgroundMusic.stop();
            this->mainMenu->setDeathScore(this->coinScore);
            this->scoreboard->saveRecord();
            break;
        } else if ((*it)->getX() + 500.f < 0) {
            delete *it;
            it = this->lasers.erase(it);
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
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape) {
                    if (!this->isMenu && !this->isGameOver) {
                        this->isPaused = !this->isPaused;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (this->isMenu) {
                    int buttonIndex = this->mainMenu->handleInput(this->event);
                    switch (buttonIndex) {
                        case 0:
                            this->isMenu = false;
                            this->resetGame();
                            this->backgroundMusic.play();
                            break;
                        case 1:
                            this->mainMenu->showScoreboard(this->scoreboard->getHighScore());
                            break;
                        default:
                            break;
                    }
                } else if (this->isPaused) {
                    int action = this->mainMenu->handlePauseInput(this->event);
                    if (action == 1) {
                        this->isPaused = false;
                    } else if (action == 2) {
                        this->isPaused = false;
                        this->isMenu = true;
                        this->backgroundMusic.stop();
                        this->resetGame();
                    }
                } else if (this->isGameOver) {
                    int action = this->mainMenu->handleDeathInput(this->event);
                    if (action == 1) {
                        this->isGameOver = false;
                        this->isMenu = true;
                        this->resetGame();
                    } else if (action == 2) {
                        this->window->close();
                    }
                } else {
                    this->scoreboard->handleInput(this->event);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (!this->isMenu && !this->isPaused) {
                    this->scoreboard->handleInput(this->event);
                }
                break;
            case sf::Event::MouseMoved:
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
        return;
    }

    if (this->gameSpeedMultiplier < this->gameSpeedMultiplierMax) {
        this->gameSpeedMultiplier += 0.01f * deltaTime;
    }

    float scaledDeltaTime = deltaTime * this->gameSpeedMultiplier;
    this->player->update(deltaTime);
    this->background->update(scaledDeltaTime);
    this->updateCoins(scaledDeltaTime);
    this->updateObstaclesAndItems(scaledDeltaTime);

    float currentVol = this->scoreboard->getVolume();
    this->backgroundMusic.setVolume(currentVol);
    this->missileSound.setVolume(currentVol);
    this->coinSound.setVolume(currentVol);
    this->alertSound.setVolume(currentVol);
    this->piggySound.setVolume(currentVol);
    this->laserSound.setVolume(currentVol);

    this->survivalTime += deltaTime;
    this->scoreboard->update(coinScore, this->survivalTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else
        player->useJetpack(false);

    auto* missile = dynamic_cast<Missile*>(this->missile);
    auto* missileAlert = dynamic_cast<MissileAlert*>(this->missileAlert);

    if (missileAlert->isAlerting()) {
        missileAlert->update(scaledDeltaTime);
        if (!missileAlert->isAlerting()) {
            if (!missile->isLaunched()) {
                this->missileSound.play();
            }
            missile->launch(missileAlert->getY());
        }
    } else if (missile->isLaunched()) {
        missile->update(scaledDeltaTime);
    } else {
        this->spawnTimer += scaledDeltaTime;
        if (this->spawnTimer >= this->spawnTimerMax) {
            missileAlert->alert();
            this->alertSound.play();
            this->spawnTimer = 0.f;
        }
    }

    if (Collision::checkCollision(player->getSprite(), missile->getSprite(), 0.6f, 0.8f, 0.5f, 0.5f)) {
        std::cout << "Collision detected! GAME OVER." << std::endl;
        this->isGameOver = true;
        this->backgroundMusic.stop();
        this->mainMenu->setDeathScore(this->coinScore);
        this->scoreboard->saveRecord();
    }
}

void Game::render() const {
    this->window->clear();

    if (this->isMenu) {
        this->mainMenu->render();
    } else {
        this->scoreboard->draw(*this->window);
        if (this->isPaused) {
            this->mainMenu->renderPause();
        } else if (this->isGameOver) {
            this->mainMenu->renderDeath();
        }

        this->background->render(*this->window);
        this->player->render(*this->window);
        this->missileAlert->render(*this->window);
        this->missile->render(*this->window);

        for (auto* coin : this->coins) {
            coin->render(*this->window);
        }
        for (auto* pb : this->piggyBanks) {
            pb->render(*this->window);
        }
        for (auto* laser : this->lasers) {
            laser->render(*this->window);
        }

        this->scoreboard->draw(*this->window);

        if (this->isPaused) {
            this->mainMenu->renderPause();
        } else if (this->isGameOver) {
            this->mainMenu->renderDeath();
        }
    }

    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}

void Game::resetGame() {
    this->survivalTime = 0.f;
    this->coinScore = 0;
    this->spawnTimer = 0.f;
    this->coinSpawnTimer = 0.f;
    this->gameSpeedMultiplier = 1.f;
    this->scoreboard->reset();

    for (auto* coin : this->coins) {
        delete coin;
    }
    this->coins.clear();

    for (auto* pb : this->piggyBanks) {
        delete pb;
    }
    this->piggyBanks.clear();
    this->piggyTimer = 0.f;

    for (auto* laser : this->lasers) {
        delete laser;
    }
    this->lasers.clear();
    this->laserTimer = 0.f;

    delete this->player;
    delete this->missileAlert;
    delete this->missile;

    this->initPlayer();
    this->initMissileAlert();
    this->initMissile();
}
