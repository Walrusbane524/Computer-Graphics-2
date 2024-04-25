# Computer-Graphics-2
Algorithms used in the Computer Graphics 2 course at my university.

## To compile and run

g++ -o build/main src/main.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl <br/>
build/main

## Compiling on Windows

g++ -o build/main src/main.cpp src/glad.c -lopengl32 -lglfw3 -lgdi32
build/main
