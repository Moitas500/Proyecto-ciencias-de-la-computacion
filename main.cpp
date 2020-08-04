#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "Director.h"
#include "Profesor.h"
#include "Archivos.h"
#include "estructura.h"
#include "CortesNotas.h"

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;
//Menu al entrar como director
void menu_director();
//Menu al entrar al area de cursos
void menu_temas();
//Menu para ver a los profesores
void menu_profesores();
//Menu al elegir la opcion estudiantes
void menu_estudiantes();
//Menu inicial
void menu_seleccion();
//Menu al entrar como profesor
void menu_profesor(Profesor profe);
//Menu para ver y modificar el esquema de notas
void menu_esquema(Profesor profe);
//Menu para registrar como director
Director menu_registrar();
//Registrar profesor
Profesor menu_registrarProfesor();
//Registrar un nuevo curso
duo<string> menu_registrarTema();
//Metodo para saber si el archivo existe en la ruta seleccionada
bool existeArchivo(string ruta);
//Menu para imprimir la lista de profesores
int menuLista(listaD<maestro> profes);
//Menu para imprimir la lista de maestros
int menuListaTemas(listaD<string> temas);
//Menu lista de cortes
Profesor menuListaDeCortes(Profesor profe, int cortes);
//Modelo general del menu para evitar repetir codigo
int menu(const char *titulo, const char *opciones[], int n); 
//Menu para loguearse
Persona menu_log();
//Metodo para añadir un profesor al archivo
void anadirProfesorArchivo(Profesor profe);
//Metodo que pide los datos de el profesor
int menuBuscarProfesor();
//Menu para buscar tema
int menuBuscarTema();
//Metodo que busca a un profesor segun la cedula
void buscarProfesor(int cedula, listaD<maestro> profes);

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
	Archivo file;
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
				if(file.crearArchivo("director/datos.txt")){
					Director dir = menu_registrar();
					file.escribirArchivo("director/datos.txt",dir.getNombre());
					file.escribirArchivo("director/datos.txt",dir.getContrasena());
					file.escribirArchivo("director/datos.txt",dir.getUsuario());
					file.escribirArchivo("director/datos.txt",dir.getCargo());
				}else{
					
					Director dir = file.leerArchivoDirector("director/datos.txt");
					
					Persona per = menu_log();
					
					if(per.getUsuario() == dir.getUsuario() && per.getContrasena() == dir.getContrasena()){
						menu_director();
					}else{
						system("cls");
					}
				}	
				break;
			}
				
			case 2:
				if(file.crearArchivo("Profesores/listaProfesores.txt")){
					system("cls");
					cout << "Aun no se ha creado ningún profesor" << endl;
					system("pause");
					file.eliminarArchivo("Profesores/listaProfesores.txt");
				}else{
					int cedula;
					listaD<maestro> maest = file.leerArchivoProfesor("Profesores/listaProfesores.txt");
					
					Persona per = menu_log();
					cout << "\n\t Cedula: ";
					cin >> cedula;
					
					if(maest.isIN(cedula)){
						duo<maestro> ma;
						ma.clave = cedula;
						ma = maest.obtener(ma.clave);
						maestro m = ma.dato;
						
						if(m.usuario == per.getUsuario() && m.contrasena == per.getContrasena() && m.cedula == cedula){
							Profesor profe(m.nombre,m.contrasena,m.usuario,m.cedula,m.apellidos,m.numClases,m.cortes);
							menu_profesor(profe);
						}else{
							system("cls");
						}
						
					}else{
						system("cls");
					}
				}
				break;
				
			case 3:
				repite = false;
				break;	
		}
		
	}while(repite);
}

Persona menu_log(){
	string usuario, contrasena;
	system("cls");
	cout << "\t\t\t LOGIN" << endl;
	cout << "\n\t Usuario: ";
	cin >> usuario;
	cout << "\n\t Contraseña: ";
	cin >> contrasena;
	
	Persona per(" ",contrasena,usuario);
	
	return per;
}

