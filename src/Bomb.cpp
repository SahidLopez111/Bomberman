#include "../include/Bomb.hpp"

/**
 * @brief Constructor for Bomb
 * @param x X position of the bomb on the map
 * @param y Y position of the bomb on the map
 * @param owner Type of owner (player or enemy)
 * @param fuseTime Time in seconds before explosion
 * @param explosionRange Range of the explosion
 */
Bomb::Bomb(int x, int y, OwnerType owner, float fuseTime, int explosionRange)
    : x(x), y(y), owner(owner), fuseTime(fuseTime), elapsedTime(0.0f), 
      exploded(false), explosionRange(explosionRange) {
}

/**
 * @brief Destructor
 */
Bomb::~Bomb() {
}

/**
 * @brief Get the X position of the bomb
 * @return X coordinate
 */
int Bomb::getX() const {
    return x;
}

/**
 * @brief Get the Y position of the bomb
 * @return Y coordinate
 */
int Bomb::getY() const {
    return y;
}

/**
 * @brief Update the bomb state
 * @param deltaTime Time elapsed since last update
 * @return True if bomb has exploded, false otherwise
 */
bool Bomb::update(float deltaTime) {
    if (exploded) {
        return true;
    }
    
    elapsedTime += deltaTime;
    
    if (elapsedTime >= fuseTime) {
        exploded = true;
        return true;
    }
    
    return false;
}

/**
 * @brief Check if the bomb has exploded
 * @return True if bomb has exploded
 */
bool Bomb::hasExploded() const {
    return exploded;
}

/**
 * @brief Get the explosion range
 * @return Range of the explosion
 */
int Bomb::getExplosionRange() const {
    return explosionRange;
}

/**
 * @brief Get remaining fuse time
 * @return Remaining time before explosion
 */
float Bomb::getRemainingTime() const {
    return fuseTime - elapsedTime;
}

/**
 * @brief Get the owner type of the bomb
 * @return OwnerType (PLAYER or ENEMY)
 */
Bomb::OwnerType Bomb::getOwner() const {
    return owner;
}

