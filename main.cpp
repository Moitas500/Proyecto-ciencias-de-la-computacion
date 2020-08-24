#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <direct.h>

#include "Director.h"
#include "Profesor.h"
#include "Archivos.h"
#include "estructura.h"
#include "CortesNotas.h"
#include "Lector.h"
#include "promedio.h"

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
//Metodo para imprimir los cortes de notas
void imprimirCortesNotas(listaD<cortesN> cortesNotas, Profesor profe);

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
							profe.setNombresClases(m.nombresClases);
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
	
	listaD<string> nombresClases;
	
	for(int i=0; i<numClases; i++){
		string nombre;
		cout << "\n\t Nombre de la clase numero: " << i + 1 << " ";
		cin >> nombre;
		
		string ruta = "./clases/" + nombre;
		string ruta2 = "./parciales/" + nombre;
		
		mkdir(ruta2.c_str());
		mkdir(ruta.c_str());
		
		nombresClases.insertar(i,nombre);
	}
	
	Profesor profe(nombre,contrasena,usuario,cedula,apellido,numClases,cortes);
	profe.setNombresClases(nombresClases);
	
	system("pause");
	
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
	const char *opciones[] = {"Cambiar numero de cortes","Ver cortes de notas","Modificar o agregar tipo de evaluacion","Salir"};
	//Numero de opciones
	int n = 4;
	Archivo file;
	
	do{
		opcion = menu(titulo, opciones, n);
		//Alternativas
		switch(opcion){
			case 1:{	
				system("cls");
				listaD<string> clases;

				listaD<string> nombresClases = profe.getNombresClases();		

			 	bool claseEncontrada=false;
				string nomclase;
				
				cout << "-------"+nombresClases.obtener(0).dato<<endl;
				cout << "Digite el nombre de la clase de la que desea cambiar el esquema de cortes: ";
				cin >> nomclase;
				for(int i=0; i<nombresClases.getTam();i++){
					cout << "-------"+nombresClases.obtener(i).dato<<endl;
					if(nombresClases.obtener(i).dato==nomclase){
						i=profe.getNumClases();
						claseEncontrada=true;
					}
				}
				if(claseEncontrada){
					string ruta = "Profesores/Cortes-"+ nomclase +".txt";
					if(file.crearArchivo(ruta)){
						profe = menuListaDeCortes(profe, profe.getCortes());
					}else{
						file.eliminarArchivo(ruta);
						file.crearArchivo(ruta);
						profe = menuListaDeCortes(profe, profe.getCortes());
					}
				listaD<cortesN> _cort;
				_cort = profe.getCortesNotas();
				file.escribirNotasCortes(_cort, ruta,profe.getCedula());
				}else{
					cout << "clase no encontrada";
					repite=false;
				}
	
				break;
			}
			
			case 2:{
				listaD<cortesN> cort;
				listaD<string> nombresClases = profe.getNombresClases();
				string nomclase;
				bool claseEncontrada=false;
				
				system("cls");
				cout << "Digite el curso al cual quiere ver su corte de notas: ";
				cin >> nomclase;
				
				for(int i=0; i<nombresClases.getTam();i++){
					if(nombresClases.obtener(i).dato==nomclase){
						i=profe.getNumClases();
						claseEncontrada=true;
					}
				}
				
				if(claseEncontrada){
					cort = file.leerNotasCorte(nomclase);
				
					imprimirCortesNotas(cort, profe);
				}else{
					system("cls");
					
					cout << "La clase no pudo ser encontrada" << endl;
					
					system("pause");
				}
				
				break;
			}
			
			case 3:{
				break;
			}
			
			case 4:{
				repite = false;
				break;
			}
		}
	}while(repite);
}

