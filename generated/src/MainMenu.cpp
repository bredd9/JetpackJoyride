#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow* window, 
                   const std::string& bgPath, 
                   const std::string& logoPath, 
                   const std::string& buttonPath, 
                   const std::string& fontPath)
    : window(window) {
    this->initTextures(bgPath, logoPath, buttonPath, fontPath);
    this->initButtons();
    this->initPauseMenu();
    this->initDeathScreen();
}

MainMenu::~MainMenu() {}

void MainMenu::initTextures(const std::string& bgPath, 
                            const std::string& logoPath, 
                            const std::string& buttonPath, 
                            const std::string& fontPath) {
    // Load textures and font
    if (!backgroundTexture.loadFromFile(bgPath)) {
        throw std::runtime_error("Failed to load background texture from " + bgPath);
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!logoTexture.loadFromFile(logoPath)) {
        throw std::runtime_error("Failed to load logo texture from " + logoPath);
    }
    logoSprite.setTexture(logoTexture);

    if (!buttonTexture.loadFromFile(buttonPath)) {
        throw std::runtime_error("Failed to load button texture from " + buttonPath);
    }

    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font from " + fontPath);
    }
}

void MainMenu::initButtons() {
    // Button titles
    std::vector<std::string> titles = {"PLAY", "SCOREBOARD"};

    // Set positions for the background and logo
    backgroundSprite.setPosition(0.f, 0.f);
    logoSprite.setPosition(125.f, 250.f);

    // Calculate button positions on the right
    float startX = window->getSize().x - buttonTexture.getSize().x - 50.f;
    float startY = window->getSize().y / 2.f -
                   (titles.size() * (buttonTexture.getSize().y + 20.f)) / 2.f;

    for (size_t i = 0; i < titles.size(); ++i) {
        // Create button sprite
        sf::Sprite button;
        button.setTexture(buttonTexture);
        button.setPosition(startX, startY + i * (buttonTexture.getSize().y + 20.f));

        // Create button label
        sf::Text text;
        text.setFont(font);
        text.setString(titles[i]);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setOutlineThickness(3.f);
        text.setOutlineColor(sf::Color::Black);

        // Center text on the button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            button.getPosition().x + buttonTexture.getSize().x / 2.f - textBounds.width / 2.f,
            button.getPosition().y + buttonTexture.getSize().y / 2.f - textBounds.height / 2.f - textBounds.top
        );

        buttons.push_back(button);
        buttonTexts.push_back(text);
    }
}

void MainMenu::render() const {
    // Draw background and logo
    window->draw(backgroundSprite);
    window->draw(logoSprite);

    // Draw buttons and labels
    for (const auto& button : buttons) {
        window->draw(button);
    }
    for (const auto& text : buttonTexts) {
        window->draw(text);
    }
}

int MainMenu::handleInput(const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos)) {
                return static_cast<int>(i); // Return index of clicked button
            }
        }
    }
    return -1; // No button clicked
}

