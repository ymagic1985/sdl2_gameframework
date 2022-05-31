
#PRECOMPILEHEADER="g++ -std=c++17 -x c++-header -o ./include/mzpch.h.gch -c ./include/mzpch.h -I./lib/spdlog/include"
COMPILE="clang++ -std=c++17 -g ./src/*.cpp ./lib/glad/src/glad.c -I./include -I./lib/spdlog/include -I./lib/stb -I./lib/glm -I./lib/glad/include -I./lib/entt/include -o ./bin/prog -lsdl2 -lsdl2_image -ldl"

#echo ${PRECOMPILEHEADER}
#eval $PRECOMPILEHEADER
echo ${COMPILE}
eval $COMPILE
