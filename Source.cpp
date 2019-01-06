#include <stdio.h>
#include  <stdlib.h>
#include <conio.h>
#include <koolplot.h>

typedef struct polinom * Position;

struct polinom {
	float faktor;
	int potencija;
	Position Next;

};



float* koordinate(int *);
void problemispis(float *,int *);
struct polinom * stvaranjepolinoma(float *, int *,struct polinom *,Position );
void citajpolinom(Position);
Position mnozi(Position, float, Position, int );
void zbroji(Position, Position);//zbraja u prvu
void fineprint(Position);
float donjifaktor(float*, int*, int );
void sveujedan(int *, struct polinom*);
float izracun(Position, float);

int main() {
	float *tocka;
	float x1;
	float y1;
	float y2;
	float koef;
	int size=0;
	int *psize=&size;
	polinom head;

	polinom * heads;

	head.Next = NULL;

	tocka=koordinate(psize);
	problemispis(tocka,psize);
	system("pause");
	//incijalizacija
	heads = (polinom *)malloc(sizeof(struct polinom)*((size / 2)+1));
	for (int i = 0;i < ((size / 2)+1);i++) {
		heads[i].Next = NULL;
		//heads[i].potencija = 0;
		//heads[i].faktor = 0;
		//printf_s("\nI=%d\n", i);
	}
	//kraj incijalizacije
	heads= stvaranjepolinoma(tocka, psize, heads,&head);
	/*for (int i = 0;i < ((size / 2) + 1);i++) {
		printf_s("\n%d. polinom:\n", i + 1);
		citajpolinom(&heads[i]);
	}*/
	printf("\n\n\n\nPolinomi bez koeficijenta\n\n");
	for (int i = 0;i < ((size / 2) + 1);i++) {
		printf("L(%d)=  ", i + 1);
		fineprint(heads[i].Next);
		printf("\n");
	}
	system("pause");
	//donji koef
	for (int i = 0;i < ((size / 2) + 1);i++) {
		koef = donjifaktor(tocka, psize, (i*2));
		printf("\nKOEF: %.2f\n", koef);
	}

	//sa donjihm koef
	printf("\n\n");
	for (int i = 0;i < ((size / 2) + 1);i++) {
		printf("L(%d)=  ", i + 1);
		printf("%.2f ", tocka[(2 * i) + 1] );
		printf("/ %.2f   *  (", donjifaktor(tocka, psize, (i * 2)));
		fineprint(heads[i].Next);
		printf(")  ");
		printf("\n\n");
	}
	system("pause");
	//pomnozeni
	for (int i = 0;i < ((size / 2) + 1);i++) {
		mnozi(&heads[i],((tocka[(2 * i) + 1])/(donjifaktor(tocka, psize, (i * 2)))), &head, 2);
	}
	printf("\n\n\n\nPolinomi sa koeficijentima\n\n");
	for (int i = 0;i < ((size / 2) + 1);i++) {
		printf("L(%d)=  ", i + 1);
		fineprint(heads[i].Next);
		printf("\n");
		//plot//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      plotdata x(-20, 20), y = x;
      //plot (x, y);
      clear(x);
      clear(y);
      for(float j = -10; j <=10; j+=0.5){
        y1=izracun(heads[i].Next, j);
         x<<j;
         y<<y1;
      }
         plot (x, y);
	//plot//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////


	}




	system("pause");
	//zbrajanje u jedan
	sveujedan(psize, heads);

	for (int i = 0;i < ((size / 2) + 1);i++) {
		printf("L(%d)=  ", i + 1);
		fineprint(heads[i].Next);
		printf("\n");
	}
	system("pause");
	system("cls");
	printf("L(%d)=  ", size/2);
	fineprint(heads[size / 2].Next);
	printf("\n");
	//gotov sa ispisom finalnog proizvoda
	//izracunaj tocku
	printf("\n\n\t Unesite tocku X: ");
	scanf("%f", &x1);
	//izracun
	y2= izracun(heads[size/2].Next, x1);
	printf("\n\n\t\tY: %.2f\n\n\n\n", y2);
	//plot//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      plotdata x(-20, 20), y = x;
      //plot (x, y);
      clear(x);
      clear(y);


      for(float i = -10; i <=10; i+=0.2){
        y1=izracun(heads[size/2].Next, i);
         x<<i;
         y<<y1;
      }


            addMark(x, y, x1, y2);

         plot (x, y,BLUE);




	//plot//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	system("pause");
	return 0;
}
float* koordinate(int *psize) {

	float* x=NULL;
	float* xplus = NULL;
	int count = 0;
	int j = 1;
	char input[6];
	int odabir;
	char c = '>';
	while (1) {
		printf("\n\tINTERPOLACIJA\n\n");
		printf("UNOS - Enter\nIZLAZ - ESC\n");
		printf(" %c ", c);
		while (1) {
			odabir = _getch();
			if (odabir == '\r') {
				printf("ENTER\n\n");
				break;
			}
			else if (odabir == 27) {
				printf("ESC\n\n");
				break;
			}

		}
		if (odabir == 27) {
			break;
		}




		printf("Ubacite koordinate:");
		count += 2;
		xplus = (float*)realloc(x, count * sizeof(int));
		x = xplus;


		printf(" X: ");
		scanf(" %s", input);
		xplus[count - 2] = strtof(input, NULL);
		printf("\n");
		printf("                   ");
		printf(" Y: ");
		scanf(" %s", input);
		xplus[count - 1] = strtof(input, NULL);
		printf("\n");


		printf("Koorditane su:   X  : %.2f  Y  : %.2f \n\n", x[count - 2], x[count - 1]);
		system("pause");
		system("cls");

	}
	system("cls");
	printf("\nKoordinate su:\n");
	for (int i = 0;i < count;i+=2) {
		printf("%d. X: %.2f  Y: %.2f\n",j, x[i], x[i + 1]);
		j++;
	}
	*psize = count;




	return x;

}
void problemispis(float *x, int * psize) {

	int count = *psize;
	int npon = count / 2;
	int k = 1;
	printf("\n\n");
	//priniting the goddamn thing



	for (int j = 0;j < count;j += 2) {
		printf("L(%d)=  ", k);
		printf("  %.2f  *  ", x[j + 1]);
		for (int i = 0;i < count;i += 2) {
			if (i != j) {
				if (x[i] < 0) {
					printf("(x+%.2f)", -x[i]);
				}
				else {
					printf("(x-%.2f)", x[i]);
				}

			}
			else {}
		}
		printf("\n");
		k++;
		printf("        -------------------------------------------------------        ");
		printf("\n");
		printf("                  ");
		for (int i = 0;i < count;i += 2) {
			if (i != j) {
				if (x[i] < 0) {
					printf("(%.2f+%.2f)", x[j], -x[i]);
				}
				else {
					printf("(%.2f-%.2f)", x[j], x[i]);
				}
			}else{}

		}
		printf("\n\n");


	}




}