void MainMenu::showScoreboard(int highScore) {
    sf::Sprite goBackButton;
    goBackButton.setTexture(buttonTexture);
    goBackButton.setPosition(
        window->getSize().x / 2.f - buttonTexture.getSize().x / 2.f,
        window->getSize().y / 2.f + 100.f
    );

    sf::Text goBackText;
    goBackText.setFont(font);
    goBackText.setString("GO BACK");
    goBackText.setCharacterSize(45);
    goBackText.setFillColor(sf::Color::White);
    goBackText.setStyle(sf::Text::Bold);
    goBackText.setOutlineThickness(3.f);
    goBackText.setOutlineColor(sf::Color::Black);

    sf::FloatRect goBackTextBounds = goBackText.getLocalBounds();
    goBackText.setPosition(
        goBackButton.getPosition().x + buttonTexture.getSize().x / 2.f - goBackTextBounds.width / 2.f,
        goBackButton.getPosition().y + buttonTexture.getSize().y / 2.f - goBackTextBounds.height / 2.f - goBackTextBounds.top
    );

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (goBackButton.getGlobalBounds().contains(mousePos)) {
                    return; // Go back to the main menu
                }
            }
        }

        window->clear();

        // Draw background
        window->draw(backgroundSprite);

        // High score button
        sf::Sprite highScoreButton;
        highScoreButton.setTexture(buttonTexture);
        highScoreButton.setPosition(
            window->getSize().x / 2.f - buttonTexture.getSize().x / 2.f,
            window->getSize().y / 2.f - 50.f
        );
        window->draw(highScoreButton);

        // High score label
        sf::Text highScoreLabel;
        highScoreLabel.setFont(font);
        highScoreLabel.setString("HIGHSCORE");
        highScoreLabel.setCharacterSize(45);
        highScoreLabel.setFillColor(sf::Color::White);
        highScoreLabel.setStyle(sf::Text::Bold);
        highScoreLabel.setOutlineThickness(3.f);
        highScoreLabel.setOutlineColor(sf::Color::Black);

        sf::FloatRect textBounds = highScoreLabel.getLocalBounds();
        highScoreLabel.setPosition(
            highScoreButton.getPosition().x + buttonTexture.getSize().x / 2.f - textBounds.width / 2.f,
            highScoreButton.getPosition().y - textBounds.height - 20.f
        );
        window->draw(highScoreLabel);

        // High score text
        sf::Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setString(std::to_string(highScore));
        highScoreText.setCharacterSize(45);
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setStyle(sf::Text::Bold);
        highScoreText.setOutlineThickness(3.f);
        highScoreText.setOutlineColor(sf::Color::Black);

        sf::FloatRect scoreTextBounds = highScoreText.getLocalBounds();
        highScoreText.setPosition(
            highScoreButton.getPosition().x + buttonTexture.getSize().x / 2.f - scoreTextBounds.width / 2.f,
            highScoreButton.getPosition().y + buttonTexture.getSize().y / 2.f - scoreTextBounds.height / 2.f - scoreTextBounds.top
        );
        window->draw(highScoreText);

        // Go back button
        window->draw(goBackButton);
        window->draw(goBackText);

        window->display();
    }
}


// ==========================================
// --- IMPLEMENTĂRI NOI PENTRU MENIUL DE PAUZĂ ---
// ==========================================

void MainMenu::initPauseMenu() {
    // 1. Fundal transparent negru
    this->pauseOverlay.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    // 2. Buton Resume
    this->resumeButton.setTexture(this->buttonTexture);
    this->resumeButton.setPosition(window->getSize().x / 2.f - this->buttonTexture.getSize().x / 2.f, 300.f);

    this->resumeText.setFont(this->font);
    this->resumeText.setString("RESUME");
    this->resumeText.setCharacterSize(45);
    this->resumeText.setFillColor(sf::Color::White);
    this->resumeText.setStyle(sf::Text::Bold);
    this->resumeText.setOutlineThickness(3.f);
    this->resumeText.setOutlineColor(sf::Color::Black);

    sf::FloatRect resBounds = this->resumeText.getLocalBounds();
    this->resumeText.setPosition(
        this->resumeButton.getPosition().x + this->buttonTexture.getSize().x / 2.f - resBounds.width / 2.f,
        this->resumeButton.getPosition().y + this->buttonTexture.getSize().y / 2.f - resBounds.height / 2.f - resBounds.top
    );

    // 3. Buton Main Menu
    this->returnMenuButton.setTexture(this->buttonTexture);
    this->returnMenuButton.setPosition(window->getSize().x / 2.f - this->buttonTexture.getSize().x / 2.f, 450.f);

    this->returnMenuText.setFont(this->font);
    this->returnMenuText.setString("MAIN MENU");
    this->returnMenuText.setCharacterSize(45);
    this->returnMenuText.setFillColor(sf::Color::White);
    this->returnMenuText.setStyle(sf::Text::Bold);
    this->returnMenuText.setOutlineThickness(3.f);
    this->returnMenuText.setOutlineColor(sf::Color::Black);

    sf::FloatRect retBounds = this->returnMenuText.getLocalBounds();
    this->returnMenuText.setPosition(
        this->returnMenuButton.getPosition().x + this->buttonTexture.getSize().x / 2.f - retBounds.width / 2.f,
        this->returnMenuButton.getPosition().y + this->buttonTexture.getSize().y / 2.f - retBounds.height / 2.f - retBounds.top
    );
}

void MainMenu::renderPause() const {
    this->window->draw(this->pauseOverlay);
    this->window->draw(this->resumeButton);
    this->window->draw(this->resumeText);
    this->window->draw(this->returnMenuButton);
    this->window->draw(this->returnMenuText);
}

int MainMenu::handlePauseInput(const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (this->resumeButton.getGlobalBounds().contains(mousePos)) return 1;
        if (this->returnMenuButton.getGlobalBounds().contains(mousePos)) return 2;
    }
    return 0; // Nu s-a apasat nimic
}

