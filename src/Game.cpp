#include "../include/Game.hpp"
#include "../include/Enemy.hpp"
#include <iostream>
#include <algorithm>
#include <optional>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor for Game
 * @param windowWidth Width of the game window
 * @param windowHeight Height of the game window
 */
Game::Game(int windowWidth, int windowHeight)
    : window(nullptr), player(nullptr), map(nullptr),
      windowWidth(windowWidth), windowHeight(windowHeight),
      cellSize(30), mapWidth(21), mapHeight(15),
      isRunning(false), gameOver(false), youWin(false),
      moveUpPressed(false), moveDownPressed(false),
      moveLeftPressed(false), moveRightPressed(false),
      moveTimer(0.0f), playerStartX(1), playerStartY(1),
      bombPlaceSound(nullptr), bombExplodeSound(nullptr),
      gameOverSound(nullptr), youWinSound(nullptr),
      powerUpSound(nullptr), audioEnabled(false) {
    // Initialize random seed for enemy AI
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

/**
 * @brief Destructor
 */
Game::~Game() {
    cleanup();
}

/**
 * @brief Initialize the game
 * @return True if initialization was successful
 */
bool Game::initialize() {
    // Create window (SFML 3.0 uses Vector2u for VideoMode)
    window = new sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)),
        "Bomberman",
        sf::Style::Close | sf::Style::Titlebar
    );
    
    if (!window) {
        std::cerr << "Error: Could not create window" << std::endl;
        return false;
    }
    
    window->setFramerateLimit(60);
    
    // Create map
    map = new Map(mapWidth, mapHeight);
    if (!map) {
        std::cerr << "Error: Could not create map" << std::endl;
        return false;
    }
    
    // Create player at starting position
    playerStartX = 1;
    playerStartY = 1;
    player = new Player(playerStartX, playerStartY);
    if (!player) {
        std::cerr << "Error: Could not create player" << std::endl;
        return false;
    }
    
    // Create enemies at different starting positions
    enemies.push_back(new Enemy(mapWidth - 2, mapHeight - 2));
    enemies.push_back(new Enemy(mapWidth - 2, 1));
    enemies.push_back(new Enemy(1, mapHeight - 2));
    
    // Initialize audio system (optional - game works without audio files)
    initializeAudio();
    
    // Try to load font (optional, for future use)
    // For now, we'll use SFML's default rendering
    
    isRunning = true;
    gameOver = false;
    clock.restart();
    
    return true;
}

/**
 * @brief Run the main game loop
 */
void Game::run() {
    while (isRunning && window->isOpen()) {
        // SFML 3.0 uses std::optional for events
        while (const std::optional<sf::Event> event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
                isRunning = false;
            }
            
            // Handle key press events
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent) {
                    if (keyEvent->code == sf::Keyboard::Key::Up) {
                        moveUpPressed = true;
                    } else if (keyEvent->code == sf::Keyboard::Key::Down) {
                        moveDownPressed = true;
                    } else if (keyEvent->code == sf::Keyboard::Key::Left) {
                        moveLeftPressed = true;
                    } else if (keyEvent->code == sf::Keyboard::Key::Right) {
                        moveRightPressed = true;
                    } else if (keyEvent->code == sf::Keyboard::Key::Space) {
                        // Place bomb
                        if (player->canPlaceBomb()) {
                            // Check if there's already a bomb at this position
                            bool bombExists = false;
                            for (Bomb* bomb : bombs) {
                                if (bomb->getX() == player->getX() && 
                                    bomb->getY() == player->getY()) {
                                    bombExists = true;
                                    break;
                                }
                            }
                            
                            if (!bombExists) {
                                // Use player's bomb range
                                Bomb* newBomb = new Bomb(player->getX(), player->getY(), 
                                                         Bomb::OwnerType::PLAYER, 
                                                         3.0f, 
                                                         player->getBombRange());
                                bombs.push_back(newBomb);
                                player->placeBomb();
                                
                                // Play bomb placement sound
                                playSound("bomb_place");
                            }
                        }
                    }
                }
            }
            
            // Handle key release events
            if (event->is<sf::Event::KeyReleased>()) {
                const auto* keyEvent = event->getIf<sf::Event::KeyReleased>();
                if (keyEvent) {
                    if (keyEvent->code == sf::Keyboard::Key::Up) {
                        moveUpPressed = false;
                    } else if (keyEvent->code == sf::Keyboard::Key::Down) {
                        moveDownPressed = false;
                    } else if (keyEvent->code == sf::Keyboard::Key::Left) {
                        moveLeftPressed = false;
                    } else if (keyEvent->code == sf::Keyboard::Key::Right) {
                        moveRightPressed = false;
                    }
                }
            }
        }
        
        // Process continuous movement
        processInput();
        
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();
        
        // Update game state
        update(deltaTime);
        
        // Render game
        render();
    }
}

