//Hecho por DañaCrack, Carlitos, y Sergio Paya
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstring>

#define clear system("clear");

using namespace std;

const int ALUMNOSMAX = 100, VEHICULOSMAX = 20, PRACTICASMAX = 100;

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

//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------
bool comprobarLetraDNI(string auxdni){
    //hay que hacerlo
    bool correcto=false;
    int numDNI=stoi(auxdni);
    char letraDNI=auxdni.back();
    string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    if(letras[numDNI%23]==letraDNI) correcto=true;
    return correcto;

}

void altaAlumno(Talumno alumnos[], int &nAlumnos){
    string auxdni, opcion;

    clear;
    header();

    if(nAlumnos >= ALUMNOSMAX){
        cout << "NO SE PUEDEN REGISTRAR MÁS ALUMNOS" << endl;
        sleep(0.5);
        cout << "DEBE DAR DE BAJA A UN ALUMNO PARA AÑADIR A UNO NUEVO" << endl;
        sleep(0.5);
    }
    else{
        cin.ignore();
        bool alumnoNuevo=true;
        while(alumnoNuevo==true){ 
            
            cout << "Introduzca el DNI del alumno: ";
            getline(cin, auxdni);

            bool existe = false; 
            for(int p = 0; p < nAlumnos; p++){
                if(auxdni == alumnos[p].dni){
                    existe = true;
                    p = nAlumnos;
                }
            }
            if(existe == true){
                cout << "ESTE DNI YA ESTÁ REGISTRADO" << endl;
                sleep(0.5);
                cout << "PRUEBE DE NUEVO" << endl;
                sleep(1);
            }
            else if(comprobarLetraDNI(auxdni) == false){
                cout << "DNI NO VÁLIDO (Letra incorrecta o formato erróneo)" << endl;
                sleep(0.5);
                cout << "PRUEBE DE NUEVO" << endl;
                sleep(1);
            }
            else{
                int i = nAlumnos; 

                alumnos[i].dni = auxdni;
                
                cout << "INTRODUZCA EL NOMBRE COMPLETO DEL ALUMNO(SIN APELLIDOS): ";
                getline(cin, alumnos[i].nombres);
                sleep(0.5);

                cout << "INTRODUZCLA LOS APELLIDOS DEL ALUMNO: ";
                getline(cin, alumnos[i].apellidos);
                sleep(0.5);

                cout << "INTRODUZCA EL NUMERO DE TELEFONO(FORMATO: +XXX XXXXXXXXX): ";
                getline(cin, alumnos[i].numeroTelefono);
                sleep(0.5);

                alumnos[i].nPracticas = 0;
                nAlumnos++;

                clear;
                header();
                cout << "Quiere añadir a otro alumno? (0-No/1-Si): ";
                getline(cin, opcion);
                //hecho para que no se entre al proceso de creacion de alumno por error
                if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                }else{
                    alumnoNuevo=false;
                }
                clear;
                header();
            }
        }
    }
}

void bajaAlumno(Talumno alumnos[], int &nAlumnos){
    string auxdni,opcion;
    clear;
    header();
    cin.ignore();
    cout<<"Introduce el DNI del alumno a dar de baja:";
    getline(cin,auxdni);
    clear;
    sleep(0.5);
    for(int i=0;i<nAlumnos;i++){
        if(auxdni==alumnos[i].dni){
            cout<<"Información del alumno a dar de baja:"<<endl;
            cout<<"Nombre: "<<alumnos[i].nombres<<" "<<alumnos[i].apellidos<<endl;
            cout<<"DNI:"<<alumnos[i].dni<<endl;
            cout<<"Número de telefono: "<<alumnos[i].numeroTelefono<<endl;
            cout<<"Número de practicas hechas: "<<alumnos[i].nPracticas<<endl;
            sleep(0.5);
            cout<<"¿Estás seguro de que quieres dar de baja a este alumno(0-No/1-Si)?";
            getline(cin,opcion);
            //Solo se acepta si para evitar eliminaciones sin querer
            if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                for(int j=i;j<nAlumnos-1;j++){
                    alumnos[j]=alumnos[j+1];
                }         
                nAlumnos--;
                cout<<"Alumno eliminado con éxito."<<endl;
            }else{
                i=nAlumnos;
            }
        }
    }
    clear;
}

void mostrarAlumnos(Talumno alumnos[], int nAlumnos){
    clear;
    //Limpiar el buffer para que no se salte la pausa de despues de la lista
    cin.ignore();
    if(nAlumnos>0){
        for(int i=0;i<nAlumnos;i++){
            //Lista de alumnos
            cout<<"Alumno nº"<<i+1<<endl;
            sleep(0.5);
            cout<<"Nombre: "<<alumnos[i].nombres<<" "<<alumnos[i].apellidos<<endl;
            cout<<"DNI:"<<alumnos[i].dni<<endl;
            cout<<"Número de telefono: "<<alumnos[i].numeroTelefono<<endl;
            cout<<"Número de practicas hechas: "<<alumnos[i].nPracticas<<endl;
            cout<<setw(20)<<"--------------------------"<<endl;
        }
        cout<<"Pulsa enter para salir.";
        //El programa no avanza hasta que el usuario pulse enter
        cin.get();
        clear;
        
    }else{
        clear;
        cout<<"No hay alumnos registrados en el sistema."<<endl;
        sleep(1.5);
        clear;
    }
}

