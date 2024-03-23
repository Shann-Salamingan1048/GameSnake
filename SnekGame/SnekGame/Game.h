#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <random>
#include <vector>
#include <sstream>
#include <iostream>
class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	// Game objects
	sf::Texture snakeBody; //unused
	sf::Texture snakeFood;
	std::vector<sf::Sprite> snakeFoodsVector;

	uint16_t maxFood;
	uint16_t currFood;
	sf::Sprite snakeFoodSprite;
	sf::Texture snakeHeadRight;
	sf::Texture snakeHeadLeft;
	sf::Texture snakeHeadDown;
	sf::Texture snakeHeadUp;
	std::vector<sf::Texture> snakeHeads;
	sf::Sprite Snake;
	float movement_x;
	float movement_y;
	uint16_t choicesFromHeads;
	uint16_t points;
	// resources 
	sf::Text uiText; 
	sf::Font font; 
	sf::Image img; // for icon

	//Background
	sf::Texture background;
	sf::Sprite backgroundSprite;

	// functions
	void initializeVariables();
	void initWindow();
	void setHead();
	void setBackground();
	void loadFiles();
	void setIcon();
	void updateFood();
	void updateText();
	void renderFood(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void initText();
public:
	Game();
	virtual ~Game();

	// Accessors
	const bool isRunning() const;
	const bool endGame() const;

	void spawnFood();
	void pollEvents();
	void update();
	void render();
};

