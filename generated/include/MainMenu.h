#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MainMenu {
private:
    sf::RenderWindow* window;
    sf::Texture backgroundTexture;
    sf::Texture logoTexture;
    sf::Texture buttonTexture;
    sf::Font font;

    sf::Sprite backgroundSprite;
    sf::Sprite logoSprite;
    std::vector<sf::Sprite> buttons;
    std::vector<sf::Text> buttonTexts;

    sf::RectangleShape pauseOverlay;
    sf::Sprite resumeButton;
    sf::Sprite returnMenuButton;
    sf::Text resumeText;
    sf::Text returnMenuText;


    // --- ELEMENTE PENTRU DEATH SCREEN ---
    sf::RectangleShape deathOverlay;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Sprite deathMenuButton;
    sf::Sprite deathExitButton;
    sf::Text deathMenuText;
    sf::Text deathExitText;

public:
    MainMenu(sf::RenderWindow* window,
             const std::string& bgPath,
             const std::string& logoPath,
             const std::string& buttonPath,
             const std::string& fontPath);
    ~MainMenu();

    void initTextures(const std::string& bgPath,
                      const std::string& logoPath,
                      const std::string& buttonPath,
                      const std::string& fontPath);
    void initButtons();
    void render() const;
    int handleInput(const sf::Event& event) const;
    void showScoreboard(int highScore);

    void initPauseMenu();
    void renderPause() const;
    int handlePauseInput(const sf::Event& event) const;

    // --- FUNCȚII PENTRU DEATH SCREEN ---
    void initDeathScreen();
    void setDeathScore(int score); // O vom apela ca să actualizăm scorul final
    void renderDeath() const;
    int handleDeathInput(const sf::Event& event) const;
};

#endif // MAINMENU_H
