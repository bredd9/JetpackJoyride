#include "Scoreboard.h"
#include <fstream>
#include <stdexcept>

Scoreboard::Scoreboard(const std::string& fontPath, const std::string& highScoreFilePath)
    : currentScore(0), highScore(0), highScoreFile(highScoreFilePath) {
    // Load font
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font: " + fontPath);
    }

    // Initialize current score text
    currentScoreText.setFont(font);
    currentScoreText.setCharacterSize(24);
    currentScoreText.setFillColor(sf::Color::Yellow);
    currentScoreText.setPosition(10, 10);
    currentScoreText.setString("Coins: 0");

    // Initialize high score text
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(10, 40);

    // Load high score from file
    std::ifstream inputFile(highScoreFile);
    if (inputFile.is_open()) {
        inputFile >> highScore;
        inputFile.close();
    }

    highScoreText.setString("High Score: " + std::to_string(highScore));
}

Scoreboard::~Scoreboard() {
    saveRecord();
}

void Scoreboard::update(int coins) {
    // Increment score
    currentScore = coins;
    currentScoreText.setString("Coins: " + std::to_string(currentScore));

    // Update high score if necessary
    if (currentScore > highScore) {
        highScore = currentScore;
        highScoreText.setString("High Score: " + std::to_string(highScore));
    }
}

void Scoreboard::draw(sf::RenderWindow& window) const {
    window.draw(currentScoreText);
    window.draw(highScoreText);
}

void Scoreboard::reset() {
    currentScore = 0;
    currentScoreText.setString("Coins: 0");
}

void Scoreboard::saveRecord() {
    std::ofstream outputFile(highScoreFile);
    if (outputFile.is_open()) {
        outputFile << highScore;
        outputFile.close();
    }
}
int Scoreboard::getHighScore() const {
    return this->highScore;
}
