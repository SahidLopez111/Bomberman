#include "../include/PowerUp.hpp"

/**
 * @brief Constructor for PowerUp
 * @param x X position on the map
 * @param y Y position on the map
 * @param type Type of power-up
 */
PowerUp::PowerUp(int x, int y, PowerUpType type)
    : x(x), y(y), type(type), collected(false) {
}

/**
 * @brief Destructor
 */
PowerUp::~PowerUp() {
}

/**
 * @brief Get the X position
 * @return X coordinate
 */
int PowerUp::getX() const {
    return x;
}

/**
 * @brief Get the Y position
 * @return Y coordinate
 */
int PowerUp::getY() const {
    return y;
}

/**
 * @brief Get the power-up type
 * @return PowerUpType
 */
PowerUpType PowerUp::getType() const {
    return type;
}

/**
 * @brief Check if power-up is collected
 * @return True if collected
 */
bool PowerUp::isCollected() const {
    return collected;
}

/**
 * @brief Mark power-up as collected
 */
void PowerUp::collect() {
    collected = true;
}


