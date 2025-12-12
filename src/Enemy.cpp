#include "../include/Enemy.hpp"
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor for Enemy
 * @param startX Initial X position on the map
 * @param startY Initial Y position on the map
 */
Enemy::Enemy(int startX, int startY)
    : x(startX), y(startY), alive(true), bombCount(1), maxBombs(1),
      moveTimer(0.0f), bombTimer(0.0f), lastDirection(-1) {
    // Initialize random seed
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

/**
 * @brief Destructor
 */
Enemy::~Enemy() {
}

/**
 * @brief Get the current X position
 * @return Current X coordinate
 */
int Enemy::getX() const {
    return x;
}

/**
 * @brief Get the current Y position
 * @return Current Y coordinate
 */
int Enemy::getY() const {
    return y;
}

/**
 * @brief Move the enemy up
 */
void Enemy::moveUp() {
    y--;
}

/**
 * @brief Move the enemy down
 */
void Enemy::moveDown() {
    y++;
}

/**
 * @brief Move the enemy left
 */
void Enemy::moveLeft() {
    x--;
}

/**
 * @brief Move the enemy right
 */
void Enemy::moveRight() {
    x++;
}

/**
 * @brief Check if enemy is alive
 * @return True if enemy is alive, false otherwise
 */
bool Enemy::isAlive() const {
    return alive;
}

/**
 * @brief Kill the enemy
 */
void Enemy::kill() {
    alive = false;
}

/**
 * @brief Get the number of bombs the enemy can place
 * @return Current bomb count
 */
int Enemy::getBombCount() const {
    return bombCount;
}

/**
 * @brief Set the number of bombs the enemy can place
 * @param count New bomb count
 */
void Enemy::setBombCount(int count) {
    bombCount = count;
    if (bombCount > maxBombs) {
        bombCount = maxBombs;
    }
}

/**
 * @brief Check if enemy can place a bomb
 * @return True if enemy can place a bomb
 */
bool Enemy::canPlaceBomb() const {
    return bombCount > 0;
}

/**
 * @brief Decrease bomb count when placing a bomb
 */
void Enemy::placeBomb() {
    if (bombCount > 0) {
        bombCount--;
        bombTimer = 0.0f; // Reset bomb timer
    }
}

/**
 * @brief Update enemy AI behavior
 * @param deltaTime Time elapsed since last update
 * @return True if enemy wants to place a bomb, false otherwise
 */
bool Enemy::update(float deltaTime) {
    moveTimer += deltaTime;
    bombTimer += deltaTime;
    
    // Randomly decide to place a bomb (30% chance when timer is ready)
    bool wantsToPlaceBomb = false;
    if (bombTimer >= bombDelay && canPlaceBomb()) {
        int random = std::rand() % 100;
        if (random < 30) { // 30% chance to place bomb
            wantsToPlaceBomb = true;
        }
    }
    
    // Update last direction for movement (will be used by Game class)
    if (moveTimer >= moveDelay) {
        moveTimer = 0.0f;
        // Direction will be chosen randomly by Game class based on walkability
        lastDirection = std::rand() % 4; // 0=up, 1=down, 2=left, 3=right
    }
    
    return wantsToPlaceBomb;
}