// ==========================================
// --- IMPLEMENTĂRI DEATH SCREEN ---
// ==========================================

void MainMenu::initDeathScreen() {
    // 1. Fundal semi-transparent roșiatic
    this->deathOverlay.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->deathOverlay.setFillColor(sf::Color(150, 0, 0, 150)); // Roșu închis transparent

    // 2. Textul uriaș GAME OVER
    this->gameOverText.setFont(this->font);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setCharacterSize(80);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setStyle(sf::Text::Bold);
    this->gameOverText.setOutlineThickness(5.f);
    this->gameOverText.setOutlineColor(sf::Color::Black);

    sf::FloatRect goBounds = this->gameOverText.getLocalBounds();
    this->gameOverText.setPosition(window->getSize().x / 2.f - goBounds.width / 2.f, 100.f);

    // 3. Textul pentru scor (poziția o setăm dinamic în setDeathScore)
    this->finalScoreText.setFont(this->font);
    this->finalScoreText.setCharacterSize(50);
    this->finalScoreText.setFillColor(sf::Color::Yellow);
    this->finalScoreText.setStyle(sf::Text::Bold);
    this->finalScoreText.setOutlineThickness(3.f);
    this->finalScoreText.setOutlineColor(sf::Color::Black);

    // 4. Butonul MAIN MENU
    this->deathMenuButton.setTexture(this->buttonTexture);
    this->deathMenuButton.setPosition(window->getSize().x / 2.f - this->buttonTexture.getSize().x / 2.f, 350.f);

    this->deathMenuText.setFont(this->font);
    this->deathMenuText.setString("MAIN MENU");
    this->deathMenuText.setCharacterSize(45);
    this->deathMenuText.setFillColor(sf::Color::White);
    this->deathMenuText.setStyle(sf::Text::Bold);
    this->deathMenuText.setOutlineThickness(3.f);
    this->deathMenuText.setOutlineColor(sf::Color::Black);

    sf::FloatRect menuBounds = this->deathMenuText.getLocalBounds();
    this->deathMenuText.setPosition(
        this->deathMenuButton.getPosition().x + this->buttonTexture.getSize().x / 2.f - menuBounds.width / 2.f,
        this->deathMenuButton.getPosition().y + this->buttonTexture.getSize().y / 2.f - menuBounds.height / 2.f - menuBounds.top
    );

    // 5. Butonul EXIT
    this->deathExitButton.setTexture(this->buttonTexture);
    this->deathExitButton.setPosition(window->getSize().x / 2.f - this->buttonTexture.getSize().x / 2.f, 500.f);

    this->deathExitText.setFont(this->font);
    this->deathExitText.setString("EXIT");
    this->deathExitText.setCharacterSize(45);
    this->deathExitText.setFillColor(sf::Color::White);
    this->deathExitText.setStyle(sf::Text::Bold);
    this->deathExitText.setOutlineThickness(3.f);
    this->deathExitText.setOutlineColor(sf::Color::Black);

    sf::FloatRect exitBounds = this->deathExitText.getLocalBounds();
    this->deathExitText.setPosition(
        this->deathExitButton.getPosition().x + this->buttonTexture.getSize().x / 2.f - exitBounds.width / 2.f,
        this->deathExitButton.getPosition().y + this->buttonTexture.getSize().y / 2.f - exitBounds.height / 2.f - exitBounds.top
    );
}

void MainMenu::setDeathScore(int score) {
    this->finalScoreText.setString("SCORE: " + std::to_string(score));
    // Recentrăm textul după ce îi schimbăm valoarea
    sf::FloatRect fsBounds = this->finalScoreText.getLocalBounds();
    this->finalScoreText.setPosition(window->getSize().x / 2.f - fsBounds.width / 2.f, 220.f);
}

void MainMenu::renderDeath() const {
    this->window->draw(this->deathOverlay);
    this->window->draw(this->gameOverText);
    this->window->draw(this->finalScoreText);
    this->window->draw(this->deathMenuButton);
    this->window->draw(this->deathMenuText);
    this->window->draw(this->deathExitButton);
    this->window->draw(this->deathExitText);
}

int MainMenu::handleDeathInput(const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (this->deathMenuButton.getGlobalBounds().contains(mousePos)) return 1; // Main Menu
        if (this->deathExitButton.getGlobalBounds().contains(mousePos)) return 2; // Exit
    }
    return 0;
}