#ifndef BOMB_HPP
#define BOMB_HPP

#include <SFML/System.hpp>

/**
 * @class Bomb
 * @brief Represents a bomb in the Bomberman game
 * 
 * This class handles bomb timing, explosion, and position.
 * Bombs explode after a certain time and create explosions.
 */
class Bomb {
public:
    /**
     * @brief Enum for bomb owner type
     */
    enum class OwnerType {
        PLAYER,     ///< Bomb placed by player
        ENEMY       ///< Bomb placed by enemy
    };
    
    /**
     * @brief Constructor for Bomb
     * @param x X position of the bomb on the map
     * @param y Y position of the bomb on the map
     * @param owner Type of owner (player or enemy)
     * @param fuseTime Time in seconds before explosion
     * @param explosionRange Range of the explosion
     */
    Bomb(int x, int y, OwnerType owner = OwnerType::PLAYER, float fuseTime = 3.0f, int explosionRange = 2);
    
    /**
     * @brief Destructor
     */
    ~Bomb();
    
    /**
     * @brief Get the X position of the bomb
     * @return X coordinate
     */
    int getX() const;
    
    /**
     * @brief Get the Y position of the bomb
     * @return Y coordinate
     */
    int getY() const;
    
    /**
     * @brief Update the bomb state
     * @param deltaTime Time elapsed since last update
     * @return True if bomb has exploded, false otherwise
     */
    bool update(float deltaTime);
    
    /**
     * @brief Check if the bomb has exploded
     * @return True if bomb has exploded
     */
    bool hasExploded() const;
    
    /**
     * @brief Get the explosion range
     * @return Range of the explosion
     */
    int getExplosionRange() const;
    
    /**
     * @brief Get remaining fuse time
     * @return Remaining time before explosion
     */
    float getRemainingTime() const;
    
    /**
     * @brief Get the owner type of the bomb
     * @return OwnerType (PLAYER or ENEMY)
     */
    OwnerType getOwner() const;

private:
    int x;                  ///< X coordinate on the map
    int y;                  ///< Y coordinate on the map
    OwnerType owner;        ///< Owner of the bomb (player or enemy)
    float fuseTime;         ///< Time before explosion
    float elapsedTime;      ///< Time elapsed since bomb was placed
    bool exploded;          ///< Whether the bomb has exploded
    int explosionRange;     ///< Range of the explosion
};

#endif // BOMB_HPP

