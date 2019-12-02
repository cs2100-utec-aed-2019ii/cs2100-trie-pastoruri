#include <iostream>
#include "Tries.h"

int main() {
    Trie t;
    //t.ejercicio1(200); //le pasas la cantidad de ips a generar y te bota una ip de ejemplo para que pruebes el comando.
    //t.ejercicio2(); // insertas fila tras fila de cadenas de 0's y 1's y te dice las repetidas
    // t.ejercicio3(); // se inserta las palabras con t.insert y se ejecuta esta función, te devolvera las palabras con frecuencia mayor que la media.

    t.insert("hola");
    t.insert("hola");
    t.insert("homero");
    t.insert("aaossss");
    t.insert("ashjdhjo");
    t.insert("hol");
    t.insert("sim");


   // t.ejercicio5("ho"); Una vez insertadas varias palabras, le pasas otra palabra a esta funcion y te devolvera las palabras en el diccionario que tienen las letras de la palabra pasada en el mismo orden en cualquier configuración.



    return 0;
}