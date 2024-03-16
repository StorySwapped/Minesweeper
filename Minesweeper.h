#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>
#include <fstream>
using namespace std;
using namespace sf;

const int cell_size = 40;

class Highscore
{
public:
	int m_scores[5];
	int e_scores[5];
	int h_scores[5];
	Highscore()
	{
		for (int i = 0; i < 5; i++)
		{
			e_scores[i] = i*2 + 50;
		}
		ifstream bout("medium.txt");
		for (int i = 0; i < 5; i++)
		{
			m_scores[i] = i * 2 + 200;
		}
		ifstream dout("hard.txt");
		for (int i = 0; i < 5; i++)
		{
			h_scores[i] = i * 2 + 400;
		}

		/*ifstream out("easy.txt");
		for (int i = 0; i < 5; i++)
		{
			out >> e_scores[i];
		}
		ifstream bout("medium.txt");
		for (int i = 0; i < 5; i++)
		{
			bout >> m_scores[i];
		}
		ifstream dout("hard.txt");
		for (int i = 0; i < 5; i++)
		{
			dout >> h_scores[i];
		}*/
		Arrange();
	}
	bool check_high_score(int a, int type)
	{
		if (type == 1)
		{
			if (a < e_scores[4])
				return true;

		}
		if (type == 2)
		{
			if (a < m_scores[4])
				return true;
		}
		if (type == 3)
		{
			if (a < h_scores[4])
				return true;
		}
	}

	void Arrange()
	{
		int min_idx;
		for (int i = 0; i < 4; i++)
		{
			min_idx = i;
			for (int j = i + 1; j < 5; j++)
			{
				if (e_scores[j] < e_scores[min_idx])
				{
					min_idx = j;
					swap(e_scores[min_idx], e_scores[i]);
				}
				if (m_scores[j] < m_scores[min_idx])
				{
					min_idx = j;
					swap(m_scores[min_idx], m_scores[i]);
				}
				if (h_scores[j] < h_scores[min_idx])
				{
					min_idx = j;
					swap(h_scores[min_idx], h_scores[i]);
				}
			}
		}
	}
	void add_new_score(int a, int type)
	{
		if (type == 1)
		{
			if (a < e_scores[4])
			{
				e_scores[4] = a;
			}
		}
		if (type == 2)
		{
			if (a < m_scores[4])
			{
				m_scores[4] = a;
			}
		}
		if (type == 3)
		{
			if (a < h_scores[4])
			{
				h_scores[4] = a;
			}
		}
		Arrange();
	}

	void Display()
	{
		string s;
		cout << endl << "EASY\n";
		for (int i = 0; i < 5; i++)
		{
			if (e_scores[i] / 60 > 9 && e_scores[i] % 60 > 9)
				s = to_string(e_scores[i] / 60) + ':' + to_string(e_scores[i] % 60);
			else if (e_scores[i] / 60 > 9 && e_scores[i] % 60 <= 9)
				s = to_string(e_scores[i] / 60) + ":0" + to_string(e_scores[i] % 60);
			else if (e_scores[i] / 60 < 9 && e_scores[i] % 60 <= 9)
				s = '0' + to_string(e_scores[i] / 60) + ":0" + to_string(e_scores[i] % 60);
			else
				s = '0' + to_string(e_scores[i] / 60) + ":" + to_string(e_scores[i] % 60);
			cout << i + 1 << ". " << s << endl;
		}
		cout << endl << "MEDIUM\n";
		for (int i = 0; i < 5; i++)
		{
			if (m_scores[i] / 60 > 9 && m_scores[i] % 60 > 9)
				s = to_string(m_scores[i] / 60) + ':' + to_string(m_scores[i] % 60);
			else if (m_scores[i] / 60 > 9 && m_scores[i] % 60 <= 9)
				s = to_string(m_scores[i] / 60) + ":0" + to_string(m_scores[i] % 60);
			else if (m_scores[i] / 60 < 9 && m_scores[i] % 60 <= 9)
				s = '0' + to_string(m_scores[i] / 60) + ":0" + to_string(m_scores[i] % 60);
			else
				s = '0' + to_string(m_scores[i] / 60) + ":" + to_string(m_scores[i] % 60);
			cout << i + 1 << ". " << s << endl;
		}
		cout << endl << "HARD\n";
		for (int i = 0; i < 5; i++)
		{
			if (h_scores[i] / 60 > 9 && h_scores[i] % 60 > 9)
				s = to_string(h_scores[i] / 60) + ':' + to_string(h_scores[i] % 60);
			else if (h_scores[i] / 60 > 9 && h_scores[i] % 60 <= 9)
				s = to_string(h_scores[i] / 60) + ":0" + to_string(h_scores[i] % 60);
			else if (h_scores[i] / 60 < 9 && h_scores[i] % 60 <= 9)
				s = '0' + to_string(h_scores[i] / 60) + ":0" + to_string(h_scores[i] % 60);
			else
				s = '0' + to_string(h_scores[i] / 60) + ":" + to_string(h_scores[i] % 60);
			cout << i + 1 << ". " << s << endl;
		}
	}