Profesor menu_registrarProfesor(){
	string nombre, usuario, contrasena, apellido;
	int cedula, numClases;
	int cortes = 3;
	
	system("cls");
	
	cout << "\t\t\t REGISTRAR PROFESOR" << endl;
	cout << "\n\t Nombre: ";
	cin >> nombre;
	cout << "\n\t Apellido: ";
	cin >> apellido;
	cout << "\n\t Usuario: ";
	cin >> usuario;
	cout << "\n\t Contraseña: ";
	cin >> contrasena;
	cout << "\n\t Cedula: ";
	cin >> cedula;
	cout << "\n\t Numero de clases: ";
	cin >> numClases;
	
	system("pause");
	
	Profesor profe(nombre,contrasena,usuario,cedula,apellido,numClases,cortes);
	
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

void menu_profesor(Profesor profe){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PROFESOR";
	//Opciones del menu
	const char *opciones[] = {"Consultar temas","Esquema de notas","Consultar estudiantes","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);		
		
		//Alternativas
		switch(opcion){
			case 1:
				menu_temas();
				break;
				
			case 2:
				menu_esquema(profe);
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

void menu_esquema(Profesor profe){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU ESQUEMA";
	//Opciones del menu
	const char *opciones[] = {"Cambiar numero de cortes","Modificar o agregar tipo de evaluacion","Salir"};
	//Numero de opciones
	int n = 3;
	Archivo file;
	
	do{
		opcion = menu(titulo, opciones, n);
		//Alternativas
		switch(opcion){
			case 1:{	
/*
				system("cls");
				int cortes;
			
				listaD<maestro> profes = file.leerArchivoProfesor("Profesores/listaProfesores.txt");
				
				cout << "Sen@r " << profe.getNombre() << " " << profe.getApellidos() << " " <<  "actualmente usted tiene: " << profe.getCortes() << " cortes." << endl;
				
				cout << "Digite la cantidad de cortes que desea realizar: ";
				cin >> cortes;
				
				file.modificarCortes(profe, cortes);
				
				if(file.crearArchivo("Profesores/" + profe.getNombre() + profe.getApellidos() + "Cortes.txt")){
					profe = menuListaDeCortes(profe, cortes);
				}else{
					file.eliminarArchivo("Profesores/" + profe.getNombre() + profe.getApellidos() + "Cortes.txt");
					file.crearArchivo("Profesores/" + profe.getNombre() + profe.getApellidos() + "Cortes.txt");
					profe = menuListaDeCortes(profe, cortes);
				}

				listaD<cortesNotas> _cort;
				
				_cort = profe.getCortesNotas();
				
				for(int i=0;i<profe.getCortes();i++){
					cortesNotas actividad;
					duo<cortesNotas> act;
					_cort.obtener(act);
					actividad = act.dato;
					
					stringstream ss;
					ss << actividad.notas->porcentaje << endl;
					string porcentaje = ss.str();
					
					file.escribirArchivo("Profesores/" + profe.getNombre() + profe.getApellidos() + "Cortes.txt", actividad.notas->tipo);
					file.escribirArchivo("Profesores/" + profe.getNombre() + profe.getApellidos() + "Cortes.txt", porcentaje);
				}
*/
				break;
			}
			
			case 2:{
				break;
			}
			
			case 3:{
				repite = false;
				break;
			}
		}
	}while(repite);
}

Profesor menuListaDeCortes(Profesor profe, int cortes){
	system("cls");
	
	int i=0;
	int a=0;
	int actividades;
	string nombre;
	int porcentaje;
	listaD<cortesNotas> _cort;
	cortesNotas actividad;
/*
	while(i < cortes){
		
		cout << "¿Cuantas actividades quiere realizar para el " << i+1 << " corte?" << endl;
		cin >> actividades;
		
		while(a < actividades){
			cout << "Digite la " << a+1 << " actividad" << endl;
			cin >> nombre;
			cout << endl << "Digite el valor de dicha actividad" << endl;
			cin >> porcentaje;

			trio *estructura;
			
			listaD<int> parejas;	//La primera lista de parejas que va a tener la actividad
			listaD<listaD<int> > notas;//La lista de listas de parejas de la primera actividad
			int c=1;
			parejas.insertar(1,100);//Le insertamos una pareja a la lista
			notas.insertar(c,parejas);//Le insertamos a la lista de listas la primera lista de parejas 
			
			estructura->porcentaje = porcentaje;
			estructura->tipo = nombre;
			estructura->puntos = notas;
			
			actividad.notas = estructura;
			
			_cort.insertar(a,actividad);
			a++;
		}
		
		i++;
	}
*/
	profe.setCortesNotas(_cort);
	
	return profe;
}

void menu_director(){
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU DIRECTOR";
	//Opciones del menu
	const char *opciones[] = {"Consultar temas","Consultar profesores","Consultar estudiantes","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:
				menu_temas();
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

duo<string> menu_registrarTema(){
	system("cls");
	duo<string> tema1;
	string nombre;
	int clave;
	
	cout << "\t\tTEMAS" << endl;
	
	cout << "Digite el nombre de el tema que desea añadir: ";
 	getline(cin,nombre);
	cout << "Digite el codigo de el tema que desea añadir: ";
	cin>>clave;
	tema1.clave=clave;
	tema1.dato=nombre;
	return tema1;
}

int menuBuscarTema(){
	system("cls");
	int codigo;
	
	cout << "\t\t BUSCAR TEMA" << endl;
	
	cout << "Digite el codigo de el tema que desea buscar: ";
	cin >> codigo;
	
	return codigo;
}

void menu_temas(){
	Archivo file;
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU TEMAS";
	//Opciones del menu
	const char *opciones[] = {"Buscar tema","Agregar tema","Borrar tema","Lista de temas","Salir"};
	//Numero de opciones
	int n = 5;
	
	do{
		opcion = menu(titulo, opciones, n);
		//Alternativas
		switch(opcion){
			case 1:{
				duo<string> tema;
				listaD<string> temas= file.leerTemas();
				tema.clave = menuBuscarTema();
				tema = temas.obtener(tema.clave);
					
				if(tema.clave == -1){
					system("cls");
					cout << "No se encontro el tema especificado";
					system("pause");
				}else{
					listaD<string> temas2;
					temas2.insertar(tema.clave,tema.dato);
						
					menuListaTemas(temas2);
				}		
				
				break;
			}
			
			case 2:{
				duo<string> tema = menu_registrarTema();
				listaD<string> temas;
				if(file.crearArchivo("Temas/Topics.txt")){		
					temas.insertar(tema.clave,tema.dato);
					file.escribirTemas(temas);
				}else{
					temas =file.leerTemas();
					temas.insertar(tema.clave,tema.dato);
					file.eliminarArchivo("Temas/Topics.txt");
					file.crearArchivo("Temas/Topics.txt");
					file.escribirTemas(temas);
				}
						
				break;
			}
			
			case 3:{
				listaD<string> temas;
				duo<string> tema = menu_registrarTema();
				
				temas= file.leerTemas();
				temas.borrar(tema.clave);
				file.escribirTemas(temas);

				break;
			}
				
			case 4:{
				listaD<string> temas;
				temas=file.leerTemas();
				menuListaTemas(temas);
				break;	
			}
				
			case 5:
				repite = false;
				break; 	 		
		}
		
	}while(repite);
}

void buscarProfesor(int cedula, listaD<maestro> profes){		//Preguntarle a camilo para que sirve esta función
	
	if(profes.isIN(cedula)){
		
		listaD<maestro> maestros;
		maestros.insertar(profes.obtener(cedula).clave,profes.obtener(cedula).dato);
		maestros.insertar(profes.obtener(cedula).clave,profes.obtener(cedula).dato);
		menuLista(maestros);
	}
	
}

int menuBuscarProfesor(){
	system("cls");
	int cedula;
	
	cout << "\t\t\t BUSCAR PROFESOR" << endl;
	cout << "\t Digite la cedula de el profesor que desea buscar: ";
	cin >> cedula;
	
	return cedula;
}

void menu_profesores(){
	Archivo file;
	bool repite = true;
	int opcion;
	//Titulo del menu
	const char *titulo = "MENU PROFESORES";
	//Opciones del menu
	const char *opciones[] = {"Buscar profesor","Lista de profesores","Añadir profesor","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			
			case 1:{
				int cedula = menuBuscarProfesor();
				listaD<maestro> profes = file.leerArchivoProfesor("Profesores/listaProfesores.txt");
				
				buscarProfesor(cedula, profes);
				break;
			}		
				
			case 2:{
				listaD<maestro> profes = file.leerArchivoProfesor("Profesores/listaProfesores.txt");
				int opcion;
				
				do{
					opcion = menuLista(profes);
					
					if(opcion == profes.getTam()+1){
						repite = false;
					}
					
				}while(repite);
				
				break;
			}
			
			case 3:
				if(file.crearArchivo("Profesores/listaProfesores.txt")){
					Profesor profe = menu_registrarProfesor();
					
					anadirProfesorArchivo(profe);
					
				}else{
					Profesor profe = menu_registrarProfesor();
					
					anadirProfesorArchivo(profe);
				}		
				break;
			
			case 4:
				repite = false;
				break;	 	 		
		}
		
	}while(repite);
}

void anadirProfesorArchivo(Profesor profe){
	Archivo file;
	stringstream ss;
	stringstream sa;
	stringstream sd;
	ss << profe.getCedula();		
	string cedula = ss.str();
	sa << profe.getNumClases();
	string numClases = sa.str();
	sd << profe.getCortes() << endl;
	string cortes = sd.str();
					
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getNombre());
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getApellidos());
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getContrasena());			
	file.escribirArchivo("Profesores/listaProfesores.txt",cedula);
	file.escribirArchivo("Profesores/listaProfesores.txt",numClases);
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getUsuario());
	file.escribirArchivo("Profesores/listaProfesores.txt",cortes);
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

int menuListaTemas(listaD<string> temas){
	duo<string> tema;
	int opcionSeleccionada = 1;
	int tecla;
	bool repite = true;	
				
	do{
		system("cls");
				
		gotoxy(15,2); cout << "LISTA DE TEMAS" << endl;
		gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
					
		int i;

		for((i=0);(i<temas.getTam());(i++))
	    {
	    	temas.obtener(tema); 
	    	gotoxy(10, 4 + i); cout << i + 1 << ") " << "Codigo: " << tema.clave << " Tema: " << tema.dato;
		}
		temas.reiniciarPuntero();			
		gotoxy(10,4+i);
		cout << i + 1 << ") " << "Salir";
					
		do
		{
			tecla = getch();
		}while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);	
				
		switch(tecla)
		{
			case TECLA_ARRIBA:
				opcionSeleccionada --;
				
				if (opcionSeleccionada < 1)
				{
					opcionSeleccionada = temas.getTam() + 1;
				}
				break;
			
			case TECLA_ABAJO:
				opcionSeleccionada ++;
				
				if (opcionSeleccionada > temas.getTam() + 1)
				{
					opcionSeleccionada = 1;
				}
				
				break;
				
			case ENTER:
				repite = false;
				break;
			}	
					
	}while(repite);
	
	return opcionSeleccionada;
}

int menuLista(listaD<maestro> profes){		//Preguntarle a camilo para que sirve esta tambien
	duo<maestro> mast;
	int opcionSeleccionada = 2;
	int tecla;
	bool repite = true;	
				
	do{
		system("cls");
				
		gotoxy(15,2); cout << "LISTA DE PROFESORES" << endl;
		gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
					
		int i = 0;

		for((i=1);(i<profes.getTam());(i++))
	    {
	    	profes.obtener(mast); 
	    	gotoxy(10, 4 + i); cout << i << ") " << "Cedula: " << mast.dato.cedula << " Nombre: " << mast.dato.apellidos << " " << mast.dato.nombre << " Numero de clases: " << mast.dato.numClases;
		}
		profes.reiniciarPuntero();			
		gotoxy(10,4+i);
		cout << i << ") " << "Salir";
					
		do
		{
			tecla = getch();
		}while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);	
				
		switch(tecla)
		{
			case TECLA_ARRIBA:
				opcionSeleccionada --;
				
				if (opcionSeleccionada < 2)
				{
					opcionSeleccionada = profes.getTam() + 1;
				}
				break;
			
			case TECLA_ABAJO:
				opcionSeleccionada ++;
				
				if (opcionSeleccionada > profes.getTam() + 1)
				{
					opcionSeleccionada = 2;
				}
				
				break;
				
			case ENTER:
				repite = false;
				break;
			}	
					
	}while(repite);
	
	return opcionSeleccionada;
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