/**
 * @brief Process user input
 */
void Game::processInput() {
    if (!player || !player->isAlive()) {
        return;
    }
    
    float moveDeltaTime = moveClock.restart().asSeconds();
    moveTimer += moveDeltaTime;
    
    if (moveTimer >= moveDelay) {
        int newX = player->getX();
        int newY = player->getY();
        bool moved = false;
        
        if (moveUpPressed) {
            newY = player->getY() - 1;
            moved = true;
        } else if (moveDownPressed) {
            newY = player->getY() + 1;
            moved = true;
        } else if (moveLeftPressed) {
            newX = player->getX() - 1;
            moved = true;
        } else if (moveRightPressed) {
            newX = player->getX() + 1;
            moved = true;
        }
        
        if (moved && map->isWalkable(newX, newY)) {
            // Check if there's a bomb at the new position
            bool bombAtPosition = false;
            for (Bomb* bomb : bombs) {
                if (bomb->getX() == newX && bomb->getY() == newY) {
                    bombAtPosition = true;
                    break;
                }
            }
            
            if (!bombAtPosition) {
                if (moveUpPressed) {
                    player->moveUp();
                } else if (moveDownPressed) {
                    player->moveDown();
                } else if (moveLeftPressed) {
                    player->moveLeft();
                } else if (moveRightPressed) {
                    player->moveRight();
                }
                moveTimer = 0.0f;
            }
        }
    }
}

/**
 * @brief Update game state
 * @param deltaTime Time elapsed since last update
 */
void Game::update(float deltaTime) {
    if (gameOver || youWin) {
        return;
    }
    
    // Handle player death and respawn
    if (player && !player->isAlive()) {
        handlePlayerDeath();
    }
    
    if (!player || !player->isAlive()) {
        return;
    }
    
    // Update enemies AI
    static float enemyMoveTimer = 0.0f;
    enemyMoveTimer += deltaTime;
    
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            // Update enemy AI
            bool wantsToPlaceBomb = enemy->update(deltaTime);
            
            // Move enemy first, then place bomb in previous position
            bool enemyMoved = false;
            int previousX = enemy->getX();
            int previousY = enemy->getY();
            
            // Move enemy randomly
            if (enemyMoveTimer >= 0.3f) {
                enemyMoveTimer = 0.0f;
                
                // Try random directions until finding a walkable one
                int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
                int dirOrder[4] = {std::rand() % 4, std::rand() % 4, std::rand() % 4, std::rand() % 4};
                
                for (int i = 0; i < 4; i++) {
                    int dir = dirOrder[i];
                    int newX = enemy->getX() + directions[dir][0];
                    int newY = enemy->getY() + directions[dir][1];
                    
                    if (map->isWalkable(newX, newY)) {
                        // Check if there's a bomb at the new position
                        bool bombAtPosition = false;
                        for (Bomb* bomb : bombs) {
                            if (bomb->getX() == newX && bomb->getY() == newY) {
                                bombAtPosition = true;
                                break;
                            }
                        }
                        
                        // Also check for explosions
                        bool explosionAtPosition = (map->getCell(newX, newY) == CellType::EXPLOSION);
                        
                        if (!bombAtPosition && !explosionAtPosition) {
                            // Save previous position before moving
                            previousX = enemy->getX();
                            previousY = enemy->getY();
                            
                            // Move enemy
                            if (dir == 0) enemy->moveUp();
                            else if (dir == 1) enemy->moveDown();
                            else if (dir == 2) enemy->moveLeft();
                            else if (dir == 3) enemy->moveRight();
                            
                            enemyMoved = true;
                            break;
                        }
                    }
                }
            }
            
            // Place bomb in previous position if enemy wants to and has moved
            // This ensures enemy is not trapped by its own bomb
            if (wantsToPlaceBomb && enemy->canPlaceBomb() && enemyMoved) {
                // Check if there's already a bomb at the previous position
                bool bombExists = false;
                for (Bomb* bomb : bombs) {
                    if (bomb->getX() == previousX && bomb->getY() == previousY) {
                        bombExists = true;
                        break;
                    }
                }
                
                if (!bombExists) {
                    // Place bomb at previous position (where enemy was before moving)
                    Bomb* newBomb = new Bomb(previousX, previousY, Bomb::OwnerType::ENEMY);
                    bombs.push_back(newBomb);
                    enemy->placeBomb();
                }
            }
        }
    }
    
    if (enemyMoveTimer >= 0.3f) {
        enemyMoveTimer = 0.0f;
    }
    
    // Update bombs
    bombsToRemove.clear();
    for (Bomb* bomb : bombs) {
        if (bomb->update(deltaTime)) {
            // Bomb exploded
            handleBombExplosion(*bomb);
            bombsToRemove.push_back(bomb);
        }
    }
    
    // Remove exploded bombs
    for (Bomb* bomb : bombsToRemove) {
        auto it = std::find(bombs.begin(), bombs.end(), bomb);
        if (it != bombs.end()) {
            // Get bomb owner from bomb itself
            Bomb::OwnerType owner = bomb->getOwner();
            
            delete *it;
            bombs.erase(it);
            
            // Return bomb to the owner
            if (owner == Bomb::OwnerType::PLAYER && player) {
                player->setBombCount(player->getBombCount() + 1);
            } else if (owner == Bomb::OwnerType::ENEMY) {
                // Return to a random alive enemy
                for (Enemy* enemy : enemies) {
                    if (enemy && enemy->isAlive()) {
                        enemy->setBombCount(enemy->getBombCount() + 1);
                        break;
                    }
                }
            }
        }
    }
    
    // Check collisions with explosions
    checkPlayerCollisions();
    checkEnemyCollisions();
    
    // Check power-up collisions
    checkPowerUpCollisions();
    
    // Check victory condition
    checkVictory();
    
    // Clear explosions after a short delay (handled in next frame)
    static float explosionTimer = 0.0f;
    explosionTimer += deltaTime;
    if (explosionTimer >= 0.5f) {
        map->clearExplosions();
        explosionTimer = 0.0f;
    }
}

