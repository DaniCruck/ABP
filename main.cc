//Hecho por Daniel Valeriev Iliev Arkhipov 
//Carlos Hernández Fernández
//Sergio Payá Romero

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <cctype>
#include <string>

#define clear system("clear");

using namespace std;

// --- NUEVO: Aumentamos constantes ---
const int ALUMNOSMAX = 100, VEHICULOSMAX = 20, PRACTICASMAX = 100, FACTURASMAX = 100;

//Registros----------------------------------------------------------------------------------------------------------------------------------------------------
struct Tvehiculo {
    string marca, modelo, matricula;
    int tipoVehiculo; //0 - Coche, 1 - Moto, 2 - Camión
    float kilometraje;
    int estado; //0 - Mantenimiento, 1 - Disponible
};

struct Tfecha{
    int dia, mes, año, hora, minutos;
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
    // --- NUEVO: Datos del responsable ---
    string nombreResponsable;
    string telefonoResponsable;
    // ------------------------------------
    Tpractica clasesRealizadas[PRACTICASMAX];
    int nPracticas;
};

// --- NUEVO: Estructura para Facturas ---
struct Tfactura {
    int idFactura;
    string nombreCliente; // Responsable
    int numClases;
    float importeTotal;
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
                
                cout << "INTRODUZCA EL NOMBRE COMPLETO DEL ALUMNO (SIN APELLIDOS): ";
                getline(cin, alumnos[i].nombres);
                sleep(0.5);

                cout << "INTRODUZCA LOS APELLIDOS DEL ALUMNO: ";
                getline(cin, alumnos[i].apellidos);
                sleep(0.5);

                cout << "INTRODUZCA EL NÚMERO DE TELÉFONO (FORMATO: +XXX XXXXXXXXX): ";
                getline(cin, alumnos[i].numeroTelefono);
                sleep(0.5);

                // --- NUEVO: Petición de datos del responsable ---
                cout << "INTRODUZCA EL NOMBRE DEL RESPONSABLE: ";
                getline(cin, alumnos[i].nombreResponsable);
                sleep(0.5);

                cout << "INTRODUZCA EL TELÉFONO DEL RESPONSABLE: ";
                getline(cin, alumnos[i].telefonoResponsable);
                sleep(0.5);
                // ------------------------------------------------

                alumnos[i].nPracticas = 0;
                nAlumnos++;

                clear;
                header();
                cout << "¿Quiere añadir a otro alumno? (0-No/1-Si): ";
                getline(cin, opcion);
                
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
    cout<<"Introduce el DNI del alumno a dar de baja: ";
    getline(cin,auxdni);
    clear;
    sleep(0.5);
    for(int i=0;i<nAlumnos;i++){
        if(auxdni==alumnos[i].dni){
            cout<<"Información del alumno a dar de baja:"<<endl;
            cout<<"Nombre: "<<alumnos[i].nombres<<" "<<alumnos[i].apellidos<<endl;
            cout<<"DNI: "<<alumnos[i].dni<<endl;
            cout<<"Número de teléfono: "<<alumnos[i].numeroTelefono<<endl;
            cout<<"Responsable: "<<alumnos[i].nombreResponsable<<endl; // NUEVO
            cout<<"Número de prácticas hechas: "<<alumnos[i].nPracticas<<endl;
            sleep(0.5);
            cout<<"¿Estás seguro de que quieres dar de baja a este alumno (0-No/1-Si)? ";
            getline(cin,opcion);
            
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
    cin.ignore();
    if(nAlumnos>0){
        for(int i=0;i<nAlumnos;i++){
            header();
            cout<<string(18,' ')<<"-Alumno nº"<<i+1<<"-"<<endl<<endl;
            sleep(0.5);
            cout<<"Nombre: "<<alumnos[i].nombres<<" "<<alumnos[i].apellidos<<endl;
            cout<<"DNI: "<<alumnos[i].dni<<endl;
            cout<<"Número de teléfono: "<<alumnos[i].numeroTelefono<<endl;
            // --- NUEVO: Mostrar responsable ---
            cout<<"Responsable: " << alumnos[i].nombreResponsable << endl;
            cout<<"Tlf Responsable: " << alumnos[i].telefonoResponsable << endl;
            // ----------------------------------
            cout<<"Número de prácticas hechas: "<<alumnos[i].nPracticas<<endl;
            if(alumnos[i].nPracticas>0){
                cout<< "-------------------------------------------------" << endl;
                cout<<string(11,' ')<<"---Prácticas del alumno---"<<endl;
                for(int j=0;j<alumnos[i].nPracticas;j++){
                    cout<<string(17,' ')<<"-Práctica nº"<<j+1<<"-"<<endl<<endl;
                    cout<<"Matrícula del vehículo usado: "<<alumnos[i].clasesRealizadas[j].matricula<<endl;
                    cout<<"Fecha: "<<alumnos[i].clasesRealizadas[j].fechaPractica.dia<<"/"<<alumnos[i].clasesRealizadas[j].fechaPractica.mes<<"/"<<alumnos[i].clasesRealizadas[j].fechaPractica.año<<endl;
                    cout<<"Hora de inicio: "<<alumnos[i].clasesRealizadas[j].fechaPractica.hora<<":"<<alumnos[i].clasesRealizadas[j].fechaPractica.minutos<<endl;
                    cout<<"Duración de la clase en minutos: "<<alumnos[i].clasesRealizadas[j].duracionPractica<<endl;
                    cout<<"Kilómetros recorridos: "<<alumnos[i].clasesRealizadas[j].kmRecorridos<<" km"<<endl;
                    cout<<"Precio de la clase: "<<alumnos[i].clasesRealizadas[j].precioClase<<"€"<<endl;
                }
            }
            cout << "-------------------------------------------------" << endl;
            
        }
        cout<<"Pulsa enter para salir.";
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
                    // --- NUEVO: Mostrar datos responsable ---
                    cout << "Nombre Responsable: " << alumnos[i].nombreResponsable << endl;
                    cout << "Teléfono Responsable: " << alumnos[i].telefonoResponsable << endl;
                    // ----------------------------------------
                    cout << "--------------------------" << endl;

                    cout << "¿Qué dato desea modificar?" << endl;
                    cout << "1 - Nombre" << endl;
                    cout << "2 - Apellidos" << endl;
                    cout << "3 - Número de teléfono" << endl;
                    // --- NUEVO: Opciones menú modificar ---
                    cout << "4 - Nombre Responsable" << endl;
                    cout << "5 - Teléfono Responsable" << endl;
                    // --------------------------------------
                    cout << "0 - Salir" << endl;
                    cin >> opcion;

                    switch(opcion){
                        case '1':
                            cin.ignore();
                            cout<<"Introduce el nuevo nombre completo (SIN APELLIDOS): ";
                            getline(cin,auxAlumno.nombres);
                            cout << "¿Seguro que es el dato correcto? (s/n): ";

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
                            cout << "¿Seguro que es el dato correcto? (s/n): ";

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

                            cout << "¿Seguro que es el dato correcto? (s/n): ";

                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].numeroTelefono = auxAlumno.numeroTelefono;
                                cout<<"Número de teléfono modificado con éxito."<<endl;
                            }
                            sleep(1);
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            break;

                        // --- NUEVO: Cases para modificar responsable ---
                        case '4':
                            cin.ignore();
                            cout<<"Introduce el nuevo nombre del responsable: ";
                            getline(cin,auxAlumno.nombreResponsable);
                            cout << "¿Seguro que es el dato correcto? (s/n): ";
                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].nombreResponsable = auxAlumno.nombreResponsable;
                                cout<<"Nombre del responsable modificado con éxito."<<endl;
                            }
                            sleep(1);
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            break;
                        
