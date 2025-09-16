#pragma once
#include "include.h"


int main() {
	Vector2u screenSize = Vector2u(1920, 1080);
	Vector2f screenSizeF = Vector2f(1920, 1080);
	VideoMode vm(screenSize);
	RenderWindow window(vm, "Plat ", State::Fullscreen);	
	
	player p1(screenSizeF/2.0f,50);
	ground g1({ screenSizeF.x / 2.0f, 1040 }, { 1920,80 });
	ground g2({ screenSizeF.x / 4.0f, 900}, { 400,280 });
	coin c1({ screenSizeF.x / 4.0f*3, 900 });

	Clock clock;

	Font font;
	if (!font.openFromFile("fonts/tuffy.ttf")) {
		cerr << "Error: Could not load font!" << endl;
		// Handle error appropriately
	}

	Text scoreText(font, "score : 0", 50U);
	scoreText.setPosition({ 0.0f, 0.0f });

	while (window.isOpen()) {
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
				// Quit the game when the window is closed
				window.close();
		}
		Time dt = clock.restart();	

		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			p1.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			p1.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
			p1.moveUp();
		}

		if (p1.position.x > screenSizeF.x / 10.0f * 8.0f) {
			g1.position.x -= 0.2;
			g2.position.x -= 0.2;
			p1.position.x -= 0.2;
		}

		if (p1.position.x < screenSizeF.x / 10.0f * 2.0f) {
			g1.position.x += 0.2;
			g2.position.x += 0.2;
			p1.position.x += 0.2;
		}
		string temp = "score :" + to_string(p1.score);
		scoreText.setString(temp);
		scoreText.setPosition({ 0.0f, 0.0f });


		p1.update(dt);
		g1.update(dt);
		g2.update(dt);
		p1.physicsUpdate(dt);
		g1.checkCollision(p1);
		g2.checkCollision(p1);
		c1.collision(p1);

		window.clear();
		window.draw(p1.shape);
		window.draw(g1.shape);
		window.draw(g2.shape);
		window.draw(c1.shape);
		window.draw(scoreText);
		window.display();
	}
	return 0;
}
