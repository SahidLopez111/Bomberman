#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bomb.hpp"
#include "Map.hpp"
#include "PowerUp.hpp"

/**
 * @class Game
 * @brief Main game class that manages the game loop and all game components
 * 
 * This class handles the main game loop, input processing, rendering,
 * and coordination between Player, Bomb, and Map objects.
 */
class Game {
public:
    /**
     * @brief Constructor for Game
     * @param windowWidth Width of the game window
     * @param windowHeight Height of the game window
     */
    Game(int windowWidth = 800, int windowHeight = 600);
    
    /**
     * @brief Destructor
     */
    ~Game();
    
    /**
     * @brief Initialize the game
     * @return True if initialization was successful
     */
    bool initialize();
    
    /**
     * @brief Run the main game loop
     */
    void run();
    
    /**
     * @brief Clean up resources
     */
    void cleanup();

private:
    /**
     * @brief Process user input
     */
    void processInput();
    
    /**
     * @brief Update game state
     * @param deltaTime Time elapsed since last update
     */
    void update(float deltaTime);
    
    /**
     * @brief Render the game
     */
    void render();
    
    /**
     * @brief Handle bomb explosions
     * @param bomb The bomb that exploded
     */
    void handleBombExplosion(const Bomb& bomb);
    
    /**
     * @brief Check collisions between player and explosions
     */
    void checkPlayerCollisions();
    
    /**
     * @brief Check collisions between enemies and explosions
     */
    void checkEnemyCollisions();
    
    /**
     * @brief Handle player death and respawn
     */
    void handlePlayerDeath();
    
    /**
     * @brief Draw the map using ASCII symbols
     */
    void drawMap();
    
    /**
     * @brief Draw the player
     */
    void drawPlayer();
    
    /**
     * @brief Draw the enemies
     */
    void drawEnemies();
    
    /**
     * @brief Draw the bombs
     */
    void drawBombs();
    
    /**
     * @brief Draw explosions
     */
    void drawExplosions();
    
    /**
     * @brief Draw game over screen
     */
    void drawGameOver();
    
    /**
     * @brief Draw you win screen
     */
    void drawYouWin();
    
    /**
     * @brief Check if all enemies are dead (victory condition)
     */
    void checkVictory();
    
    /**
     * @brief Draw HUD (lives, etc.)
     */
    void drawHUD();
    
    /**
     * @brief Draw power-ups
     */
    void drawPowerUps();
    
    /**
     * @brief Check collisions between player and power-ups
     */
    void checkPowerUpCollisions();
    
    /**
     * @brief Spawn a power-up at a position (random chance)
     * @param x X coordinate
     * @param y Y coordinate
     */
    void spawnPowerUp(int x, int y);
    
    /**
     * @brief Initialize audio system
     * @return True if audio initialization was successful
     */
    bool initializeAudio();
    
    /**
     * @brief Play sound effect
     * @param soundName Name of the sound to play
     */
    void playSound(const std::string& soundName);

    sf::RenderWindow* window;           ///< SFML render window
    Player* player;                     ///< Player object
    std::vector<Enemy*> enemies;       ///< List of enemies
    Map* map;                          ///< Game map
    std::vector<Bomb*> bombs;          ///< List of active bombs
    std::vector<Bomb*> bombsToRemove;  ///< Bombs to remove after update
    std::vector<PowerUp*> powerUps;    ///< List of power-ups on the map
    
    int windowWidth;                   ///< Window width
    int windowHeight;                  ///< Window height
    int cellSize;                      ///< Size of each cell in pixels
    int mapWidth;                      ///< Map width in cells
    int mapHeight;                     ///< Map height in cells
    
    bool isRunning;                    ///< Game running state
    bool gameOver;                     ///< Game over state
    bool youWin;                       ///< Victory state
    sf::Clock clock;                   ///< Clock for delta time calculation
    sf::Clock moveClock;               ///< Clock for movement timing
    sf::Font font;                     ///< Font for text rendering
    
    // Audio system
    sf::Music backgroundMusic;         ///< Background music
    sf::SoundBuffer bombPlaceBuffer;   ///< Sound buffer for bomb placement
    sf::SoundBuffer bombExplodeBuffer;///< Sound buffer for bomb explosion
    sf::SoundBuffer gameOverBuffer;   ///< Sound buffer for game over
    sf::SoundBuffer youWinBuffer;     ///< Sound buffer for victory
    sf::SoundBuffer powerUpBuffer;    ///< Sound buffer for power-up collection
    sf::Sound* bombPlaceSound;        ///< Sound for bomb placement
    sf::Sound* bombExplodeSound;      ///< Sound for bomb explosion
    sf::Sound* gameOverSound;          ///< Sound for game over
    sf::Sound* youWinSound;            ///< Sound for victory
    sf::Sound* powerUpSound;           ///< Sound for power-up collection
    bool audioEnabled;                 ///< Whether audio is enabled
    
    // Movement flags to handle continuous movement
    bool moveUpPressed;
    bool moveDownPressed;
    bool moveLeftPressed;
    bool moveRightPressed;
    float moveTimer;                   ///< Timer for movement delay
    const float moveDelay = 0.15f;     ///< Delay between movements in seconds
    
    // Player starting position for respawn
    int playerStartX;
    int playerStartY;
};

#endif // GAME_HPP

