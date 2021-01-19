#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>


class field {
private:
	std::vector<std::vector<char>> cells;
	int SIZ1;
public:
	field(int x1, int y1, int player_up,
		int player_down, int LB, int RB, int PLAYER, int SIZ) {
		SIZ1 = SIZ;
		for (int i = 0; i < SIZ; i++) {
			std::vector<char> v;
			for (int j = 0; j < SIZ; j++) {
				if (i == x1 + 1 && j == y1 + 1)
					v.push_back('O');
				else if (i == 0 && !(j > SIZ / 2 - LB && j < SIZ / 2 + RB))
					v.push_back('Z');
				else if (i == SIZ - 1 && !(j > SIZ / 2 - LB && j < SIZ / 2 + RB))
					v.push_back('Z');
				else if (j == 0 || j == SIZ - 1)
					v.push_back('Z');
				else if (i == SIZ - 2 && j >= player_down - PLAYER && j <= player_down + PLAYER)
					v.push_back('=');
				else if (i == 1 && j >= player_up - PLAYER && j <= player_up + PLAYER)
					v.push_back('=');
				else
					v.push_back(' ');

			}
			cells.push_back(v);
		}
	}
	friend std::ostream& operator<< (std::ostream& out, const field& f)
	{
		for (int i = 0; i < f.SIZ1; i++) {
			for (int j = 0; j < f.SIZ1; j++)
			{
				out << f.cells[i][j];
			}
			out << '\n';
		}
		return out;
	}
};


class GameField {
private:
	int x;
	int y;
	int player_up;
	int player_down;
	int LB;
	int RB;
	int PLAYER;
	int SIZ;
	int SPEED;

public:
	GameField(int x1, int y1, int LB1, int RB1, int PLAYER1, int SIZ1, int SPEED1) {
		x = x1;
		y = y1;
		LB = LB1;
		RB = RB1;
		PLAYER = PLAYER1;
		SIZ = SIZ1;
		player_up = SIZ / 2;
		player_down = SIZ / 2;
		SPEED = SPEED1;
	}

	bool move_up() {
		return x > 0;
	}
	bool move_down() {
		return x < SIZ - 3;
	}
	bool move_left() {
		return y > 0;
	}
	bool move_right() {
		return y < SIZ - 3;
	}

	void move_up_do() {
		x -= 1;
	}
	void move_down_do() {
		x += 1;
	}
	void move_right_do() {
		y += 1;
	}
	void move_left_do() {
		y -= 1;
	}

	bool player_up_move_left() {
		if (player_up > 1 + PLAYER) {
			player_up -= 1;
			return true;
		}
		return false;
	}
	bool player_down_move_left() {
		if (player_down > 1 + PLAYER) {
			player_down -= 1;
			return true;
		}
		return false;
	}
	bool player_up_move_right() {
		if (player_up < SIZ - 2 - PLAYER) {
			player_up += 1;
			return true;
		}
		return false;
	}
	bool player_down_move_right() {
		if (player_down < SIZ - 2 - PLAYER) {
			player_down += 1;
			return true;
		}
		return false;
	}


