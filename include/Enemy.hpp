#ifndef ENEMY_HPP
#define ENEMY_HPP

/**
 * @class Enemy
 * @brief Represents an enemy character in the Bomberman game
 * 
 * This class handles enemy movement, position, and AI behavior.
 * Enemies can move randomly and place bombs.
 */
class Enemy {
public:
    /**
     * @brief Constructor for Enemy
     * @param startX Initial X position on the map
     * @param startY Initial Y position on the map
     */
    Enemy(int startX, int startY);
    
    /**
     * @brief Destructor
     */
    ~Enemy();
    
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
     * @brief Move the enemy up
     */
    void moveUp();
    
    /**
     * @brief Move the enemy down
     */
    void moveDown();
    
    /**
     * @brief Move the enemy left
     */
    void moveLeft();
    
    /**
     * @brief Move the enemy right
     */
    void moveRight();
    
    /**
     * @brief Check if enemy is alive
     * @return True if enemy is alive, false otherwise
     */
    bool isAlive() const;
    
    /**
     * @brief Kill the enemy
     */
    void kill();
    
    /**
     * @brief Get the number of bombs the enemy can place
     * @return Current bomb count
     */
    int getBombCount() const;
    
    /**
     * @brief Set the number of bombs the enemy can place
     * @param count New bomb count
     */
    void setBombCount(int count);
    
    /**
     * @brief Check if enemy can place a bomb
     * @return True if enemy can place a bomb
     */
    bool canPlaceBomb() const;
    
    /**
     * @brief Decrease bomb count when placing a bomb
     */
    void placeBomb();
    
    /**
     * @brief Update enemy AI behavior
     * @param deltaTime Time elapsed since last update
     * @return True if enemy wants to place a bomb, false otherwise
     */
    bool update(float deltaTime);

private:
    int x;              ///< X coordinate on the map
    int y;              ///< Y coordinate on the map
    bool alive;         ///< Enemy's alive status
    int bombCount;      ///< Number of bombs enemy can place
    int maxBombs;       ///< Maximum number of bombs enemy can have
    
    float moveTimer;    ///< Timer for movement delay
    float bombTimer;    ///< Timer for bomb placement
    int lastDirection;  ///< Last movement direction (0=up, 1=down, 2=left, 3=right)
    const float moveDelay = 0.3f;      ///< Delay between movements in seconds
    const float bombDelay = 2.0f;      ///< Delay between bomb placements in seconds
};

#endif // ENEMY_HPP


