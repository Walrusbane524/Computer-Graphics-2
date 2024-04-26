# Arquivo CMakeLists.txt no diretório src

# Adiciona todos os arquivos de código-fonte presentes no diretório src/classes ao executável principal
file(GLOB CLASS_SOURCES "classes/*.cpp")

# Adiciona o executável principal
add_executable(main ./triforce.cpp ${CLASS_SOURCES})

# Adiciona o diretório include para procurar os headers
target_include_directories(main PUBLIC ../include/headers)

# Compila o glad.c como uma biblioteca estática
add_library(glad STATIC glad.c)

# Encontra e adiciona as bibliotecas GLFW
find_package(glfw3 3.3 REQUIRED)

# Vincula as bibliotecas necessárias
target_link_libraries(main PRIVATE glad glfw ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