void imprimirCortesNotas(listaD<cortesN> cortesNotas, Profesor profe){
	system("cls");
	
	int tecla;
	bool repite = true;	
	
	gotoxy(30,1); cout << "Cortes de notas del profesor/a: " << profe.getNombre() << " " << profe.getApellidos();
	
	int y = 0;
	int x = 0;

	trio elemento;	//Objeto de tipo trio que resivira las actividades en el arreglo cortesNotas
	duo<cortesN> corte;
	duo<int> pr;	//Elemento de tipo duo que obtendra cada una de las parejas
	duo<listaD<int> > lista;	//Elemento de tipo duo que obtendra la lista de parejas (de la lista de listas de parejas);
	for(int i=0;i<cortesNotas.getTam();i++){	//El for recorre la lista cortesNotas
		gotoxy(5,3 + y); cout << "-------------------------------------------------------------------------------------------";
		gotoxy(7,4 + y); cout<<"Corte "<<i+1<<endl;
		corte=cortesNotas.obtener(i);
		for(int i=0;i<(corte.dato.getTam())-1;i++){	//For que recorre el arreglo obteniendo las actividades
			elemento=corte.dato.getElemento(i);	//Se obtiene la actividad de la posición i
			if(elemento.tipo!="NN"){		//Se hace la verificación que le comente
				gotoxy(16,4 + y); cout<<"Actividad "<<elemento.tipo;
				gotoxy(40,4 + y); cout<<"Porcentaje "<<elemento.porcentaje;
				while(elemento.puntos.obtener(lista)){	//While que recorera la lista de listas de parejas para obtener cada lista de parejas
					while(lista.dato.obtener(pr)){		//While que recorre la lista de parejas para obtener cada parejas
						gotoxy(63, 4 + y); cout<<"Tema "<<pr.clave;	//Impresión del tema
						gotoxy(80, 4 + y); cout<<"Valor "<<pr.dato;	//Impresión del porcentaje
						y += 2;
					}
					gotoxy(60, 3 + y); cout << "------------------------------------";
				}
			}								
		}
	}
	
	for(int b = 0; b <= 6; b++){
		for(int i = 0; i < y; i++){
			gotoxy(5 + x,4 + i); cout << "|";
		}
		if(b == 1){
			x += 10;
		}
		if(b == 2){
			x += 23;
		}
		if(b == 3){
			x += 20;
		}
		if(b == 4){
			x += 15;
		}
		if(b == 5){
			x += 22;
		}
	}
	
	gotoxy(5,3 + y); cout << "-------------------------------------------------------------------------------------------";
	
	gotoxy(30,5 + y); cout << "Presione ENTER para salir";
	
	do{
		do
			{
				tecla = getch();
			}while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);	
					
		switch(tecla)
		{			
			case ENTER:
				repite = false;
				break;
		}
	}while(repite);
	
}

Profesor menuListaDeCortes(Profesor profe, int cortes){
	system("cls");
	int numActividades;
	int tema;
	int valor;
	int numA;	//Numero de actividades de cada actividad
	int numPuntos;// Numero de puntos de cada actividad
	string tipo;
	int porcentajeA;
	int porcentaje;
		//La primera lista de parejas que va a tener la actividad
	listaD<cortesN> cortesNotas;
	for(int i=0;i<cortes;i++){
		//////////////////////////INSERCIÓN//////////////////////////////////////////////////
		cout<<"Ingrese el numero de Actividades el el corte "<<i+1<<endl;
		cin>>numActividades;
		cortesN corte(numActividades);
		for(int x=0;x<numActividades;x++){
			cout<<"Ingrese nombre de la actividad "<<(x+1)<<endl;
			cin>>tipo;
			cout<<"Ingrese el porcentaje de la activdad "<<(x+1)<<endl;
			cin>>porcentajeA;
			cout<<"Ingrese el numero de estas actividades en el corte "<<(x+1)<<endl;
			cin>>numA;
			listaD<listaD<int> > notas;//La lista de listas de parejas de la primera actividad
			for(int y=0;y<numA;y++){
				cout<<"Ingrese el numero de puntos  para la actividad "<<y+1<<endl;
				cin>>numPuntos;
				listaD<int> parejas;
				for(int z=0;z<numPuntos;z++){
					cout<<"Ingrese el codigo del tema el punto "<<z+1<<endl;
					cin>>tema;
					cout<<"Ingrese el porcentaje del punto "<<z+1<<endl;
					cin>>porcentaje;
					parejas.insertar(tema,porcentaje);
				}
				notas.insertar(x,parejas);
			}
			corte.insertarActividad(tipo,porcentajeA,notas);
		}
		cortesNotas.insertar(i,corte);
	}
	profe.setCortesNotas(cortesNotas);
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
				int numero;
				
				system("cls");
				cout << "Digite el numero de clases para encontrar a los profesores: ";
				cin >> numero;
				
				listaD<maestro> nuevos;
				
				for(int i=0; i < profes.getTam(); i++){
					duo<maestro> maest;
					profes.obtener(maest);
					maestro pr = maest.dato;
					
					if(pr.numClases == numero){
						cout << pr.numClases;
						system("pause");
						nuevos.insertar(pr.cedula,pr);
					}
				}
				
				profes.reiniciarPuntero();
				
				do{
					opcion = menuLista(nuevos);
					
					if(opcion == nuevos.getTam() + 2){
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
	sd << profe.getCortes();
	string cortes = sd.str();
					
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getNombre());
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getApellidos());
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getContrasena());			
	file.escribirArchivo("Profesores/listaProfesores.txt",cedula);
	file.escribirArchivo("Profesores/listaProfesores.txt",numClases);
	file.escribirArchivo("Profesores/listaProfesores.txt",profe.getUsuario());		
	file.escribirArchivo("Profesores/listaProfesores.txt",cortes);
	
	listaD<string> nombresClases = profe.getNombresClases();
	
	for(int i=0; i<profe.getNumClases(); i++){
		duo<string> dato;
		
		dato = nombresClases.obtener(i);
		
		file.escribirArchivo("Profesores/listaProfesores.txt", dato.dato);
	}	
	
	file.saltoDeLinea("Profesores/listaProfesores.txt");
}