/**
 * @brief Handle bomb explosions
 * @param bomb The bomb that exploded
 */
void Game::handleBombExplosion(const Bomb& bomb) {
    // Play explosion sound
    playSound("bomb_explode");
    
    // Store positions where blocks were destroyed (for power-up spawning)
    std::vector<std::pair<int, int>> destroyedBlocks;
    
    int range = bomb.getExplosionRange();
    int x = bomb.getX();
    int y = bomb.getY();
    
    // Check center explosion
    if (map->isValidPosition(x, y)) {
        CellType cell = map->getCell(x, y);
        if (cell == CellType::BLOCK) {
            destroyedBlocks.push_back({x, y});
        }
    }
    
    // Check explosions in four directions
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    for (int dir = 0; dir < 4; dir++) {
        for (int r = 1; r <= range; r++) {
            int newX = x + directions[dir][0] * r;
            int newY = y + directions[dir][1] * r;
            
            if (!map->isValidPosition(newX, newY)) {
                break;
            }
            
            CellType cell = map->getCell(newX, newY);
            
            // Stop explosion at walls
            if (cell == CellType::WALL) {
                break;
            }
            
            // Track destroyed blocks
            if (cell == CellType::BLOCK) {
                destroyedBlocks.push_back({newX, newY});
                break; // Stop explosion after destroying block
            }
        }
    }
    
    // Create explosion
    map->createExplosion(x, y, range);
    
    // Spawn power-ups at destroyed block positions (30% chance each)
    for (const auto& pos : destroyedBlocks) {
        if (std::rand() % 100 < 30) {
            spawnPowerUp(pos.first, pos.second);
        }
    }
}

/**
 * @brief Check collisions between player and explosions
 */
void Game::checkPlayerCollisions() {
    if (!player || !player->isAlive()) {
        return;
    }
    
    // Check collision with explosions
    CellType cell = map->getCell(player->getX(), player->getY());
    if (cell == CellType::EXPLOSION) {
        player->kill();
        return;
    }
    
    // Check collision with enemies
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            if (enemy->getX() == player->getX() && enemy->getY() == player->getY()) {
                // Enemy touched player - kill player
                player->kill();
                return;
            }
        }
    }
}

/**
 * @brief Check collisions between enemies and explosions
 */
void Game::checkEnemyCollisions() {
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            CellType cell = map->getCell(enemy->getX(), enemy->getY());
            if (cell == CellType::EXPLOSION) {
                enemy->kill();
            }
        }
    }
}

/**
 * @brief Check if all enemies are dead (victory condition)
 */
void Game::checkVictory() {
    if (youWin || gameOver) {
        return;
    }
    
    bool allEnemiesDead = true;
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            allEnemiesDead = false;
            break;
        }
    }
    
    if (allEnemiesDead && enemies.size() > 0) {
        youWin = true;
        // Play victory sound
        playSound("you_win");
    }
}

/**
 * @brief Handle player death and respawn
 */
