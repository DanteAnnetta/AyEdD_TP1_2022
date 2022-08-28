#include <iostream>
#include <fstream>

using namespace std;

//funcion que se encarga de ordenar los arreglos acorde los valores del primero sean ascendentes
void ordenar_doble(float datos[] , int indices[] , int dim){
  float piv;
  int pivind;
  for (int i = 0 ; i < dim ; i++){
    for (int j = i + 1 ; j < dim ; j++){
      if (datos[i] > datos[j]){
	piv = datos[i];
	pivind = indices[i];
	datos[i] = datos[j];
	indices[i] = indices[j];
	datos[j] = piv;
	indices[j] = pivind;
      }
    }
  }
}



int main(){
  // estructuras de datos

  float distancias[8][5];
  float pesos[8][5];
  int entrxprod[] {0 , 0 , 0 , 0 , 0};
  

  // para que funcione correctamente, todos sus valores tienen que empezar siendo nulos

  for (int i = 0; i < 8 ; i++){

    for (int j = 0; j < 5 ; j++){
      pesos[i][j] = 0;
      distancias[i][j] = 0;

    }

  }
  
  int cli;
  int prod;
  float pes;
  float dist;

  
  // Se cargan los datos del archivo de nombres
  ifstream file1;
  file1.open("Nombres.txt");
  string pal;
  string venom[13];
  
  if(!file1){
    cout << "Error: no se pudo abrir el archivo Nombres.txt" << endl;
    return 1;
  }
  
  int count = 0;
  while(file1 >> pal){
    venom[count] = pal;
    count++;
  }
  file1.close();

  // Se leen los datos de archivo de datos

  file1.open("Datos.txt");
  if(!file1){
    cout << "Error: no se pudo abrir el archivo Datos.txt" << endl;
    return 1;
  }
  while(file1 >> cli >> prod >> pes >> dist){
    pesos[cli][prod] = pesos[cli][prod] + pes;
    distancias[cli][prod] = distancias[cli][prod] + dist; 
    entrxprod[prod] = entrxprod[prod] + 1;
  }
  
  file1.close();

  // ________________INICIO DE LA PARTE 1____________________________
  cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: " << endl;
  int pesados[5];
  int npesados;
  int maspesados = 0;
  int clientepesado;
  for (int c = 0 ; c < 8 ; c++){

    for (int i = 0 ; i < 5 ; i++){
      pesados[i] = 0;
    }
    
    npesados = 0;
    cout << venom[c] << ": ";
    
    for (int p = 0 ; p < 5 ; p++){
      
      if(pesos [c][p] > 13000){
	//cout << venom[p + 8] << ", ";
	pesados[npesados] = p;
	npesados ++;
	
      }
      
    }

    if(maspesados < npesados ){
      maspesados = npesados;
      clientepesado = c;
    }


    for (int i = 0 ; i < npesados + 1 ; i++){

      if (i == npesados && npesados != 0){
	cout << venom[pesados[i] + 8];
      }
      else{
	cout << venom[pesados[i] + 8 ] << ", "; 
      }

    }
    
    cout << endl;
  }

  cout << endl;
  //____________________________FINAL DE LA PARTE 1___________________________________
  //____________________________Parte2________________________________________________

  float distcli[5];
  int indiceprod[5];
  
  for (int i = 0 ; i < 5 ; i++){
    distcli[i] = distancias[clientepesado][i];
    indiceprod[i] = i;
  }

  ordenar_doble(distcli , indiceprod , 5);

  cout << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;
  int masentregas;
  for (int i = 0; i < 5 ; i++){
    cout << venom [8 + indiceprod[i]] << ": " << distcli[i] << endl;
    masentregas = 8 + indiceprod[i];
  }
  
  // parte 3
  cout << endl;
  cout << "Cantidad de entregas para el producto " << venom[masentregas] << ": " <<  entrxprod[masentregas - 8       ]    << endl;
  
  
  return 0;
}