                        case '5':
                            cin.ignore();
                            cout<<"Introduce el nuevo teléfono del responsable: ";
                            getline(cin,auxAlumno.telefonoResponsable);
                            cout << "¿Seguro que es el dato correcto? (s/n): ";
                            cin >> confirmacion;
                            if(confirmacion == 's' || confirmacion == 'S'){
                                alumnos[i].telefonoResponsable = auxAlumno.telefonoResponsable;
                                cout<<"Teléfono del responsable modificado con éxito."<<endl;
                            }
                            sleep(1);
                            cout << "¿Desea modificar otro dato de este alumno? (s/n): ";
                            cin >> repetir;
                            break;
                        // -----------------------------------------------

                        case '0':
                            cout<<"Saliendo del menú de modificación."<<endl;
                            sleep(1);

                            repetir = 'n';

                            break;
                        default:
                            cout<<"Opción no válida"<<endl;
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
            if(auxMatricula.length()==7){
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
                    cout << "¿Quiere añadir a otro vehículo? (0-No/1-Si): ";
                    getline(cin,opcion);
                    if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                        clear;
                        header();
                    }else{
                        vehiculoNuevo=false;
                    }
                }
            }else{
                clear;
                cout<<"La matrícula no cumple el formato pedido. Intente de nuevo."<<endl;
                sleep(1.5);
                clear;
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
        cout<<"Introduce la matrícula del vehículo a dar de baja: ";
        getline(cin,auxMatricula);
        clear;
        sleep(0.5);
        for(int i=0;i<nVehiculos;i++){
            if(auxMatricula==vehiculos[i].matricula){
                header();
                encontrado=true;
                cout<<"Información del vehículo a dar de baja"<<endl;
                cout << "-------------------------------------------------" << endl;
                cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
                cout<<"Marca: "<<vehiculos[i].marca<<endl;
                cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
                cout<<"Tipo de vehículo: ";
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
                cout<<"Estado: ";
                if(vehiculos[i].estado==0){
                    cout<<"En mantenimiento"<<endl;
                }else{
                    cout<<"Disponible"<<endl;
                }
                sleep(0.5);
                cout<<"¿Estás seguro de que quieres dar de baja a este vehículo (0-No/1-Si)? ";
                getline(cin,opcion);
                //Solo se acepta si para evitar eliminaciones sin querer
                if(opcion == "si"||opcion == "Si"||opcion == "SI"||opcion == "s"||opcion == "S"||opcion == "1"){
                    for(int j=i;j<nVehiculos-1;j++){
                        vehiculos[j]=vehiculos[j+1];
                    }        
                    nVehiculos--;
                    cout<<"Vehículo eliminado con éxito."<<endl;
                    sleep(1.5);
                }
            }
        }
        if(encontrado==false){
            header();
            cout<<"Ningún vehículo tiene esa matrícula."<<endl;
            sleep(1.5);
        }
        clear;
    }
    
}

