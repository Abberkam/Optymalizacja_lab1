#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>

using namespace std;

int ile=100000;							//ile tras podczasz szukania najkrótszej
const char* f_in="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\exp0.txt";
const char* f_out0="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\wynik0_0.txt";
const char* f_out1="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\wynik0_1.txt";

//struktura przechowuj¹ca trasê i jej d³ugoœæ
struct trasa{
	int t[10];
	int suma;
};

void wczytajDane(FILE *f, int n, int **d, int *t)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			fscanf_s(f,"%i",&d[i][j]);
			//cout<<d[i][j]<<" ";
		}
		//cout<<endl;
	}

	for(i=0; i<n+1; i++)
	{
		fscanf_s(f,"%i",&t[i]);
		//cout<<t[i]<<" ";
	}
	//cout<<endl;

	fclose(f);
}

int dlugoscTrasy(int n, int **d, int *t)
{
	int suma=0;
	for(int i=1; i<n+1; i++)
	{
		suma+=d[t[i-1]][t[i]];
		//cout<<t[i-1]<<" do "<<t[i]<<" "<<d[t[i-1]][t[i]]<<endl;
	}
	//cout<<"Dlugosc trasy wynosi: "<<suma<<endl;
	return suma;
}

void szukajDrogi(struct trasa *a, int ile, int n, int **d, int *t)
{
	srand((unsigned int)time(NULL));
	int i, j, r1, r2=0, tmp;

	for(j=0; j<n+1; j++)
	{
		a[0].t[j]=t[j];
	}
	a[0].suma=dlugoscTrasy(n,d,a[0].t);

	for(i=1; i<ile; i++)
	{
		for(j=0; j<n+1; j++)
		{
			a[i].t[j]=a[i-1].t[j];
		}

		r1=rand() %8+1;
		r2=rand() %8+1;

		tmp=a[i].t[r1];
		a[i].t[r1]=a[i].t[r2];
		a[i].t[r2]=tmp;

		a[i].suma=dlugoscTrasy(n,d,a[i].t);
	}

	struct trasa temp;
	temp.suma=a[0].suma;
	int min;
	for(i=1;i<ile;i++)
	{
		if(a[i].suma<temp.suma)
		{
			min=i;
			temp.suma=a[i].suma;
		}
	}
	for(i=0;i<n+1;i++)
		temp.t[i]=a[min].t[i];

	FILE *w;
	fopen_s(&w,f_out1, "w");
	fprintf(w,"Najkrótsza trasa ma:\nd³ugoœæ: %i i kolejnoœæ: ",temp.suma);
	cout<<"Najkrótsza trasa ma d³ugoœæ: "<<temp.suma<<","<<endl<<"kolejnoœæ odwiedzania miast to: ";
	for(i=0;i<n+1;i++)
	{
		fprintf(w,"%i ",temp.t[i]);
		cout<<temp.t[i]<<" ";
	}
	cout<<endl;
	fprintf(w,"\n\nDANE:\n");
	for(i=0;i<ile;i++)
	{
		fprintf(w,"trasa: ");
		for(j=0;j<n+1;j++)
		{
			fprintf(w,"%i ",a[i].t[j]);
		}
		fprintf(w,"dlugosc: %i\n",a[i].suma);
	}
	fclose(w);
}

int main()
{
	setlocale(LC_ALL,"polish");
	int n;								//liczba miast
	FILE *f;
	fopen_s(&f,f_in, "rt");				//otwarcie pliku z danymi
	fscanf_s(f,"%i",&n);				//pobranie liczby miast

	int ** d = new int * [n];			//tablica odleg³oœæi pomiêdzy miastami
	for (int i = 0; i<n; i++)
		d[i] = new int [n];
	int * t = new int[n];				//wektor kolejnoœci odwiedzania miast

	wczytajDane(f,n,d,t);				//wcztuje dane i zamyka plik f

	FILE *w;							//liczy d³ugoœæ trasy t i zapisuje wynik do pliku wynik0_0.txt
	fopen_s(&w,f_out0, "w");
	fprintf(w,"%i",dlugoscTrasy(n,d,t));
	fclose(w);

	struct trasa *a= new struct trasa [ile];		//tablica struktur
	szukajDrogi(a,ile,n,d,t);			//liczy d³ugoœci tras dla zamiany 2 dowolnych miast na trasie i zapisuje wynik do pliku wynik0_1.txt

	system("PAUSE");
	return 0;
}