void Game::handlePlayerDeath() {
    if (!player) {
        return;
    }
    
    // Check lives BEFORE respawn (kill() already reduced lives)
    // We need to check if there are lives remaining AFTER the death
    int currentLives = player->getLives();
    
    if (currentLives > 0) {
        // Respawn player at starting position
        player->respawn(playerStartX, playerStartY);
    } else {
        // Game over - no lives left
        gameOver = true;
        // Play game over sound
        playSound("game_over");
    }
}

/**
 * @brief Render the game
 */
void Game::render() {
    if (!window) {
        return;
    }
    
    window->clear(sf::Color::Black);
    
    // Draw map
    drawMap();
    
    // Draw bombs
    drawBombs();
    
    // Draw explosions
    drawExplosions();
    
    // Draw enemies
    drawEnemies();
    
    // Draw power-ups
    drawPowerUps();
    
    // Draw player
    if (player && player->isAlive()) {
        drawPlayer();
    }
    
    // Draw HUD
    drawHUD();
    
    // Draw game over or victory screen
    if (gameOver) {
        drawGameOver();
    } else if (youWin) {
        drawYouWin();
    }
    
    window->display();
}

/**
 * @brief Draw the map using ASCII symbols
 */
void Game::drawMap() {
    if (!map || !window) {
        return;
    }
    
    int offsetX = (windowWidth - mapWidth * cellSize) / 2;
    int offsetY = (windowHeight - mapHeight * cellSize) / 2;
    
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            CellType cell = map->getCell(x, y);
            sf::RectangleShape rect(sf::Vector2f(cellSize - 1, cellSize - 1));
            rect.setPosition(sf::Vector2f(offsetX + x * cellSize, offsetY + y * cellSize));
            
            switch (cell) {
                case CellType::EMPTY:
                    rect.setFillColor(sf::Color(50, 50, 50));
                    break;
                case CellType::WALL:
                    rect.setFillColor(sf::Color(100, 50, 0));
                    break;
                case CellType::BLOCK:
                    rect.setFillColor(sf::Color(150, 75, 0));
                    break;
                case CellType::EXPLOSION:
                    rect.setFillColor(sf::Color::Red);
                    break;
            }
            
            window->draw(rect);
        }
    }
}

/**
 * @brief Draw the player
 */
void Game::drawPlayer() {
    if (!player || !window) {
        return;
    }
    
    int offsetX = (windowWidth - mapWidth * cellSize) / 2;
    int offsetY = (windowHeight - mapHeight * cellSize) / 2;
    
    sf::CircleShape playerShape(cellSize / 2 - 2);
    playerShape.setPosition(sf::Vector2f(
        offsetX + player->getX() * cellSize + 1,
        offsetY + player->getY() * cellSize + 1
    ));
    playerShape.setFillColor(sf::Color::Blue);
    
    window->draw(playerShape);
}

/**
 * @brief Draw the bombs
 */
void Game::drawBombs() {
    if (!window) {
        return;
    }
    
    int offsetX = (windowWidth - mapWidth * cellSize) / 2;
    int offsetY = (windowHeight - mapHeight * cellSize) / 2;
    
    for (Bomb* bomb : bombs) {
        sf::CircleShape bombShape(cellSize / 3);
        bombShape.setPosition(sf::Vector2f(
            offsetX + bomb->getX() * cellSize + cellSize / 3,
            offsetY + bomb->getY() * cellSize + cellSize / 3
        ));
        bombShape.setFillColor(sf::Color::Black);
        
        window->draw(bombShape);
    }
}

/**
 * @brief Draw explosions
 */
void Game::drawExplosions() {
    // Explosions are already drawn in drawMap()
    // This function is kept for future enhancements
}

/**
 * @brief Draw the enemies
 */
void Game::drawEnemies() {
    if (!window) {
        return;
    }
    
    int offsetX = (windowWidth - mapWidth * cellSize) / 2;
    int offsetY = (windowHeight - mapHeight * cellSize) / 2;
    
    for (Enemy* enemy : enemies) {
        if (enemy && enemy->isAlive()) {
            sf::CircleShape enemyShape(cellSize / 2 - 2);
            enemyShape.setPosition(sf::Vector2f(
                offsetX + enemy->getX() * cellSize + 1,
                offsetY + enemy->getY() * cellSize + 1
            ));
            enemyShape.setFillColor(sf::Color::Red);
            
            window->draw(enemyShape);
        }
    }
}

/**
 * @brief Draw HUD (lives, etc.)
 */
