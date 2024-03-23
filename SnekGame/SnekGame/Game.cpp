#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;
	this->movement_x = 0.f;
	this->movement_y = 0.f;
	this->maxFood = 3;
	this->choicesFromHeads = 3;
	this->currFood = 1;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode.height = 1200;
	this->videoMode.width = 2000;
	this->window = new sf::RenderWindow(this->videoMode, "Snek Game", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
}

void Game::setHead()
{
	this->Snake.setTexture(this->snakeHeads[this->choicesFromHeads]);

	// Get the size of the texture
	sf::Vector2u textureSize = this->snakeHeads[this->choicesFromHeads].getSize(); // Vector2u means 2d unsigned int

	// Calculate the scale factors to fit the texture within your desired rectangle size
	float scaleX = 100 / static_cast<float>(textureSize.x);
	float scaleY = 100 / static_cast<float>(textureSize.y);

	// Set the scale to fit the texture within the rectangle
	this->Snake.setScale(scaleX, scaleY);

	// Set the texture rectangle to show the entire texture
	this->Snake.setTextureRect(sf::IntRect(10, 10, textureSize.x, textureSize.y)); // hit box
	this->window->draw(this->Snake);
	//std::cout << "X: " << this->Snake.getPosition().x << ", Y: " << this->Snake.getPosition().y << ", W_x: " 
		//<< this->window->getSize().x << ", W_y: " << this->window->getSize().y << "\n";
}

void Game::setBackground()
{
	// Scale the background sprite to fill the window
	float scaleX = static_cast<float>(this->window->getSize().x) / this->background.getSize().x;
	float scaleY = static_cast<float>(this->window->getSize().y) / this->background.getSize().y;

	this->backgroundSprite.setScale(scaleX, scaleY);
	this->window->draw(this->backgroundSprite);
	
}

void Game::loadFiles()
{
		this->snakeHeadRight.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/SnakeHeadRight.png");
		this->snakeHeadLeft.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/SnakeHeadLeft.png");
		this->snakeHeadDown.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/SnakeHeadDown.png");
		this->snakeHeadUp.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/SnakeHeadUp.png");
		this->snakeHeads.push_back(this->snakeHeadDown);
		this->snakeHeads.push_back(this->snakeHeadUp);
		this->snakeHeads.push_back(this->snakeHeadLeft);
		this->snakeHeads.push_back(this->snakeHeadRight);
		// Load background texture
		this->background.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/Background.jpg");
		// Set up background sprite
		this->backgroundSprite.setTexture(this->background);
		// load icon
		this->img.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/IconSnekGame.png");

	// food initialize
		this->snakeFood.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/SnakeGamePicture/Food.png");
		this->snakeFoodSprite.setTexture(this->snakeFood);

		// Get the size of the texture
		sf::Vector2u textureSize = this->snakeHeads[this->choicesFromHeads].getSize();

		// Calculate the scale factors to fit the texture within your desired rectangle size
		float scaleX = 100 / static_cast<float>(textureSize.x);
		float scaleY = 100 / static_cast<float>(textureSize.y);

		// Set the scale to fit the texture within the rectangle
		this->snakeFoodSprite.setScale(scaleX, scaleY);

		// Set the texture rectangle to show the entire texture
		this->snakeFoodSprite.setTextureRect(sf::IntRect(10,10, textureSize.y + 100, textureSize.x + 100)); // hit box
	// end of food initalization

		//font
		this->font.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/Fonts/Rosela.ttf");
}


void Game::setIcon()
{
	// set Icon
	this->window->setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

Game::Game() // constructor
{
	this->initializeVariables();
	this->initWindow();
	this->loadFiles();
	this->setIcon();
	this->initText();
}

Game::~Game() // destructor
{
	delete this->window;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

const bool Game::endGame() const
{
	if (this->Snake.getPosition().x >= this->window->getSize().x || this->Snake.getPosition().x < 0)
		return true;
	else if (this->Snake.getPosition().y >= this->window->getSize().y || this->Snake.getPosition().y < 0)
		return true;
	return false;
}

void Game::pollEvents()
{

	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			switch (this->event.key.code)
			{
			case sf::Keyboard::W:
				this->movement_y = -10.f;
				this->movement_x = 0.f;
				this->choicesFromHeads = 1;
				break;

			case sf::Keyboard::S:
				this->movement_y = 10.f;
				this->movement_x = 0.f;
				this->choicesFromHeads = 0;
				break;

			case sf::Keyboard::A:
				this->movement_y = 0.f;
				this->movement_x = -10.f;
				this->choicesFromHeads = 2;
				break;

			case sf::Keyboard::D:
				this->movement_y = 0.f;
				this->movement_x = 10.f;
				this->choicesFromHeads = 3;
				break;
			}
			// this->window->close();
			break;
		}
	}
	this->Snake.move(this->movement_x, this->movement_y);
}

void Game::update()
{
	this->pollEvents();
	this->updateFood();
	this->updateText(); // Call updateText before rendering
}

void Game::spawnFood()
{
	if (this->currFood <= this->maxFood)
	{
		// Seed for the random number generator
		std::random_device rd;
		std::mt19937 gen(rd());

		// Define the range and distribution
		std::uniform_int_distribution<int> distribution_x(1, 120); // for x
		std::uniform_int_distribution<int> distribution_y(1, 200); // for x

		sf::Vector2f posFood;
		// Generate a random number within the range
		posFood.x = static_cast<float>((distribution_x(gen) * 10) % static_cast<int>(this->window->getSize().x - this->snakeFood.getSize().x));
		posFood.y = static_cast<float>((distribution_y(gen) * 10) % static_cast<int>(this->window->getSize().y - this->snakeFood.getSize().y));


		this->snakeFoodSprite.setPosition(posFood.x, posFood.y);
		this->snakeFoodsVector.push_back(this->snakeFoodSprite);
		this->currFood++;
	}
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << "\n";
    this->uiText.setPosition(10, 10); // Adjust the position as needed
    this->uiText.setString(ss.str());
}
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(50);
	this->uiText.setFillColor(sf::Color::Black);

}
void Game::updateFood()
{
	this->spawnFood();
	for (uint16_t i = 0; i < this->snakeFoodsVector.size(); i++)
	{
		// Assuming Snake is a sprite or object representing your snake
		sf::FloatRect snakeBounds = this->Snake.getGlobalBounds();
		sf::FloatRect foodBounds = this->snakeFoodsVector[i].getGlobalBounds();

		// Check for collision between snake and food
		if (snakeBounds.intersects(foodBounds))
		{
			this->snakeFoodsVector.erase(this->snakeFoodsVector.begin() + i);
			this->currFood--;
			this->points++;
			
		}
	}
}
void Game::renderFood(sf::RenderTarget& target)
{
	for (auto& food : snakeFoodsVector)
	{
		target.draw(food);
	}
}
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();
	this->setBackground();
	this->setHead();
	this->renderFood(*this->window);
	this->renderText(*this->window); // Render text after updating
	this->window->display();
}