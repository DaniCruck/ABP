//Hecho por DañaCrack, Carlitos, y Sergio Payune
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <string>

#define clear system("clear");

using namespace std;

const int alumnosMax = 100, vehiculosMax = 20, practicasMax = 100;

//Registros----------------------------------------------------------------------------------------------------------------------------------------------------
struct vehiculo {
    string marca, modelo, matricula;
    int tipoVehiculo; //0 - Coche, 1 - Moto, 2 - Camión
    float kilometraje;
    int estado; //0 - Mantenimiento, 1 - Disponible
};

struct fecha{
    int dia, mes, año;
};

struct practica{
    string matricula;
    fecha fechaPractica;
    int duracionPractica, precioClase;
    float kmRecorridos;
};

struct alumno{
    char dni[9];
    string nombres, apellidos, numeroTelefono;
    practica clasesRealizadas[100];
    int nPracticas;
};
//Registros---------------------------------------------------------------------------------------------------------------------------------------------------

//Encabezado--------------------------------------------------------------------------------------------------------------------------------------------------
void header(){
    cout << "-----" << "PROGRAMA DE GESTIÓN DE CLASES PRÁCTICAS" << "-----" << endl;
    cout << "-------------------------------------------------" << endl;
}
//Encabezado--------------------------------------------------------------------------------------------------------------------------------------------------

//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------
void altaAlumno(alumno alumnos[], int &nAlumnos){
    alumno aux;
    int opcion;

    nAlumnos++; 
    clear;
    header();
    if(nAlumnos >= alumnosMax){
        nAlumnos--;
        cout << "NO SE PUEDEN REGISTRAR MÁS ALUMNOS" << endl;
        sleep(1);
        cout << "DEBE DAR DE BAJA A UN ALUMNO PARA AÑADIR A UNO NUEVO" << endl;
        sleep(1);
    }
    else{
        cin.ignore(256, '\n');
        cout << "Introduzca el DNI del alumno: ";
        cin.getline(aux.dni, 9);
        cout << "Introduzca el nombre del alumno: ";
        getline(cin, aux.nombres);
        cout << "Introduzca los apellidos del alumno: ";
        getline(cin, aux.apellidos);
        cout << "Introduzca el número de teléfono: ";
        getline(cin, aux.numeroTelefono);
        
        aux.nPracticas = 0;
        alumnos[nAlumnos - 1] = aux;
        
        cout << "Alumno registrado correctamente" << endl;
        sleep(2);
    }
}
//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------


//Funciones del menú------------------------------------------------------------------------------------------------------------------------------------------

void menuAlumnos(alumno alumnos[],int &nAlumnos){
    int opcion;
    
    do{
        system("clear");
        header();
        cout << "1 - " << setw(5) << "Dar de alta a un alumno nuevo" << endl;
        cout << "2 - " << setw(5) << "Dar de baja a un alumno" << endl;
        cout << "3 - " << setw(5) << "Modificar datos de un alumno" << endl;
        cout << "0 - " << setw(5) << "Salir" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Introduzca una opción: ";
    
        cin >> opcion;

        if((opcion < 0) || (opcion > 3)){
            cout << "RANGO INVALIDO" << endl;
            sleep(1);
            cout << "INTENTE DE NUEVO" << endl;
            sleep(1);
        }
        else{
            switch(opcion){
                case 1:{
                    altaAlumno(alumnos,nAlumnos);
                    break;
                }
                case 2:{
                    //Implementar baja de alumnos
                    break;
                }
                case 3 :{
                    //Implementar modificación de datos
                    break;
                }
                case 0:{ //Sale del apartado de alumnos
                    break;
                }
            }
            if(opcion == 0) break;
        }
    }while(true);
}

void menuVehiculos(){
    int opcion;

    do{
        clear;

        header();
        cout << "1 - " << setw(5) << "Dar de alta a un vahiculo nuevo" << endl;
        cout << "2 - " << setw(5) << "Dar de baja a un vehiculo" << endl;
        cout << "3 - " << setw(5) << "Modificar datos de un vehiculo" << endl;
        cout << "0 - " << setw(5) << "Salir" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Introduzca una opción: ";

        cin >> opcion;

        if((opcion < 0) || (opcion > 3)){
            cout << "RANGO INVALIDO" << endl;
            sleep(1);
            cout << "INTENTE DE NUEVO" << endl;
            sleep(1);
        }

    }while((opcion < 0) || (opcion > 3));

    switch(opcion){
        case 1:{
            //Implementar alta de vehiculos
            clear;
            break;
        }
        case 2:{
            //Implementar baja de vehiculos
            clear;
            break;
        }
        case 3 :{
            //Implementar modificación de datos
            clear;
            break;

        }
        default:{ //Sale del apartado de vehiculos
            clear;
            break;
        }
    }
}

void menuListas(){
    int opcion;

    clear;

    do{
        header();
        cout << "1 - " << setw(5) << "Mostrar alumnos" << endl;
        cout << "2 - " << setw(5) << "Mostrar vehiculos" << endl;
        cout << "0 - " << setw(5) << "Salir" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Introduzca una opción: ";

        cin >> opcion;

        if((opcion < 0) || (opcion > 3)){
            cout << "RANGO INVALIDO" << endl;
            sleep(1);
            cout << "INTENTE DE NUEVO" << endl;
            sleep(1);
        }
    }while((opcion < 0) || (opcion > 2));    

}

int menu(){
    int opcion;
    clear;

    header();
    cout << "1 - " << setw(5) << "Gestionar alumnos" << endl;
    cout << "2 - " << setw(5) << "Gestionar vehiculos" << endl;
    cout << "3 - " << setw(5) << "Dar de alta una clase" << endl;
    cout << "4 - " << setw(5) << "Mostrar listas" << endl;
    cout << "0 - " << setw(5) << "Salir" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Introduzca una opción: ";
    cin >> opcion; 
    if((opcion < 0) || (opcion > 4)){
        cout << "RANGO INVALIDO" << endl;
        sleep(1);
        cout << "INTENTE DE NUEVO" << endl;
        sleep(1);
    }
    else if(opcion == 0){
        clear;
    }
    return opcion;
}
//Funciones del menú------------------------------------------------------------------------------------------------------------------------------------------



//Función main------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    //Listas de los distintos objetos
    alumno alumnos[alumnosMax];
    vehiculo vehiculos[vehiculosMax];
    practica practicas[practicasMax];

    int opcion, nAlumnos = 0, nVehiculos, nClases;

    //Función del menu principal
    do{
        opcion = menu();

        switch(opcion){
            case 1:{
                menuAlumnos(alumnos, nAlumnos);
                break;
            }
            case 2:{
                menuVehiculos();
                break;
            }
            case 3:{
                //Implementar funcion de las clases practicas
                break;
            }
            case 4:{
                menuListas();
                break;
            }
        }
    }while(opcion != 0);
    return 0;
}
//Función main--------------------------------------------------------------------------------------------------------------------------------------------------