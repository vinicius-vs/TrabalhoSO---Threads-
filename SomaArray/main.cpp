#include <iostream>

const int sizeArray = 10;

// Variaveis para usar na soma usando o PThread
pthread_mutex_t  em;
float  valorTotalPthread = 0;

typedef struct {
    float floatArray[sizeArray] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    int inicio = 0;
    int fim = 0;
} arguments, *argus;


//Soma simples do arrey

float somarArray( float  Array[sizeArray])
{
    float valorTotal = 0;
    for(int i = 0; i < sizeArray;++i)
    {
        valorTotal += Array[i];
    }
    return valorTotal;
}


void SomarArrayThread(void *arg)
{
    argus argumentos = (argus)arg;

    float valorTotal = 0;
    for (int i = argumentos->inicio; i < argumentos->fim ; ++i)
    {

        valorTotal += argumentos->floatArray[i];
    }

    pthread_mutex_lock(&em);
    valorTotalPthread += valorTotal;
    pthread_mutex_unlock(&em);
}



void somaArrayPThread()
{
    pthread_t t1,t2;
    arguments arguments1[2];
    arguments1[0].inicio = 0;
    arguments1[0].fim = sizeArray/2;
    arguments1[1].inicio = sizeArray/2;

    arguments1[1].fim = sizeArray;


    pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(SomarArrayThread), &arguments1[0]);
    pthread_create(&t2, NULL, reinterpret_cast<void *(*)(void *)>(SomarArrayThread), &arguments1[1]);

    pthread_join( t1, NULL);
    pthread_join( t2, NULL);


}



int main() {
    arguments arrayA;
    float valorTotalArraySimple;
    clock_t time;
    std::cout<<"---------- Soma Array Simples -------------\n";
    time = clock();
    valorTotalArraySimple =  somarArray(arrayA.floatArray);
    time = clock() - time;
    std::cout<<"Valor total: "<<valorTotalArraySimple<<"\nTempo de execução: "<<(double )time/CLOCKS_PER_SEC;

    std::cout<<"\n\n---------- Soma Array PThread -------------\n";
    clock_t timePthread;
    timePthread = clock();
    somaArrayPThread();
    timePthread = clock() - time;
    std::cout<<"\nValor total: "<<valorTotalPthread<<"\nTempo de execução: "<<(double )timePthread/CLOCKS_PER_SEC;


    std::cout<<"\n\n---------- Soma Array OpenMp -------------\n";
    float valorTotalArrayOpenMp;
    clock_t timeOpenMp;
    timeOpenMp = clock();
    #pragma  omp parallel private()
    {
        valorTotalArrayOpenMp =  somarArray(arrayA.floatArray);
    }
    timeOpenMp = clock() - time;
    std::cout<<"\nValor total: "<<valorTotalArraySimple<<"\nTempo de execução: "<<(double )time/CLOCKS_PER_SEC;
}
