#include "../include/Player.hpp"

/**
 * @brief Constructor for Player
 * @param startX Initial X position on the map
 * @param startY Initial Y position on the map
 */
Player::Player(int startX, int startY) 
    : x(startX), y(startY), startX(startX), startY(startY), 
      alive(true), lives(3), bombCount(1), maxBombs(1), bombRange(2) {
}

/**
 * @brief Destructor
 */
Player::~Player() {
}

/**
 * @brief Get the current X position
 * @return Current X coordinate
 */
int Player::getX() const {
    return x;
}

/**
 * @brief Get the current Y position
 * @return Current Y coordinate
 */
int Player::getY() const {
    return y;
}

/**
 * @brief Move the player up
 */
void Player::moveUp() {
    y--;
}

/**
 * @brief Move the player down
 */
void Player::moveDown() {
    y++;
}

/**
 * @brief Move the player left
 */
void Player::moveLeft() {
    x--;
}

/**
 * @brief Move the player right
 */
void Player::moveRight() {
    x++;
}

/**
 * @brief Check if player is alive
 * @return True if player is alive, false otherwise
 */
bool Player::isAlive() const {
    return alive;
}

/**
 * @brief Kill the player (reduces lives)
 */
void Player::kill() {
    // Only kill if still alive (avoid multiple kills in same frame)
    if (alive && lives > 0) {
        lives--;
        alive = false;
    } else if (alive && lives <= 0) {
        // Already at 0 lives, just mark as dead
        alive = false;
    }
    // If already dead, do nothing
}

/**
 * @brief Respawn the player at starting position
 * @param startX Starting X position
 * @param startY Starting Y position
 */
void Player::respawn(int startX, int startY) {
    this->startX = startX;
    this->startY = startY;
    x = startX;
    y = startY;
    alive = true;
    bombCount = maxBombs; // Reset bomb count
}

/**
 * @brief Get the number of lives remaining
 * @return Number of lives
 */
int Player::getLives() const {
    return lives;
}

/**
 * @brief Check if player has any lives left
 * @return True if player has lives remaining
 */
bool Player::hasLives() const {
    return lives > 0;
}

/**
 * @brief Get the number of bombs the player can place
 * @return Current bomb count
 */
int Player::getBombCount() const {
    return bombCount;
}

/**
 * @brief Set the number of bombs the player can place
 * @param count New bomb count
 */
void Player::setBombCount(int count) {
    bombCount = count;
    if (bombCount > maxBombs) {
        bombCount = maxBombs;
    }
}

/**
 * @brief Check if player can place a bomb
 * @return True if player can place a bomb
 */
bool Player::canPlaceBomb() const {
    return bombCount > 0;
}

/**
 * @brief Decrease bomb count when placing a bomb
 */
void Player::placeBomb() {
    if (bombCount > 0) {
        bombCount--;
    }
}

/**
 * @brief Add an extra life
 */
void Player::addLife() {
    lives++;
}

/**
 * @brief Increase maximum bomb capacity
 */
void Player::increaseMaxBombs() {
    maxBombs++;
    bombCount = maxBombs; // Refill bomb count
}

/**
 * @brief Get maximum bomb capacity
 * @return Maximum number of bombs
 */
int Player::getMaxBombs() const {
    return maxBombs;
}

/**
 * @brief Get bomb explosion range
 * @return Explosion range
 */
int Player::getBombRange() const {
    return bombRange;
}

/**
 * @brief Increase bomb explosion range
 */
void Player::increaseBombRange() {
    bombRange++;
}

