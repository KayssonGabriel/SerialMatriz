# Multiplicação serial de matrizes

Exercício em C++ que multiplica duas matrizes quadradas de números de ponto flutuante na CPU. [main.cpp](main.cpp) lê a dimensão `N`, preenche as entradas com valores aleatórios e cronometra os três laços da multiplicação. O custo de cálculo cresce com o cubo de `N`.

## Como executar

Use CMake 3.29 ou superior e um compilador C++20.

~~~sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
~~~

O alvo em [CMakeLists.txt](CMakeLists.txt) se chama `untitled6`. Execute `build/untitled6` no Linux ou `build/Release/untitled6.exe` no Windows com o gerador do Visual Studio. Digite uma dimensão positiva pequena, como `4`. O terminal mostra o tempo de processamento.
