#include <iostream>
#include <string>
#include <fstream>




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
 void estadisticas(); // Debe mostrar las estadisticas
};

//Función hash
int registro_cuentas::hash(std::string rol){
    
    unsigned long index = 0; 
    for(int i = 0; i < 10; i++){
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
    std::cout << "Index final: " << index << std::endl;
    std::cout << "Cuenta agregada" << std::endl;

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

    std::cout << "Rol: " << tabla[index].rol << std::endl;
    std::cout << "Nombre: " << tabla[index].nombre << std::endl;
    std::cout << "Descripcion: " << tabla[index].descripcion << std::endl;

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
        std::cout << "No existe la cuenta a eliminar" << std::endl;
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


int main(){

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