	~Highscore()
	{
		ofstream out("hard.txt");
		for (int i = 0; i < 5; i++)
		{
			out << h_scores[i] << " ";
		}
		ofstream vout("medium.txt");
		for (int i = 0; i < 5; i++)
		{
			vout << m_scores[i] << " ";
		}
		ofstream dout("easy.txt");
		for (int i = 0; i < 5; i++)
		{
			dout << e_scores[i] << " ";
		}
	}
};

class GRID 
{
public:
	int rows;
	int cols;
	int mines;
	int** grid;
	GRID(int r, int c, int m)
	{
		rows = r;
		cols = c;
		mines = m;
		grid = new int* [r];
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new int[cols];
			for (int j = 0; j < cols; j++)
			{
				grid[i][j] = 0;
			}
		}
		
		this->DistributeMines();

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] != 9)
					grid[i][j] = this->mineCount(i, j);
			}
		}

	}
	void DistributeMines()
	{
		int less;
		srand(time(0));
		less = mines;
		while (less != 0)
		{
			int i = rand() % rows, j = rand() % cols;
			if (grid[i][j] != 9)
			{
				grid[i][j] = 9;
				less--;
			}
		}
	}
	int mineCount(int i, int j)
	{
		int count = 0;
		if (grid[i][j + 1] == 9 && j < cols - 1)
			count++;
		if (grid[i][j - 1] == 9 && j > 0)
			count++;
		if (i < rows - 1)
		{
			if (grid[i + 1][j + 1] == 9 && j < cols - 1)
				count++;
			if (grid[i + 1][j - 1] == 9 && j > 0)
				count++;
			if (grid[i + 1][j] == 9)
				count++;
		}
		if (i > 0)
		{
			if (grid[i - 1][j + 1] == 9 && j < cols - 1)
				count++;
			if (grid[i - 1][j - 1] == 9 && j > 0)
				count++;
			if (grid[i - 1][j] == 9)
				count++;
		}
		return count;
	}
	~GRID()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] grid[i];
		}
		delete[] grid;
	}

};

class Minesweeper : public GRID
{
public:
	int** sp;
	RenderWindow* window;
	RectangleShape** cell;
	Texture** texture;
	int win;
	Highscore S;
	/*FlagCount flag;*/


	Minesweeper(int a, int b, int c) : GRID(a, b, c)
	{
		sp = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			sp[i] = new int[cols];
			for (int j = 0; j < cols; j++)
			{
				sp[i][j] = 0;
			}
		}
		cell = new RectangleShape * [rows];
		for (int i = 0; i < rows; i++)
		{
			cell[i] = new RectangleShape[cols];
			for (int j = 0; j < cols; j++)
			{
				cell[i][j].setSize(Vector2f(cell_size, cell_size));
				cell[i][j].setPosition(Vector2f(j * cell_size, i * cell_size + 50));
			}
		}
		window = new RenderWindow(VideoMode(cols * cell_size, rows * cell_size + 50, 32), "Minesweeper", Style::Resize | Style::Titlebar | Style::Close | Style::Default);

