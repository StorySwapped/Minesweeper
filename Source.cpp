#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Minesweeper.h"
#include <time.h>
using namespace std;
using namespace sf;

int main()
{
restart:
	system("CLS");
	int choice = 0, flags;
	char high;
	cout << "ENTER YOUR CHOICE\n";
	cout << "1. Beginner\n2. Intermediate\n3. Expert\n";
	
	cout << "Your choice: ";
	

	
	cin >> choice;
	
	while (choice != 1 && choice != 2 && choice != 3)
	{
		if (choice != 4)
			cout << "ENTER A VALID CHOICE!\n";
		cout << "1. Easy\n2. Medium\n3. Hard\n";
		cout << "Your choice: ";
		cin >> choice;
		
	}
	

	cout << endl << endl;
	Minesweeper* game = nullptr;
label:
	{
		if (choice == 1)
		{
			game = new Minesweeper(9, 9, 10);
			flags = 10;
		}
		else if (choice == 2)
		{
			game = new Minesweeper(16, 9, 40);
			flags = 40;
		}
		else if (choice == 3)
		{
			game = new Minesweeper(16, 30, 99);
			flags = 99;
		}
		
		
		
	}
	
	
	Clock clock;
	int finalTime;
	int selected = 0;
	clock.restart();
	int TimerStart = 0;
	Font font;
	font.loadFromFile("Yagora.ttf");
	string s;
	while (game->window->isOpen())
	{
		system("CLS");
		
		Time elapsed1 = clock.getElapsedTime();
		if (game->win == -1)
		{
			if (selected == 0)		
			{
				finalTime = (int)elapsed1.asSeconds();
				selected = 1;
			}
			string sf;

			if (finalTime / 60 > 9 && finalTime % 60 > 9)
				s = to_string(finalTime / 60) + ':' + to_string(finalTime % 60);
			else if (finalTime / 60 > 9 && finalTime % 60 <= 9)
				s = to_string(finalTime / 60) + ":0" + to_string(finalTime % 60);
			else if (finalTime / 60 < 9 && finalTime % 60 <= 9)
				s = '0' + to_string(finalTime / 60) + ":0" + to_string(finalTime % 60);
			else
				s = '0' + to_string(finalTime / 60) + ":" + to_string(finalTime % 60);
		}
		
		if (game->win == 0)
		{
			int t = (int)elapsed1.asSeconds();
			if (TimerStart >= 1)
			{
				if (t / 60 > 9 && t % 60 > 9)
					s = to_string(t / 60) + ':' + to_string(t % 60);
				else if (t / 60 > 9 && t % 60 <= 9)
					s = to_string(t / 60) + ":0" + to_string(t % 60);
				else if (t / 60 < 9 && t % 60 <= 9)
					s = '0' + to_string(t / 60) + ":0" + to_string(t % 60);
				else
					s = '0' + to_string(t / 60) + ":" + to_string(t % 60);
			}
			else
				s = "00:00";
		}
		
		/*cout << s << "\r";*/
		Event ev;
		while (game->window->pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				delete game;
				goto restart;
			}
				
		}

		game->window->clear(Color(0, 0, 0));

		Text Minecount;
		Minecount.setFont(font);
		Minecount.setString(to_string(flags));
		Minecount.setStyle(Text::Bold);
		Minecount.setCharacterSize(40);
		Minecount.setFillColor(Color(200, 200, 200));
		Minecount.setPosition(Vector2f(5, 0));

		Text TIME;
		TIME.setFont(font);
		TIME.setString(s);
		TIME.setStyle(Text::Bold);
		TIME.setCharacterSize(40);
		TIME.setFillColor(Color(200, 200, 200));
		TIME.setPosition(Vector2f(game->cols*cell_size - 110, 0));

		game->window->draw(Minecount);
		game->window->draw(TIME);
		if (game->win == 2)
		{
			delete game;
			goto label;
		}
		
		if (game->win == 1)
		{
			
			finalTime = (int)elapsed1.asSeconds();
			
			string sf;

			if (finalTime / 60 > 9 && finalTime % 60 > 9)
				sf = to_string(finalTime / 60) + ':' + to_string(finalTime % 60);
			else if (finalTime / 60 > 9 && finalTime % 60 <= 9)
				sf = to_string(finalTime / 60) + ":0" + to_string(finalTime % 60);
			else if (finalTime / 60 < 9 && finalTime % 60 <= 9)
				sf = '0' + to_string(finalTime / 60) + ":0" + to_string(finalTime % 60);
			else
				sf = '0' + to_string(finalTime / 60) + ":" + to_string(finalTime % 60);

			if (game->S.check_high_score(finalTime, choice))
			{
				game->S.add_new_score(finalTime, choice);
				s = "HIGH SCORE: " + sf;

			}
			else
				s = "Your Time: " + sf;
			Minecount.setFont(font);
			Minecount.setString("YOU WIN!");
			Minecount.setStyle(Text::Bold);
			Minecount.setCharacterSize(game->cols * cell_size / 8);
			Minecount.setFillColor(Color(200, 200, 200));
			Minecount.setPosition(Vector2f(game->cols * cell_size / 5.5 , 30));

			TIME.setFont(font);
			TIME.setString(s);
			TIME.setStyle(Text::Bold);
			TIME.setCharacterSize(game->cols* cell_size / 15);
			TIME.setFillColor(Color(200, 200, 200));
			TIME.setPosition(Vector2f(game->cols* cell_size / 5, game->cols* cell_size / 8 + game->cols * cell_size / 15 + game->rows*2));
			

			delete game->window;
			game->window = new RenderWindow(VideoMode(game->cols * cell_size, game->rows * cell_size + 50, 32), "Minesweeper", Style::Resize | Style::Titlebar | Style::Close | Style::Default);
			
			while (game->window->isOpen())
			{
				
				Event ev;
				while (game->window->pollEvent(ev))
				{
					if (ev.type == Event::Closed)
					{
						game->window->close();
						
						
					}
						
				}
				game->window->draw(Minecount);
				game->window->draw(TIME);
				game->window->display();
			}		
			goto restart;
		}

		bool win = true;
		game->PrintCells();
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			game->MouseLeft(ev.mouseButton.x, ev.mouseButton.y);
			TimerStart++;
			if (TimerStart == 1)
				clock.restart();
		}

		if (Mouse::isButtonPressed(Mouse::Right))
		{
			game->MouseRight(ev.mouseButton.x, ev.mouseButton.y, flags);
			TimerStart++;
			if (TimerStart == 1)
				clock.restart();
		}
		string st = to_string(flags);		

		game->window->display();
	}

	
	delete game;
}