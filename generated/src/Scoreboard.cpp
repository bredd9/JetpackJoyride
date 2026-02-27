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

    // Initialize current time text
    currentTimeText.setFont(font);
    currentTimeText.setCharacterSize(24);
    currentTimeText.setFillColor(sf::Color::White);
    currentTimeText.setPosition(10, 70);
    currentTimeText.setString("Time: 0s");

    // Load high score from file
    std::ifstream inputFile(highScoreFile);
    if (inputFile.is_open()) {
        inputFile >> highScore ;
        inputFile.close();
    }

    highScoreText.setString("High Score: " + std::to_string(highScore));

    // ==========================================
    // --- INIȚIALIZARE SLIDER VOLUM ---
    // ==========================================
    this->currentVolume = 50.f; // Volum inițial la jumătate
    this->isDraggingSlider = false;

    // Bara slider-ului (poziționată în dreapta sus)
    this->sliderTrack.setSize(sf::Vector2f(150.f, 10.f));
    this->sliderTrack.setFillColor(sf::Color(100, 100, 100));
    // ATENȚIE: Dacă fereastra ta are altă lățime, ajustează X-ul (aici e 1000)
    this->sliderTrack.setPosition(1000.f, 20.f);

    // Butonul slider-ului
    this->sliderKnob.setSize(sf::Vector2f(20.f, 30.f));
    this->sliderKnob.setFillColor(sf::Color::White);
    this->sliderKnob.setOrigin(10.f, 15.f);
    // Îl punem la 50% pe bară inițial
    this->sliderKnob.setPosition(this->sliderTrack.getPosition().x + 75.f, this->sliderTrack.getPosition().y + 5.f);
}

Scoreboard::~Scoreboard() {
    saveRecord();
}

void Scoreboard::update(int coins, float time) {
    // Increment score
    currentScore = coins;
    currentScoreText.setString("Coins: " + std::to_string(currentScore));

    // Update high score if necessary
    if (currentScore > highScore) {
        highScore = currentScore;
        highScoreText.setString("High Score: " + std::to_string(highScore));
    }

    // Actualizăm textul cu timpul curent (secunde)
    currentTimeText.setString("Time: " + std::to_string(static_cast<int>(time)) + "s");
}

void Scoreboard::draw(sf::RenderWindow& window) const {
    window.draw(currentScoreText);
    window.draw(highScoreText);
    window.draw(currentTimeText);
    window.draw(sliderTrack);
    window.draw(sliderKnob);
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

void Scoreboard::handleInput(const sf::Event& event) {
    // Dacă dăm click stânga pe buton sau pe bară
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (this->sliderKnob.getGlobalBounds().contains(mousePos) || this->sliderTrack.getGlobalBounds().contains(mousePos)) {
            this->isDraggingSlider = true;
        }
    }

    // Dacă eliberăm click-ul
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        this->isDraggingSlider = false;
    }

    // Dacă mișcăm mouse-ul în timp ce ținem apăsat
    if (event.type == sf::Event::MouseMoved && this->isDraggingSlider) {
        float mouseX = event.mouseMove.x;
        float trackLeft = this->sliderTrack.getPosition().x;
        float trackRight = trackLeft + this->sliderTrack.getSize().x;

        // Nu lăsăm butonul să iasă de pe bară
        if (mouseX < trackLeft) mouseX = trackLeft;
        if (mouseX > trackRight) mouseX = trackRight;

        // Actualizăm poziția butonului și calculăm volumul matematic (0-100)
        this->sliderKnob.setPosition(mouseX, this->sliderKnob.getPosition().y);
        this->currentVolume = ((mouseX - trackLeft) / this->sliderTrack.getSize().x) * 100.f;
    }
}

float Scoreboard::getVolume() const {
    return this->currentVolume;
}
