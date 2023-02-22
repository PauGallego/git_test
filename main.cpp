#include <iostream>

//Creamos la cadena
char TCadena[120];

//Creamos las variables
bool menu=true, mostrar, pal, igual;
int a = 0;

//Declaramos las funciones
int Longitud(char TCadena[120], bool mostrar);
bool Palindrom(char TCadena[120]);
int vocals(char TCadena[120]);
char contar(char TCadena[120]);
char reves(char TCadena[120]);
bool lletraigual(char TCadena[120]);

int main ( int argc, char const *argv[]){

    //Pedimos y asignamos valores a TCadena
    printf("Introdueix una cadena de caracters:");
    fgets(TCadena,120,stdin);

    while (menu){

        //Pedimos y asignamos un valor a la avriable a (Mostramos menu)
        printf("Seleccióna una de les seguents opcions:\n(1) Tornar i mostrar la seva longitud.\n(2) Tornar (bool) si la frase és palíndrom o no.\n(3) Tornar quantes vocals (majuscules i minuscules) té la frase.\n(4) Tornar la lletra més utilitzada.\n(5) Tornar i mostrar la frase al revés.\n(6) Tornar (bool) si comença i acaba per la mateixa lletra.\n(0) Sortir\n");
        scanf("%d", &a);

        switch (a){
            case 1:

                //Modificamos mostrar a true
                mostrar=true;

                //Llamamos a la funcion Longitud enviando como parametros Tcadena y el booleano mostrar
                Longitud(TCadena,mostrar);

                break;

            case 2:

                //Llamamos a la funcion Longitud enviando como parametros Tcadena y el booleano mostrar
                pal= Palindrom(TCadena);

                //Si pal es true, mostramos que es palindromo
                if(pal){
                    printf("Es palindrom ^^\n");

                //Sino, mostramos que no lo es
                }else{
                    printf("NO es palindrom :c\n");
                }

                break;

            case 3:

                //Mostramos el return de vocals enviando TCadena como parametro
                printf("La cadena de caracters te %d vocals\n", vocals(TCadena));

                break;
            
            case 4:

                //Mostramos el return de contar enviando TCadena como parametro
                printf("La lletra mes utilitzada es: %c\n", contar(TCadena));


                break;
            case 5:

                //Llamamos i mostramos la funcion reves enviando TCadena como parametro
                std::cout << "La cadena al reves es:" << reves(TCadena) << "\n";

                break;
            case 6:

                    //Asignamos a igual el return de lletraigual enviando como parametro TCadena
                    igual= lletraigual(TCadena);

                    //Si es true, mostramos que la pirmera y la ultima letra son iguales
                    if(igual){
                        printf("La pirmera i la ultima lletra son iguals\n");

                    //Sino, mostramos que no
                    }else{
                        printf("La pirmera i la ultima lletra NO son iguals\n");
                    }
                

                break;
            case 0:

                //Canviamos el booleano menu a false
                menu=false;
                break;
            default:
                printf("Opció no valida :c\n");
                break;
        }
    }    

    system("PAUSE");
    return 0;

}

//Funcion 1
int Longitud(char TCadena[120], bool mostrar){

    //Creeamos Variables
    bool found=false;
    int longitud=0;
        
        //Bucle que pase por todas las posiciones de TCadena mientars el bool Found sea false
        for(int i=0; i<120 && !found;i++){

            //Si la posicion actual es igual a \0 entramos al if
            if(TCadena[i]=='\0'){

                //Asignamos el valor de i -1 a longitud(longitud de posiciones ocupadas)
                longitud=i-1;

                //Volvemos true el booleano found
                found=true;
            }
        }

    //Si el parametro mostrar es true, mostramos por pantalla el valor de longitud y lo devolvemos
    if (mostrar){
        printf("La longitud es: %d\n", longitud);
        return longitud;
    
    //Sino, solo devolvemos el valor, no lo mostramos
    }else{
        return longitud;
    }

}

//Funcion 2
bool Palindrom(char TCadena[120]){

    //Creamos booleanos
    bool mostrar=false;
    bool palindromo=true;

    //Creamos variable con el return de la funcion Longitud
    int max= Longitud(TCadena,mostrar);

    //Bucle que pase todas las posiciones de TCadena
    for(int i=0; i<max;i++){

        //Si el valor de la posicion actual de TCadena es diferente a la misma posicion empezando al reves -1(evitamos el \0) entramos al if 
        if(TCadena[i]!=TCadena[max-i-1]){

            //Modificamos palindromo a false
            palindromo=false;
        }
    }

    //Devolvemos el booleano palindromo
    return palindromo;

}

