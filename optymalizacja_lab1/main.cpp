#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>

using namespace std;

int ile=10000;							//ile tras podczasz szukania najkrótszej
const char* f_in="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\exp0.txt";
const char* f_out0="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\wynik0_0.txt";
const char* f_out1="C:\\Users\\abberkam\\Source\\Repos\\Optymalizacja\\wynik0_1.txt";

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

	FILE *w;
	fopen_s(&w,f_out0, "w");
	fprintf(w,"%i",suma);
	fclose(w);

	return suma;
}

void szukajDrogi(struct trasa *a, int ile, int n, int **d, int *t)
{
	srand((unsigned int)time(NULL));
	int i, j, r1, r2=0, tmp;

	for(i=0; i<ile; i++)
	{
		a[i].suma=0;
		for(j=0; j<n+1; j++)
		{
			a[i].t[j]=t[j];
		}

		r1=rand() %8+1;
		r2=rand() %8+1;
		while(r1<1 || r1>8 || r2<1 || r2>8)
			r2=rand() %9+1;

		tmp=a[i].t[r1];
		a[i].t[r1]=a[i].t[r2];
		a[i].t[r2]=tmp;

		a[i].suma=dlugoscTrasy(n,d,a[i].t);
	}

	struct trasa temp;
	temp.suma=a[0].suma;
	int min=1;
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
	fprintf(w,"Najkrótsza trasa ma:\nd³ugoœæ: %i i drogê: ",temp.suma);
	for(i=0;i<n+1;i++)
		fprintf(w,"%i ",temp.t[i]);
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
	int n;
	FILE *f;
	fopen_s(&f,f_in, "rt");
	fscanf_s(f,"%i",&n);

	int ** d = new int * [n];
	for (int i = 0; i<n; i++)
		d[i] = new int [n];
	int * t = new int[n];

	wczytajDane(f,n,d,t);				//zamyka plik f

	dlugoscTrasy(n,d,t);				//zapisuje wynik do pliku wynik0_0.txt

	struct trasa *a= new struct trasa [ile];
	szukajDrogi(a,ile,n,d,t);			//zapisuje wynik do pliku wynik0_1.txt

	system("PAUSE");
	return 0;
}