#include <iostream>
#include <math.h>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <winbgim.h>

using namespace std;


//definizione dei prototipi della funzione
void leyup(int);
int max(int[], int);
int min(int[], int);
int somma(int[], int);
float media(int[], float);
int ripetuto(int[], int);
void testo();
void migliaia(int);
void ricorrenza(int[], int);
float lunghezza_float (float);
void max_ricorrenza (int[], int);
void arrey_rand (int[], int, int, int);
void posizione_0_arrey (int[], int);
void posizione_arrey (int[], int);
void posizione_arrey2 (int[], int);
void magg_min_arrey (int [], int [], int);
void magg_min_arrey2 (int [], int [], int);
void char_ascii (char);
void ascii_char (int);
void ascii_char_arrey (int [], int);
void primo (int);
void button (int x1, int y1, int lung, int alt, char scritta[], int colorBK = COLOR (100, 100, 100));
bool button_click (int x1, int y1, int lung, int alt, int x, int y);
void print_array (int vettore [], int dim);


void leyup(int lung) {
	
	//pulisce lo schermo
	system("cls");
	
	//scrive la  prima riga
	for (int i = 0; i < lung; i++) {
		cout << "*";
	}

	cout << endl;

	cout << "*";
	
	//inserisce gli spazzi prima della parola
	for (int s = 0; s < ((lung - 3 - 2) / 2); s++) {
		cout << " ";
	}
	cout << "yes";
	
	//inserisce gli spazzi dopo della parola
	for (int d = 0; d < ((lung - 3 - 2) / 2); d++) {
		cout << " ";
	}
	cout << "*" << endl;

	//fa l'ultima riga
	for (int i = 0; i < lung; i++) {
		cout << "*";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

int max(int numeri[], int n) {
	
	//imposta come massimo il primo numero e poi controlla se i successivi sono maggiori
	//se si li imposta coma massimo
	int max = numeri[0];
	for (int i = 1; i < n; i++) {
		if (numeri[i] > max) {
			max = numeri[i];
		}
	}
	return max;
}

int min(int numeri[], int n) {
	
	//imposta come minimo il primo numero e poi controlla se i successivi sono maggiori
	//se si li imposta coma minimo
	int min = numeri[0];
	for (int i = 1; i < n; i++) {
		if (numeri[i] < min) {
			min = numeri[i];
		}
	}
	return min;
}

int somma(int numeri[], int n) {
	
	//imposta la somma a 0 e poi somma volta per volta gli elementi di un arrey
	int somma = 0;
	for (int i = 0; i < n; i++) {
		somma = somma + numeri[i];
	}
	return somma;
}

float media(int vettore[], float n) {
	
	//stramite la somma calcola la media dividendola per il numero di elementi dell'arrey della somma
	float media = 0;
	media = somma(vettore, n) / n;
	return media;
}

int ripetuto(int vettore[], int n) {

	//calcola il numero che si ripete più volte in un arrey
	int x;
	int num = 0;
	int dim;
	/*
	vet	9 5 0 3 0 2 5 0 7 1

	cou	3 1 1 1 0 2 0 1 0 1
	i	0 1 2 3 4 5 6 7 8 9
	*/

	//imposta in un vettore counter il numero di volte che ogni numero dell'arrey si ripete
	
	//crea il vettore con dimensione uguale al numero massimo del primo vettore
	dim = max(vettore, n) + 1;
	int counter[dim];

	//azzera tutti i valori dell'arrey counter
	for (int i = 0; i < dim; i++) {
		
		counter[i] = 0;
	}

	//aumenta di 1 la posizione del counter uguale al numero dell' arrey 	es: arrey 9, pos counter [9] = +1
	for (int i = 0; i < n; i++) {

		counter[vettore[i]] ++;
	}

	//verifica quale delle posizioni del counter ha un valore piu` alto e da il valore corrispondente dell' arrey a num
	for (int i = 0; i < n; i++) {
		
		if (counter[i] == max(counter, n)) {
			num = i;
		}
	}

	return num;
}

void testo() {
	
	//funzionamento uguale al leyup ma variabile

	int lungp;
	cout << "quanto e' lunga la parola?" << endl;
	cin >> lungp;
	char parola[lungp];
	int lung = lungp + 10;
	
	cout << "inserire la parola" << endl;
	for (int i = 0; i < lungp; i++) {
		cin >> parola[i];
	}


	for (int i = lung; i > 0; i--) {
		cout << "*";
	}
	cout << endl;

	cout << "*";

	for (int d = 0; d < ((lung - lungp - 2) / 2); d++) {
		cout << " ";
	}

	for (int i = 0; i < lungp; i++) {
		cout << parola[i];
	}

	for (int d = 0; d < ((lung - lungp - 2) / 2); d++) {
		cout << " ";
	}
	
	cout << "*" << endl;
	
	for (; lung > 0; lung--) {
		cout << "*";
	}
}

void migliaia (int n) {
	
	
	int lung = 0;
	int f = 0;
	
	/*
	123456
	100000		10 ^ 5 * 1
	20000		10 ^ 4 * 2
	3000		10 ^ 3 * 3
	400			10 ^ 2 * 4
	50			10 ^ 1 * 5
	6			10 ^ 0 * 6
	*/
	
	//conta quanto e` lungo il numero	
	int i = n;
	while (i > 0) {
		i = i / 10;
		f++;
		lung++;
	}
	
	
	
	int c = n;
	int lung2 = lung - 1;
	
	//tramite il sistema posizionale divide il numero in singole cifre
	for (int i = 0; i < lung; i++) {
		
		cout << c / (int) pow (10, lung2);
		c = c - (c / (int) pow (10, lung2) * (int) pow (10, lung2));
		lung2--;
		
		//se il numero della posizione e` divisibile per 3 e non e` l'ultimo inserisce un punto
		if ((i + 1) % 3 == 0 && i + 1 == lung2 + 1) {
			cout << ".";
		}	
	}
	cout << endl;
}

void ricorrenza (int vettore[], int n) {
	
	//funzionamento simile a ripetuto
	
	//calcola il numero che si ripete più volte in un arrey
	int x;
	int num = 0;
	int dim;
	/*
	vet	9 5 0 3 0 2 5 0 7 1

	cou	3 1 1 1 0 2 0 1 0 1
	i	0 1 2 3 4 5 6 7 8 9
	*/

	dim = max(vettore, n) + 1;
	int counter[dim];

	for (int i = 0; i < dim; i++) {

		counter[i] = 0;
	}

	for (int i = 0; i < n; i++) {

		counter[vettore[i]] ++;
	}

	//scrive per ogni numero da 0 al massimo quante volte si ripete in base ai valori dell'arrey counter
	for (int i = 0; i < n; i++) {
		cout << i << " = " << counter [i] << endl;
	}
}

float lunghezza_float (float num) {
	
	int decim = 10;
	
	/*
	13,46427527527754768675
				
	13,4642752752
	*/
	
	//tramite il precision scrive il float di lunghezza decim
	cout.precision(decim);
	cout << "numero sistemato:" << num <<endl;
	return 0;
}

void max_ricorrenza (int vettore[], int n) {
	
	//calcola il numero che si ripete più volte in un arrey e scrive solo quante volte si ripete
	int x;
	int dim;
	int massimo;
	/*
	vet	9 5 0 3 0 2 5 0 7 1

	cou	3 1 1 1 0 2 0 1 0 1
	i	0 1 2 3 4 5 6 7 8 9
	
	cout -> 3
	*/

	//imposta in un vettore counter il numero di volte che ogni numero dell'arrey si ripete
	
	//crea il vettore con dimensione uguale al numero massimo del primo vettore
	dim = max(vettore, n) + 1;
	int counter[dim];

	//azzera tutti i valori dell'arrey counter
	for (int i = 0; i < dim; i++) {
		
		counter[i] = 0;
	}

	//aumenta di 1 la posizione del counter uguale al numero dell' arrey 	es: arrey 9, pos counter [9] = +1
	for (int i = 0; i < n; i++) {

		counter[vettore[i]] ++;
	}

	//verifica quale numero si ripete piu` volte e da a massimo il numero di ripetizioni del numero
	for (int i = 0; i < n; i++) {
		
		if (counter[i] == max(counter, n)) {
			massimo = counter[i];
		}
	}
	cout << "il numero che si ripete piu` volte si ripete " << massimo << " volte" << endl;
}

void arrey_rand (int vettore[], int n, int max, int min) {
	
	//tramite la funzione rand dare alle celle di un arrey valore casuale
	
	srand (time (0));
	for (int i = 0; i < n; i++) {
		
		vettore [i] = min + rand() % (max - min);
		cout << vettore [i] << " ";
	}
}

void posizione_0_arrey (int vettore[], int n) {
	
	
	//trovare la posizione dello 0 in un arrey
	int num = 0;
	
	for (int i = 0; i < n; i++) {
		
		if (vettore[i] == 0) {
			
			cout << i << " ";
		}
	}
}

void posizione_arrey (int vettore[], int n) {
	
	//trovare la posizione di un numero in un arrey
	int num = 4;
	
	for (int i = 0; i < n; i++) {
		
		if (vettore[i] == num) {
			
			cout << i << " ";
		}
	}
}

void posizione_arrey2 (int vettore [], int n) {
	
	//trovare la posizione di un numero in un arrey se non c'e` restituire -1
	int num = 12;
	int counter = 0;
	
	for (int i = 0; i < n; i++) {
		
		if (vettore[i] == num) {
			
			cout << i << " ";
		}
		else {
			counter++;
		}
	}
	if (counter == n) {
		
		cout << "-1";
	}
}

void magg_min_arrey (int vettore[], int vettore2[], int n) {
	
	//confronta 2 array di uguale lunghezza e restituisce -1 se il primo è minore, 0 se uguali, 1 se maggiore
	//un arrey e` maggiore se dal primo elemento anche solo uno e` maggiore dell'altro
	
	for (int i = 0; i < n; i++) {
		
		if (vettore [i] > vettore2 [i]) {
			
			cout << "1";
			break;
		}
		if (vettore [i] < vettore2 [i]) {
			
			cout << "-1";
			break;
		}
		else if (vettore [n - 1] == vettore2 [n - 1]) {
			
			cout << "0";
		}	
	}	
}

void magg_min_arrey2 (int vettore[], int vettore2[], int n) {
	
	//confronta 2 array di uguale lunghezza fino ad uno 0 e restituisce -1 se il primo è minore, 0 se uguali, 1 se maggiore
	//un arrey e` maggiore se dal primo elemento anche solo uno e` maggiore dell'altro
	
	for (int i = 0; i < n; i++) {
		
		if (vettore [i] == 0) {
			break;
		}
		
		if (vettore [i] > vettore2 [i]) {
			
			cout << "1";
			break;
		}
		if (vettore [i] < vettore2 [i]) {
			
			cout << "-1";
			break;
		}
		else if (vettore [i] != vettore2 [i] && vettore [n - 1] == vettore2 [n - 1]) {
			
			cout << "0";
			break;
		}	
	}	
}

void char_ascii (char carattere) {
	
	//da un carattere resttiuisce il codice ascii
	//tramite una conversione
	cout << (int) carattere;
}

void ascii_char_arrey (int ascii) {
	
	//restituire dal codisce ascii il carattere
	//tramite una conversione
	cout << (char) ascii;
}

void ascii_char_arrey (int vettore[], int n) {

	//restituire dal codisce ascii il carattere dei valori in un arrey
	//tramite una conversione
	for (int i = 0; i < n; i++) {
		cout << (char) vettore [i];
	}	
}

void primo (int n) {
	
	//calcolare se un valore e` primo
	
	int ndiv = 0;
	
	for (int i = 1; i <= n; i++) {
		
		if (i % n == 0) {
			
			ndiv++;
		}
	}
	if (ndiv == 2) {
		
		cout << "primo";
	}
	else {
		
		cout << "non primo";
	}
}

void button (int x1, int y1, int lung, int alt, char scritta[], int colorBK) {
	
	
	setcolor (colorBK);
	setfillstyle (1, colorBK);
	//crea un rettangolo tridimensionale spostato di 50 dai bordi e spesso 10
	bar3d (x1, y1, x1 + lung, y1 + alt, 10, true );
	settextstyle (4, 0, 4);
	settextjustify (1, 1);
	setcolor (COLOR (1, 1, 1));
	setbkcolor (colorBK);
	outtextxy (x1 + lung / 2, y1 + alt / 2, scritta);
	
}

bool button_click (int x1, int y1, int lung, int alt, int x, int y) {
	return x >= x1 && x <= x1 + lung && y >= y1 && y <= y1 + alt;
}

void print_array (int vettore [], int dim) {
	
	for (int i = 0; i < dim; i++) {
		
		cout << vettore [i];
	}
	cout << endl;
}
