# Arquivo CMakeLists.txt no diretório raiz

# Versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(CG2)

# Opção para escolher o nome do executável
option(CHOOSE_EXECUTABLE "Escolha o nome do executável (main ou main2)" "main")

# Adiciona o subdiretório src
add_subdirectory(src)
