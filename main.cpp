#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/*
AGREGAR QUE IMPRIMA ROL YA EXISTENTE EN LA FUNCION AGREGAR SI ES QUE EXISTE
AGREGAR QUE IMPRIMA ROL NO EXISTENTE EN LA FUNCION QUITAR SI ES QUE NO EXISTE
LO MISMO DE ARRIBA PERO EN LA FUNCION MODIFICAR

Hacer documentacion

Arreglar fin lectura archivo https://discord.com/channels/1215059900179152906/1253182879006068809

Quizas cambiar el manejo de colisiones a algo mas complejo ejemplo: https://discord.com/channels/1215059900179152906/1253459083235819622



*/





struct cuenta {
 // El rol es el identificador de la persona.
 // El nombre y la descripcion son valores asociados al rol
 std::string rol, nombre, descripcion;
};


class registro_cuentas {
 private:


 float FACTOR_CARGA_MAXIMO = 0.75;
 int ranuras_ocupadas = 0;

 float factor_de_carga = 0.0;

 cuenta *tabla; // Aca se almacenaran los elementos de la tabla
 int ranuras = 15; // Cuantas ranuras tiene la tabla hash (inicialmente)

 int hash(std::string rol); // Se obtiene el hash dado el rol                                                                   LISTO
 int p(std::string rol, int i); // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i                 LISTO
 public:
 registro_cuentas() {
    tabla = new cuenta[ranuras];
 } // (Recuerde que puede crear con distintos parametros)
    ~registro_cuentas() {
        delete[] tabla;
    } // Destructor
 cuenta obtener(std::string rol); // Dado el rol, devuelve la cuenta con ese rol                                               LISTO
 void agregar(cuenta c); // Se agrega una cuenta a la tabla                                                                    LISTO
 void eliminar(std::string rol); // Se elimina la cuenta                                                                       LISTO
 void modificar(std::string rol, std::string descripcion); // Se modifica la descripcion del rol                               LISTO
 void redimensionar(int n); // Se redimensiona la tabla a n espacios                                                           LISTO
 void estadisticas(); // Debe mostrar las estadisticas                                                                         LISTO
};

//Función hash
int registro_cuentas::hash(std::string rol){
    
    unsigned long index = 0; 
    int longitud = rol.length();
    for(int i = 0; i < longitud; i++){
        index += rol[i];
    }
    
    index = index % ranuras;
    return index;
}




//Caso de colisión cuadrática
int registro_cuentas::p(std::string rol, int i){
    
    int hash_inicial = hash(rol);
    return (hash_inicial + i * i) % ranuras;
}


//Funcion para agregar una cuenta
void registro_cuentas::agregar(cuenta c){

    if(factor_de_carga >= FACTOR_CARGA_MAXIMO){
        redimensionar(ranuras * 2);
    }


    int index = hash(c.rol);
    int i = 0;



    while(tabla[index].rol != ""){
        index = p(c.rol, i);
        i++;
    }

    tabla[index].rol = c.rol;
    tabla[index].nombre = c.nombre;
    tabla[index].descripcion = c.descripcion;

    ranuras_ocupadas++;

    factor_de_carga = (float)ranuras_ocupadas / (float)ranuras;


}







//Funcion para redimensionar la tabla
void registro_cuentas::redimensionar(int n){
    
    cuenta *tabla_nueva = new cuenta[n];
    for(int i = 0; i < ranuras; i++){
        if(tabla[i].rol != ""){
            int index = hash(tabla[i].rol);
            int j = 0;
            while(tabla_nueva[index].rol != ""){
                index = p(tabla[i].rol, j);
                j++;
            }
            tabla_nueva[index] = tabla[i];
        }
    }
    delete[] tabla;
    tabla = tabla_nueva;
    ranuras = n;
    factor_de_carga = (float)ranuras_ocupadas / (float)ranuras;
    
}



//Funcion para obtener una cuenta
cuenta registro_cuentas::obtener(std::string rol){
    
    int index = hash(rol);
    int i = 1;

    while(tabla[index].rol != rol && i <= ranuras){
        index = p(rol, i);
        i++;
    }

    if(tabla[index].rol != rol){
        std::cout << "ROL NO EXISTENTE" << std::endl;
        return tabla[index];
    }

    std::cout << tabla[index].nombre << " " << tabla[index].descripcion << std::endl;
    
    return tabla[index];
}