void mostrarMAtricula(Tvehiculo vehiculos[], int nVehiculos){
    string busqueda;
    clear;
    cin.ignore();
    header();

    cout << "Introduzca la matrícula del vehículo/s a buscar: ";
    cin >> busqueda;
    bool encontrado = false;
    clear;
    cout << "\n--- RESULTADOS DE BÚSQUEDA ---" << endl;
    cout << "-------------------------------------------------" << endl;
    for(int i = 0; i < nVehiculos; i++) {
        // La función .find() devuelve string::npos si NO encuentra la coincidencia.
        // Si es diferente de npos, significa que SÍ lo encontró.
        if (vehiculos[i].matricula.find(busqueda) != string::npos) {
            cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
            cout<<"Marca: "<<vehiculos[i].marca<<endl;
            cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
            cout<<"Tipo de vehículo: ";
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
            cout<<"Estado: ";
            if(vehiculos[i].estado==0){
                cout<<"En mantenimiento"<<endl;
            }else{
                cout<<"Disponible"<<endl;
            }
            cout << "-------------------------------------------------" << endl;
            encontrado = true;
        }
    }
    if(!encontrado) {
        cout << "No se encontraron vehículos con esas letras" << endl;
    }
}

void mostrarVehiculos(Tvehiculo vehiculos[], int nVehiculos){
    int opcion;
    clear;
    cin.ignore();
    header();
    if(nVehiculos<1){
        cout<<"No hay vehículos registrados en el sistema."<<endl;
        sleep(1.5);
        clear;
    }else{
        cout<<"1- Mostrar todos los vehículos"<<endl;
        cout<<"2- Mostrar los vehículos disponibles"<<endl;
        cout<<"3- Mostrar los vehículos en mantenimiento"<<endl;
        cout<<"4- Mostrar los vehículos ordenados por letras de matrícula"<<endl;
        cin>> opcion;
        clear;
        switch(opcion){
            case 1:
                for(int i=0;i<nVehiculos;i++){
                    cout << "-------------------------------------------------" << endl;
                    cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
                    cout<<"Marca: "<<vehiculos[i].marca<<endl;
                    cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
                    cout<<"Tipo de vehículo: ";
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
                    cout<<"Estado: ";
                    if(vehiculos[i].estado==0){
                        cout<<"En mantenimiento"<<endl;
                    }else{
                        cout<<"Disponible"<<endl;
                    }
                    
                }
                break;
            case 2:
                for(int i =0; i<nVehiculos; i++){
                    if(vehiculos[i].estado==1){
                        cout << "-------------------------------------------------" << endl;
                        cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
                        cout<<"Marca: "<<vehiculos[i].marca<<endl;
                        cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
                        cout<<"Tipo de vehículo: ";
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
                        cout<<"Estado: ";
                        if(vehiculos[i].estado==0){
                            cout<<"En mantenimiento"<<endl;
                        }else{
                            cout<<"Disponible"<<endl;
                        }
                    }
                }break;
                case 3:
                for(int i =0; i<nVehiculos; i++){
                    if(vehiculos[i].estado==0){
                        cout << "-------------------------------------------------" << endl;
                        cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
                        cout<<"Marca: "<<vehiculos[i].marca<<endl;
                        cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
                        cout<<"Tipo de vehículo: ";
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
                        cout<<"Estado: ";
                        if(vehiculos[i].estado==0){
                            cout<<"En mantenimiento"<<endl;
                        }else{
                            cout<<"Disponible"<<endl;
                        }
                    }
                }
                break;
                case 4:
                    mostrarMAtricula(vehiculos, nVehiculos);
                    break;

        }
        cin.ignore();
        cout<<"Pulsa enter para salir.";
         //El programa no avanza hasta que el usuario pulse enter
         cin.get();
         clear;
    }
}

