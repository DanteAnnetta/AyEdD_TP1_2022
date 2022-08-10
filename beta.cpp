#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


int main(){

    // SE PROCESAN LOS DATOS DE LOS NOMBRES (Nombres.txt)

     const int cli = 8; // cantidad de clientes
     const int pd = 5;   // cantidad de productos

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

    file1.close();


    // SE PROCESAN LOS DATOS DE LAS ENTREGAS (Datos.txt)

    file1.open("Datos.txt");

    if (!file1){
        cout << "Error: no such file Datos.txt" << endl;
        return 1;
    }


    int clopd;                  // cliente o producto
    float psodist;              // peso o distancia
    string pal;                 // hacia esta variable está dirigido el flujo del archivo, de modo que dependiendo de lo necesario se convertirá o en int o en float
    int count = 0;              // un contador para saber en que columna acomodar el dato que se está procesando
    int filcount = 1;           // un contador para saber la cantidad de filas 
    int masentregas[] {0 , 0}; // almacena el numero de cliente que tiene más entregas superiores a 13000, junto con la cantidad de las mismas
    vector<int> clients;
    vector<int> products;
    vector<float> peso;
    vector<float> distance;

    while(file1 >> pal){  // el archivo se lee palabra a palabra
        if(count == 4){
            count = 0;
            filcount++;
        }

        switch(count){   // dependiendo de en que columna se encuentre, se agregará al final de uno de estos 4 vectores
            case 0:
                clopd = stoi(pal);
                clients.push_back(clopd);
                break;
            case 1:
                clopd = stoi(pal);
                products.push_back(clopd);
                break;
            case 2:
                psodist = stof(pal);
                peso.push_back(psodist);
                break;
            case 3:
                psodist = stof(pal);
                distance.push_back(psodist);
                break;
            default:
                continue;
                break;
        }

        count++;
    }

    file1.close(); // con estos datos ya procesados de esta forma, el archivo no se necesitará más

    //____________________________FIN DEL PROCESADO DE ARCHIVOS_________________________________

    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;

    bool psds;   // bool "pesados". Cambia de estado si hay al menos un producto con peso mayor a 13000kg por cliente
    int nprods;  // contador de productos
    float psprod;
    float ndis;

    float dist[cli][pd]; // (parte 2): en esta matriz se almacenarán los datos de la distancia de cada producto para cada cliente
    string producto;

    for(int c = 0; c < cli ; c++){ // bucle de cada cliente

        psds = true;
        nprods = 0;
        

        for (int p = 0 ; p < pd ; p++ ){ // bucle de cada producto

            psprod = 0;
            ndis = 0;

            for (int i = 0 ; i < filcount ; i++ ){ // bucle de cada linea de data
                if( clients[i] == c && products[i]== p){
                    psprod = psprod + peso[i];
                    producto = nombres[ products[i] + cli ];
                    ndis = ndis + distance[i];
                    //cout << "    -" << nombres[ products[i] + 8  ]<< "       Peso[kg]: " << peso[i]<< "       Distancia[km]: " << distance[i] << endl;
                }
            }
            dist[c][p] = ndis;

            if(psprod > 13000){
                if(psds == true){
                    cout << nombres[c] << ": ";
                }
                else{
                    cout << ", ";
                }
                psds = false;
                //cout << "       Peso de productos " << product << " transportados: " << pesoprod << " kg."<< endl;
                cout << producto;
                nprods ++; // (parte 2): se cuenta la cantidad de productos de cada cliente

            }

        
        
        if (nprods > masentregas[1]){
            masentregas[0] = c; // (parte 2): el numero de cliente es el primer valor de la array
            masentregas[1] = nprods; // (parte 2): cuando se cambia de cliente se termina de armar la array
        }

        
        
        }

        cout << endl;

    }
    cout << endl;
    cout << "Listado de Km recorridos por tipo de producto (ascendente): " << endl;

    int ind[pd];

    for (int i = 0; i < pd ; i++){
        ind[i] = i;
    }

    float aux;
    int indaux;
    for (int i = 0 ; i < pd ; i++){

        for(int j = i + 1 ; j < pd ; j++){
            if(dist[masentregas[0]][i] > dist[masentregas[0]][j]){
                aux = dist[masentregas[0]][i];
                indaux = ind[i];
                ind[i] = ind[j];
                ind[j] = indaux;
                dist[masentregas[0]][i] = dist[masentregas[0]][j];
                dist[masentregas[0]][j] = aux;
            }
        }

    }

    int cod; // variable que almacena el codigo de producto con mas cantidad de kilometros recorridos
    for (int i = 0 ; i < pd ; i++){
        cout << nombres[ind[i] + cli] << ": " << dist[masentregas[0]][i] << endl;
        cod = ind[i];

    }

    int nentregas = 0; // contador de entregas realizadas

    for (int i = 0; i < filcount + 1; i++){
        if (products[i] == cod){ 
            nentregas++;
        }
    }

    cout << endl;
    cout << "Cantidad de entregas para el tipo de producto " << nombres[cod + cli] << ": " << nentregas << endl;



    return 0;
}