struct polinom * stvaranjepolinoma(float * tocka, int * psize,struct polinom * heads, Position X) {
	int size = *psize;
	Position P;
	int j=0;
	for (int i = 0;i < size / 2;i++) {
		//printf_s("%d\n", heads[i].potencija);
		j = 0;
		if (heads[i].Next == NULL) {
			//prvi clan
			heads[i].Next = (Position)malloc(sizeof(struct polinom));
			P = heads[i].Next;
			P->Next = NULL;//safe
			P->faktor = 1;
			P->potencija = 1;
			//drugi clan
			P->Next = (Position)malloc(sizeof(struct polinom));
			P = P->Next;
			P->potencija = 0;
			P->Next = NULL;
			if (j == (i * 2)) {
				//printf_s("\nI=%d  J=%d", i, j);
				j++;

			}
			P->faktor = -tocka[j * 2];
			//nadovezivanje na druge funckije itd itd
			printf("\n%d. polinom:\n", i + 1);
			//faktor
		}

			j = 0;
			for (j = 0;j < size;j += 2) {
				//printf_s("\nI = %d  J = %d\n", i,j);
				if ((i==0 && j==0) || (i==0 && j==2)) {
					//prvi slucaj ne radi nista

				}
				else if ((i!=0 && j==0) || ((i*2)==j)) {
					//ostali slucaji
				}


				else					{



					//printf_s("Size %d\n", size);
					citajpolinom(&heads[i]);
					mnozi(&heads[i], -tocka[j], X, 1);//mnozi sa faktorom
					printf("\nPolinom X pomnozuen sa %f\n", -tocka[j]);
					citajpolinom(X);
					printf("\nPolinom heads originalan");
					citajpolinom(&heads[i]);
					mnozi(&heads[i], 1, X, 0);// mnozi sa x
					printf("\nPolinom heads pomnozen sa x");
					citajpolinom(&heads[i]);

					zbroji(&heads[i], X);//zbrajanje
					printf("\nPolinom nakon zbrajanja");
					citajpolinom(&heads[i]);
				}
			}



			}

			/*
			mnozi(&heads[i], 3, X, 1);// mnozi sa faktorom
			citajpolinom(X);
			citajpolinom(&heads[i]);
			mnozi(&heads[i], 1, X, 0);// mnozi sa x
			citajpolinom(&heads[i]);

			*/
			//faktor odredit i napravit za zbrajanje funkciju5