void Game::drawHUD() {
    if (!window || !player) {
        return;
    }
    
    // Draw lives indicator using simple shapes
    int offsetX = 10;
    int offsetY = 10;
    
    // Draw "Lives: " text representation using rectangles
    for (int i = 0; i < player->getLives(); i++) {
        sf::RectangleShape lifeRect(sf::Vector2f(20, 20));
        lifeRect.setPosition(sf::Vector2f(offsetX + i * 25, offsetY));
        lifeRect.setFillColor(sf::Color::Green);
        lifeRect.setOutlineColor(sf::Color::White);
        lifeRect.setOutlineThickness(1);
        window->draw(lifeRect);
    }
}

/**
 * @brief Draw power-ups
 */
void Game::drawPowerUps() {
    if (!window) {
        return;
    }
    
    int offsetX = (windowWidth - mapWidth * cellSize) / 2;
    int offsetY = (windowHeight - mapHeight * cellSize) / 2;
    
    for (PowerUp* powerUp : powerUps) {
        if (powerUp && !powerUp->isCollected()) {
            sf::RectangleShape powerUpShape(sf::Vector2f(cellSize / 2, cellSize / 2));
            powerUpShape.setPosition(sf::Vector2f(
                offsetX + powerUp->getX() * cellSize + cellSize / 4,
                offsetY + powerUp->getY() * cellSize + cellSize / 4
            ));
            
            // Different colors for different power-up types
            switch (powerUp->getType()) {
                case PowerUpType::EXTRA_BOMB:
                    powerUpShape.setFillColor(sf::Color::Yellow);
                    break;
                case PowerUpType::EXTRA_LIFE:
                    powerUpShape.setFillColor(sf::Color::Magenta);
                    break;
                case PowerUpType::INCREASE_RANGE:
                    powerUpShape.setFillColor(sf::Color::Cyan);
                    break;
            }
            
            window->draw(powerUpShape);
        }
    }
}

/**
 * @brief Check collisions between player and power-ups
 */
void Game::checkPowerUpCollisions() {
    if (!player || !player->isAlive()) {
        return;
    }
    
    for (PowerUp* powerUp : powerUps) {
        if (powerUp && !powerUp->isCollected()) {
            if (powerUp->getX() == player->getX() && powerUp->getY() == player->getY()) {
                // Play power-up collection sound
                playSound("powerup");
                
                // Apply power-up effect
                switch (powerUp->getType()) {
                    case PowerUpType::EXTRA_BOMB:
                        player->increaseMaxBombs();
                        break;
                    case PowerUpType::EXTRA_LIFE:
                        player->addLife();
                        break;
                    case PowerUpType::INCREASE_RANGE:
                        player->increaseBombRange();
                        break;
                }
                
                powerUp->collect();
            }
        }
    }
    
    // Remove collected power-ups
    powerUps.erase(
        std::remove_if(powerUps.begin(), powerUps.end(),
            [](PowerUp* pu) {
                if (pu && pu->isCollected()) {
                    delete pu;
                    return true;
                }
                return false;
            }),
        powerUps.end()
    );
}

/**
 * @brief Spawn a power-up at a position (random chance)
 * @param x X coordinate
 * @param y Y coordinate
 */
void Game::spawnPowerUp(int x, int y) {
    // Check if there's already a power-up at this position
    for (PowerUp* powerUp : powerUps) {
        if (powerUp && powerUp->getX() == x && powerUp->getY() == y) {
            return; // Don't spawn if already exists
        }
    }
    
    // Randomly choose power-up type
    int random = std::rand() % 3;
    PowerUpType type;
    switch (random) {
        case 0:
            type = PowerUpType::EXTRA_BOMB;
            break;
        case 1:
            type = PowerUpType::EXTRA_LIFE;
            break;
        case 2:
            type = PowerUpType::INCREASE_RANGE;
            break;
        default:
            type = PowerUpType::EXTRA_BOMB;
    }
    
    PowerUp* newPowerUp = new PowerUp(x, y, type);
    powerUps.push_back(newPowerUp);
}

/**
 * @brief Draw game over screen
 */