		texture = new Texture * [rows];
		for (int i = 0; i < rows; i++)
			texture[i] = new Texture[cols];
		win = 0;
	}
	void PrintCells()	
	{
		RectangleShape emoji;
		int total = 0;
		emoji.setSize(Vector2f(cell_size + 10, cell_size + 10));
		emoji.setPosition(Vector2f((cols*cell_size/2) - 5-cell_size/2, 0));
		Texture tex1;
		if (win == 1)
			tex1.loadFromFile("Win.jpg");	
		else if (win == -1)
			tex1.loadFromFile("lost.jpg");
		else
			tex1.loadFromFile("Smile.jpg");
		
		emoji.setTexture(&tex1);
		window->draw(emoji);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (sp[i][j] == 0)
				{
					RectangleShape temp;

					temp.setSize(Vector2f(cell_size, cell_size));
					temp.setPosition(Vector2f(j * cell_size, i * cell_size + 50));

					Texture tex;
					tex.loadFromFile("Unopen.jpg");
					if (!tex.loadFromFile("Unopen.jpg"))
					{
						cout << "Picture not loaded\n";
					}

					temp.setTexture(&tex);
					window->draw(temp);
				}
				else if (sp[i][j] == -1)
				{
					RectangleShape temp;

					temp.setSize(Vector2f(cell_size, cell_size));
					temp.setPosition(Vector2f(j * cell_size, i * cell_size + 50));

					Texture tex;
					tex.loadFromFile("Flag.jpg");

					temp.setTexture(&tex);
					window->draw(temp);
				}
				else
				{
					total++;
					window->draw(cell[i][j]);
				}
					
			}	
		}

		if (total == rows * cols - mines)
			win = 1;
		
	}
	void OpenSurrounded(int i, int j)
	{
		if (sp[i][j] == 2)
		{
			if (grid[i][j + 1] != 9 && j < cols - 1)
			{
				ExposeCell(i, j + 1);
			}
			if (grid[i][j - 1] != 9 && j > 0)
			{
				ExposeCell(i, j - 1);
			}
			if (i < rows - 1)
			{
				if (grid[i + 1][j + 1] != 9 && j < cols - 1)
				{
					ExposeCell(i + 1, j + 1);
				}
				if (grid[i + 1][j - 1] != 9 && j > 0)
				{
					ExposeCell(i + 1, j - 1);
				}
				if (grid[i + 1][j] != 9)
				{
					ExposeCell(i + 1, j);
				}
			}
			if (i > 0)
			{
				if (grid[i - 1][j + 1] != 9 && j < cols - 1)
				{
					ExposeCell(i - 1, j + 1);
				}
				if (grid[i - 1][j - 1] != 9 && j > 0)
				{
					ExposeCell(i - 1, j - 1);
				}
				if (grid[i - 1][j] != 9)
				{
					ExposeCell(i - 1, j);
				}
			}
		}
	}
	void ExposeCell(int i, int j)
	{
		if (sp[i][j] == 0)
		{
			if (grid[i][j] == 9)
			{
				texture[i][j].loadFromFile("RedMine.jpg");
				if (!texture[i][j].loadFromFile("RedMine.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}

			else if (grid[i][j] == 0)
			{
				texture[i][j].loadFromFile("0.jpg");
				if (!texture[i][j].loadFromFile("0.jpg"))
				{
					cout << "Picture not loaded\n";
				}
				sp[i][j] = 2;
				OpenSurrounded(i, j);
			}
			else if (grid[i][j] == 1)
			{
				texture[i][j].loadFromFile("1.jpg");
				if (!texture[i][j].loadFromFile("1.jpg"))
				{
					cout << "Picture not loaded\n";
				}

			}
			else if (grid[i][j] == 2)
			{
				texture[i][j].loadFromFile("2.jpg");
				if (!texture[i][j].loadFromFile("2.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 3)
			{
				texture[i][j].loadFromFile("3.jpg");
				if (!texture[i][j].loadFromFile("3.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 4)
			{
				texture[i][j].loadFromFile("4.jpg");
				if (!texture[i][j].loadFromFile("4.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 5)
			{
				texture[i][j].loadFromFile("5.jpg");
				if (!texture[i][j].loadFromFile("5.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 6)
			{
				texture[i][j].loadFromFile("6.jpg");
				if (!texture[i][j].loadFromFile("6.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 7)
			{
				texture[i][j].loadFromFile("7.jpg");
				if (!texture[i][j].loadFromFile("7.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			else if (grid[i][j] == 8)
			{
				texture[i][j].loadFromFile("8.jpg");
				if (!texture[i][j].loadFromFile("8.jpg"))
				{
					cout << "Picture not loaded\n";
				}
			}
			cell[i][j].setTexture(&texture[i][j]);
			sp[i][j] = 1;
		}
		
	}
	void MouseLeft(int x, int y)
	{
		
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (x < j * cell_size + cell_size && y < i * cell_size + 50 + cell_size && x >= j * cell_size && y >= i * cell_size + 50)
				{
					
					ExposeCell(i, j);
					if (grid[i][j] == 0 && sp[i][j] != 2)
					{
						sp[i][j] == 2;
						OpenSurrounded(i, j);
					}

					if (grid[i][j] == 9 && sp[i][j] != 0)
					{
						GameEnd();
						win = -1;
					}
						
					break;
				}
		if (x >= cols * cell_size / 2 - 5 && y >= 0 && x < cols * cell_size / 2 + 45 && y < 50)
		{
			win = 2;
		}
	}
	void MouseRight(int x, int y, int&f)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (x < j * cell_size + cell_size && y < i * cell_size + 50 + cell_size && x >= j * cell_size && y >= i * cell_size + 50)
				{
					if (sp[i][j] != -1 && sp[i][j] == 0)
					{
						sp[i][j] = -1;	
						f--;
					}
					else if (sp[i][j] == -1)
					{
						sp[i][j] = 0;
						f++;
					}
						
					break;
				}
	}
	void GameEnd()
	{
		win = -1;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (sp[i][j] == -1 && grid[i][j] != 9)
				{
					sp[i][j] = 1;
					texture[i][j].loadFromFile("CrossedMine.jpg");
					if (!texture[i][j].loadFromFile("CrossedMine.jpg"))
					{
						cout << "Picture not loaded\n";
					}
					cell[i][j].setTexture(&texture[i][j]);
				}
				if (sp[i][j] == 0 && grid[i][j] == 9)
				{
					sp[i][j] = 1;
					texture[i][j].loadFromFile("Mine.jpg");
					if (!texture[i][j].loadFromFile("Mine.jpg"))
					{
						cout << "Picture not loaded\n";
					}
					cell[i][j].setTexture(&texture[i][j]);
				}
				if (sp[i][j] == 0)
					ExposeCell(i, j);
			}
	}
	~Minesweeper()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] sp[i];
			delete[] cell[i];
			delete[] texture[i];
		}
		delete[] window;
		delete[] sp;
		delete[] cell;
		delete[] texture;
	}
};


