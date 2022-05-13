#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <chrono>
#include <ratio>
#include <ctime>
#include "Libreria.h"


struct coord {
	
	int x;
	int y;
};


using namespace std;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using namespace std::chrono;

int menu ();
void quadrati ();
void draw_start_snake (int [][20]);
void move_snake (int [][20], int, int &, int &, int, int &);
int get_direction (int &); // 1 <-, 2 ->, 3 ^, 4 v
int draw_food (int [][20], int &, int &, int &);
void snake_eat_food (int [][20], int, int, int, int, int &, int &, int &);
void draw_wall (int [][20]);
void snake_hit_border (int [][20], int &, int, int);
void snake_hit_wall (int [][20], int &, int, int);
void toloidal_field (int [][20], int &, int &);
void game_over (int, int);



int main () {
	
	srand (time( 0));
	
	initwindow (1000, 1000);
	
	int x = 10, y = 14, lung = 3, life = 1, point = 0, dir = 1, speed; //snake
	bool toloidal = true; //field
	int xf, yf, food = 0; //food
	int dif;
	char points [999];
	
	// 1 <-, 2 ->, 3 ^, 4 v
	int campo [20][20];
	//0 = field, 1 = dnake, -1 = apple,-2 = wall
	
	for (int i = 0; i < 20; i++) {
		for (int n = 0; n < 20; n++) {
			
			campo [i][n] = 0;
		}
	}

	dif = menu ();
	//1 = easy, 2 = medium, 3 = hard
	
	switch (dif) {
		case 1:
			speed = 400;
			break;
		case 2:
			speed = 250;
			break;
		case 3:
			speed = 200;
			break;
	}
	
	quadrati ();
	
	draw_start_snake (campo);
/*		
	for (int i = 0; i < 20; i++) {
		for (int n = 0; n < 20; n++) {
			cout << campo[i][n] << " ";
		}
		cout << endl;
	}
*/
	do {
		

				
		itoa (point, points, 10);
		setbkcolor (COLOR(162, 209, 73));
		setcolor (COLOR (0, 0, 0));
		outtextxy (0, 0, points);
		
		
		
		if (dif > 1) {
			
			draw_wall (campo);
		}
		
		draw_food (campo, xf, yf, food);
		
		
		auto t1 = steady_clock::now();
		auto t2 = t1+chrono::milliseconds(speed);	
		
		bool play = true;
		
		
		while (play) {
			
			chrono::steady_clock::duration d = t2-t1;
			if (d <= chrono::steady_clock::duration::zero()){
				
				if (dif < 3) {
			
					toloidal_field (campo, x, y);
				}
				
				move_snake (campo, dir, x, y, lung, life);
				
				snake_eat_food (campo, xf, yf, x, y, food, lung, point);
			
				if (dif > 1) {
						
					snake_hit_wall (campo, life, x, y);
				}
					
				if (dif == 3) {
						
					snake_hit_border (campo, life, x, y);
				}

				if (kbhit ()) {
					
					int key = (char) getch ();
				
					dir = get_direction (key);
				}				

				play = false;
			} else {	
							
				t1 = steady_clock::now();
			
			}
		}
		
		game_over (life, point);
/*
		for (int i = 0; i < 20; i++) {
			for (int n = 0; n < 20; n++) {
				cout << campo[i][n] << " ";
			}
			cout << endl;
		}		
		
		
		
		cout << "point " << point << endl;
		cout << "lung " << lung << endl;
 		cout << "life " << life << endl;
*/
 		
	} while (life > 0);
		
	getch ();
}

