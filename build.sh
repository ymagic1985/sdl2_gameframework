
#PRECOMPILEHEADER="g++ -std=c++17 -x c++-header -o ./include/mzpch.h.gch -c ./include/mzpch.h -I./lib/spdlog/include"
COMPILE="clang++ -std=c++17 -v -g ./engine/src/*.cpp ./sandbox/src/*.cpp  ./engine/lib/glad/src/glad.c -I./sandbox/include -I./engine/include -I./engine/lib/spdlog/include -I./engine/lib/stb -I./engine/lib/glm -I./engine/lib/glad/include -I./engine/lib/entt/include -o ./bin/prog -lsdl2 -lsdl2_image -ldl"

#echo ${PRECOMPILEHEADER}
#eval $PRECOMPILEHEADER
echo ${COMPILE}
eval $COMPILE