	void game() {
		int dir = 1 + rand() % 4;
		int upii = 1;
		int counter = 1;


		while (true) {
			counter += 1;
			counter %= 10;
			if (_kbhit())
			{

				switch (_getch())
				{
				case 75:
					this->player_down_move_left();
					break;
				case 77:
					this->player_down_move_right();
					break;
				}
			}

			if (counter % 10 == 0) {
				if (y >= player_up) {
					this->player_up_move_right();
				}
				else {
					this->player_up_move_left();
				}

				switch (dir) {
				case(1): {
					if ((x == 0 && (y + 1 <= SIZ / 2 - LB || y + 1 >= SIZ / 2 + RB))
						|| (x == 1 && y + 1 <= player_up + PLAYER && y + 1 >= player_up - PLAYER))
						dir = 2;
					else  if (y == SIZ - 3)
						dir = 4;
					else {
						this->move_right_do();
						this->move_up_do();
					}
					break;
				}
				case(2): {
					if ((x == SIZ - 2 && (y + 1 <= SIZ / 2 - LB || y + 1 >= SIZ / 2 + RB))
						|| (x == SIZ - 3 && y + 1 <= player_down + PLAYER && y + 1 >= player_down - PLAYER))
						dir = 1;
					else  if (y == SIZ - 3)
						dir = 3;
					else {
						this->move_right_do();
						this->move_down_do();
					}
					break;
				}
				case(3): {
					if ((x == SIZ - 3 && (y - 1 <= SIZ / 2 - LB || y - 1 >= SIZ / 2 + RB))
						|| (x == SIZ - 4 && y - 1 <= player_down + PLAYER && y - 1 >= player_down - PLAYER))
						dir = 4;
					else  if (y == 0)
						dir = 2;
					else {
						this->move_left_do();
						this->move_down_do();
					}
					break;
				}
				case(4): {
					if ((x == 0 && (y - 1 <= SIZ / 2 - LB || y - 1 >= SIZ / 2 + RB))
						|| (x == 1 && y - 1 <= player_up + PLAYER && y - 1 >= player_up - PLAYER))
						dir = 3;
					else  if (y == 0)
						dir = 1;
					else {
						this->move_left_do();
						this->move_up_do();
					}
					break;
				}
				}
			}


			Sleep(SPEED);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
			std::cout << field(x, y, player_up, player_down, LB, RB, PLAYER, SIZ);
			if ((x == -1 || x == SIZ - 2)) {
				std::cout << "\n----GAME OVER----\n";
				break;
			}
		}
	}
};



int main() {
	int LB = 5;
	int RB = 4;
	int PLAYER = 1;
	int SIZ = 20;
	int SPEED = 0;

	while (true) {
		std::cout << "\n____PRESS Q TO START GAME____\n";
		std::cout << "\n____PRESS S TO SETTINGS____\n";
		std::cout << "\n____PRESS OTHER KEY TO LEAVE____\n";
		char inpt;
		std::cin >> inpt;
		if (inpt == 'Q' || inpt == 'q' || inpt == 'й' || inpt == 'Й') {
			GameField F = GameField(3 + rand() % (SIZ - 5), 3 + rand() % (SIZ - 5), LB, RB, PLAYER, SIZ, SPEED);
			system("cls");
			F.game();
		}
		else if(inpt == 'S' || inpt == 's') {
			system("cls");
			std::cout << "\n____TO CHANGE LEFT BORDER PRESS L_____\n";
			std::cout << "\n____TO CHANGE RIGHT BORDER PRESS R____\n";
			std::cout << "\n____TO CHANGE PLAYER SIZE PRESS P_____\n";
			std::cout << "\n____TO CHANGE FIELD SIZE PRESS F______\n";
			std::cout << "\n____TO CHANGE SPEED PRESS S___________\n";
			std::cout << "\n____TO EXIT PRESS OTHER KEY___________\n";
			char set_inpt;
			std::cin >> set_inpt;
			system("cls");


			if (set_inpt == 'L' || set_inpt == 'l') {
				std::cout << "\n____SET VALUE OF LB______\n";
				int LB1;
				std::cin >> LB1;
				LB = LB1;
				system("cls");
			}
			else if (set_inpt == 'R' || set_inpt == 'r') {
				std::cout << "\n____SET VALUE OF RB______\n";
				int RB1;
				std::cin >> RB1;
				RB = RB1;
				system("cls");
			}
			else if (set_inpt == 'P' || set_inpt == 'p') {
				std::cout << "\n____SET VALUE OF PLAYER______\n";
				int PLAYER1;
				std::cin >> PLAYER1;
				PLAYER = PLAYER1;
				system("cls");
			}
			else if (set_inpt == 'F' || set_inpt == 'f') {
				std::cout << "\n____SET VALUE OF SIZ______\n";
				int SIZ1;
				std::cin >> SIZ1;
				SIZ = SIZ1;
				system("cls");
			}
			else if (set_inpt == 'S' || set_inpt == 's') {
				std::cout << "\n____SET VALUE OF SPEED______\n";
				int SPEED1;
				std::cin >> SPEED1;
				SPEED = SPEED1;
				system("cls");
			}
			else {
				continue;
			}
		}
		else{
			return 0;
		}
	}
}

