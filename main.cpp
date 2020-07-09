#include<cstdlib>
#include<conio.h>
#include<iostream>
#include<windows.h>

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

void menu_director();
void menu_cursos();
void menu_profesores();
void menu_estudiantes();
void menu_seleccion();
void menu_profesor();
int menu(const char *titulo, const char *opciones[], int n); 

int main(int argc, char** argv) {
	menu_seleccion();
	
	return 0;
}

void gotoxy(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
}

void menu_seleccion(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PRINCIPAL";
	//Opciones del menu
	const char *opciones[] = {"Ingresar director de area","Ingresar como profesor","Salir"};
	//Numero de opciones
	int n = 3;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				menu_director();
				break;
				
			case 2:
				menu_profesor();
				break;
				
			case 3:
				repite = false;
				break;	
		}
		
	}while(repite);
}

void menu_profesor(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PRINCIPAL";
	//Opciones del menu
	const char *opciones[] = {"Consultar cursos","Esquema de notas","Consultar estudiantes","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				menu_cursos();
				break;
				
			case 2:
				menu_profesores();
				break;
				
			case 3:
				menu_estudiantes();
				break;
				
			case 4:
				repite = false;
				break; 		
		}
		
	}while(repite);
}

void menu_director(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PRINCIPAL";
	//Opciones del menu
	const char *opciones[] = {"Consultar cursos","Consultar profesores","Consultar estudiantes","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				menu_cursos();
				break;
				
			case 2:
				menu_profesores();
				break;
				
			case 3:
				menu_estudiantes();
				break;
				
			case 4:
				repite = false;
				break; 		
		}
		
	}while(repite);
}

void menu_cursos(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU CURSOS";
	//Opciones del menu
	const char *opciones[] = {"Buscar curso","Salir"};
	//Numero de opciones
	int n = 2;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				cout << "hola";
				break;
				
			case 2:
				repite = false;
				break; 	 		
		}
		
	}while(repite);
}


void menu_profesores(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PROFESORES";
	//Opciones del menu
	const char *opciones[] = {"Buscar profesor","Lista de profesores segun cantidad de clases","Salir"};
	//Numero de opciones
	int n = 3;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				cout << "hola";
				break;
				
			case 2:
				repite = false;
				break; 	 		
		}
		
	}while(repite);
}

void menu_estudiantes(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU ESTUDIANTES";
	//Opciones del menu
	const char *opciones[] = {"Buscar estudiante","Salir"};
	//Numero de opciones
	int n = 2;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				cout << "hola";
				break;
				
			case 2:
				repite = false;
				break; 	 		
		}
		
	}while(repite);
}

int menu(const char *titulo, const char *opciones[], int n)
{
	int opcionSeleccionada = 1;
	int tecla;
	bool repite = true;
	
	do
	{
		system("cls");
		
	    gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
	    
	    //Imprime el título
	    gotoxy(15,2); cout << titulo;
	    
	    //Imprime las opciones
	    int i;
	    
	    for((i=0);(i<n);(i++))
	    {
	    	gotoxy(10, 4 + i); cout << i+1 << ") " << opciones[i];
		}
		
		do
		{
			tecla = getch();
		}
		while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);
		
		switch(tecla)
		{
			case TECLA_ARRIBA:
				opcionSeleccionada --;
				
				if (opcionSeleccionada < 1)
				{
					opcionSeleccionada = n;
				}
				
				break;
			
			case TECLA_ABAJO:
				opcionSeleccionada ++;
				
				if (opcionSeleccionada > n)
				{
					opcionSeleccionada = 1;
				}
				
				break;
				
			case ENTER:
				repite = false;
				break;
		}
    }
    while(repite);
	
	return opcionSeleccionada;
}