void modificarAlumno(Talumno alumnos[], int nAlumnos){
    char  opcion;
    Talumno auxAlumno;
    char confirmacion, repetir;
    clear;
    header();
    cin.ignore();
    if(nAlumnos<1){
        cout<<"No hay alumnos registrados en el sistema."<<endl;
        sleep(1.5);
        clear;
    }else{
        cout<<"Introduce el DNI del alumno a modificar: ";
        getline(cin,auxAlumno.dni);
        for(int i = 0; i < nAlumnos; i++){
            if(auxAlumno.dni == alumnos[i].dni){
                do{
                    clear;
                    header();
                    cout << "Datos actuales del alumno:" << endl;
                    cout << "--------------------------" << endl;
                    cout << "DNI: " << alumnos[i].dni << endl;
                    cout << "Nombre: " << alumnos[i].nombres << endl;
                    cout << "Apellidos: " << alumnos[i].apellidos << endl;
                    cout << "Número de teléfono: " << alumnos[i].numeroTelefono << endl;
                    cout << "--------------------------" << endl;

                    cout << "Que dato desea modificar?" << endl;
                    cout << "1 - Nombre" << endl;
                    cout << "2 - Apellidos" << endl;
                    cout << "3 - Número de teléfono" << endl;
                    cout << "0 - Salir" << endl;
                    cin >> opcion;

                    switch(opcion){
                        case '1':
                            cin.ignore();
                            cout<<"Introduce el nuevo nombre completo (SIN APELLIDOS): ";
                            getline(cin,auxAlumno.nombres);
                            cout << "Seguro que es el dato correcto? (s/n): ";

                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].nombres = auxAlumno.nombres;
                                cout<<"Nombre modificado con éxito."<<endl;
                            }
                            sleep(1);
                            
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            
                            break;

                        case '2':
                            cin.ignore();
                            cout<<"Introduce los nuevos apellidos: ";
                            getline(cin,auxAlumno.apellidos);
                            cout << "Seguro que es el dato correcto? (s/n): ";

                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].apellidos = auxAlumno.apellidos;
                                cout<<"Apellidos modificados con éxito."<<endl;
                            }
                            sleep(1);
                            
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            
                            break;

                        case '3':
                            cin.ignore();
                            cout<<"Introduce el nuevo número de teléfono: ";
                            getline(cin,auxAlumno.numeroTelefono);

                            cout << "Seguro que es el dato correcto? (s/n): ";

                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].numeroTelefono = auxAlumno.numeroTelefono;
                                cout<<"Número de teléfono modificado con éxito."<<endl;
                            }
                            sleep(1);
                            
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            
                            break;

                        case '0':
                            cout<<"Saliendo del menú de modificación."<<endl;
                            sleep(1);

                            repetir = 'n';

                            break;
                    }
                    
                }while(repetir == 's' || repetir == 'S');
                i = nAlumnos; //Para salir del bucle una vez encontrado el alumno
            }
        }
    }

}

void altaVehiculo(Tvehiculo vehiculos[], int &nVehiculos){
    string auxMatricula, tipo;
    string opcion;
    clear;
    header();
    if(nVehiculos >= VEHICULOSMAX){
        cout << "NO SE PUEDEN REGISTRAR MÁS VEHÍCULOS" << endl;
        sleep(0.5);
        cout << "DEBE DAR DE BAJA A UN VEHÍCULO PARA AÑADIR A UNO NUEVO" << endl;
        sleep(0.5);
    }
    else{
        cin.ignore();
        bool vehiculoNuevo=true;
        while(vehiculoNuevo==true){ 
            cout << "Introduzca la matrícula del vehículo (Formato: 1234ABC): ";
            getline(cin, auxMatricula);

            bool existe = false; 
            for(int p = 0; p < nVehiculos; p++){
                if(auxMatricula == vehiculos[p].matricula){
                    existe = true;
                    p = nVehiculos;
                }
            }
            if(existe == true){
                cout << "ESTA MATRÍCULA YA ESTÁ REGISTRADA" << endl;
                sleep(0.5);
                cout << "PRUEBE DE NUEVO" << endl;
                sleep(1);
            }
            else{
                int i = nVehiculos; 

                vehiculos[i].matricula = auxMatricula;
                
                cout << "INTRODUZCA LA MARCA DEL VEHÍCULO: ";
                getline(cin, vehiculos[i].marca);
                sleep(0.5);

                cout << "INTRODUZCA EL MODELO DEL VEHÍCULO: ";
                getline(cin, vehiculos[i].modelo);
                sleep(0.5);

                cout << "INTRODUZCA EL TIPO DE VEHÍCULO (0-Coche/1-Moto/2-Camión): ";
                cin >> vehiculos[i].tipoVehiculo;
                sleep(0.5);

                cout << "INTRODUZCA EL KILOMETRAJE DEL VEHÍCULO: ";
                cin >> vehiculos[i].kilometraje;
                sleep(0.5);

                cout << "INTRODUZCA EL ESTADO DEL VEHÍCULO (0-Mantenimiento/1-Disponible): ";
                cin >> vehiculos[i].estado;
                sleep(0.5);

                nVehiculos++;
                cin.ignore();
                clear;
                header();
                cout << "Quiere añadir a otro vehículo? (0-No/1-Si): ";
                getline(cin,opcion);
                if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                    clear;
                    header();
                }else{
                    vehiculoNuevo=false;
                }
            }
        }
    }
}

