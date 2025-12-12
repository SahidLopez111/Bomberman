#ifndef POWERUP_HPP
#define POWERUP_HPP

/**
 * @enum PowerUpType
 * @brief Types of power-ups available in the game
 */
enum class PowerUpType {
    EXTRA_BOMB,     ///< Allows placing more bombs simultaneously
    EXTRA_LIFE,     ///< Adds an extra life
    INCREASE_RANGE  ///< Increases bomb explosion range
};

/**
 * @class PowerUp
 * @brief Represents a power-up item in the Bomberman game
 * 
 * Power-ups appear when blocks are destroyed and can be collected by the player.
 */
class PowerUp {
public:
    /**
     * @brief Constructor for PowerUp
     * @param x X position on the map
     * @param y Y position on the map
     * @param type Type of power-up
     */
    PowerUp(int x, int y, PowerUpType type);
    
    /**
     * @brief Destructor
     */
    ~PowerUp();
    
    /**
     * @brief Get the X position
     * @return X coordinate
     */
    int getX() const;
    
    /**
     * @brief Get the Y position
     * @return Y coordinate
     */
    int getY() const;
    
    /**
     * @brief Get the power-up type
     * @return PowerUpType
     */
    PowerUpType getType() const;
    
    /**
     * @brief Check if power-up is collected
     * @return True if collected
     */
    bool isCollected() const;
    
    /**
     * @brief Mark power-up as collected
     */
    void collect();

private:
    int x;                  ///< X coordinate on the map
    int y;                  ///< Y coordinate on the map
    PowerUpType type;       ///< Type of power-up
    bool collected;         ///< Whether power-up has been collected
};

#endif // POWERUP_HPP


