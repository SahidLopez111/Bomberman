#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

/**
 * @class Player
 * @brief Represents the player character in the Bomberman game
 * 
 * This class handles player movement, position, and basic game state.
 * The player can move in four directions using arrow keys.
 */
class Player {
public:
    /**
     * @brief Constructor for Player
     * @param startX Initial X position on the map
     * @param startY Initial Y position on the map
     */
    Player(int startX, int startY);
    
    /**
     * @brief Destructor
     */
    ~Player();
    
    /**
     * @brief Get the current X position
     * @return Current X coordinate
     */
    int getX() const;
    
    /**
     * @brief Get the current Y position
     * @return Current Y coordinate
     */
    int getY() const;
    
    /**
     * @brief Move the player up
     */
    void moveUp();
    
    /**
     * @brief Move the player down
     */
    void moveDown();
    
    /**
     * @brief Move the player left
     */
    void moveLeft();
    
    /**
     * @brief Move the player right
     */
    void moveRight();
    
    /**
     * @brief Check if player is alive
     * @return True if player is alive, false otherwise
     */
    bool isAlive() const;
    
    /**
     * @brief Kill the player (reduces lives)
     */
    void kill();
    
    /**
     * @brief Respawn the player at starting position
     * @param startX Starting X position
     * @param startY Starting Y position
     */
    void respawn(int startX, int startY);
    
    /**
     * @brief Get the number of lives remaining
     * @return Number of lives
     */
    int getLives() const;
    
    /**
     * @brief Check if player has any lives left
     * @return True if player has lives remaining
     */
    bool hasLives() const;
    
    /**
     * @brief Get the number of bombs the player can place
     * @return Current bomb count
     */
    int getBombCount() const;
    
    /**
     * @brief Set the number of bombs the player can place
     * @param count New bomb count
     */
    void setBombCount(int count);
    
    /**
     * @brief Check if player can place a bomb
     * @return True if player can place a bomb
     */
    bool canPlaceBomb() const;
    
    /**
     * @brief Decrease bomb count when placing a bomb
     */
    void placeBomb();
    
    /**
     * @brief Add an extra life
     */
    void addLife();
    
    /**
     * @brief Increase maximum bomb capacity
     */
    void increaseMaxBombs();
    
    /**
     * @brief Get maximum bomb capacity
     * @return Maximum number of bombs
     */
    int getMaxBombs() const;
    
    /**
     * @brief Get bomb explosion range
     * @return Explosion range
     */
    int getBombRange() const;
    
    /**
     * @brief Increase bomb explosion range
     */
    void increaseBombRange();

private:
    int x;              ///< X coordinate on the map
    int y;              ///< Y coordinate on the map
    int startX;         ///< Starting X position for respawn
    int startY;         ///< Starting Y position for respawn
    bool alive;         ///< Player's alive status
    int lives;          ///< Number of lives remaining
    int bombCount;      ///< Number of bombs player can place
    int maxBombs;       ///< Maximum number of bombs player can have
    int bombRange;      ///< Explosion range of player's bombs
};

#endif // PLAYER_HPP

