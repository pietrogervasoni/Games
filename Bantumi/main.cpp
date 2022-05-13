/*
	Name: Bantumi
	Author: Gervasoni Pietro
	Date: 13/02/22
*/

#include <iostream>
#include <winbgim.h>
#include <time.h>
#include <stdlib.h>
#include "libreriagrossa.h"

using namespace std;

void campo (int x, int xe, int ye, char n [], char n1 []);
int n_ciotola (int x, int y, int xi, int yi, int xf, int yf, int turni);
int sposta_semi (int vettore[], int nciotola);

int main () {
	
	srand (time (0));
	int xb = 50, x;
	int xe = 100, ye = 595;
	int s, g = 0;
	//s = rand () % 4 + 3;
	//int semi [14] = {s, s , s, s, s, s, g, s, s, s, s, s, s, g};
	int granaio1 = 6;
	int granaio2 = 13;
	int turni;
	char nsemi [999], nsemig [999];
	char n [999], n1 [999];
	int semi [14] = {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0};
	int semi2 [14];
	int semitot1 = 0, semitot2 = 0, semitot;
	
	initwindow (1000, 700);
	
	//disegna il tabellone
	itoa (s, nsemi, 10);
	itoa (g, nsemig, 10);
	campo (xb, xe, ye, nsemi, nsemig);
	
		
	turni = rand () % 2 + 1;
	//cout << "turno: " << turni << endl;
	
	//scrive il turno a schermo
	setcolor (COLOR (255, 255, 255));
	settextstyle (10, 0, 4);
	if (turni == 1) {
		
		setbkcolor (COLOR (1, 1, 1));
		outtextxy (475, 325, "TURNO GIOCATORE 1");
	} else {
		
		setbkcolor (COLOR (1, 1, 1));
		outtextxy (475, 325, "TURNO GIOCATORE 2");
	}
	
	
	int x1, y1, x2, y2;
		do{
		
		if (turni == 1) {
			
			//aspetta fino a quando non si clicca con il mouse
			while (!ismouseclick(WM_LBUTTONDOWN)) {
				
				delay (20);
			}
			
			for (int i = 0; i < 14; i ++) {
				
				semi2 [i] = semi [i];
			}
			cout << "semi2 ";
			print_array (semi2, 14);
			
			//rileva il click e la posizione e in base ad esso capisce che ciotola si seleziona
			getmouseclick (WM_LBUTTONDOWN, x1, y1);
			cout << x1 << " - " << y1 << endl;
			cout << "i " << n_ciotola (x1, y1, 50, 500, 150, 600, turni) << endl;
			int nciotola = n_ciotola (x1, y1, 50, 500, 150, 600, turni);
			cout << "prima di spostamento: ";
			print_array (semi, 14);
			//sposta i semi uno ad uno nelle celle successive a quellaselezionata
			sposta_semi (semi, nciotola);
			cout << "dopo spostamento: ";
			print_array (semi, 14);
						
			//furto
			
			//int semi [14] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0};
			//int semi2 [14] = {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0};
			
			// se la cella in cui finisce l'ultimo seme spostato e` zero entra nell' if
			if (semi2 [semi2 [nciotola - 1] + 7] == 0) {
				
				//somma a tale cella il valore della cella opposta es: 1 - 13, 5 - 9 ed azzera quest'ultima
				semi [6] += semi2 [13 - nciotola];
				cout << nciotola << endl;
				semi [13 - nciotola - 1] = 0;
			}
			cout << "dopo furto: ";
			print_array (semi, 14);
			
			
			turni = 2;
			
			//ripeti turno
			
			if (semi2 [nciotola - 1] + nciotola == 7) {
				
				turni = 1;
			}		
		} 
		
		cleardevice ();
		delay (200);
		x = 50;
		
		for (int i = 12; i > 6; i--) {
			
			itoa (semi [i], n, 10);
			button (x, 50, 100, 100, n, COLOR (134, 89, 45));
			x += 150;
		}
		itoa (semi [13], n1, 10);
		button (50, 300, 150, 100, n1, COLOR (134, 89, 45));
		
		/*
		for (int i = 13; i < 7; i--) {
			
			itoa (semi [i], n, 10);
			button (x, 50, 100, 100, n, COLOR (134, 89, 45));
			x += 150;
		}
		itoa (semi [13], n1, 10);
		button (50, 300, 150, 100, n1, COLOR (134, 89, 45));
		*/
		
		x = 50;
		for (int i = 0; i < 6; i++) {
			
			itoa (semi [i], n, 10);
			button (x, 500, 100, 100, n, COLOR (134, 89, 45));
			x += 150;
		}
		itoa (semi [6], n1, 10);
		button (750, 300, 150, 100, n1, COLOR (134, 89, 45));
		
		setcolor (COLOR (255, 255, 255));
		settextstyle (10, 0, 4);
		if (turni == 1) {
			
			setbkcolor (COLOR (1, 1, 1));
			outtextxy (475, 325, "TURNO GIOCATORE 1");
		} else {
			
			setbkcolor (COLOR (1, 1, 1));
			outtextxy (475, 325, "TURNO GIOCATORE 2");
		}
		
		if (turni == 2) {
			
			while (!ismouseclick(WM_LBUTTONDOWN)) {
				
				delay (20);
			}

			for (int i = 0; i < 14; i ++) {
				
				semi2 [i] = semi [i];
			}
			cout << "semi2 ";
			print_array (semi2, 14);
			
			getmouseclick (WM_LBUTTONDOWN, x2, y2);
			cout << x2 << " - " << y2 << endl;			
			cout << "i " << n_ciotola (x2, y2, 800, 50, 900, 150, turni) << endl;
			int nciotola2 = n_ciotola (x2, y2, 800, 50, 900, 150, turni);
			cout << "prima di spostamento: ";			
			print_array (semi, 14);
			sposta_semi (semi, nciotola2);
			cout << "dopo spostamento: ";
			print_array (semi, 14);
			
			//furto
			
			//int semi [14] = {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0};
			//int semi2 [14] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0};
			
			// se la cella in cui finisce l'ultimo seme spostato e` zero entra nell' if
			if (semi2 [semi2 [nciotola2 - 1] + 7] == 0) {
				
				//somma a tale cella il valore della cella opposta es: 1 - 13, 5 - 9 ed azzera quest'ultima
				semi [13] += semi2 [13 - nciotola2 - 1];
				cout << nciotola2 << endl;
				semi [13 - nciotola2 - 1] = 0;
			}
			cout << "dopo furto: ";
			print_array (semi, 14);
			
			turni = 1;
			
			//ripeti turno
			
			if (semi2 [nciotola2 - 1] + nciotola2 == 14) {
				
				turni = 2;
			}	
		}
		
		//cout << "turni " << turni << endl;
		
		
		cleardevice ();
		delay (200);
		x = 50;
		
		for (int i = 12; i > 6; i--) {
			
			itoa (semi [i], n, 10);
			button (x, 50, 100, 100, n, COLOR (134, 89, 45));
			x += 150;
		}
		itoa (semi [13], n1, 10);
		button (50, 300, 150, 100, n1, COLOR (134, 89, 45));
		
		x = 50;
		for (int i = 0; i < 6; i++) {
			
			itoa (semi [i], n, 10);
			button (x, 500, 100, 100, n, COLOR (134, 89, 45));
			x += 150;
		}
		itoa (semi [6], n1, 10);
		button (750, 300, 150, 100, n1, COLOR (134, 89, 45));
		
		setcolor (COLOR (255, 255, 255));
		settextstyle (10, 0, 4);
		if (turni == 1) {
			
			setbkcolor (COLOR (1, 1, 1));
			outtextxy (475, 325, "TURNO GIOCATORE 1");
		} else {
			
			setbkcolor (COLOR (1, 1, 1));
			outtextxy (475, 325, "TURNO GIOCATORE 2");
		}
		
		cout << endl;
		cout << endl;
		semitot1 = 0;
		semitot2 = 0;
		
		for (int i = 0; i < 7; i++) {
			
			semitot1 += semi [i];
			semitot2 += semi [i + 7];
		}
		//cout << "semitot 1: " << semitot1 << endl;
		//cout << "semitot 2: " << semitot2 << endl;
		semitot = semitot1 + semitot2;
		
	} while (semitot1 <= semitot / 2 + 1 && semitot2 <= semitot / 2 + 1);
	
	if (semi[13] > semi[6]) {
		
		cout << "GIOCATORE 2 HAI VINTO" << endl;
	} else {
		
		cout << "GIOCATORE 1 HAI VINTO" << endl;
	}
	
	getch ();
}

