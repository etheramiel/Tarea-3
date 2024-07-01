#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


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

 int hash(std::string rol); // Se obtiene el hash dado el rol                                                                   
 int p(std::string rol, int i); // Se otiene la ranura a revisar en caso de colisión dado el rol y el intento i                 
 public:
 registro_cuentas() {
    tabla = new cuenta[ranuras];
 } // (Recuerde que puede crear con distintos parametros)
    ~registro_cuentas() {
        delete[] tabla;
    } // Destructor
 cuenta obtener(std::string rol); // Dado el rol, devuelve la cuenta con ese rol                                               
 void agregar(cuenta c); // Se agrega una cuenta a la tabla                                                                   
 void eliminar(std::string rol); // Se elimina la cuenta                                                                       
 void modificar(std::string rol, std::string descripcion); // Se modifica la descripcion del rol                               
 void redimensionar(int n); // Se redimensiona la tabla a n espacios                                                           
 void estadisticas(); // Debe mostrar las estadisticas                                                                         
};

/*****
* int registro_cuentas::hash
******
*  Obtiene el hash dado el rol.
******
* Input: 
* std::string rol : Rol de la cuenta a agregar.
*  
******
* Returns:
* int : Hash del rol.
* 
*****/
int registro_cuentas::hash(std::string rol){
    
    unsigned long index = 0; 
    int longitud = rol.length();
    for(int i = 0; i < longitud; i++){
        index += rol[i];
    }
    
    index = index % ranuras;
    return index;
}




/*****
* int registro_cuentas::p
******
*  Obtiene la ranura a revisar en caso de colisión dado el rol y el intento i.
******
* Input: 
* std::string rol : Rol de la cuenta a agregar.
* int i : Intento de colisión.
*  
******
* Returns:
* int : Ranura a revisar en caso de colisión.
* 
*****/
int registro_cuentas::p(std::string rol, int i){
    
    return (hash(rol) + i) % ranuras;

}


/*****
* void registro_cuentas::agregar
******
*  Agrega una cuenta a la tabla hash.
******
* Input: 
* cuenta c : Cuenta a agregar.
*  
******
* Returns: Nada, pero agrega una cuenta a la tabla hash.
* 
*****/
void registro_cuentas::agregar(cuenta c){

    if(factor_de_carga >= FACTOR_CARGA_MAXIMO){
        redimensionar(ranuras * 1.5);
    }


    int index = hash(c.rol);
    int i = 0;


    if(tabla[index].rol == c.rol){
        std::cout << "ROL YA EXISTENTE" << std::endl;
        return;
    }


    while(tabla[index].rol != ""){
        index = p(c.rol, i);
        i++;
    }

    tabla[index].rol = c.rol;
    tabla[index].nombre = c.nombre;
    tabla[index].descripcion = c.descripcion;

    ranuras_ocupadas++;
    factor_de_carga = static_cast<float>(ranuras_ocupadas) / ranuras;

    return;

}







/*****
* void registro_cuentas::redimensionar
******
*  Modifica la tabla hash a un tamaño n.
******
* Input: 
* int n : Nuevo tamaño de la tabla hash.
*  
******
* Returns: Nada, pero modifica la tabla hash a un tamaño n.
* 
*****/
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
    factor_de_carga = static_cast<float>(ranuras_ocupadas) / ranuras;
    
}



/*****
* void registro_cuentas::obtener
******
*  Obtiene los datos de un rol en la tabla hash.
******
* Input: 
* std::string rol : Rol de la cuenta a obtener.
*  
******
* Returns: 
* cuenta Cuenta con el rol especificado
* 
*****/
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


/*****
* void registro_cuentas::eliminar
******
*  Elimina un rol de la tabla hash.
******
* Input: 
* std::string rol : Rol de la cuenta a eliminar.
*  
******
* Returns: Nada, pero elimina un rol de la tabla hash.
* 
*****/
void registro_cuentas::eliminar(std::string rol){
    
    int index = hash(rol);
    int i = 1;

    while(tabla[index].rol != rol && i <= ranuras){
        index = p(rol, i);
        i++;
    }

    if(tabla[index].rol != rol){
        std::cout << "ROL NO EXISTENTE" << std::endl;
        return;
    }


    delete(&tabla[index].rol);
    tabla[index].rol = "";
    tabla[index].nombre = "";
    tabla[index].descripcion = "";
    ranuras_ocupadas--;
   factor_de_carga = static_cast<float>(ranuras_ocupadas) / ranuras;
    return;

}

/*****
* void registro_cuentas::modificar
******
*  Modifica la descripcion de un rol en la tabla hash.
******
* Input: 
* std::string rol : Rol de la cuenta a modificar.
* std::string descripcion : Nueva descripcion de la cuenta.
*  
******
* Returns: Nada, pero modifica la descripcion de un rol en la tabla hash.
* 
*****/
void registro_cuentas::modificar(std::string rol, std::string descripcion){
    
    int index = hash(rol);
    int i = 1;

    while(tabla[index].rol != rol && i <= ranuras){
        index = p(rol, i);
        i++;
    }

    

    if(tabla[index].rol != rol){
        std::cout << "ROL NO EXISTENTE" << std::endl;
        return;
    }

    
    
    tabla[index].descripcion = descripcion;
    
    return;

}

/*****
* void registro_cuentas::estadisticas
******
*  Muestra las estadisticas de la tabla hash.
******
* Input: 
* Nada
*  
******
* Returns: Nada, pero imprime las estadisticas de la tabla hash.
* 
*****/
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

        }else{
            break;
        }

        
        
    }
    delete[] instrucciones;
}


/*****
* int main
******
*  Función principal del programa que ejecuta las instrucciones de un archivo de texto llamado "prueba.txt".
******
* Input: 
* Nada
*  
******
* Returns:
* int : 0
* 
*****/
int main(){
    instrucciones("prueba.txt");
    return 0;
}
