#!bin/bash

COMPILER="g++"
ARGS="-g -std=c++17 -D MAN520_DEBUG"
SRC="$(find ./engine -type f -iregex ".*\.cpp")"
LIBSRC="./lib/glad/src/glad.c ./lib/stb/stb_image.cpp ./lib/imgui/*.cpp"
CLIENTSRC="./sandbox/3D/src/*.cpp"
CLIENTINC="-I./sandbox/3D/include"
INCLUDE="-I./engine -I./lib/spdlog/include -I./lib/stb -I./lib/glm -I./lib/glad/include -I./lib/entt/include -I./lib/imgui"
BINARY="./bin/prog"
LIBS="-lsdl2 -lsdl2_image -ldl"

# Echo out the platform we are compilng on.
echo "Compiling on ${OSTYPE}"

# Build the compile string
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo ""
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Compilng on Mac"
    #INCLUDE="./engine -I./lib/spdlog/include -I./lib/stb -I./lib/glm -I./lib/glad/include -I./lib/entt/include `sdl2-config --clfags`"
    #LIBS="`sdl2-config --libs`"
    echo ""
elif [[ "$OSTYPE" == "mysys" ]] ; then
    echo "Compiling on Windows(mysys)"
    LIBS="-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer"
    echo ""
else
    echo "Not sure what operating system to build for?? Trying defaults"
    echo ""
fi

COMPILE="${COMPILER} ${ARGS} ${SRC} ${LIBSRC} ${CLIENTSRC} ${CLIENTINC} ${INCLUDE} -o ${BINARY} ${LIBS}"

# Write out the compile string for the user to see
echo ${COMPILE}

# Evaluate the compile string
eval $COMPILE

#PRECOMPILEHEADER="g++ -std=c++17 -x c++-header -o ./include/mzpch.h.gch -c ./include/mzpch.h -I./lib/spdlog/include"
#Compile options:
#"-D MAN520_DEBUG" 
#COMPILE="clang++ -std=c++17 -D MAN520_DEBUG -g $(find ./engine -type f -iregex ".*\.cpp") ./sandbox/src/*.cpp ./lib/glad/src/glad.c -I./sandbox/include -I./engine -I./lib/spdlog/include -I./lib/stb -I./lib/glm -I./lib/glad/include -I./lib/entt/include -o ./bin/prog -lsdl2 -lsdl2_image -ldl"

#echo ${PRECOMPILEHEADER}
#eval $PRECOMPILEHEADER
#echo ${COMPILE}
#eval $COMPILE
