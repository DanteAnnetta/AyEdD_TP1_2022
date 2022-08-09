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

    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;

    float pesoprod;
    string product;
    bool tieneprods;
    int nprods;
    int results[] {0 , 0};
    float dist[8][5]; // (parte 2): en esta matriz se almacenarán los datos de la distancia de cada producto para cada cliente
    float ndis;

    for (int client ; client < 8 ; client ++){ // bucle de cada cliente
        // si tiene al menos un producto con entregas mayores a los 13000 kg:
        tieneprods = true;

        nprods = 0; // (parte 2): se pone en 0 el contador de productos

        for (int prod = 0; prod < 5 ; prod++){ // bucle de cada producto
            pesoprod = 0;
            ndis = 0;
            for (int i = 0; i < indxf + 1 ; i++){ // se lee linea a linea la matriz 

                if (client == data[i][0] && prod == data[i][1]){ // para que muestre una linea de data tiene que corresponder a un cliente  pero tambien tiene que corresponder a un producto
                    pesoprod = pesoprod + data[i][2];
                    ndis = ndis + data[i][3];
                    //cout<< "    -" << nombres[ data[i][1] + 8  ]<< "       Peso[kg]: " << data[i][2]<< "       Distancia[km]: " << data[i][3] << endl;
                    product = nombres[ data[i][1] + 8  ];
                }
                
            }

            dist[client][prod] = ndis; // (parte 2): se le asigna el valor de la distancia a la matriz de acuerdo al cliente y al producto

            if (pesoprod > 13000){ // el nombre del cliente se imprime desde acá y no arriba, ya que solo importan los clientes que superan
                if (tieneprods == true){ // los 13000kg en sus entregas
                    cout << nombres[client] << ": ";
                    
                }
                else{
                    cout << ", ";
                }
                tieneprods = false;
                //cout << "       Peso de productos " << product << " transportados: " << pesoprod << " kg."<< endl;
                cout << product;
                nprods ++; // (parte 2): se cuenta la cantidad de productos de cada cliente
            }
            

        }
        if (nprods > results[1]){
            results[0] = client; // (parte 2): el numero de cliente es el primer valor de la array
            results[1] = nprods; // (parte 2): cuando se cambia de cliente se termina de armar la array
        }
        
        cout << endl;
    }

   //__________PARTE 1__________


   //__________PARTE 2__________
   /*Consigna: Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto 
     anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos, 
     ordenado por total de kilómetros en forma ascendente.
    Nota: No alterar el vector de nombres.*/

  // PD: ¿qué pasaría en el caso de que dos o más clientes estén empatados en la cantidad de tipos de producto superior a los 13000 kg?
  // lo lógico sería intentar "desempatarlos" de alguna forma, pero sin embargo es difícil encontrar un criterio correcto para hacerlo.

    cout << endl;
    cout << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;

    // nuevamente, se puede aprovechar el código de la parte 1: el recorrido de la matriz de datos se da en el formato producto a producto,
    // cliente a cliente, por lo que se puede armar una nueva matriz en la que las filas correspondan a los clientes y las columnas a las distancias
    // que se recorren en las entregas de cada producto, haciendo que en esta sección se encargue de parsear la fila indicada por results[0]

    // para esta parte 2, una vez teniendo la matriz de distancias, hay que ordenar los valores de forma ascendiente
    
    
    // una vez deducido que cliente es el que tiene más cantidad de "grandes entregas", se buscaran únicamente sus datos en la matriz de datos

    float maskm = 0;
    int cod; // el codigo del producto que tiene más km recorridos


    for (int i = 0 ; i < 5 ; i++){
        if (dist[results[0]][i] > maskm){
            maskm = dist[results[0]][i];
            cod = i;
        }
    }



    // se ordena la columna correspondiente al cliente con los datos de menor a mayor.(algoritmo burbuja)
    // aprovechando este algoritmo, se ordena un arreglo con los codigos de producto de la misma forma que dicha columna, de modo tal que 
    // cuando se impriman por consola los datos, siga existiendo un indicador de que producto se trata

    int ind[5];

    for (int i = 0; i < 5 ; i++){
        ind[i] = i;
    }

    // este algoritmo funciona casi bien: los códigos de cada producto son correctos, pero el ordenamiento confunde dos posiciones
    float aux;
    int indaux;
    for (int i = 0 ; i < 5 ; i++){

        for(int j = i + 1 ; j < 5 ; j++){
            if(dist[results[0]][i] > dist[results[0]][j]){
                aux = dist[results[0]][i];
                indaux = ind[i];
                ind[i] = ind[j];
                ind[j] = indaux;
                dist[results[0]][i] = dist[results[0]][j];
                dist[results[0]][j] = aux;
            }
        }

    }


    for (int i = 0 ; i < 5 ; i++){
        cout << nombres[ind[i] + 8] << ": " << dist[results[0]][i] << endl;
        //cout << dist[results[0]][i] << endl;
    }



 


   //__________PARTE 2__________

   //__________PARTE 3__________
   /*Consigna: Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e 
     informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente).*/
    
     // este codigo funciona perfecto, si el resultado es erróneo, el bug está en la obtención de la variable cod
    int n = 0;
    
    for (int i = 0; i < indxf + 1 ; i++){
        if (data[i][1] == cod){ // si el codigo de producto es igual al obtenido anteriormente se suma una entrega a la cantidad total
            n++;
        }
    }

    cout << endl;
    cout << "Cantidad de entregas para el tipo de producto " << nombres[cod + 8 ] << ": " << n << endl;
   //__________PARTE 3__________
    return 0;
}