//Funcion 3
int vocals(char TCadena[120]){

    //Creamos una cadena con vocales
    char vocal[10]={'A','E','I','O','U','a','e','i','o','u'};

    //Creamos las variables
    char a;
    char b;
    int contar=0;

    bool mostrar=false;

    //Creamos variable con el return de la funcion Longitud
    int max= Longitud(TCadena,mostrar);

    //Bucle longitud de TCadena
    for(int i=0; i<max;i++){

        //Asignamos a la variable a el valor actual de TCadena
        a=TCadena[i];

        for(int j=0;j<10;j++){

            //Asignamos a la variable b el valor actual de vocal
            b=vocal[j];

            //Si el valor de a es igual al de b, sumamos 1 a contar
            if(a==b){
                contar++;
            }
        }
    }

    //Devolvemos el valor de contar
    return contar;
}


//Funcion 4

char contar(char TCadena[120]){

    //Cremaos la cadena letra
    int letra[27][2];

    //Creamos las variables
    int comp,pos,cont=0;
    bool found= false;
    bool mostrar=false;
    char result;



    //Creamos variable con el return de la funcion Longitud
    int max= Longitud(TCadena,mostrar);


    //Bucle para inicializar el array letra desde el 97 hasta el 120 que es a-z en ascii
    for (int i=97 ; i<123;i++){

        letra[cont][0]=i;

        //Inicializamod la segunda dimension con0
        letra[cont][1] = 0;

        cont++;
    }

    //Bucle que recorre todas las posiciones de TCadena
    for(int i=0;i<max;i++){

        //Modificamos found a false
        found=false;

        //Bucle que pare si found es true de todas las posiciones de letra
        for(int j=0; j<27 && !found;j++){

            //Si la posicion actual de letra tiene el mismo valor que la posicion actual de TCadena
            if(letra[j][0]== TCadena[i] ){

                //Modificamos found a true
                found=true;

                //Sumamos 1 a la segunda dimension de la posicion actual de letra
                letra[j][1]++;
            }

        }

    }

    //Inicialicamos la variable con el numero de veces que ha salido la letra en la primera posicion
    comp=letra[0][1];

    //Bucle que recorre toda la cadena de letra
    for(int i=0; i<27;i++){

        //Si el valor de la segunda dimension de letra es mayor al valor de comp
        if(letra[i][1]>comp){

            //Le asignamos a comp el valor actual de la segunda dimension de letra
            comp= letra[i][1];

            //Guardamos la posicion en la variable pos
            pos = i;
        }

    }

    //Asignamos a result el valor  en char de la posicion pos de la primera dimension de letra
    result= (char)letra[pos][0];

    //Devolvemos result
    return result;
}



//Funcion 5
char reves(char TCadena[120]){

    //creamos variable
    bool mostrar=false;

    //Creamos cadena de caracteres
    char TCadenarev[120]="";

    //Creamos variable con el return de la funcion Longitud
    int max= Longitud(TCadena,mostrar);

    //Bucle que recorre todas las posiciones de TCadena+1 (para contar el \0)
    for(int i; i<max+1;i++){

        //Asignamos a la posicion actual de TCadenarev el valor contrario de TCadena
        TCadenarev[i]=TCadena[max-i];
    }

    //Mostramos el valor de TCadenarev
    std::cout << TCadenarev;

    //Devolvemos la cadena TCadenarev
    return TCadenarev[120];

}

//Funcion 6
bool lletraigual(char TCadena[120]){

     //creamos variable
    bool mostrar=false;

    bool resultat;

    //Creamos variable con el return de la funcion Longitud
    int max= Longitud(TCadena,mostrar);

    //Si el primer valor de la cadena es igual al ultimo (su longitud -1) entramos al if
    if(TCadena[0]==TCadena[max-1]){

        //Marcamos el booleano como true
        resultat=true;

    //Sino
    }else{
        
        //Marcamos el booleano como false
        resultat=false;
    }


    //Devolvemos el booleano resultat
    return resultat;


}