void modificarVehiculo(Tvehiculo vehiculos[], int &nVehiculos){
    int opcion;
    string busqueda, auxMatricula;
    char repetir, confirmar;
    clear;
    cin.ignore();
    header();
    if(nVehiculos == 0){
        cout<<"No hay vehículos registrados en el programa "<<endl;
        sleep(1.5);
        clear;
    }else{
        cout << "Introduzca la matrícula del vehículo/s a buscar: ";
        cin >> busqueda;
        bool encontrado = false;
        clear;
        for(int i = 0; i < nVehiculos; i++) {
            if (vehiculos[i].matricula == busqueda) {
                do{
                    header();
                    cout << "--- RESULTADOS DE BÚSQUEDA ---" << endl;
                    cout << "-------------------------------------------------" << endl;
                    cout<<"Matrícula: "<<vehiculos[i].matricula<<endl;
                    cout<<"Marca: "<<vehiculos[i].marca<<endl;
                    cout<<"Modelo: "<<vehiculos[i].modelo<<endl;
                    cout<<"Tipo de vehículo: ";
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
                    cout<<"Estado: ";
                    if(vehiculos[i].estado==0){
                        cout<<"En mantenimiento"<<endl;
                    }else{
                        cout<<"Disponible"<<endl;
                    }
                    encontrado = true;
                    cout << "--------------------------" << endl;
                    cout << "1 - Matrícula" << endl;
                    cout << "2 - Marca" << endl;
                    cout << "3 - Modelo" << endl;
                    cout << "4 - Kilometraje" << endl;
                    cout << "5 - Estado" << endl;
                    cout << "0 - Salir" << endl;
                    cout << "--------------------------" << endl;
                    cout << "¿Qué datos desea modificar?: ";
                    cin >> opcion;
                    clear;
                    switch(opcion){
                        case 0:
                            cout<<"Saliendo del menú..."<<endl;
                            repetir = 'n';
                            clear;
                            break;
                        case 1:
                            do{
                                cout<<"Introduzca la matrícula nueva del vehículo: ";
                                cin>>auxMatricula;  
                                if(auxMatricula.length()!=7){
                                    clear;
                                    cout<<"Formato de matrícula incorrecto. Vuelva a intentarlo."<<endl;
                                    sleep(1.5);
                                    clear;
                                }
                            }while(auxMatricula.length()!=7);                        
                            cout<<"¿Seguro que desea modificar la matrícula? (S / N)"<<endl;
                            cin>>confirmar;
                            clear;
                            if(confirmar == 'S' || confirmar=='s'){
                                vehiculos[i].matricula=auxMatricula;
                                cout<<"La modificación se ha realizado con éxito."<<endl;
                                cout<<endl;
                                cout<<"¿Desea modificar algún dato más? (S/N)"<<endl;
                                cin>>repetir;
                            }
                            sleep(0.5);
                            clear;
                            break;
                        case 2:
                            cout<<"Introduzca la marca nueva del vehículo: ";
                            cin>>vehiculos[i].marca;
                            cout<<"¿Seguro que desea modificar la marca? (S/N)"<<endl;
                            cin>>confirmar;
                            if(confirmar == 'S' || confirmar=='s'){
                                cout<<"La modificación se ha realizado con éxito."<<endl;
                                cout<<endl;
                                cout<<"¿Desea modificar algún dato más? (S/N)"<<endl;
                                cin>>repetir;
                            }
                            sleep(0.5);
                            clear;
                            break;
                        case 3:
                            cout<<"Introduzca el nuevo modelo del vehículo: ";
                            cin>>vehiculos[i].modelo;
                            cout<<"¿Seguro que desea modificar el modelo del vehículo? (S/N)"<<endl;
                            cin>>confirmar;
                            if(confirmar == 'S' || confirmar=='s'){
                                cout<<"La modificación se ha realizado con éxito."<<endl;
                                cout<<endl;
                                cout<<"¿Desea modificar algún dato más? (S/N)"<<endl;
                                cin>>repetir;
                            }
                            sleep(0.5);
                            clear;
                            break;
                        case 4:
                            do{
                                cout<<"Introduzca el kilometraje nuevo del vehículo: ";
                                cin>>vehiculos[i].kilometraje;
                                if(vehiculos[i].kilometraje<0){
                                    cout<<"Kilometraje no válido. Intente de nuevo."<<endl;
                                    sleep(1.5);
                                    clear;
                                }else{
                                    cout<<"¿Seguro que desea modificar el kilometraje del vehículo? (S / N)"<<endl;
                                    cin>>confirmar;
                                    if(confirmar == 'S' || confirmar=='s'){
                                        cout<<"La modificación se ha realizado con éxito."<<endl;
                                        cout<<endl;
                                        cout<<"¿Desea modificar algún dato más? (S/n)"<<endl;
                                        cin>>repetir;
                                    }
                                }
                            }while(vehiculos[i].kilometraje<0);
                            sleep(0.5);
                            clear;
                            break;
                        case 5:
                            do{
                                cout<<"Introduzca el estado nuevo del vehículo (0 - Mantenimiento, 1 - Disponible): ";
                                cin>>vehiculos[i].estado;
                                if(vehiculos[i].estado<0 || vehiculos[i].estado>1){
                                    cout<<"Valor fuera del rango, vuelve a introducirlo"<<endl;
                                }
                            }while(vehiculos[i].estado<0 || vehiculos[i].estado>1);
                            cout<<"¿Seguro que desea modificar el estado? (S / N)"<<endl;
                            cin>>confirmar;
                            if(confirmar == 'S' || confirmar=='s'){
                                cout<<"La modificación se ha realizado con éxito."<<endl;
                                cout<<endl;
                                cout<<"¿Desea modificar algún dato más? (S/n)"<<endl;
                                cin>>repetir;
                            }
                            sleep(0.5);
                            clear;
                            break;
                    }
                }while(repetir == 'S' || repetir == 's');
            }
            }
            if(!encontrado) {
                header();
                cout << "No se encontraron vehículos con esas letras" << endl;
                sleep(1.5);
            }
        }
    }

