#include <iostream> 
#include <time.h> 
#include <windows.h> 
#include <conio.h> 

enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 

void setColor(Color text, Color background) 
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); 
}
using namespace std; 

enum Napravlenie { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, escepushka = 27, BackSpace = 8, Q = 113 };


void SetCursor(int x, int y) 
{
	COORD myCoords = { x,y }; 
	SetConsoleCursorPosition(hStdOut, myCoords); 
}
struct Ships
{
	int deck = { 0 };
	bool horizontal = true;
	bool alive = true;
	int x, y;
};
void explosion(Ships* characteristic, int ship_pos[12][24], int plus, int& end) 
{
	int A = 0;
	int B = 13; 
	int C = 0; 
	bool alive = false; 
	for (int n = 13; n > 3; n--)
	{
		for (int i = 1; i < 11; i++) 
		{
			for (int r = 2; r < 22; r++)
			{
				if (ship_pos[i][r] == n) 
				{
					alive = true; 
					i = 11; 
					break; 
				}
			}
		}
		if (alive == false) 
		{
			characteristic[B - n + plus].alive = false; 
		}
		else 
		{
			alive = false; 
		}
	}
	for (int i = plus; i < 10 + plus; i++) 
	{
		if (i == 0 || i == 10) 
		{
			A = 0; 
		}
		else if (i == 1 || i == 2 || i == 11 || i == 12)  
		{
			A = 1; 
		}
		else if (i > 2 && i < 6 || i > 12 && i < 16)  
		{
			A = 2; 
		}
		else  
		{
			A = 3; 
		}
		if (characteristic[i].alive == false) 
		{
			if (characteristic[i].horizontal == true) 
			{
				for (int q = 0; q < 3; q++)
					for (int w = 0; w < characteristic[i].deck * 3 + A; w++)
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x - 4 + w] = 2; 
				}
				for (int g = 0; g < 2 * characteristic[i].deck; g++)
				{
					ship_pos[characteristic[i].y - 1][characteristic[i].x - 2 + g] = 3;
				}
			}
			else if (characteristic[i].horizontal == false)  
			{
				for (int q = 0; q < characteristic[i].deck + 2; q++)
				{
					for (int w = -4; w < 2; w++)  
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x + w] = 2; 
					}
				}
				for (int g = 0; g < characteristic[i].deck; g++) 
				{
					for (int n = -2; n < 0; n++) 
					{
						ship_pos[characteristic[i].y - 1 + g][characteristic[i].x + n] = 3; 
					}
				}
			}
			C++; 
		}
	}
	if (C == 10 && plus == 0) 
	{
		end = 1; 
	}
	else if (C == 10 && plus == 10) 
	{
		end = 2; 
	}
	else 
	{
		C = 0;
	}
}
void LoadCharactShips(Ships* characteristic) 
{
	for (int i = 0; i < 20; i++)
	{
		if (i == 0 || i == 10) 
		{
			characteristic[i].deck = 4; 
		}
		else if (i > 0 && i <= 2 || i > 10 && i <= 12) 
		{
			characteristic[i].deck = 3; 
		}
		else if (i > 2 && i <= 5 || i > 12 && i <= 15) 
		{
			characteristic[i].deck = 2; 
		}
		else if (i > 5 && i <= 9 || i > 15 && i <= 19) 
		{
			characteristic[i].deck = 1;  
		}
	}
}
void auto_arrangement(Ships* characteristic, int ship_pos[12][24], int plus)  
{
	int y, x, ship = plus;  
	while (ship < plus + 10)  
	{
		characteristic[ship].horizontal = 0 + rand() % 2;  
		y = 2 + rand() % 9, x = (1 + rand() % 9) * 2;  
		if (characteristic[ship].horizontal == false && y + characteristic[ship].deck >= 13)
			 
		{
			y -= y + characteristic[ship].deck - 12;  
		}
		else if (characteristic[ship].horizontal == true && x + characteristic[ship].deck * 2 >= 24)
			 
		{
			x -= (x + characteristic[ship].deck * 2) - 22;  
		}
		if (characteristic[ship].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[ship].deck * 2 - 2] == 0)
			 
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y;  
			for (int q = 0; q < 3; q++)
			{
				for (int w = 1; w < characteristic[ship].deck * 3 + 1; w++)
				{
					ship_pos[y - 2 + q][x - 3 + w] = 1;   
				}
			}
			for (int g = 0; g < 2 * characteristic[ship].deck; g++)  
			{
				ship_pos[y - 1][x + g] = 13 - ship + plus;   
			}
			ship++;  
		}
		if (characteristic[ship].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[ship].deck - 2][x] == 0)
			 
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y; 
			for (int q = 0; q < characteristic[ship].deck + 2; q++)
			{
				for (int w = 0; w < 6; w++)
				{
					ship_pos[y - 2 + q][x - 2 + w] = 1;  
				}
			}
			for (int g = 0; g < characteristic[ship].deck; g++)
			{
				for (int n = 0; n < 2; n++)  
				{
					ship_pos[y - 1 + g][x + n] = 13 - ship + plus;  
				}
			}
			ship++;  
		}
	}
}
void PaintPos(int mas[12][24], int x, int num_color)  
{
	for (int i = 1; i < 11; i++)
	{
		int y = 1 + i;  
		SetCursor(x, y);  

		for (int g = 2; g < 22; g++)
		{
			if (mas[i][g] == 2)  
			{
				setColor(LightGray, LightGray);  
			}
			else if (mas[i][g] == 3)  
			{
				setColor(LightMagenta, LightMagenta);  
			}
			else if (mas[i][g] >= 4)  
			{
				setColor(Color(num_color), Color(num_color));  
			}
			else  
			{
				setColor(White, White);  
			}
			cout << "+"; 
		}
		cout << "\n";  
	}
}
void Avake()  
{
	setColor(White, LightBlue);  
	SetCursor(24, 12);  
	cout << "MORSKOY BOY";  
}
void CreatField(int speed, int X, int num_color)  
{
	SetCursor(X, 1);  
	char mas[10] = { 'A','B','C','D','E','F','G','H','I','K' }; 
	setColor(White, Color(num_color)); 
	int A = 0, B = 0;  
	cout << "  " << mas[0];  
	for (int i = 0; i < 12; i++)
	{
		if (B == 0)  
		{
			SetCursor(X + 3, 1 + i);  
			B++;  
		}
		else  
		{
			SetCursor(X, 1 + i);   
		}
		for (int g = 0; g < 23; g++)
		{
			if (i == 0 && g == 22)  
			{
				setColor(Color(num_color), Color(num_color));  
				Sleep(speed);  
				cout << '+';  
			}
			if (i == 0 && g > 0 && g < 10)  
			{
				setColor(White, Color(num_color));  
				Sleep(speed);  
				cout << " " << mas[g]; 
			}
			else if (i > 0 && i < 11 && g == 0)  
			{
				setColor(White, Color(num_color)); 
				if (i < 10)  
				{
					Sleep(speed);  
					cout << i << ' ';  
				}
				else 
				{
					Sleep(speed);  
					cout << i;  
				}
			}
			else if (i == 11 || g > 20 && g < 23)  
			{
				if (A == 0 && i == 11)  
				{
					Sleep(speed); 
					cout << "+"; 
					A++;  
				}
				setColor(Color(num_color), Color(num_color));  
				Sleep(speed);  
				cout << '+';  
			}
			else if (i > 0)  
			{
				Sleep(speed);  
				setColor(White, White);  
				cout << '+'; 
			}
		}
	}
	setColor(Black, Black); 
}
void Paint(char variant[2][30], int T)  
{
	system("cls"); 
	for (int i = 0; i < 2; i++)
	{
		SetCursor(30, 6 + i);  
		for (int p = 0; p < 30; p++)
		{
			if (i == T)  
			{
				setColor(Black, White);  
			}
			else  
			{
				setColor(White, Black); 
			}
			cout << variant[i][p];  
		}
	}
	CreatField(0, 0, 9);  
}
void Meny(int num)
{
	char variant[11][40] = { "VRAQ DUMAET KUDA UDARITY...","VRAQ PROMAZAL!", "VRAQ POPAL!", "VRAQ POBEDIL... NE QRUSTI...", "TVOY XOD." , "TI PROMAZAL...", "TI POPAL!", "TI POBEDIL, POZDRAVLAYU!", "+++++++++++++++++++++++++++++++++++++++", "TI POPAL XODI SNOVA!", "VAUU, TI UNICTOJIL VRAJRSKIY KORABL!" };
	 
	SetCursor(22, 15); 
	setColor(Black, Black); 
	for (int i = 0; i < 25; i++)
	{
		cout << variant[10][i]; 
		cout << variant[10][i]; 
	}
	SetCursor(22, 15); 
	if (num > 0 && num < 4) 
	{
		setColor(Red, Black); 
	}
	else 
	{
		setColor(Green, Black); 
	}
	for (int i = 0; i < 30; i++)
	{
		cout << variant[num][i];  
	}
}
int main()  
{
	srand(time(NULL)); 
	char variant[2][30] = { "AVTOMATICESKAYA RASTANOVKA","RUCNAYA RASTANOVKA" };
	int ship_pos[12][24] = { 0 };  
	int enemy_ship_pos[12][24] = { 0 };  
	
	Ships* characteristic = new Ships[20]; 
	LoadCharactShips(characteristic);  
	int key = 1, y = 2, x = 2, num = 0, change = 1, A = 0, xx = 37, yy = 2, up = 0, down = 0, over = 0;
	bool manual_placement = true, your_turn = 0 + rand() % 2, start = false;  
	
	Avake();  
	Sleep(1500);  
	setColor(White, Black);  
	system("cls");  
	CreatField(1, 0, 9);  
	Paint(variant, change);
	do  
	{
		key = _getch();  
		switch (key)  
		{
		case Up:  
			if (y > 0)  
			{
				y--;  
				change = y;  
				Paint(variant, change); 
			}
			break;
		case Down:  
			if (y < 1)  
			{
				y++; 
				change = y;  
				Paint(variant, change);  
			}
			break;
		case Enter:
			do
			{
				switch (change)
				{
				case 0:  
					manual_placement = false;  
					A++;  
					break;
				case 1:
					manual_placement = true;  
					A++;  
					y++;  
					break;
				}
			} while (key != Enter);
		}
	} while (A < 1);
	system("cls");  
	CreatField(0, 0, 9); 
	x = 2, y = 2;
	if (manual_placement == false)  
	{
		auto_arrangement(characteristic, ship_pos, 0); 
		PaintPos(ship_pos, 2, 0);  
		start = true; 
	}
	else if (manual_placement == true && num < 10)  
	{
		do  
		{
			PaintPos(ship_pos, 2, 0);  
			SetCursor(x, y);  
			setColor(Black, Black);  
			if (characteristic[num].horizontal == true)  
			{
				for (int i = 0; i < characteristic[num].deck; i++)
				{
					cout << "++";  
				}
			}
			else if (characteristic[num].horizontal == false)
			{
				y += characteristic[num].deck;  
				for (int i = 0; i < characteristic[num].deck; i++)
				{
					cout << "++";  
					y--;  
					SetCursor(x, y);  
				}
			}
			key = _getch(); 
			switch (key)  
			{
			case Left:  
				if (x > 3)  
				{
					x -= 2;  
				}
				break;
			case Right:  
				if (characteristic[num].horizontal == true)  
				{
					if (x < 22 - characteristic[num].deck * 2)  
					{
						x += 2;  
					}
				}
				else   
				{
					if (x < 20)  
					{
						x += 2;  
					}
				}
				break; 
			case Up: 
				if (y > 2)  
				{
					y--;   
				}
				break; 
			case Down:  
				if (characteristic[num].horizontal == false)  
				{
					if (y < 12 - characteristic[num].deck)
					{
						y++;   
					}
				}
				else
				{
					if (y < 11)  
					{
						y++;  
					}
				}
				break;  
			case Q:  
				characteristic[num].horizontal = !characteristic[num].horizontal; 
				if (characteristic[num].horizontal == false && y + characteristic[num].deck >= 13)
					 
				{
					y -= y + characteristic[num].deck - 12;  
				}
				else if (characteristic[num].horizontal == true && x + characteristic[num].deck * 2 >= 24)
					 
				{
					x -= (x + characteristic[num].deck * 2) - 22;  
				}
				for (int i = 0; i < 10 - num; i++)
				{
					characteristic[num + i].horizontal = characteristic[num].horizontal; 
				}
				break;  
			case Enter:  
				if (characteristic[num].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[num].deck * 2 - 2] == 0)
				{
					characteristic[num].x = x + 2, characteristic[num].y = y;
					for (int q = 0; q < 3; q++)
					{
						for (int w = 1; w < characteristic[num].deck * 3 + 1; w++)
						{
							ship_pos[y - 2 + q][static_cast<unsigned long long>(x) - 3 + w] = 1;
						}
					}
					for (int g = 0; g < 2 * characteristic[num].deck; g++)  
					{
						ship_pos[y - 1][x + g] = 13 - num;   
					}
					num++;  
				}
				if (characteristic[num].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[num].deck - 2][x] == 0)
				{
					characteristic[num].x = x + 2, characteristic[num].y = y;
					for (int q = 0; q < characteristic[num].deck + 2; q++)
					{
						for (int w = 0; w < 6; w++)
						{
							ship_pos[y - 2 + q][x - 2 + w] = 1;  
						}
					}
					for (int g = 0; g < characteristic[num].deck; g++)  
					{
						for (int n = 0; n < 2; n++)  
						{
							ship_pos[y - 1 + g][x + n] = 13 - num;  
						}
					}
					num++;  
				}
			}
			start = true; 
		} while (num <= 9);  
	}
	Sleep(20);
	CreatField(1, 35, 4);  
	auto_arrangement(characteristic, enemy_ship_pos, 10);  
	PaintPos(enemy_ship_pos, 37, 15);  
	do
	{
		if (your_turn == true)  
		{
			do  
			{
				x = xx, y = yy; 
				PaintPos(enemy_ship_pos, 37, 15);  
				setColor(DarkGray, DarkGray);  
				SetCursor(x, y); 
				cout << "++";  
				key = _getch();
				switch (key)  
				{
				case Left: 
					if (x > 38) 
					{
						x -= 2;  
						xx = x;  
					}
					break;
				case Right:  
					if (x < 55)  
					{
						x += 2;  
						xx = x;  
					}
					break;  
				case Up:  
					if (y > 2)  
					{
						y--;   
						yy = y; 
					}
					break; 
				case Down: 
					if (y < 11)  
					{
						y++;  
						yy = y; 
					}
					break;
				case Enter:
					if (enemy_ship_pos[y - 1][x - 35] >= 4)  
					{
						for (int i = 0; i < 2; i++)
						{
							enemy_ship_pos[y - 1][x - 35 + i] = 3;  
							explosion(characteristic, enemy_ship_pos, 10, over);  
						}
						Meny(9);  
						Sleep(500); 
					}
					else if (enemy_ship_pos[y - 1][x - 35] < 2)  
					{
						for (int i = 0; i < 2; i++)
						{
							enemy_ship_pos[y - 1][x - 35 + i] = 2;  
						}
						Sleep(500); 
						Meny(5);  
						your_turn = false;  
					}
					break;
				}
			} while (key != Enter); 
		}
		if (your_turn == false)  
		{
			Sleep(0 + rand() % 400);  
			Meny(0);  
			PaintPos(ship_pos, 2, 0);  
			Sleep(0 + rand() % 400); 
			x = (2 + rand() % 10) * 2, y = 2 + rand() % 10;  
			if (ship_pos[y - 1][x - 1] >= 4)  
			{
				for (int i = 0; i < 2; i++)
				{
					ship_pos[y - 1][x - 2 + i] = 3;  
					explosion(characteristic, ship_pos, 0, over);  
				}
				Meny(2);  
				Sleep(0 + rand() % 750);  
			}
			else if (ship_pos[y - 1][x - 1] <= 2)  
			{
				for (int i = 0; i < 2; i++)
				{
					ship_pos[y - 1][x - 2 + i] = 2;  
				}
				Meny(1); 
				Sleep(0 + rand() % 750);  
				your_turn = true;  
			}
		}
	} while (over == 0);
	PaintPos(ship_pos, 2, 0);
	PaintPos(enemy_ship_pos, 37, 15); 
	if (over == 2) 
	{
		Meny(7);
	}
	else
	{
		Meny(3);
	}
	Sleep(500000);
}