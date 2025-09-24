#pragma once
#include "include.h"


int main() {
	// Create the main window ******************************************************
	Vector2u screenSize = Vector2u(1920, 1080);
	Vector2f screenSizeF = Vector2f(1920, 1080);
	VideoMode vm(screenSize);
	RenderWindow window(vm, "Plat ", State::Fullscreen);	
		
	// Create game objects *********************************************************
	vector<ground > grounds;
	vector<coin> coins;
	vector<enemy> enemies;

	player p1({ screenSizeF.x / 2.0f * 1 ,screenSizeF.y /2 }, 50, 500);

	ground g1({ screenSizeF.x / 2.0f, 1040 }, { 1920,80 });
	grounds.push_back(g1);

	ground g2({ screenSizeF.x / 4.0f, 900}, { 400,280 });
	grounds.push_back(g2);

	ground g3({ screenSizeF.x / 8.0f *11, 1040  }, { 1000,80 });
	grounds.push_back(g3);

	ground g4({ screenSizeF.x / 2.0f * 3 + 550, 550 }, { 500,80 });
	grounds.push_back(g4);

	ground g5({ screenSizeF.x / 2.0f * 4 + 250, 800}, { 250,80 });
	grounds.push_back(g5);

	ground g6({ screenSizeF.x / 2.0f * 5 + 1060, 1040 }, { 1920,80 });
	grounds.push_back(g6);

	ground g7({ screenSizeF.x / 2.0f * 8, 1040 }, { 1920,80 });
	grounds.push_back(g7);	

	enemy e1( {g3.position.x, 100 }, -400, 400, 225);
	enemies.push_back(e1);

	coin c1({ screenSizeF.x / 4.0f*3, 900 });
	coins.push_back(c1);

	//initialize game variables ****************************************************
	Clock clock;
	Clock gameTimer; // Separate timer for damage system
	float offset = 0.0f;
	Font font;
	if (!font.openFromFile("fonts/tuffy.ttf")) {
		cerr << "Error: Could not load font!" << endl;
		// Handle error appropriately
	}

	Text scoreText(font, "score : 0", 50U);
	scoreText.setPosition({ 0.0f, 0.0f });

	Text livesText(font, "lives : 3", 50U);
	livesText.setPosition({200.0f, 0.0f });
	// Start the game loop *********************************************************
	while (window.isOpen()) {
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
				// Quit the game when the window is closed
				window.close();
		}

		Time tt = gameTimer.getElapsedTime(); // Use separate timer that doesn't reset
		Time dt = clock.restart();

		// Player input handling ***************************************************
		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			p1.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			p1.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
			p1.moveUp();
		}

		// Side scrolling logic ****************************************************
		if (p1.position.x > screenSizeF.x / 10.0f * 7.5f) {
			offset -= 0.2;	
			p1.position.x -= 0.2;
			for (int i = 0; i < grounds.size(); i++) {
				grounds[i].position.x -= 0.2;
			}
			for( int i = 0; i < coins.size(); i++) {
				coins[i].position.x -= 0.2;
			}
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].position.x -= 0.2;
				enemies[i].startPos.x -= 0.2; // Also update start position for bounds
			}
		}

		if (p1.position.x < screenSizeF.x / 10.0f * 2.5f) {
			offset += 0.2;
			p1.position.x += 0.2;
			for (int i = 0; i < grounds.size(); i++) {
				grounds[i].position.x += 0.2;
			}
			for (int i = 0; i < coins.size(); i++) {
				coins[i].position.x += 0.2;
			}
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].position.x += 0.2;
				enemies[i].startPos.x += 0.2; // Also update start position for bounds
			}
		}

		// Update score and lives text *********************************************
		string temp = "score :" + to_string(p1.score);
		scoreText.setString(temp);
		scoreText.setPosition({ 0.0f, 0.0f });

		string temp2 = "lives :" + to_string(p1.lives);
		livesText.setString(temp2);
		livesText.setPosition({ 200.0f, 0.0f });


		p1.update(dt, offset);//update  ********************************************

		for (int i = 0; i < grounds.size() ; i++) {
			grounds[i].update(dt);
		}

		for (int i = 0; i < coins.size() ; i++) {
			coins[i].update(dt);
		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].update(dt);
		}

		p1.physicsUpdate(dt);

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].physicsUpdate(dt);
		}

		
		for (int i = 0; i < grounds.size(); i++) {//check collisions ***************
			grounds[i].checkCollision(p1);
			for (int j = 0; j < enemies.size(); j++) {
				grounds[i].checkEnemyCollision(enemies[j]);
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].checkCollision(p1,tt);
		}

		for (int i = 0; i < coins.size(); i++) {
			coins[i].checkCollision(p1);
		}

		window.clear();// Clear the window with black color ************************

		window.draw(p1.shape);

		for (int i = 0; i < grounds.size(); i++) {
			window.draw(grounds[i].shape);
		}

		for (int i = 0; i < coins.size(); i++) {
			window.draw(coins[i].shape);
		}
		
		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i].shape);
		}

		window.draw(scoreText);
		window.draw(livesText);


		window.display();
	}
	return 0;
}
