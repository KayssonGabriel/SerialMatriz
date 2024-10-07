#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <charconv>
#include <iomanip>
#include <new>
#include <string>
#include <vector>

void matrixMultiplySerial(float* A, float* B, float* C, std::size_t N) {
    for (std::size_t i = 0; i < N; i++) {
        for (std::size_t j = 0; j < N; j++) {
            float sum = 0;
            for (std::size_t k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

void fillMatrix(float* matrix, std::size_t N) {
    for (std::size_t i = 0; i < N * N; i++) {
        matrix[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
}

int main() {
    srand(time(0));

    std::string entrada;
    std::cout << "Digite o tamanho da matriz (NxN): ";
    std::cin >> entrada;
    std::size_t n = 0;
    const char* inicio_entrada = entrada.data();
    if (!entrada.empty() && entrada.front() == '+') {
        ++inicio_entrada;
    }
    const char* fim_entrada = entrada.data() + entrada.size();
    const auto conversao = std::from_chars(inicio_entrada, fim_entrada, n);
    if (conversao.ec != std::errc() || conversao.ptr != fim_entrada || n == 0) {
        std::cerr << "Dimensão inválida. Informe um inteiro positivo.\n";
        return 1;
    }
    if (n > std::vector<float>().max_size() / n) {
        std::cerr << "Dimensão grande demais para alocar a matriz.\n";
        return 1;
    }
    const auto elementos = n * n;

    try {
        std::vector<float> a(elementos), b(elementos), c(elementos);
        fillMatrix(a.data(), n);
        fillMatrix(b.data(), n);
        const auto inicio = std::chrono::steady_clock::now();
        matrixMultiplySerial(a.data(), b.data(), c.data(), n);
        const std::chrono::duration<double> tempo = std::chrono::steady_clock::now() - inicio;
        std::cout << std::fixed << std::setprecision(6)
                  << "Tempo Serial: " << tempo.count() << " segundos\n";
    } catch (const std::bad_alloc&) {
        std::cerr << "Memória insuficiente para a dimensão informada.\n";
        return 1;
    }
    return 0;
}
