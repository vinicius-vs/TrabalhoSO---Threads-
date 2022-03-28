#include <iostream>
#include <time.h>
#include <pthread.h>

const int size = 3;

typedef struct {
    int vetorAuxiliarA[size] = {0}, vetorAuxiliarB[size] = {0},posicao;
} VetoresAuxiliar, *vetorAux;

int  matrizA[size][size] = {{1,2,3},
                            {4,5,6},
                            {7,8,9}};

int  matrizB[size][size] = {{9,8,7},
                            {6,5,4},
                            {3,2,1}};

int matrizC[size][size] = {0};

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;


void multiplicarLinhaColuna(void * arg);
void AdicionarCalunaMatrizC(int coluna[size],int posicaoColuna);
void imprimirMatrizes();
void imprimirDados(clock_t time);

int main() {

    VetoresAuxiliar vetoresAuxiliar[size];
    pthread_t t[3];

    clock_t time;
    time = clock();
    for (int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            vetoresAuxiliar[i].vetorAuxiliarA[j] = matrizA[j][i];
            vetoresAuxiliar[i].vetorAuxiliarB[j]= matrizB[i][j];
        }
        vetoresAuxiliar[i].posicao = i;
        pthread_create(&(t[i]), NULL, reinterpret_cast<void *(*)(void *)>(multiplicarLinhaColuna), (void * )&(vetoresAuxiliar[i]));
    }
    time = clock() - time;
    imprimirMatrizes();
    imprimirDados(time);
}

void multiplicarLinhaColuna(void *arg)
{
    vetorAux  vertorAuxiliar = (vetorAux)arg;
    int vetorAuxiliarC[size] = {0};

    for (int i = 0; i < size; ++i) {
        vetorAuxiliarC[i] = vertorAuxiliar->vetorAuxiliarA[i] * vertorAuxiliar->vetorAuxiliarB[i];
    }
    AdicionarCalunaMatrizC(vetorAuxiliarC, vertorAuxiliar->posicao);
}

void AdicionarCalunaMatrizC(int coluna[size],int posicaoColuna)
{
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < size; ++i )
    {
        matrizC[i][posicaoColuna] = coluna[i];
    }
    pthread_mutex_unlock(&mutex);
}
void imprimirMatrizes()
{
    std::cout<<"----- MATRIZ A ------\n\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout<<" "<<matrizA[i][j]<<" |";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"----- MATRIZ B ------\n\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout<<" "<<matrizB[i][j]<<" |";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"----- MATRIZ C ------\n\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout<<" "<<matrizC[i][j]<<" |";
        }
        std::cout<<std::endl;
    }
}
void imprimirDados(clock_t time)
{
    std::cout<<std::endl;
    std::cout<<"Tempo da execução da mutiplicação: "<<(double) time/CLOCKS_PER_SEC;
}