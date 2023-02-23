# Optimització de programari
## Pau Gallego Fagundez Act03

---
## Index
- [Optimització de programari](#optimització-de-programari)
  - [Pau Gallego Fagundez Act03](#pau-gallego-fagundez-act03)
  - [Index](#index)
  - [1. Eliminació de codi](#1-eliminació-de-codi)
  - [2. Creació de funcions / Susbtitució de codi](#2-creació-de-funcions--susbtitució-de-codi)
  - [3. Orde i bugfixing](#3-orde-i-bugfixing)
---

## 1. Eliminació de codi

Al llegir i entendre el codi per primera vegada podrem veure que existeixen diverses biblioteques i variables que no es fan servir o la seva utilitat és nul·la, com per exemple:

- Originalment teníem aquestes llibreries:

```c++
#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>
```
- Pero realment nomes son utils les seguents:
```c++
//Eliminamos Librerias, son inecesarias
#include <iostream>
#include <thread>
```
Una altra clara eliminació ha estat l'array de números , que només es feia servir un cop i no era necessari, ocupat un espai en memòria.

- Array amb la seva utilització anterior
```c++
int numeros[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = numeros[i];
			baraja[contador].palo = palos[j];
			contador++;
		}
	}
```
 - ELiminació de array y modificació del for por i + 1
```c++
 //Bucle creacion de cartas
  for (int i = 0; i < 13; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      baraja[contador].numero = i + 1;
      baraja[contador].palo = palos[j];
      contador++;
    }
  }
```

També existia un contadorAS, que no aportava cap informació i la seva utilització en un if sempre es complia, per tant, no era necessari.

 - ContadorAS i el seu us anterior
```c++
int contadorAS;
            contadorAS++;
                if (contadorAs >= 1 && puntos+11 > 21){
                  puntos = puntos + 1;
                } else {
                  puntos = puntos + 11;
                }
                num_cartas_mano++;
```
 
- Eliminació del contadorAS fent servir una nova funció (Explicació mes endevant)

```c++
 for (int contadorMano = 0; contadorMano < 12; contadorMano++){
        if (mano[contadorMano].palo != ""){

//Llamamos a la funcion mostrarcarta y le asignamos el return a putnos
          puntos = mostrarcarta(puntos, mano[contadorMano]);
          num_cartas_mano++;
        }
      }
```
  
- La longitud dels arrays de mano, seran reduïts de 52 a 12, ja que no pots tenir a la ma mes d'11 cartes.

```c++
struct carta baraja[52] , mano[12], manoMaquina[12];
```


## 2. Creació de funcions / Susbtitució de codi

Originalment, mola part del codi es repetia, sobretot en la part de mostrar nom de carta i veure puntuació actual per decidir si s'havia perdut, guanyat o calia més torns i, per tant, he creat 2 funcions per reduir la quantitat de codi del programa.

- Com es mostrava abans una carta i es contava la puntuació:
```c++
if (mano[contadorMano].palo != ""){
              if( mano[contadorMano].numero == 1){
                cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
                contadorAs++;
                if (contadorAs >= 1 && puntos+11 > 21){
                  puntos = puntos + 1;
                } else {
                  puntos = puntos + 11;
                }
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 11){
                cout <<  "\033[1;33m Sota de " << mano[contadorMano].palo << "\033[0m"<< endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 12){
                cout <<  "\033[1;33m Caballo de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              } else if (mano[contadorMano].numero == 13){
                cout <<  "\033[1;33m Rey de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              } else {
                cout << "\033[1;33m "<< mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + mano[contadorMano].numero;
                num_cartas_mano++;
              }
            }
```
- Com es mostra una carta actualment i es suma la puntuació:

```c++
if (mano[contadorMano].palo != ""){

          //Llamamos a la funcion mostrarcarta y le asignamos el return a putnos
          puntos = mostrarcarta(puntos, mano[contadorMano]);
          num_cartas_mano++;
        }
```

Com podem veure , la quantitat de codi es redueix massivament, i permet veure un codi molt mes net i optimitzat.

La funció en qüestió, rep la carta que volem mostrar i contar juntament amb la posició actual, i segons cada valor, mostrara una frase o una alta i tornara la nova puntuació del usuari.
```c++
//Funcion para contar puntuacion y mostrar valor de carta
int mostrarcarta(int puntos, carta mano)
{

  //Segun el valor de la carta mostramos un nombre o otro y segun el valaor de puntos sumamos un valor o otro
  switch (mano.numero){
    case 1:
      cout << "\033[1;33m A de " << mano.palo << "\033[0m" << endl;
      if (puntos + 11 > 21){
        puntos = puntos + 1;
      }
      else{
        puntos = puntos + 11;
      }
      break;
    case 11:
      cout << "\033[1;33m Sota de " << mano.palo << "\033[0m" << endl;
      puntos = puntos + 10;
      break;
    case 12:
      cout << "\033[1;33m Caballo de " << mano.palo << "\033[0m" << endl;
      puntos = puntos + 10;
      break;
    case 13:
      cout << "\033[1;33m Rey de " << mano.palo << "\033[0m" << endl;
      puntos = puntos + 10;
      break;

    default:
      cout << "\033[1;33m " << mano.numero << " de " << mano.palo << "\033[0m" << endl;
      puntos = puntos + mano.numero;
      break;
  }

  //Devolvemos la nueva puntuacion
  return puntos;
}
```
L'altre cas mencionat, era el que mostrava un missatge al final de cada torn i decidia si es continuava o no la partida, com es repetia alguns cops, creem una altra funció per aquest cas.

- Codi anterior

```c++
if (puntos > 21){
                  cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
                  cout << "\033[1;31mHas perdido\033[0m" << endl;
                  repetir = false;
                  break;
                } else if (puntos == 21){ 
                  cout << "\033[1;33mFELICIDADES tienes " << puntos <<  " puntos!(Blackjack)\033[0m" << endl;
                  repetir = false;
                  break;
                } else {
                  cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
                }
                break;
```

- Codi actual

```c++
//Llamamos a la funcion repetir, y le asignamos el return a repetir
      repetir=puntuacion(puntos);

      //Si repetir es false, salimos del bucle
      if(!repetir){break;}

```

Aquesta funció rep la puntuació actual, mostrat per pantalla el missatge adequat per a cada decisió i tornant un true o false per decidir si continua la partida o no.
```c++
//Funcion para mostrar el estado actual de nuestra puntuacion
bool puntuacion(int puntos){
  
  //Booleano por defecto true
  bool repetir = true;

  //Si es mayor de 21 o igual a 21 mostramos cada caso y enviamos false, los demas casos mostramos puntuacion y enviamos true
  if (puntos > 21)
      {
        cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
        cout << "\033[1;31mHas perdido\033[0m" << endl;
        repetir = false;
      }
      else if (puntos == 21)
      {
        cout << "\033[1;33mFELICIDADES tienes " << puntos << " puntos!(Blackjack)\033[0m" << endl;
        repetir = false;
      }
      else
      {
        cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << endl;
      }
  
  //Devolvemos el booleano
  return repetir;
}
```


## 3. Orde i bugfixing


Finalment, per permetre una lectura molt més còmode i tenir una bona organització del codi, s'han ordenat totes les variables, estructures i arrays fora del main seguint un mateix ordre.

- Exemple de variables desordenades anteriorment
```c++
	const string palos[4] = { "Corazones", "Diamantes", "Picas", "Treboles" };
	
	int contador = 0; 

	for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = numeros[i];
			baraja[contador].palo = palos[j];
			contador++;
		}
	}

  int opcion;
  bool repetir = true;  
  struct carta mano[52], manoMaquina[52];
  int num_cartas_mano, carta_mano_maquina, puntos, contadorAs, puntosMaquina, turno = 0;
 
  //Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand()%52];
  }

```

- Orde actual del codi (abançs del main)
```c++
//Eliminamos Librerias, son inecesarias
#include <iostream>
#include <thread>

using namespace std;

struct carta{
  int numero;
  string palo;
};

//Movemos la creacion de las estructuras fuera del main
struct carta baraja[52] , mano[12], manoMaquina[12];

//Declaramos las funciones
int mostrarcarta(int puntos, carta mano);
bool puntuacion(int puntos);

//Movemos las variables fuera del main
bool repetir = true;
int opcion,num_cartas_mano, carta_mano_maquina, puntos, puntosMaquina, turno = 0, contador=0;
const string palos[4] = {"Corazones", "Diamantes", "Picas", "Treboles"};
```

Al crear les funcions, a vegades pasava un bug que feia contar els punts de manera quasi infinita, i per resoldre-ho ha calgut introduir la següent funció per limpiar el cin.

```c++
 cout << "\nIngrese una opcion: ";
    cin >> opcion;
    turno++;

    //Arreglamos fallon con cin
    cin.ignore();
```