void bajaVehiculo(Tvehiculo vehiculos[], int &nVehiculos){
    string auxMatricula,opcion;
    bool encontrado=false;
    clear;
    header();
    cin.ignore();
    if(nVehiculos==0){
        cout<<"No hay vehículos registrados en el sistema."<<endl;
        sleep(1.5);
    }else{
        cout<<"Introduce la matricula del vehiculo a dar de baja:";
        getline(cin,auxMatricula);
        clear;
        sleep(0.5);
        for(int i=0;i<nVehiculos;i++){
            if(auxMatricula==vehiculos[i].matricula){
                header();
                encontrado=true;
                cout<<"Información del vehciulo a dar de baja"<<endl;
                cout << "-------------------------------------------------" << endl;
                cout<<"Matricula:"<<vehiculos[i].matricula<<endl;
                cout<<"Marca:"<<vehiculos[i].marca<<endl;
                cout<<"Modelo:"<<vehiculos[i].modelo<<endl;
                cout<<"Tipo de vehiculo:";
                switch(vehiculos[i].tipoVehiculo){
                    case 0:
                        cout<<" Coche"<<endl;
                        break;
                    case 1:
                        cout<<" Moto"<<endl;
                        break;
                    case 2:
                        cout<<" Camión"<<endl;
                        break;
                }
                cout<<"Kilometraje: "<<vehiculos[i].kilometraje<<endl;
                cout<<"Estado:"<<vehiculos[i].estado<<endl;

                sleep(0.5);
                cout<<"¿Estás seguro de que quieres dar de baja a este vehiculo(0-No/1-Si)?";
                getline(cin,opcion);
                //Solo se acepta si para evitar eliminaciones sin querer
                if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                    for(int j=i;j<nVehiculos-1;j++){
                        vehiculos[j]=vehiculos[j+1];
                    }        
                    nVehiculos--;
                    cout<<"Vehiculo eliminado con éxito."<<endl;
                    sleep(1.5);
                }
            }
        }
        if(encontrado==false){
            header();
            cout<<"Ningun vehículo tiene esa matricula."<<endl;
            sleep(1.5);
        }
        clear;
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
                    bajaAlumno(alumnos,nAlumnos);
                    break;
                }
                case 3 :{
                    modificarAlumno(alumnos,nAlumnos);
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

void menuVehiculos(Tvehiculo vehiculos[], int &nVehiculos){
    int opcion;
    do{
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
                altaVehiculo(vehiculos, nVehiculos);
                clear;
                break;
            }
            case 2:{
                bajaVehiculo(vehiculos, nVehiculos);
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
    }while(true && opcion!=0);
}

void menuListas(Talumno alumnos[], int nAlumnos){
    int opcion;

    clear;
//While true es para que al salir de cualquiera de las listas vuelva a repetir el menu hasta que se envie un 0
    do{
        do{
            header();
            cout << "1 - " << setw(5) << "Mostrar alumnos" << endl;
            cout << "2 - " << setw(5) << "Mostrar vehiculos" << endl;
            cout << "0 - " << setw(5) << "Salir" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Introduzca una opción: ";

            cin >> opcion;

            if((opcion < 0) || (opcion >= 3)){
                cout << "RANGO INVALIDO" << endl;
                sleep(1);
                cout << "INTENTE DE NUEVO" << endl;
                sleep(1);
                clear;
            }else{
                switch(opcion){
                    case 1:
                        mostrarAlumnos(alumnos, nAlumnos);
                        break;
                }
            }
        }while((opcion < 0) || (opcion > 2));
    }while(true && opcion!=0);    

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
    Talumno alumnos[ALUMNOSMAX];
    Tvehiculo vehiculos[VEHICULOSMAX];
    Tpractica practicas[PRACTICASMAX];

    int opcion, nAlumnos = 0, nVehiculos=0, nClases=0;

    //Función del menu principal
    do{
        opcion = menu();

        switch(opcion){
            case 1:{
                menuAlumnos(alumnos, nAlumnos);
                break;
            }
            case 2:{
                menuVehiculos(vehiculos, nVehiculos);
                break;
            }
            case 3:{
                //Implementar funcion de las clases practicas
                break;
            }
            case 4:{
                menuListas(alumnos, nAlumnos);
                break;
            }
        }
    }while(opcion != 0);
    return 0;
}
//Función main--------------------------------------------------------------------------------------------------------------------------------------------------