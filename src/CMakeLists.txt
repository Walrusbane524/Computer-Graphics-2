# Arquivo CMakeLists.txt no diretório src

# Função para adicionar um executável
function(add_executable_from_source EXECUTABLE_NAME SOURCE)
    # Adiciona todos os arquivos de código-fonte presentes no diretório src/classes ao executável principal
    file(GLOB CLASS_SOURCES "classes/*.cpp")

    # Adiciona o executável principal
    add_executable(${EXECUTABLE_NAME} ${SOURCE} ${CLASS_SOURCES})

    # Adiciona o diretório include para procurar os headers
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ../include/headers)

    # Compila o glad.c como uma biblioteca estática
    add_library(glad STATIC ./lib/glad.c)

    # Compila o stb.cpp como uma biblioteca estática
    add_library(stb STATIC ./lib/stb.cpp)

    # Encontra e adiciona as bibliotecas GLFW
    find_package(glfw3 3.3 REQUIRED)

    find_package(OpenGL REQUIRED)

    # Adiciona o diretório include para procurar os headers de glad, glfw e stb
    target_include_directories(${EXECUTABLE_NAME} PUBLIC
            ../libraries/include
    )

    # Vincula as bibliotecas necessárias
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE glad glfw stb ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
endfunction()

# Verifica se foi fornecido o nome do executável
if(NOT DEFINED MAIN_EXECUTABLE)
    message(FATAL_ERROR "Por favor, especifique o nome do executável. Use -DMAIN_EXECUTABLE=<nome_executável>.")
endif()

# Adiciona o executável usando o nome fornecido
add_executable_from_source(${MAIN_EXECUTABLE} ${MAIN_EXECUTABLE}.cpp)