int menu () {
	
	//line (500, 0, 500, 1000);
	int x = 0, y = 0, x1 = 0, y1 = 0;
	int counter [3] = {3, 2, 1};
	char counter2 [3];
	
	settextstyle (10, 0, 5);	
	outtextxy (425, 200, "snake");
	outtextxy (390, 400, "difficolta`");
	
	while (x <= 325 || x >= 600 || y <= 400 || y >= 450) {
		
		while (!ismouseclick(WM_LBUTTONDOWN)) {
				
			delay (20);
		
		}
		getmouseclick (WM_LBUTTONDOWN, x, y);
		cout << x << " - " << y << endl;
	}
	
	
	
	
	if (x >= 325 && x <= 600 && y >= 400 && y <= 450) {
		
		
		delay (20);
		cleardevice ();
		//line (500, 0, 500, 1000);
		outtextxy (430, 200, "facile");
		outtextxy (420, 400, "medio");
		outtextxy (410, 600, "difficile");
		
		
		while (x1 <= 325 || x1 >= 600 || y1 <= 200 || y1 >= 650) {
			
			while (!ismouseclick(WM_LBUTTONDOWN)) {
					
			delay (20);
			}
			
			getmouseclick (WM_LBUTTONDOWN, x1, y1);
			cout << x1 << " - " << y1 << endl;
		}
		
		for (int i = 0; i < 601; i += 200) {
			
			if (x1 >= 325 && x1 <= 600 && y1 >= i && y1 <= i + 50) {
				
				//1 = easy, 2 = medium, 3 = hard
				
				delay (20);
				cleardevice ();
				
				quadrati ();
				
				return i / 200;
			}
		}
	}	
}

void quadrati () {
	
	
	cleardevice ();
	setfillstyle (1, COLOR(162, 209, 73));
	floodfill (1, 1 , COLOR(162, 209, 73));
	
	setcolor (COLOR(170, 215, 81));
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (int i = 0; i < 50; i++) {
			
		line (x1, 0, x2, 1000);
		line (0, y1, 1000, y2);
		x1 += 50;
		x2 += 50;
		y1 += 50;
		y2 += 50;
	}
	
	for (int i = 0; i < 1000; i += 50) {
		for (int n = 0; n < 1000; n += 50) {
			
			if (pari (i / 10) == true) {
				
				if (pari (n / 10) == true) {
					
					setfillstyle (1, COLOR(162, 209, 73));
					floodfill (i + 5, n + 5, COLOR(162, 209, 73));
				}
				if (pari (n / 10) == false) {
				
					setfillstyle (1, COLOR(170, 215, 81));
					floodfill (i + 5, n + 5, COLOR(170, 215, 81));
				}
			}
			
			if (pari (i / 10) == false) {
				
				if (pari (n / 10) == true) {
					
					setfillstyle (1, COLOR(170, 215, 81));
					floodfill (i + 5, n + 5, COLOR(170, 215, 81));
				}
				if (pari (n / 10) == false) {
				
					setfillstyle (1, COLOR(162, 209, 73));
					floodfill (i + 5, n + 5, COLOR(162, 209, 73));
				}
			}
		}
	}
}

void draw_start_snake (int campo [][20]) {
	
	for (int i = 1; i <= 3; i++) {
		
		campo [10][13 + i] = i;
	}
	
	setcolor (COLOR (51, 102, 255));
	for (int i = 0; i < 20; i++) {
		for (int n = 0; n < 20; n++) {
		
			if (campo [i][n] > 0) {
				
				circle (n * 50 + 25, i * 50 + 25, 25);
				setfillstyle (1, COLOR (51, 102, 255));
				floodfill (n * 50 + 25, i * 50 + 25, COLOR (51, 102, 255));
			}
		}
	}
}