void darDeAltaClase(Talumno alumnos[], int nAlumnos, Tvehiculo vehiculos[], int nVehiculos){
    cin.ignore();
    clear;
    string auxDNI, auxMatricula;
    int numAlumno=0, numVehiculo=0;
    bool existeDNI=false, existeVehiculo=false;
    header();
    cout<<"Introduce el DNI del alumno: ";
    getline(cin, auxDNI);
    //Comprobacion de que el DNI esta en el sistema
    for(int i=0;i<nAlumnos;i++){
        if(alumnos[i].dni==auxDNI) {
            existeDNI=true;
            numAlumno=i;
        }
    }
    if(existeDNI==false){
        clear;
        header();
        cout<<"El DNI introducido no está registrado en el sistema."<<endl;
        sleep(1.5);
    }else{
        if(alumnos[numAlumno].nPracticas>=100){
            clear;
            header();
            cout<<"El alumno ha realizado el número máximo de prácticas permitido."<<endl;
            sleep(1.5);
            clear;
        }else{
            clear;
            header();
            cout<<"Introduce la matrícula del vehículo con el que se realizó la práctica: ";
            getline(cin, auxMatricula);
            for(int i=0;i<nVehiculos;i++){
                if(auxMatricula==vehiculos[i].matricula){
                    existeVehiculo=true;
                    alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].matricula=auxMatricula;
                    numVehiculo=i;
                }
            }
            if(existeVehiculo==false){
                clear;
                header();
                // Corregido "matricula"
                cout<<"La matrícula introducida no está registrada en el sistema."<<endl;
                sleep(1.5);
                clear;
            }else{
                    clear;
                    //No sale del bucle hasta que no introduzca una fecha válida

                    //DIAS
                    do{
                        clear;
                        header();
                        cout<<"Introduce el día en el que se realizó la práctica (1-31): ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.dia;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.dia<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.dia > 31){
                            clear;
                            cout<<"Día no válido. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.dia<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.dia > 31);
                    cout<<endl;

                    //MESES
                   do{
                        clear;
                        header();
                        cout<<"Introduce el mes en el que se realizó la práctica (1-12): ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.mes;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.mes<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.mes > 12){
                            clear;
                            cout<<"Mes no válido. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.mes<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.mes > 12);
                    cout<<endl;

                    //AÑOS
                    do{
                        clear;
                        header();
                        cout<<"Introduce el año en el que se realizó la práctica (1900-2026): ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.año;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.año<1900 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.año > 2026){
                            clear;
                            cout<<"Año no válido. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.año<1900 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.año > 2026);

                    //Hora
                    do{
                        clear;
                        header();
                        cout<<"Introduce la hora en la que se realizó la práctica (1-24): ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.hora;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.hora<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.hora > 24){
                            clear;
                            cout<<"Hora no válida. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.hora<1 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.hora > 24);

                    //Minutos
                    do{
                        clear;
                        header();
                        cout<<"Introduce el minuto en el que se realizó la práctica (0-59): ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.minutos;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.minutos<0 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.minutos > 59){
                            clear;
                            cout<<"Minutos no válidos. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.minutos<0 || alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].fechaPractica.minutos > 59);

                    //Duracion
                    do{
                        clear;
                        header();
                        cout<<"Introduce la duración de la práctica en minutos: ";
                        cin>>alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].duracionPractica;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].duracionPractica<0){
                            clear;
                            cout<<"Duración no válida. Intente de nuevo"<<endl;
                            sleep(1.5);
                            clear;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].duracionPractica<0);

                    //Kilometros recorridos
                    do{
                        clear;
                        header();
                        cout<<"Introduce los kilómetros recorridos: ";
                        cin >> alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].kmRecorridos;
                        if(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].kmRecorridos<0){
                            clear;
                            cout<<"Valor inválido. Intente de nuevo."<<endl;
                            clear;
                        }else{
                            vehiculos[numVehiculo].kilometraje+=alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].kmRecorridos;
                        }
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].kmRecorridos<0);

                    //Precio de la clase
                    do{
                        clear;
                        header();
                        cout<<"Introduce el precio total de la clase: ";
                        cin >> alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].precioClase;
                    }while(alumnos[numAlumno].clasesRealizadas[alumnos[numAlumno].nPracticas].precioClase < 0);
                    alumnos[numAlumno].nPracticas++;

            }
        }
    }

}
//Funciones solicitadas---------------------------------------------------------------------------------------------------------------------------------------