void Game::drawGameOver() {
    if (!window) {
        return;
    }
    
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window->draw(overlay);
    
    // Draw "GAME OVER" text using rectangles (since we don't have font loaded)
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int textSize = 60;
    
    // Draw large rectangles to represent "GAME OVER"
    // G
    sf::RectangleShape g1(sf::Vector2f(textSize, 10));
    g1.setPosition(sf::Vector2f(centerX - 150, centerY - 30));
    g1.setFillColor(sf::Color::Red);
    window->draw(g1);
    
    sf::RectangleShape g2(sf::Vector2f(10, textSize));
    g2.setPosition(sf::Vector2f(centerX - 150, centerY - 30));
    g2.setFillColor(sf::Color::Red);
    window->draw(g2);
    
    sf::RectangleShape g3(sf::Vector2f(textSize, 10));
    g3.setPosition(sf::Vector2f(centerX - 150, centerY + 20));
    g3.setFillColor(sf::Color::Red);
    window->draw(g3);
    
    sf::RectangleShape g4(sf::Vector2f(10, textSize / 2));
    g4.setPosition(sf::Vector2f(centerX - 90, centerY));
    g4.setFillColor(sf::Color::Red);
    window->draw(g4);
    
    // A
    sf::RectangleShape a1(sf::Vector2f(10, textSize));
    a1.setPosition(sf::Vector2f(centerX - 50, centerY - 30));
    a1.setFillColor(sf::Color::Red);
    window->draw(a1);
    
    sf::RectangleShape a2(sf::Vector2f(textSize, 10));
    a2.setPosition(sf::Vector2f(centerX - 50, centerY - 30));
    a2.setFillColor(sf::Color::Red);
    window->draw(a2);
    
    sf::RectangleShape a3(sf::Vector2f(10, textSize));
    a3.setPosition(sf::Vector2f(centerX + 10, centerY - 30));
    a3.setFillColor(sf::Color::Red);
    window->draw(a3);
    
    sf::RectangleShape a4(sf::Vector2f(textSize, 10));
    a4.setPosition(sf::Vector2f(centerX - 50, centerY + 5));
    a4.setFillColor(sf::Color::Red);
    window->draw(a4);
    
    // M
    sf::RectangleShape m1(sf::Vector2f(10, textSize));
    m1.setPosition(sf::Vector2f(centerX + 50, centerY - 30));
    m1.setFillColor(sf::Color::Red);
    window->draw(m1);
    
    sf::RectangleShape m2(sf::Vector2f(10, textSize));
    m2.setPosition(sf::Vector2f(centerX + 110, centerY - 30));
    m2.setFillColor(sf::Color::Red);
    window->draw(m2);
    
    sf::RectangleShape m3(sf::Vector2f(10, textSize / 2));
    m3.setPosition(sf::Vector2f(centerX + 70, centerY - 10));
    m3.setFillColor(sf::Color::Red);
    window->draw(m3);
    
    // E
    sf::RectangleShape e1(sf::Vector2f(10, textSize));
    e1.setPosition(sf::Vector2f(centerX + 130, centerY - 30));
    e1.setFillColor(sf::Color::Red);
    window->draw(e1);
    
    sf::RectangleShape e2(sf::Vector2f(textSize / 2, 10));
    e2.setPosition(sf::Vector2f(centerX + 130, centerY - 30));
    e2.setFillColor(sf::Color::Red);
    window->draw(e2);
    
    sf::RectangleShape e3(sf::Vector2f(textSize / 2, 10));
    e3.setPosition(sf::Vector2f(centerX + 130, centerY + 5));
    e3.setFillColor(sf::Color::Red);
    window->draw(e3);
    
    sf::RectangleShape e4(sf::Vector2f(textSize / 2, 10));
    e4.setPosition(sf::Vector2f(centerX + 130, centerY + 20));
    e4.setFillColor(sf::Color::Red);
    window->draw(e4);
    
    // O (for OVER)
    sf::RectangleShape o1(sf::Vector2f(10, textSize));
    o1.setPosition(sf::Vector2f(centerX - 150, centerY + 50));
    o1.setFillColor(sf::Color::Red);
    window->draw(o1);
    
    sf::RectangleShape o2(sf::Vector2f(textSize, 10));
    o2.setPosition(sf::Vector2f(centerX - 150, centerY + 50));
    o2.setFillColor(sf::Color::Red);
    window->draw(o2);
    
    sf::RectangleShape o3(sf::Vector2f(10, textSize));
    o3.setPosition(sf::Vector2f(centerX - 90, centerY + 50));
    o3.setFillColor(sf::Color::Red);
    window->draw(o3);
    
    sf::RectangleShape o4(sf::Vector2f(textSize, 10));
    o4.setPosition(sf::Vector2f(centerX - 150, centerY + 100));
    o4.setFillColor(sf::Color::Red);
    window->draw(o4);
    
    // V (for OVER)
    sf::RectangleShape v1(sf::Vector2f(10, textSize - 20));
    v1.setPosition(sf::Vector2f(centerX - 50, centerY + 50));
    v1.setFillColor(sf::Color::Red);
    window->draw(v1);
    
    sf::RectangleShape v2(sf::Vector2f(10, textSize - 20));
    v2.setPosition(sf::Vector2f(centerX - 10, centerY + 50));
    v2.setFillColor(sf::Color::Red);
    window->draw(v2);
    
    sf::RectangleShape v3(sf::Vector2f(10, 20));
    v3.setPosition(sf::Vector2f(centerX - 30, centerY + 100));
    v3.setFillColor(sf::Color::Red);
    window->draw(v3);
    
    // E (for OVER)
    sf::RectangleShape e5(sf::Vector2f(10, textSize));
    e5.setPosition(sf::Vector2f(centerX + 10, centerY + 50));
    e5.setFillColor(sf::Color::Red);
    window->draw(e5);
    
    sf::RectangleShape e6(sf::Vector2f(textSize / 2, 10));
    e6.setPosition(sf::Vector2f(centerX + 10, centerY + 50));
    e6.setFillColor(sf::Color::Red);
    window->draw(e6);
    
    sf::RectangleShape e7(sf::Vector2f(textSize / 2, 10));
    e7.setPosition(sf::Vector2f(centerX + 10, centerY + 75));
    e7.setFillColor(sf::Color::Red);
    window->draw(e7);
    
    sf::RectangleShape e8(sf::Vector2f(textSize / 2, 10));
    e8.setPosition(sf::Vector2f(centerX + 10, centerY + 100));
    e8.setFillColor(sf::Color::Red);
    window->draw(e8);
    
    // R (for OVER)
    sf::RectangleShape r1(sf::Vector2f(10, textSize));
    r1.setPosition(sf::Vector2f(centerX + 50, centerY + 50));
    r1.setFillColor(sf::Color::Red);
    window->draw(r1);
    
    sf::RectangleShape r2(sf::Vector2f(textSize / 2, 10));
    r2.setPosition(sf::Vector2f(centerX + 50, centerY + 50));
    r2.setFillColor(sf::Color::Red);
    window->draw(r2);
    
    sf::RectangleShape r3(sf::Vector2f(10, textSize / 2));
    r3.setPosition(sf::Vector2f(centerX + 80, centerY + 50));
    r3.setFillColor(sf::Color::Red);
    window->draw(r3);
    
    sf::RectangleShape r4(sf::Vector2f(textSize / 2, 10));
    r4.setPosition(sf::Vector2f(centerX + 50, centerY + 75));
    r4.setFillColor(sf::Color::Red);
    window->draw(r4);
    
    sf::RectangleShape r5(sf::Vector2f(10, textSize / 2));
    r5.setPosition(sf::Vector2f(centerX + 80, centerY + 85));
    r5.setFillColor(sf::Color::Red);
    window->draw(r5);
}

