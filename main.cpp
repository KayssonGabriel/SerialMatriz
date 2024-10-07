#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip> // Para std::setprecision

void matrixMultiplySerial(float* A, float* B, float* C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

void fillMatrix(float* matrix, int N) {
    for (int i = 0; i < N * N; i++) {
        matrix[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
}

int main() {
    srand(time(0));

    // Solicitar o tamanho da matriz ao usuário
    int N;
    std::cout << "Digite o tamanho da matriz (NxN): ";
    std::cin >> N;

    size_t bytes = N * N * sizeof(float);

    // Alocação de memória para as matrizes
    float* h_A = (float*)malloc(bytes);
    float* h_B = (float*)malloc(bytes);
    float* h_C = (float*)malloc(bytes); // Resultado Serial

    // Preencher as matrizes A e B com números aleatórios
    fillMatrix(h_A, N);
    fillMatrix(h_B, N);

    // Multiplicação Serial
    auto start_serial = std::chrono::high_resolution_clock::now();
    matrixMultiplySerial(h_A, h_B, h_C, N);
    auto end_serial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_serial = end_serial - start_serial;

    // Imprimir os resultados em segundos com 6 casas decimais
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Tempo Serial: " << time_serial.count() << " segundos\n";

    // Liberar memória
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
