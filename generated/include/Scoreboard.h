#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Scoreboard {
private:
    sf::Font font;
    sf::Text currentScoreText;
    sf::Text highScoreText;

    int currentScore;
    int highScore;

    const std::string highScoreFile;

public:
    Scoreboard(const std::string& fontPath, const std::string& highScoreFilePath);
    ~Scoreboard();

    void update(int coins);
    void draw(sf::RenderWindow& window) const;
    void reset();
    void saveRecord();

    int getHighScore() const;
};

#endif // SCOREBOARD_H