/**
 * @brief Draw you win screen
 */
void Game::drawYouWin() {
    if (!window) {
        return;
    }
    
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window->draw(overlay);
    
    // Draw "YOU WIN!" text using rectangles
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int textSize = 50;
    int letterWidth = textSize;
    int letterHeight = textSize;
    int letterSpacing = 15;
    
    // Helper function to draw a rectangle
    auto drawRect = [&](float x, float y, float w, float h) {
        sf::RectangleShape rect(sf::Vector2f(w, h));
        rect.setPosition(sf::Vector2f(x, y));
        rect.setFillColor(sf::Color::Green);
        window->draw(rect);
    };
    
    // "YOU" - First line
    int startX = centerX - 120;
    int startY = centerY - 60;
    
    // Y
    drawRect(startX, startY, 8, letterHeight / 2);
    drawRect(startX + letterWidth - 8, startY, 8, letterHeight / 2);
    drawRect(startX + letterWidth / 2 - 4, startY + letterHeight / 2, 8, letterHeight / 2);
    
    startX += letterWidth + letterSpacing;
    
    // O
    drawRect(startX, startY, 8, letterHeight);
    drawRect(startX + letterWidth - 8, startY, 8, letterHeight);
    drawRect(startX, startY, letterWidth, 8);
    drawRect(startX, startY + letterHeight - 8, letterWidth, 8);
    
    startX += letterWidth + letterSpacing;
    
    // U
    drawRect(startX, startY, 8, letterHeight);
    drawRect(startX + letterWidth - 8, startY, 8, letterHeight);
    drawRect(startX, startY + letterHeight - 8, letterWidth, 8);
    
    // "WIN!" - Second line
    startX = centerX - 100;
    startY = centerY + 20;
    
    // W
    drawRect(startX, startY, 8, letterHeight);
    drawRect(startX + letterWidth / 2 - 4, startY + letterHeight / 2, 8, letterHeight / 2);
    drawRect(startX + letterWidth - 8, startY, 8, letterHeight);
    
    startX += letterWidth + letterSpacing;
    
    // I
    drawRect(startX + letterWidth / 2 - 4, startY, 8, letterHeight);
    
    startX += letterWidth + letterSpacing;
    
    // N
    drawRect(startX, startY, 8, letterHeight);
    drawRect(startX + letterWidth / 2 - 4, startY, 8, letterHeight);
    drawRect(startX + letterWidth - 8, startY, 8, letterHeight);
    
    startX += letterWidth + letterSpacing;
    
    // !
    drawRect(startX + letterWidth / 2 - 4, startY, 8, letterHeight - 20);
    drawRect(startX + letterWidth / 2 - 4, startY + letterHeight - 8, 8, 8);
}

