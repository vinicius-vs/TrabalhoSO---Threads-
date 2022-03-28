#include <iostream>
#include <time.h>
#include <omp.h>

const int size = 3;

typedef struct {
    int vetorAuxiliarA[size] = {0}, vetorAuxiliarB[size] = {0},posicao;
} VetoresAuxiliar;

int  matrizA[size][size] = {{1,2,3},
                            {4,5,6},
                            {7,8,9}};

int  matrizB[size][size] = {{9,8,7},
                            {6,5,4},
                            {3,2,1}};

int matrizC[size][size] = {0};

void multiplicarLinhaColuna(VetoresAuxiliar vetores);
void AdicionarCalunaMatrizC(int coluna[size],int posicaoColuna);
void imprimirMatrizes();
void imprimirDados(clock_t time);

int main() {

    VetoresAuxiliar vetoresAB;

    clock_t time;

    time = clock();
    #pragma omp parallel private()
    {
        #pragma omp for
        for (int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                vetoresAB.vetorAuxiliarA[j] = matrizA[j][i];
                vetoresAB.vetorAuxiliarB[j] = matrizB[i][j];
            }
            vetoresAB.posicao = i;
            multiplicarLinhaColuna(vetoresAB);
        }
    }
    time = clock() - time;
    imprimirMatrizes();
    imprimirDados(time);
}

void multiplicarLinhaColuna(VetoresAuxiliar vetores)
{
    int vetorAuxiliarC[size] = {0};

    for (int i = 0; i < size; ++i) {
        vetorAuxiliarC[i] = vetores.vetorAuxiliarA[i] * vetores.vetorAuxiliarB[i];
    }
    AdicionarCalunaMatrizC(vetorAuxiliarC, vetores.posicao);
}

void AdicionarCalunaMatrizC(int coluna[size],int posicaoColuna)
{
    for(int i = 0; i < size; ++i )
    {
        matrizC[i][posicaoColuna] = coluna[i];
    }
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