/* Nom: Pau Gallego Fagundez
=============================
S'ha d'optimitzar aquest codi tot el que pugueu.
Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.
Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.
*/

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

int main(){

  //Generamos num aleatorio
  time_t t;
  srand((unsigned)time(&t));

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

  // Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand() % 52];
  }

  do{
    cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
    cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
    cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
    cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
    cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
    cout << "\033[1;32m 0. SALIR \033[0m" << endl;

    if (turno == 0){
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      puntos = 0;

      for (int contadorMano = 0; contadorMano < 12; contadorMano++){
        if (mano[contadorMano].palo != ""){

          //Llamamos a la funcion mostrarcarta y le asignamos el return a putnos
          puntos = mostrarcarta(puntos, mano[contadorMano]);
          num_cartas_mano++;
        }
      }

      //Llamamos a la funcion repetir, y le asignamos el return a repetir
      repetir=puntuacion(puntos);

      //Si repetir es false, salimos del bucle
      if(!repetir){break;}
    }

    cout << "\nIngrese una opcion: ";
    cin >> opcion;
    turno++;

    //Arreglamos fallon con cin
    cin.ignore();

    switch (opcion){
    case 1:
      system("clear");
      mano[num_cartas_mano + 1] = baraja[rand() % 52];
      cout << "\033[1;32mTu carta es: \033[0m" << endl;

      //Mismo caso que el anterior con la funcion mostrarcarta     
      puntos = mostrarcarta(puntos, mano[num_cartas_mano +1]);
      num_cartas_mano++;
    
      //Mismo caso que el anterior con la funcion puntuacion  
      repetir=puntuacion(puntos);
      break;

    case 2:
      system("clear");
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      puntos = 0;
      for (int contadorMano = 0; contadorMano < 12; contadorMano++){
        if (mano[contadorMano].palo != ""){

          //Mismo caso que el anterior con la funcion mostrarcarta 
          puntos = mostrarcarta(puntos, mano[contadorMano]);
          num_cartas_mano++;
        }
      }
      cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << endl;
      break;

    case 3:
      system("clear");
      cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << endl;
      cout << "\033[1;36mAhora juega la máquina\033[0m" << endl;
      while (puntosMaquina < puntos){
        cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        manoMaquina[carta_mano_maquina] = baraja[rand() % 52];
        
        //Mismo caso que los anteriores con mostrarcarta, pero añadimos puntuacion a la maquina y no al usuario
        puntosMaquina = mostrarcarta(puntosMaquina, manoMaquina[carta_mano_maquina]);       
        cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
        carta_mano_maquina++;
      }
      
      //Podriamos crear una funcion parecida a la de puntuacion, pero como solo se usa 1 vez no es necesario
      if (puntosMaquina > 21){
        cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
        cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
      }
      else if (puntosMaquina == puntos){
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;33mEmpate\033[0m" << endl;
      }
      else{
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;31mHas perdido...\033[0m" << endl;
      }
      cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
      repetir = false;
      break;

    case 4:
      for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++)
      {
        //Llamamos a la funcion mostrar carta pero enviando toda la baraja para ver que queda
        puntos = mostrarcarta(puntos, baraja[contadorBaraja]);
      }
      break;

    case 0:
      repetir = false;
      break;
    }
  } while (repetir);

  return 0;
}

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