void menu_estudiantes(){
	bool repite = true;
	int opcion;
	Archivo file;
	//Titulo del menu
	const char *titulo = "MENU ESTUDIANTES";
	//Opciones del menu
	const char *opciones[] = {"Consultar promedio de un estudiante","Generar archivos parcial","Consultar promedio por curso","Salir"};
	//Numero de opciones
	int n = 4;
	
	do{
		opcion = menu(titulo, opciones, n);
		
		//Alternativas
		switch(opcion){
			case 1:{
				int cedula;
				string nombreClase;
				string nombreEstudiante;
				string apellidoEstudiante;
				bool encontrado = false;
				
				system("cls");
				cout << "Digite la cedula del profesor de la clase: ";
				cin >> cedula;
				
				cout << "Digite el nombre de la clase del estudiante: ";
				cin >> nombreClase;
				
				cout << "Digite el nombre del estudiante: ";
				cin >> nombreEstudiante;
				
				cout << "Digite el apellido del estudiante: ";
				cin >> apellidoEstudiante;
				
				//Toca arreglar esto para que se vea bien
				promedio p;
				float pr=p.promedioEstudiante(cedula,nombreClase,nombreEstudiante,apellidoEstudiante);
				cout<<"El promedio de "<<nombreEstudiante<<" "<<apellidoEstudiante<<" es "<<pr<<endl;
				system("pause");
				
				//Aqui se llama a la funcion de Juli para calcular el promedio del estudiante
				
				break;
			}
				
			case 2:{
				system("cls");
				promedio p;
				int cedula;
				string clase;
				cout<<"Ingrese la cedula del profesor"<<endl;
				cin>>cedula;
				cout<<"Ingrse el nombre de la clase"<<endl;
				cin>>clase;
				p.escribirParcialPromedios(cedula,clase);
				cout<<"Se generaron correctamente en la carpeta Parciales/"<<clase<<endl;
				system("pause");
				break;
			}
			case 3:{
				system("cls");
				string nombreCurso;
				int cedula;
				cout << "Digite el nombre del curso: ";
				cin >> nombreCurso;
				cout << endl;
				cout << "Digite la cedula del profesor: ";
				cin >> cedula;
				
				promedio pr;
				float ps = pr.promedioCurso(nombreCurso,cedula);
				
				system("cls");
				
				cout << "El promedio del curso " << nombreCurso << " es " << ps << endl;
				
				system("pause");
				break;
			}		
				
			case 4:
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

		for((i=1);(i<=profes.getTam());(i++))
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
					opcionSeleccionada = profes.getTam() + 2;
				}
				break;
			
			case TECLA_ABAJO:
				opcionSeleccionada ++;
				
				if (opcionSeleccionada > profes.getTam() + 2)
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