//Funcion para eliminar una cuenta
void registro_cuentas::eliminar(std::string rol){
    
    int index = hash(rol);
    int i = 1;

    while(tabla[index].rol != rol && i <= ranuras){
        index = p(rol, i);
        i++;
    }

    if(tabla[index].rol != rol){
        return;  
    }



    tabla[index].rol = "";
    tabla[index].nombre = "";
    tabla[index].descripcion = "";
    ranuras_ocupadas--;
    return;

}

//Modificar la descripcion de una cuenta
void registro_cuentas::modificar(std::string rol, std::string descripcion){
    
    int index = hash(rol);
    int i = 1;

    while(tabla[index].rol != rol && i <= ranuras){
        index = p(rol, i);
        i++;
    }

    if(tabla[index].rol != rol){
        
        return;  
    }

    
    
    tabla[index].descripcion = descripcion;
    
    return;

}

//Funcion para mostrar estadisticas 
void registro_cuentas::estadisticas(){
    std::cout << "RANURAS OCUPADAS: " << ranuras_ocupadas << std::endl;
    std::cout << "RANURAS TOTALES: " << ranuras << std::endl;
    std::cout << "FACTOR DE CARGA: " << factor_de_carga << std::endl;
    return;
}



/*****
* void leer_instrucciones
******
*  Lee las instrucciones de un archivo de texto y las almacena en un arreglo de strings.
******
* Input: 
* std::string nombre_archivo : Nombre del archivo de texto que contiene las instrucciones.
* std::string *&instrucciones : Referencia a un puntero de string donde se almacenarán las instrucciones.
* int &numInstrucciones : Referencia a un entero donde se almacenará el número de instrucciones.
*  
******
* Returns: Nada, pero almacena las instrucciones en un arreglo de strings.
* 
*****/

void leer_instrucciones(std::string nombre_archivo, std::string *&instrucciones, int &numInstrucciones){
    #include <fstream>
    std::ifstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            numInstrucciones++;
        }
        archivo.clear(); // Restablecer el puntero del archivo al inicio
        archivo.seekg(0, std::ios::beg); // Mover el puntero del archivo al inicio

        // Reservar memoria para el arreglo de instrucciones
        instrucciones = new std::string[numInstrucciones];

        // Leer las instrucciones del archivo y almacenarlas en el arreglo
        int i = 0;
        while (std::getline(archivo, linea)) {
            instrucciones[i++] = linea;
        }

        archivo.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << std::endl;
    }

}



/*****
* void instrucciones
******
*  Lee las instrucciones de un archivo de texto y las ejecuta sobre la clase registro_cuentas.
******
* Input: std::string nombre_archivo : Nombre del archivo de texto que contiene las instrucciones.
*  
******
* Returns: Nada, pero ejecuta las instrucciones sobre la clase registro_cuentas.
* 
*****/

void instrucciones(std::string nombre_archivo){
    std::string *instrucciones;
    int numInstrucciones = 0;
    leer_instrucciones(nombre_archivo, instrucciones, numInstrucciones);
    registro_cuentas accion;
    for (int i = 0; i < numInstrucciones; i++) {
        std::string instruccion = instrucciones[i];
        std::istringstream ss(instruccion);
        std::string comando;
        ss >> comando;
        if (comando == "AGREGAR") {
            std::string rol, nombre, descripcion;
            ss >> rol >> nombre >> descripcion;
            accion.agregar({rol, nombre, descripcion});

            
        } else if (comando == "QUITAR") {
            std::string rol;
            ss >> rol;
            accion.eliminar(rol);

        } else if (comando == "MODIFICAR") {
            std::string rol, descripcion;
            ss >> rol >> descripcion;
            accion.modificar(rol, descripcion);

        } else if (comando == "OBTENER") {
            std::string rol;
            ss >> rol;
            accion.obtener(rol);

        } else if (comando == "ESTADISTICAS") {
            accion.estadisticas();

        } else if (comando == "FIN") {
            break;
        }
    }
    delete[] instrucciones;
}

int main(){
    
    instrucciones("prueba.txt");


    //despues eliminar todo lo de abajo. solo son para probar


    registro_cuentas registro;
    cuenta c1;
    c1.rol = "12345678-9";
    c1.nombre = "Juan Perez";
    c1.descripcion = "Estudiante";
    registro.agregar(c1);
    registro.obtener("12345678-9");


    
    c1.rol = "12345679-8";
    c1.nombre = "Pedro Perez";
    c1.descripcion = "Profesor";
    registro.agregar(c1);
    registro.obtener("12345679-8");

    registro.eliminar("12345679-8");
    registro.obtener("12345679-8");


    return 0;

}