// --- Funciones examen --------------------------------------------------------------------------------------------------------------------------------------
void emitirFactura(Talumno alumnos[], int nAlumnos, Tfactura facturas[], int &nFacturas) {
    clear;
    header();
    cin.ignore();

    if (nFacturas >= FACTURASMAX) {
        cout << "NO SE PUEDEN EMITIR MÁS FACTURAS (MEMORIA LLENA)" << endl;
        sleep(2);
        return;
    }

    string nombreResponsableBusqueda;
    cout << "Introduce el nombre del responsable: ";
    getline(cin, nombreResponsableBusqueda);

    // Buscar alumnos asociados a ese responsable
    int indicesEncontrados[ALUMNOSMAX]; // Guardamos el índice 'i' de los alumnos que coinciden
    int cantidadEncontrados = 0;

    for (int i = 0; i < nAlumnos; i++) {
        if (alumnos[i].nombreResponsable == nombreResponsableBusqueda) {
            indicesEncontrados[cantidadEncontrados] = i;
            cantidadEncontrados++;
        }
    }

    if (cantidadEncontrados == 0) {
        cout << "ERROR: No se ha encontrado ningún responsable con ese nombre." << endl;
        sleep(2);
    } else {
        // Seleccionar alumno si hay varios, o confirmar si hay uno
        int indiceAlumnoSeleccionado = -1;
        
        cout << "\nSe han encontrado los siguientes alumnos para el responsable " << nombreResponsableBusqueda << ":" << endl;
        for (int k = 0; k < cantidadEncontrados; k++) {
            int realIndex = indicesEncontrados[k];
            cout << k + 1 << " - " << alumnos[realIndex].nombres << " " << alumnos[realIndex].apellidos 
                 << " (DNI: " << alumnos[realIndex].dni << ")" << endl;
        }

        int opcionAlumno;
        do {
            cout << "Seleccione el número del alumno para facturar (1-" << cantidadEncontrados << "): ";
            cin >> opcionAlumno;
            if (opcionAlumno < 1 || opcionAlumno > cantidadEncontrados) {
                cout << "Opción inválida." << endl;
            }
        } while (opcionAlumno < 1 || opcionAlumno > cantidadEncontrados);

        indiceAlumnoSeleccionado = indicesEncontrados[opcionAlumno - 1];
        Talumno &alu = alumnos[indiceAlumnoSeleccionado]; // Referencia para escribir menos

        // Generar Factura
        int nuevoNumeroFactura = nFacturas + 1;
        float totalImporte = 0.0;
        int totalClases = alu.nPracticas;

        // Calcular totales
        for (int j = 0; j < alu.nPracticas; j++) {
            totalImporte += alu.clasesRealizadas[j].precioClase;
        }

        // Mostrar Factura en Pantalla (Formato solicitado)
        clear;
        cout << "Autoescuela Campus" << string(19, ' ') << endl;
        cout << "Alicante" << endl;
        cout << "----------------------------------------" << endl;
        cout << endl;
        cout << "Factura nº " << nuevoNumeroFactura << endl;
        cout << "Cliente .: " << alu.nombreResponsable << " responsable " << alu.telefonoResponsable << endl;
        cout << "Alumno . : dni " << alu.dni << " nombre del alumno " << alu.nombres << endl;
        cout << endl;
        cout << "Fecha " << string(10, ' ') << "km" << string(8, ' ') << " precio" << endl;
        cout << "----------" << string(5, ' ') << "---" << string(7, ' ') << " ------" << endl;

        for (int j = 0; j < alu.nPracticas; j++) {
            Tfecha f = alu.clasesRealizadas[j].fechaPractica;
            cout << setfill('0') << setw(2) << f.dia << "-" << setw(2) << f.mes << "-" << f.año << setfill(' '); // Fecha
            cout << string(5, ' ') << setw(3) << alu.clasesRealizadas[j].kmRecorridos; // Km
            cout << string(7, ' ') << fixed << setprecision(2) << setw(6) << (float)alu.clasesRealizadas[j].precioClase << endl; // Precio
        }

        cout << string(17, ' ') << string(20, ' ') << "---------" << endl;
        cout << totalClases << " clases" << string(3, ' ') << " Total importe  " << fixed << setprecision(2) << totalImporte << endl;
        cout << endl;
        cout << "----------------------------------------" << endl;

        // Guardar la factura en la estructura
        facturas[nFacturas].idFactura = nuevoNumeroFactura;
        facturas[nFacturas].nombreCliente = alu.nombreResponsable;
        facturas[nFacturas].numClases = totalClases;
        facturas[nFacturas].importeTotal = totalImporte;
        nFacturas++;

        cout << "\nFactura emitida y guardada correctamente. Pulsa Enter para continuar.";
        cin.ignore();
        cin.get();
    }
}

