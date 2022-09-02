#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
// Esta funcion split tomara el string equivalente a un polinomio, y extrae todos sus terminos y exponentes, guardandolos respectivamente en un array de floats
int split(string str, float (&coeficientes)[10], float (&exponentes)[10]){
    // declarando varibales
      string temp = "";
      string temp2 = "";
      int cont = 0;
      str.erase(std::remove(str.begin(),str.end(),' '),str.end());
      // separando string por monomios en un ciclo for hasta que se termine el string, guardando cada caracter "i" en un string temp, hasta que se encuentre los caracteres '+' o '-',
      // en donde si esto ocurre, se procedera a analizar y guardar cada termino en su respectivo array
      for(int i=0; i<(int)str.size()+1; i++){
         if(str[i] != '+' && str[i] != '-' && i != (int)str.size() || i==0){
            temp += str[i];
        }
          else{
              //añadiendo signos a cada monomio que posea un signo negativo
              if(str[i - (int)temp.size()-1] == '-'){
              temp.insert(0, 1, str[i - (int)temp.size()-1]);
              }
        //extrayendo coeficientes de monomios desde el string "temp", buscando si es que existe caracter 'x' en cada monomio, donde se guardaran en el array "coeficientes"
              if (temp.find('x') != std::string::npos){
                  //si es 1
                  if(temp[0] == 'x'){
                      coeficientes[cont] = 1;
                  }
                  //si es -1
                  else if(temp[0]=='-' && temp[1]=='x'){
                      coeficientes[cont] = -1;
                  }
                  //si es distinto a 1
                else{
                  for(int j = 0; temp[j] != 'x'; j++){
                      temp2+=temp[j];
                  }
                  coeficientes[cont]=stof(temp2);
                  temp2="";
                }

              }
              else{	  
                  //Si es que no posee x
                  coeficientes[cont] = stof(temp);
              }
       //extrayendo exponentes de monomios, donde se guardaran en el array de floats "exponentes"
                // se hace busqueda de los caracteres '**', y se se encuentra, se guarda todo lo que se encuentra despues de "**", es decir el exponente del monomio
              if (temp.find('*') != std::string::npos){
                  exponentes[cont]=stof(temp.substr(temp.find("*") + 2));
              }
              else{
                  // si es que no se encuentra el caracter "x", se le asigna el exponente 0 o 1, haciendo uso de la funcion "find()"
                  if (temp.find('x') != std::string::npos){
                      exponentes[cont] = 1;
                  }
                  // si es que el exponente es 0
                  else{
                      exponentes[cont] = 0;
                  }
              }
              // See continua el ciclo, a partir del termino del ultimo monomio analizado, y se reinicia el valor de "temp"
              cont++;
              temp = "";
        }
    }
     //retorna el numero de terminos que posee el polinomio a usar
     return cont;

}
void derivada(float (&coeficientes)[10], float (&exponentes)[10], float (&coef)[10], float (&expo)[10]){

     for(int i=0;i<10;i++){
         coef[i] = coeficientes[i]*exponentes[i];
         expo[i] = exponentes[i]-1;
     }

}

float evaluarFuncion(float cf[10],float xp[10],float x,int numTerminos){
    float suma = 0;
    for (int i=0;i<numTerminos;i++){
        suma+=cf[i]*pow(x,xp[i]);
    }
    return suma;
}


int main(int argc, char** argv) {
    string str = argv[1] ;               // string to be split

    float coeficientes[10];
    float exponentes[10];
    float coef[10];
    float expo[10];
    int n = split(str,coeficientes,exponentes);
    derivada(coeficientes,exponentes,coef,expo);
    float a,e=0,z;
    cout<<"Ingrese numero ";
    cin>>a;
    do
    {   e++;
        z=a-(evaluarFuncion(coeficientes,exponentes,a,n)/evaluarFuncion(coef,expo,a,n));
        cout<<"Iteracion "<<e<<": "<<z;
        a=z;
        cout<<endl;
    }while(abs(evaluarFuncion(coeficientes,exponentes,z,n))>0.001);

    return 0;
}
