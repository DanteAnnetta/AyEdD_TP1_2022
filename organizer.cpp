#include <iostream>
#include <vector>

using namespace std;

int main(){
    int data[5] {6 , 5 , 7 , 2 , 0};
    int tam = 5;
    int aux = 0;

    for (int i = 0 ; i < tam ; i++){

        for(int j = i + 1 ; j < tam ; j++){
            if(data[i] > data[j]){
                aux = data[i];
                data[i] = data[j];
                data[j] = aux;
            }
        }

    }

    for (int i = 0 ; i < 5 ; i++){
        cout << data[i] << endl;
    }

    return 0;
}