void listarFacturas(Tfactura facturas[], int nFacturas) {
    clear;
    header();
    cout << "LISTADO DE FACTURAS EMITIDAS" << endl;
    cout << endl;
    
    cout << "Factura  responsable " << string(13, ' ') << "clases     importe" << endl;
    cout << "-------  ---------------- " << string(5, ' ') << "------    --------" << endl;

    float sumaTotalImportes = 0.0;
    
    for(int i = 0; i < nFacturas; i++) {
        cout << setw(7) << facturas[i].idFactura << "  ";
        // Ajustamos el nombre para que no rompa la tabla, cortamos si es muy largo o rellenamos
        string nombreMostrar = facturas[i].nombreCliente;
        if(nombreMostrar.length() > 16) nombreMostrar = nombreMostrar.substr(0, 16);
        cout << left << setw(16) << nombreMostrar << right;
        cout << string(9, ' ') << setw(2) << facturas[i].numClases;
        cout << string(5, ' ') << fixed << setprecision(2) << setw(8) << facturas[i].importeTotal << endl;

        sumaTotalImportes += facturas[i].importeTotal;
    }

    cout << "-------  ---------------- " << string(5, ' ') << "------    --------" << endl;
    cout << setw(7) << nFacturas << " facturas" << string(19, ' ') << "total   " << fixed << setprecision(2) << setw(9) << sumaTotalImportes << endl;

    cout << "\nPulsa enter para salir.";
    cin.ignore();
    cin.get();
    clear;
}
// --- Fin Funciones examen ----------------------------------------------------------------------------------------------------------------------------------


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
            cout << "RANGO INVÁLIDO" << endl;
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
            cout << "1 - " << setw(5) << "Dar de alta a un vehículo nuevo" << endl;
            cout << "2 - " << setw(5) << "Dar de baja a un vehículo" << endl;
            cout << "3 - " << setw(5) << "Modificar datos de un vehículo" << endl;
            cout << "0 - " << setw(5) << "Salir" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Introduzca una opción: ";

            cin >> opcion;

            if((opcion < 0) || (opcion > 3)){
                cout << "RANGO INVÁLIDO" << endl;
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
                modificarVehiculo(vehiculos, nVehiculos );
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

void menuListas(Talumno alumnos[], int nAlumnos , Tvehiculo vehiculos[], int nVehiculos){
    int opcion;

    clear;
//While true es para que al salir de cualquiera de las listas vuelva a repetir el menu hasta que se envie un 0
    do{
        do{
            header();
            cout << "1 - " << setw(5) << "Mostrar alumnos" << endl;
            cout << "2 - " << setw(5) << "Mostrar vehículos" << endl;
            cout << "0 - " << setw(5) << "Salir" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Introduzca una opción: ";

            cin >> opcion;

            if((opcion < 0) || (opcion >= 3)){
                cout << "RANGO INVÁLIDO" << endl;
                sleep(1);
                cout << "INTENTE DE NUEVO" << endl;
                sleep(1);
                clear;
            }else{
                switch(opcion){
                    case 1:
                        mostrarAlumnos(alumnos, nAlumnos);
                        break;
                    case 2: 
                        mostrarVehiculos(vehiculos, nVehiculos);
                        break;
                }
            }
        }while((opcion < 0) || (opcion > 2));
    }while(true && opcion!=0);    

}

// --- NUEVO: Menú para facturación ---
void menuFacturas(Talumno alumnos[], int nAlumnos, Tfactura facturas[], int &nFacturas) {
    int opcion;
    do {
        clear;
        header();
        cout << "1 - Emitir factura" << endl;
        cout << "2 - Listado de facturas" << endl;
        cout << "0 - Salir" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Introduzca una opción: ";
        cin >> opcion;

        if (opcion < 0 || opcion > 2) {
            cout << "RANGO INVÁLIDO" << endl;
            sleep(1);
        } else {
            switch(opcion) {
                case 1:
                    emitirFactura(alumnos, nAlumnos, facturas, nFacturas);
                    break;
                case 2:
                    listarFacturas(facturas, nFacturas);
                    break;
                case 0:
                    break;
            }
        }

    } while (opcion != 0);
    clear;
}
// ------------------------------------

int menu(){
    int opcion=0;
    clear;

    header();
    cout << "1 - " << setw(5) << "Gestionar alumnos" << endl;
    cout << "2 - " << setw(5) << "Gestionar vehículos" << endl;
    cout << "3 - " << setw(5) << "Dar de alta una clase" << endl;
    cout << "4 - " << setw(5) << "Mostrar listas" << endl;
    // --- NUEVO: Opción 5 ---
    cout << "5 - " << setw(5) << "Gestionar facturas" << endl;
    // -----------------------
    cout << "0 - " << setw(5) << "Salir" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Introduzca una opción: ";
    cin >> opcion; 
    if((opcion < 0) || (opcion > 5)){ // Corregido a 5
        cout << "RANGO INVÁLIDO" << endl;
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

//Ejemplos para probar el codigo
// --- FUNCIÓN PARA CARGAR DATOS DE PRUEBA AUTOMÁTICAMENTE ---
void cargarDatosDePrueba(Talumno alumnos[], int &nAlumnos, Tvehiculo vehiculos[], int &nVehiculos) {
    // ALUMNO 1 (DNI válido: 12345678Z)
    alumnos[nAlumnos].dni = "12345678Z";
    alumnos[nAlumnos].nombres = "Daniel";
    alumnos[nAlumnos].apellidos = "Iliev Arkhipov";
    alumnos[nAlumnos].numeroTelefono = "+34 600111222";
    // --- NUEVO ---
    alumnos[nAlumnos].nombreResponsable = "Padre Daniel";
    alumnos[nAlumnos].telefonoResponsable = "600000001";
    // -------------
    alumnos[nAlumnos].nPracticas = 0;
    nAlumnos++;

    // ALUMNO 2 (DNI válido: 11111111H)
    alumnos[nAlumnos].dni = "11111111H";
    alumnos[nAlumnos].nombres = "Carlos";
    alumnos[nAlumnos].apellidos = "Hernandez Fernandez";
    alumnos[nAlumnos].numeroTelefono = "+34 600333444";
    // --- NUEVO ---
    alumnos[nAlumnos].nombreResponsable = "Madre Carlos";
    alumnos[nAlumnos].telefonoResponsable = "600000002";
    // -------------
    alumnos[nAlumnos].nPracticas = 0;
    nAlumnos++;

    // ALUMNO 3 (DNI válido: 22222222J)
    alumnos[nAlumnos].dni = "22222222J";
    alumnos[nAlumnos].nombres = "Sergio";
    alumnos[nAlumnos].apellidos = "Paya Romero";
    alumnos[nAlumnos].numeroTelefono = "+34 600555666";
    // --- NUEVO ---
    alumnos[nAlumnos].nombreResponsable = "Padre Daniel"; // Pongo el mismo que Daniel para probar búsquedas múltiples
    alumnos[nAlumnos].telefonoResponsable = "600000001";
    // -------------
    alumnos[nAlumnos].nPracticas = 0;
    nAlumnos++;

    // VEHICULO 1 (Coche - Disponible)
    vehiculos[nVehiculos].matricula = "1234ABC";
    vehiculos[nVehiculos].marca = "Toyota";
    vehiculos[nVehiculos].modelo = "Yaris";
    vehiculos[nVehiculos].tipoVehiculo = 0; // Coche
    vehiculos[nVehiculos].kilometraje = 50000.5;
    vehiculos[nVehiculos].estado = 1; // Disponible
    nVehiculos++;

    // VEHICULO 2 (Moto - Mantenimiento)
    vehiculos[nVehiculos].matricula = "5678DEF";
    vehiculos[nVehiculos].marca = "Yamaha";
    vehiculos[nVehiculos].modelo = "MT-07";
    vehiculos[nVehiculos].tipoVehiculo = 1; // Moto
    vehiculos[nVehiculos].kilometraje = 12000.0;
    vehiculos[nVehiculos].estado = 0; // Mantenimiento
    nVehiculos++;

    // VEHICULO 3 (Camión - Disponible)
    vehiculos[nVehiculos].matricula = "9012GHI";
    vehiculos[nVehiculos].marca = "Volvo";
    vehiculos[nVehiculos].modelo = "FH16";
    vehiculos[nVehiculos].tipoVehiculo = 2; // Camión
    vehiculos[nVehiculos].kilometraje = 150000.0;
    vehiculos[nVehiculos].estado = 1; // Disponible
    nVehiculos++;

    // --- AÑADIDO: EJEMPLOS DE CLASES PRÁCTICAS ---

    // Práctica 1: Daniel (Alumno index 0) hace práctica con el Toyota (Vehículo index 0)
    int idAlum1 = 0; 
    int idVeh1 = 0;
    alumnos[idAlum1].clasesRealizadas[0].matricula = vehiculos[idVeh1].matricula;
    alumnos[idAlum1].clasesRealizadas[0].fechaPractica.dia = 10;
    alumnos[idAlum1].clasesRealizadas[0].fechaPractica.mes = 5;
    alumnos[idAlum1].clasesRealizadas[0].fechaPractica.año = 2024;
    alumnos[idAlum1].clasesRealizadas[0].fechaPractica.hora = 11;
    alumnos[idAlum1].clasesRealizadas[0].fechaPractica.minutos = 30;
    alumnos[idAlum1].clasesRealizadas[0].duracionPractica = 45;
    alumnos[idAlum1].clasesRealizadas[0].precioClase = 30;
    alumnos[idAlum1].clasesRealizadas[0].kmRecorridos = 15.5;
    alumnos[idAlum1].nPracticas++; 
    vehiculos[idVeh1].kilometraje += 15.5; // Actualizamos el KM del coche

    // Práctica 2: Carlos (Alumno index 1) hace práctica con el Camión (Vehículo index 2)
    int idAlum2 = 1;
    int idVeh2 = 2;
    alumnos[idAlum2].clasesRealizadas[0].matricula = vehiculos[idVeh2].matricula;
    alumnos[idAlum2].clasesRealizadas[0].fechaPractica.dia = 12;
    alumnos[idAlum2].clasesRealizadas[0].fechaPractica.mes = 6;
    alumnos[idAlum2].clasesRealizadas[0].fechaPractica.año = 2024;
    alumnos[idAlum2].clasesRealizadas[0].fechaPractica.hora = 16;
    alumnos[idAlum2].clasesRealizadas[0].fechaPractica.minutos = 00;
    alumnos[idAlum2].clasesRealizadas[0].duracionPractica = 60;
    alumnos[idAlum2].clasesRealizadas[0].precioClase = 50;
    alumnos[idAlum2].clasesRealizadas[0].kmRecorridos = 40.0;
    alumnos[idAlum2].nPracticas++;
    vehiculos[idVeh2].kilometraje += 40.0; // Actualizamos el KM del camión

    cout << ">>> DATOS DE PRUEBA Y CLASES CARGADOS CORRECTAMENTE <<<" << endl;
    sleep(1);
}

//Función main------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    //Listas de los distintos objetos
    Talumno alumnos[ALUMNOSMAX];
    Tvehiculo vehiculos[VEHICULOSMAX];
    Tpractica practicas[PRACTICASMAX];
    
    // --- NUEVO: Array de facturas y contador ---
    Tfactura facturas[FACTURASMAX];
    int nFacturas = 0;
    // -------------------------------------------

    int opcion, nAlumnos = 0, nVehiculos=0, nClases=0;
    cargarDatosDePrueba(alumnos, nAlumnos, vehiculos, nVehiculos);
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
                darDeAltaClase(alumnos, nAlumnos, vehiculos, nVehiculos);
                break;
            }
            case 4:{
                menuListas(alumnos, nAlumnos,vehiculos, nVehiculos);
                break;
            }
            // --- NUEVO: Case 5 ---
            case 5: {
                menuFacturas(alumnos, nAlumnos, facturas, nFacturas);
                break;
            }
            // ---------------------
        }
    }while(opcion != 0);
    return 0;
}
//Función main--------------------------------------------------------------------------------------------------------------------------------------------------