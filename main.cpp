#include<cstdlib>
#include<conio.h>
#include<iostream>
#include<windows.h>
#include <fstream>

#include "Director.h"
#include "Profesor.h"

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;
//Menu al entrar como director
void menu_director();
//Menu al entrar al area de cursos
void menu_cursos();
//Menu para ver a los profesores
void menu_profesores();
//Menu al elegir la opcion estudiantes
void menu_estudiantes();
//Menu inicial
void menu_seleccion();
//Menu al entrar como profesor
void menu_profesor();
//Menu para registrar como director
Director menu_registrar();
//Registrar profesor
Profesor menu_registrarProfesor();
//Modelo general del menu para evitar repetir codigo
int menu(const char *titulo, const char *opciones[], int n); 
//Menu para loguearse
bool menu_log(string _usuario, string _contrasena);

//Funcion principal
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
			case 1:{
				ifstream archivo;
				archivo.open("director/datos.txt");
				if(archivo.fail()){
					archivo.close();
					ofstream crear;
					crear.open("director/datos.txt");
					Director dir = menu_registrar();
					crear << dir.getNombre() << endl;
					crear << dir.getContrasena() << endl;
					crear << dir.getUsuario() << endl;
					crear << dir.getCargo();
					crear.close();
				}else{
					string nombre, usuario, contrasena;
					
					archivo >> nombre;
					archivo >> contrasena;
					archivo >> usuario;
					
					Director dir(nombre, contrasena, usuario, "Director");
					
					if(menu_log(dir.getUsuario(),dir.getContrasena())){
						menu_director();
					}else{
						system("cls");
					}
				}
				
				archivo.close();
				break;
			}
				
			case 2:
				menu_profesor();
				break;
				
			case 3:
				repite = false;
				break;	
		}
		
	}while(repite);
}

bool menu_log(string _usuario, string _contrasena){
	string usuario, contrasena;
	system("cls");
	cout << "\t\t\t LOGIN" << endl;
	cout << "\n\t Usuario: ";
	getline(cin,usuario);
	cout << "\n\t Contraseña: ";
	getline(cin,contrasena);
	
	if(usuario == _usuario && contrasena == _contrasena){
		return true;
	}
	
	return false;
}

Profesor menu_registrarProfesor(){
	string nombre, usuario, contrasena, apellido;
	int cedula, numClases;
	
	system("cls");
	
	cout << "\t\t\t REGISTRAR PROFESOR" << endl;
	cout << "\n\t Nombre: ";
	getline(cin,nombre);
	cout << "\n\t Apellido: ";
	getline(cin,apellido);
	cout << "\n\t Usuario: ";
	getline(cin,usuario);
	cout << "\n\t Contraseña: ";
	getline(cin,contrasena);
	cout << "n\t Cedula: ";
	cin >> cedula;
	cout << "\n\t Numero de clases: ";
	cin >> numClases;
	
	Profesor profe(nombre,contrasena,usuario,cedula,apellido,numClases);
	
	return profe;
}

Director menu_registrar(){
	string nombre, usuario, contrasena;
	
	system("cls");
	
	cout << "\t\t\t REGISTRO" << endl;
	cout << "\n\t Nombre: ";
	getline(cin, nombre);
	cout << "\n\t Usuario: ";
	getline(cin, usuario);
	cout << "\n\t Contraseña: ";
	getline(cin, contrasena);
	
	Director dir(nombre,contrasena,usuario,"Director");
	
	return dir;
}

void menu_profesor(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PROFESOR";
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
	const char *titulo = "MENU DIRECTOR";
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
	const char *opciones[] = {"Buscar profesor","Lista de profesores segun cantidad de clases","Añadir profesor","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				cout << "hola";
				break;
				
			case 2:
				cout << "hola";
				break;
			
			case 3:
				menu_registrarProfesor();
				break;
			
			case 4:
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