void move_snake (int campo [][20], int dir, int& x, int& y, int lung, int &life) {
	
	// 1 <-, 2 ->, 3 ^, 4 v
	
	coord si[400];
	for (int i = 0; i < 400; i++){
		
		si[i] = coord {0, 0};
	}
	int temp = 0;
	
	setlinestyle (0, 1, 1);
	
	
	
	switch (dir) {
		
		case 1:
			
			if (campo[x][y - 1] > 1) {
				
				life--;
			}
			
			//scrolls the whole matrix
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
					
					//if the array cell is greater than zero and is different from the length increases it
					if (campo [i][n] > 0) {
						
						if (campo [i][n] != lung) {
							
							campo [i][n]++;
						}
						//if the matrix cell is equal to the length it resets it because the snake moves
						else {
							campo [i][n] = 0;
							si [temp] = coord {n, i};
							temp++;
						}
					}
				}
			}
			//set to 1 the cell in which the head goes
			campo [x][y - 1] = 1;
			y--;
			
			//draw the snake
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
				
					if (campo [i][n] > 0) {
						
						setcolor (COLOR (51, 102, 255));
						circle (n * 50 + 25, i * 50 + 25, 25);
						setfillstyle (1, COLOR (51, 102, 255));
						floodfill (n * 50 + 25, i * 50 + 25, COLOR (51, 102, 255));
						
					}
				}
			}
			
			for (int i = 0; i < temp; i++) {
				
				if (pari (si [i].x) == true && pari (si [i].y) == true) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == true && pari (si [i].y) == false) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == false) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == true) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
				
			}
			
			
			break;
		case 2:
			
			if (campo[x][y + 1] > 1) {
				
				life--;
			}
			
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
					
					if (campo [i][n] > 0) {
						
						if (campo [i][n] != lung) {
							
							campo [i][n]++;
						}
						else {
							campo [i][n] = 0;
							si [temp] = coord {n, i};
							temp++;
						}
					}
				}
			}
			campo [x][y + 1] = 1;
			y++;
			
			
						
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
				
					if (campo [i][n] > 0) {
						setcolor (COLOR (51, 102, 255));
						circle (n * 50 + 25, i * 50 + 25, 25);
						setfillstyle (1, COLOR (51, 102, 255));
						floodfill (n * 50 + 25, i * 50 + 25, COLOR (51, 102, 255));
					}
				}
			}
			
			for (int i = 0; i < temp; i++) {
				
				if (pari (si [i].x) == true && pari (si [i].y) == true) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == true && pari (si [i].y) == false) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == false) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == true) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
			}
			break;
		case 3:			
			
			if (x != 1) {
				
				if (campo[x - 1][y] > 1) {
					
					life--;
				}
			}
			if (x == 1) {
				
				if (campo[19][y] > 1) {
					
					life--;
				}
			}
			
			
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
					
					if (campo [i][n] > 0) {
						
						if (campo [i][n] != lung) {
							
							campo [i][n]++;
						}
						else {
							campo [i][n] = 0;
							si [temp] = coord {n, i};
							temp++;
						}
					}
				}
			}
			campo [x - 1][y] = 1;
			x--;
			
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
				
					if (campo [i][n] > 0) {
						setcolor (COLOR (51, 102, 255));
						circle (n * 50 + 25, i * 50 + 25, 25);
						setfillstyle (1, COLOR (51, 102, 255));
						floodfill (n * 50 + 25, i * 50 + 25, COLOR (51, 102, 255));
					}
				}
			}
			
			for (int i = 0; i < temp; i++) {
				
				if (pari (si [i].x) == true && pari (si [i].y) == true) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == true && pari (si [i].y) == false) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == false) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == true) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
			}
			break;
		case 4:
			
			if (x != 18) {
				
				if (campo[x + 1][y] > 1) {
					
					life--;
				}
			}
			if  (x == 18) {
				
				if (campo[0][y] > 1) {
					
					life--;
				}
			}
			
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
					
					if (campo [i][n] > 0) {
						
						if (campo [i][n] != lung) {
							
							campo [i][n]++;
						}
						else {
							campo [i][n] = 0;
							si [temp] = coord {n, i};
							temp++;
						}
					}
				}
			}
			campo [x + 1][y] = 1;
			x++;
			
			for (int i = 0; i < 20; i++) {
				for (int n = 0; n < 20; n++) {
				
					if (campo [i][n] > 0) {
						setcolor (COLOR (51, 102, 255));
						circle (n * 50 + 25, i * 50 + 25, 25);
						setfillstyle (1, COLOR (51, 102, 255));
						floodfill (n * 50 + 25, i * 50 + 25, COLOR (51, 102, 255));
					}
				}
			}
			
			for (int i = 0; i < temp; i++) {
				
				if (pari (si [i].x) == true && pari (si [i].y) == true) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == true && pari (si [i].y) == false) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == false) {
					
					setcolor (COLOR (162, 209, 73));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (162, 209, 73));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (162, 209, 73));
				}
				
				if (pari (si [i].x) == false && pari (si [i].y) == true) {
					
					setcolor (COLOR (170, 215, 81));
					rectangle (si [i].x * 50, si [i].y * 50, si [i].x * 50 + 50, si [i].y * 50 + 50);
					setfillstyle (1, COLOR (170, 215, 81));
					floodfill (si [i].x * 50 + 15, si [i].y * 50 + 15, COLOR (170, 215, 81));
				}
			}
			break;	
	}
}

