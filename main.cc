//Hecho por DañaCrack, Carlitos, y Sergio Payune
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <string>

#define clear system("clear");

using namespace std;

const int alumnosMax = 100, vehiculosMax = 20, practicasMax = 100;

//Registros----------------------------------------------------------------------------------------------------------------------------------------------------
struct Tvehiculo {
    string marca, modelo, matricula;
    int tipoVehiculo; //0 - Coche, 1 - Moto, 2 - Camión
    float kilometraje;
    int estado; //0 - Mantenimiento, 1 - Disponible
};

struct Tfecha{
    int dia, mes, año;
};

struct Tpractica{
    string matricula;
    Tfecha fechaPractica;
    int duracionPractica, precioClase;
    float kmRecorridos;
};

struct Talumno{
    string dni;
    string nombres, apellidos, numeroTelefono;
    Tpractica clasesRealizadas[100];
    int nPracticas;
};
//Registros---------------------------------------------------------------------------------------------------------------------------------------------------

//Encabezado--------------------------------------------------------------------------------------------------------------------------------------------------
void header(){
    cout << "-----" << "PROGRAMA DE GESTIÓN DE CLASES PRÁCTICAS" << "-----" << endl;
    cout << "-------------------------------------------------" << endl;
}
//Encabezado--------------------------------------------------------------------------------------------------------------------------------------------------
bool comprobarLetraDNI(Talumno alumnos[], int i){
//hay que hacerlo
bool correcto;
int numDNI=stoi(alumnos[i].dni);
char letraDNI=alumnos[i].dni.back();
switch(numDNI%23){
    case 0:
        if(letraDNI=='T') correcto=true;
}

}
//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------
void altaAlumno(Talumno alumnos[], int &nAlumnos){
    string auxdni,
           opcion;


    clear;
    header();
    if(nAlumnos >= alumnosMax){
        cout << "NO SE PUEDEN REGISTRAR MÁS ALUMNOS" << endl;
        sleep(0.5);
        cout << "DEBE DAR DE BAJA A UN ALUMNO PARA AÑADIR A UNO NUEVO" << endl;
        sleep(0.5);
    }
    else{
        cin.ignore();
        int cont=0;
        for(int i = 0; i <= nAlumnos; i++){
            cout << "Introduzca el DNI del alumno: ";
            getline(cin,auxdni);
            for(int p = 0; p<=nAlumnos; p++){
                //comprobacion si el dni esta registrado 
                cont=0;
                for(int j = 0; j < 9; j++){
                    if(auxdni[j]==alumnos[p].dni[j])cont++;
                }
                if(cont==9)p=nAlumnos;
            }
            if(cont==9){
                cout << "ESTE DNI YA ESTÁ REGISTRADO" << endl;
                sleep(1);
                cout << "PRUEBE DE NUEVO" << endl;
                sleep(0.5);
                i--;
            }else{
                //creación de nuevo alumno
                //comprobar si la letra introducida en el DNI corresponde a los números
                comprobarLetraDNI(alumnos, i);
                alumnos[i].dni = auxdni;
                //Entrada del nombre de pila con el segundo, sin incluir el apellido
                cout << "INTRODUZCA EL NOMBRE COMPLETO DEL ALUMNO(SIN APELLIDOS): ";
                getline(cin, alumnos[i].nombres);
                sleep(0.5);

                //Entrada de los apellidos.
                cout << "INTRODUZCLA LOS APELLIDOS DEL ALUMNO: ";
                getline(cin, alumnos[i].apellidos);
                sleep(0.5);

                //Entrada del telefono
                cout << "INTRODUZCA EL NUMERO DE TELEFONO(FORMATO: +XXX XXXXXXXXX): ";
                getline(cin, alumnos[i].numeroTelefono);
                sleep(0.5);

                alumnos[i].nPracticas = 0;
                nAlumnos++;

                clear;
                header();
                cout << "Quiere añadir a otro alumno? (0-No/1-Si): ";
                getline(cin,opcion);
                if(opcion == "no"||opcion == "No"||opcion == "NO"||opcion == "n"||opcion == "N"||opcion == "0"){
                    i = nAlumnos;
                }
            }
            
        }
    }
}
//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------


//Funciones del menú------------------------------------------------------------------------------------------------------------------------------------------

void menuAlumnos(Talumno alumnos[],int &nAlumnos){
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
    int opcion=0;
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
    Talumno alumnos[alumnosMax];
    Tvehiculo vehiculos[vehiculosMax];
    Tpractica practicas[practicasMax];

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