/**
 * @brief Clean up resources
 */
void Game::cleanup() {
    // Delete all bombs
    for (Bomb* bomb : bombs) {
        delete bomb;
    }
    bombs.clear();
    
    // Delete all enemies
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    
    // Delete all power-ups
    for (PowerUp* powerUp : powerUps) {
        delete powerUp;
    }
    powerUps.clear();
    
    // Delete player
    if (player) {
        delete player;
        player = nullptr;
    }
    
    // Delete map
    if (map) {
        delete map;
        map = nullptr;
    }
    
    // Stop and cleanup audio
    if (backgroundMusic.getStatus() == sf::Music::Status::Playing) {
        backgroundMusic.stop();
    }
    
    // Delete sound objects
    if (bombPlaceSound) {
        delete bombPlaceSound;
        bombPlaceSound = nullptr;
    }
    if (bombExplodeSound) {
        delete bombExplodeSound;
        bombExplodeSound = nullptr;
    }
    if (gameOverSound) {
        delete gameOverSound;
        gameOverSound = nullptr;
    }
    if (youWinSound) {
        delete youWinSound;
        youWinSound = nullptr;
    }
    if (powerUpSound) {
        delete powerUpSound;
        powerUpSound = nullptr;
    }
    
    // Close window
    if (window) {
        window->close();
        delete window;
        window = nullptr;
    }
}

/**
 * @brief Initialize audio system
 * @return True if audio initialization was successful
 */
bool Game::initializeAudio() {
    audioEnabled = false;
    
    // Try to load background music
    if (backgroundMusic.openFromFile("assets/background_music.ogg") ||
        backgroundMusic.openFromFile("assets/background_music.wav")) {
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(70.0f);
        backgroundMusic.play();
        audioEnabled = true;
    }
    
    // Try to load sound effects
    bool soundsLoaded = false;
    
    if (bombPlaceBuffer.loadFromFile("assets/bomb_place.wav") ||
        bombPlaceBuffer.loadFromFile("assets/bomb_place.ogg")) {
        bombPlaceSound = new sf::Sound(bombPlaceBuffer);
        bombPlaceSound->setVolume(70.0f);
        soundsLoaded = true;
    }
    
    if (bombExplodeBuffer.loadFromFile("assets/bomb_explode.wav") ||
        bombExplodeBuffer.loadFromFile("assets/bomb_explode.ogg")) {
        bombExplodeSound = new sf::Sound(bombExplodeBuffer);
        bombExplodeSound->setVolume(35.0f);
        soundsLoaded = true;
    }
    
    if (gameOverBuffer.loadFromFile("assets/game_over.wav") ||
        gameOverBuffer.loadFromFile("assets/game_over.ogg")) {
        gameOverSound = new sf::Sound(gameOverBuffer);
        gameOverSound->setVolume(100.0f);
        soundsLoaded = true;
    }
    
    if (youWinBuffer.loadFromFile("assets/you_win.wav") ||
        youWinBuffer.loadFromFile("assets/you_win.ogg")) {
        youWinSound = new sf::Sound(youWinBuffer);
        youWinSound->setVolume(100.0f);
        soundsLoaded = true;
    }
    
    if (powerUpBuffer.loadFromFile("assets/powerup.wav") ||
        powerUpBuffer.loadFromFile("assets/powerup.ogg")) {
        powerUpSound = new sf::Sound(powerUpBuffer);
        powerUpSound->setVolume(80.0f);
        soundsLoaded = true;
    }
    
    if (soundsLoaded) {
        audioEnabled = true;
    }
    
    // Audio is optional - game will work without it
    return true;
}

/**
 * @brief Play sound effect
 * @param soundName Name of the sound to play
 */
void Game::playSound(const std::string& soundName) {
    if (!audioEnabled) {
        return;
    }
    
    if (soundName == "bomb_place" && bombPlaceSound) {
        bombPlaceSound->play();
    } else if (soundName == "bomb_explode" && bombExplodeSound) {
        bombExplodeSound->play();
    } else if (soundName == "game_over" && gameOverSound) {
        gameOverSound->play();
    } else if (soundName == "you_win" && youWinSound) {
        youWinSound->play();
    } else if (soundName == "powerup" && powerUpSound) {
        powerUpSound->play();
    }
}