void campo (int x, int xe, int ye, char n [], char n1 []) {
	
	for (int i = 0; i < 6; i++) {
		
		//x = 50
		button (x, 50, 100, 100, n, COLOR (134, 89, 45));
		button (x, 500, 100, 100, n, COLOR (134, 89, 45));
		button (50, 300, 150, 100, n1, COLOR (134, 89, 45));
		button (750, 300, 150, 100, n1, COLOR (134, 89, 45));
		x += 150;
	}
}

int n_ciotola (int x, int y, int xi, int yi, int xf, int yf, int turni) {
	
	int nciotola;
	//controlla se il click e` compreso in una delle ciotole e restituisce quale e`
	//se il giocatore e` 1 le ciotole partono da 1 se e` 2 partono da 8
	if (turni == 1) {
		
		for (int i = 1; i <= 6; i++) {
				
			if (x >= xi && x <= xf && y >= yi && y <= yf) {
				
				nciotola = i;
				break;
			}
			else {
				
				nciotola = 0;
			}
			xi += 150;
			xf += 150;
			
		}
	}
	if (turni == 2) {
		
		for (int i = 8; i <= 13; i++) {
				
			if (x >= xi && x <= xf && y >= yi && y <= yf) {
				
				nciotola = i;
				break;
			}
			else {
				
				nciotola = 0;
			}
			xi -= 150;
			xf -= 150;
			
		}
	}
	return nciotola;	
}

int sposta_semi (int vettore[], int nciotola) {
	
	int counter = 0, nciotola2;

	//aumenta di uno tutte le ciotole seguenti a quella selezionata e azzera la stessa
	for (int i = vettore [nciotola - 1]; i > 0; i--) {
		
		//se il seme da aggiungere va oltre il numero delle ciotole torna alla prima sottraendole tutte alla prima tramite il counter
		if (nciotola == 14 || nciotola + counter == 14) {
			
			counter = -13;
		}
		//cout << i << " ";
		vettore [nciotola + counter]++;
		counter++;
	}

	vettore [nciotola - 1] = 0;
}