int get_direction (int &key) {
	
	// 1 <-, 2 ->, 3 ^, 4 v
	
	int dir;
	//get the key code
	
	
	if (key != 0) {
		
		//the key is a character
		switch (key) {
			
			case 'w': key = 3; break;
			case 'a': key = 1; break;
			case 's': key = 4; break;
			case 'd': key = 2; break;
		}
	} 
	else {
		
		//the key is a special character
		key = (char) getch ();
		
		switch (key) {
			
			case KEY_UP: key = 3; break;
			case KEY_DOWN: key = 4; break;
			case KEY_LEFT: key = 1; break;
			case KEY_RIGHT: key = 2; break;
		}
	}
	
	dir = key;
	return dir;
}

int draw_food (int campo [][20], int& x, int& y, int& food) {
	
	int r = 15;

	//if ther's no food on the field it draw one
	if (food == 0) {
		
		do {
			
			x = rand () % 20;
			y = rand () % 20;			
		} while (campo [x][y] != 0);
		
		
		cout << "x food" << x << endl;
		cout << "y food" << y << endl;
		
		//sets the matrix cell that contains the apple at -1 (apple value)
		campo [x][y] = -1;
		
		//set the food variable to 1 untill the player eat the apple
		food = 1;
	}

	//apple
	setcolor (COLOR (152, 12, 21));			
	circle (y * 50 + 25, x * 50 + 35, r);
	setfillstyle (1, COLOR (152, 12, 21));
	floodfill (y * 50 + 25, x * 50 + 35, COLOR (152, 12, 21));


	//branch
	setcolor ( COLOR (97, 51, 5));
	setlinestyle (0, 1, 4);
	arc (y * 50 + 25, x * 50 + 11, 270, -45, 13);


	//leaf
	setcolor ( COLOR (8, 136, 23));
	ellipse (y * 50 + 25, x * 50 + 12, 330, 330, 5, 7);
	setfillstyle (1, COLOR (8, 136, 23));
	floodfill (y * 50 + 25, x * 50 + 12, COLOR (8, 136, 23));

}

void snake_eat_food (int campo [][20], int xf, int yf, int xs, int ys, int &food, int &lung, int &point) {
	
	if (xf == xs && yf == ys) {
		
		food = 0;
		lung++;
		point++;
	}
}

void snake_hit_border (int campo [][20], int &life, int x, int y) {
	
	if (x < 0) {
		
		life--;
	}
	if (x > 20) {
		
		life--;
	}
	if (y < 0) {
		
		life--;
	}
	if (y > 20) {
		
		life--;
	}
}

void snake_hit_wall (int campo [][20], int &life, int x, int y) {
	
	int x1 = 6, y1 = 6;
	for (int i = 1; i <= 2; i++){
		for (int k = 1; k <= 2; k++) {
			
			campo [x1 * i][y1 * k] = -2;
		}
	}
	for (int i = 1; i <= 2; i++) {
		for (int k = 1; k <= 2; k++) {
			
			if (x == x1 * i && y == y1 * k) {
				life--;
			}
		}
	}
}

void draw_wall (int campo [][20]) {
	
	int x = 6, y = 6;
	for (int i = 1; i <= 2; i++) {
		for (int k = 1; k <= 2; k++) {
			
			setcolor (COLOR (102, 132, 46));
			rectangle (50 * x * i, 50 * y * k, 50 * x * i + 50, 50 * y * k + 50);
			setfillstyle (1, COLOR (102, 132, 46));
			floodfill (50 * x * i + 1, 50 * y * k + 1, COLOR (102, 132, 46));
		}
	}
}

void toloidal_field (int campo [][20], int &x, int &y) {

	if (x > 20) {
		
		x = 0;
	}
	if (x < 0) {
		
		x = 20;
	}
	if (y > 20) {
		
		y = 0;
	}
	if (y < 0) {
		
		y = 20;
	}
}

void game_over (int life, int points) {
	
	if (life == 0) {
		
		char point [999];
		
		cleardevice ();
		setfillstyle (1, COLOR (1, 1, 1));
		floodfill (1, 1, COLOR (1, 1, 1));
		itoa (points, point, 10);
		setbkcolor (COLOR (1, 1, 1));
		outtextxy (350, 400, "GAME OVER");
		outtextxy (500, 450, point);
	}
}