			//<---------------------------------------------------------------->
	return heads;
		}






void citajpolinom(Position P) {
	printf("\n");

	if (P == NULL) {
		printf("\nPolinom je prazan!\n");
		return;
	}
	P = P->Next;
	while (P!= NULL) {

		printf("%2.0fx^%d", P->faktor, P->potencija);
		printf(" + ");
		P = P->Next;

	}
	printf("\n");

}
Position mnozi(Position Q, float ftor, Position X, int flag) {//0-samopotneciranje i vracanje potenciranog
	if (flag == 0) {
		Q = Q->Next;
		while (Q != NULL) {

			Q->potencija += 1;
			Q = Q->Next;
		}




	}
	else if (flag == 1) {    //1 - mnozenje sa faktorom i kreiranje novog
		while (Q->Next != NULL) {
			X->Next = (Position)malloc(sizeof(struct polinom));
			X = X->Next;
			Q = Q->Next;
			X->potencija = Q->potencija;
			X->faktor = Q->faktor * ftor;
			X->Next = NULL;

		}


		return X;


	}
	else if (flag == 2) {
		Q = Q->Next;
		while (Q != NULL) {

			Q->faktor *= ftor;
			Q = Q->Next;
		}

	}




}
void zbroji(Position P, Position X) {
	P = P->Next;
	P = P->Next;
	X = X->Next;
	while (P != NULL) {
		P->faktor += X->faktor;
		if (P->Next == NULL) {
			break;
		}
		P = P->Next;
		X = X->Next;
	}
	P->Next = (Position)malloc(sizeof(struct polinom));
	X = X->Next;
	P = P->Next;
	P->faktor = X->faktor;
	P->potencija = X->potencija;
	P->Next = NULL;





}
void fineprint(Position P) {
	if (P == NULL) {
		printf("\tPolinom je prazan!");
		return;
	}
	//print prvog


		printf("%.2f", P->faktor);




		printf("x^");
		printf("%d", P->potencija);

	P = P->Next;
	//kraj prvog



	while (P != NULL) {

        if (P->faktor > 0) {
			printf(" + ");
			printf("%.2f", P->faktor);

		}
		else if(P->faktor < 0){
			printf(" - ");
			printf("%.2f", -(P->faktor));
		}
		else {
			printf(" + ");
			printf("%.2f", P->faktor);

		}

			printf("x");



			printf("^%d", P->potencija);

		P = P->Next;



	}




}
float donjifaktor(float * x, int * psize, int counter) {
	float koef=1;
	int size = *psize;
	for (int i = 0;i < (size / 2);i++) {
		//printf_s("\n %.2f - %.2f", x[counter], x[i * 2]);
		if (x[counter] == x[i * 2]) {

		}
		else {
			koef *= x[counter] - x[i * 2];
		}
	}
	return koef;
}
void sveujedan(int * psize, struct polinom* heads) {
	int size = *psize;
	float y1;
	int headsize = (size / 2);
	Position P;
	Position Q;
	Position X;
	P = heads[0].Next;//nije bitno koji
	if (P == NULL) {
		printf("Nema polinoma!");
		return;
	}
	heads[headsize].Next = (Position)malloc(sizeof(struct polinom));
	Q = heads[headsize].Next;
	X = Q;
	Q->potencija = P->potencija;
	Q->faktor = 0;
	Q->Next = NULL;
	//printf_s("\n\nVelicina je: %d", size);
	while (P != NULL) {
		if (P->Next == NULL) { break; }
		else {
			P = P->Next;

			Q->Next = (Position)malloc(sizeof(struct polinom));
			Q = Q->Next;
			Q->potencija = P->potencija;
			Q->faktor = 0;
			Q->Next = NULL;
		}
	}
		//stvoren dummy za nadodavanje
		//nadodavanje
		for (int i = 0; i < headsize;i++) {
			P = heads[i].Next;
			Q = heads[headsize].Next;
			while (Q != NULL) {
				Q->faktor += P->faktor;
				Q = Q->Next;
				P = P->Next;

			}

			printf("\nL(%d) = ", headsize+1);
			fineprint(heads[headsize].Next);
			printf("\n\n");
				//plotanje svih na jedan







		}

	}
float izracun(Position P, float x) {
	float suma=0;
	float y=0;
	while (P != NULL) {
		suma = 1;
		for (int i = 0;i < P->potencija ;i++) {
			suma *= x;

		}
		suma *= P->faktor;


		y += suma;
		P = P->Next;
	}



	return y;
}




