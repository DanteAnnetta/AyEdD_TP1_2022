#include <iostream>
#include <fstream>
#include <vector>
/*

Posibles features para un futuro (suponiendo de que sean legales):
    -utilizacion de punteros de espacio de memoria: en este código hay muchas variables "descartables",
    si se utilizan punteros de espacio de memoria, cuando termina la vida útil de la variable se la puede
    liberar haciendo que el código sea mucho mas eficiente. Esto sería despreciable cuando se trabaja con
    variables unitarias, pero como la matriz de datos es del tipo string (ahora mismo podría ser float para ser mas ligera), 
    hay que convertir todos los datos o a int o a float, lo que es totalmente ineficiente ya que queda en memoria una matriz 
    que desperdicia memoria y no se usa mas.  CON LA CREACION DE NUEVAS MATRICES ES ALGO QUE VALDRÁ LA PENA HACER
*/

using namespace std;


int main(){

//SE GENERA EL VECTOR DE NOMBRES_________________________________________________________

    // A partir de aqui, el archivo de nombres pasa a indicar los tipos de productos (es dato)
    //const int clientes = 7; 

    ifstream file1;
    file1.open("Nombres.txt");
    if (!file1){
        cout << "Error: no such file Nombres.txt" << endl;
        return 1;
    }

    
    string line;
    vector <string> nombres;
    while (file1 >> line){
        nombres.push_back(line);
    }

    /*
    for (int i = 0 ; i < nombres.size() ; i++){ // Test del vector de nombres
        cout << nombres[i] << endl;
    }
    */

    file1.close();


// _________________________________________________________

    // SE PROCESAN LOS DATOS DE LAS ENTREGAS (Datos.txt)

    file1.open("Datos.txt");

    if (!file1){
        cout << "Error: no such file Datos.txt" << endl;
        return 1;
    }
    
    int lin = 1;
    while (getline(file1, line)){
        lin++;
    }

    // evitar esto, porque implica enviar los datos del disco al buffer dos veces
    // esto tiene que ser corregido si o si para la versión final
    //___________________________________________________________________________
    file1.close();
    file1.open("Datos.txt");
    //___________________________________________________________________________


    // a medida de que se lee el archivo (por segunda vez), se va procesando en una matriz de floats
    // esto no alcanza a ser lo más eficiente del mundo, pero sin mebargo es mejor que una matriz de 
    // strings, ya que se ocupa menos memoria que si fuesen caracteres

    float data [lin][4];
    int indxf = 0;
    int indxc = 0;
    // ir dato a dato no es lo mas efiicente, pero permite separar los datos con 
    // mucha mas facilidad
    while(file1 >> line){  // funciona correctamente (verificado)
        if (indxc == 4){
            indxc = 0;
            indxf++;
        }

        data[indxf][indxc] = stof(line);
        indxc++;
    }

    file1.close(); // ya no se trabajará más con el archivo de datos

   

   // hasta este punto de acá, se obtuvo un vector con los nombres y una matriz de datos convertidos a float, 
   // lo que permite realizar operaciones matemáticas (no de la forma más eficiente posible) entre los distintos valores

   /*
   Nomenclatura de los datos:
    1. Código de Cliente. Un entero que va de 0 a 7.
    2. Código de Tipo de Producto. Un entero que va de 0 a 4.
    3. Peso total transportado, en Kg con decimales.
    4. Distancia recorrida, en Km con decimales.
   */

   //__________PARTE 1__________
   /* Consigna: Emita un listado donde para cada cliente liste los tipos de producto tal que la cantidad total de 
      kilos transportados es mayor a 13000.*/

    // Esto ordena la matriz de datos primero por cliente y luego por tipo de producto, haciendo que sea mucho más sencillo 
    // visualizar la información

    cout << "__________PARTE 1__________" << endl;

    float pesoprod;
    string product;

    for (int client ; client < 8 ; client ++){ // bucle de cada cliente
        cout << endl;
        cout << "Entregas del cliente: " << nombres[client] << endl;
        cout << endl;

        for (int prod = 0; prod < 5 ; prod++){ // bucle de cada producto
            pesoprod = 0;
            for (int i = 0; i < indxf + 1 ; i++){ // se lee linea a linea la matriz 

                if (client == data[i][0] && prod == data[i][1]){ // para que muestre una linea de data tiene que corresponder a un cliente  pero tambien tiene que corresponder a un producto
                    pesoprod = pesoprod + data[i][2];
                    //cout<< "    -" << nombres[ data[i][1] + 8  ]<< "       Peso[kg]: " << data[i][2]<< "       Distancia[km]: " << data[i][3] << endl;
                    product = nombres[ data[i][1] + 8  ];
                }
                
            }

            if (pesoprod > 13000){
                cout << "       Peso de productos " << product << " transportados: " << pesoprod << " kg."<< endl;
            }
            

        }


    }
    
    cout << "__________PARTE 1__________" << endl;



   //__________PARTE 1__________


   //__________PARTE 2__________
   /*Consigna: Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto 
     anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos, 
     ordenado por total de kilómetros en forma ascendente.
    Nota: No alterar el vector de nombres.*/






   //__________PARTE 2__________

   //__________PARTE 3__________
   /*Consigna: Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e 
     informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente).*/


   //__________PARTE 3__________
    return 0;
}