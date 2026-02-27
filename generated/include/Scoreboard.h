#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Scoreboard {
private:
    sf::Font font;
    sf::Text currentScoreText;
    sf::Text highScoreText;
    sf::Text currentTimeText;
    int currentScore;
    int highScore;

    sf::RectangleShape sliderTrack;
    sf::RectangleShape sliderKnob;
    bool isDraggingSlider;
    float currentVolume;

    const std::string highScoreFile;

public:
    Scoreboard(const std::string& fontPath, const std::string& highScoreFilePath);
    ~Scoreboard();

    void update(int coins, float time);
    void draw(sf::RenderWindow& window) const;
    void reset();
    void saveRecord();

    void handleInput(const sf::Event& event); // Pentru drag & drop pe slider
    float getVolume() const;

    int getHighScore() const;
};

#endif // SCOREBOARD_H
