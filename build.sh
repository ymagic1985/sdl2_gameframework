
#PRECOMPILEHEADER="g++ -std=c++17 -x c++-header -o ./include/mzpch.h.gch -c ./include/mzpch.h -I./lib/spdlog/include"
#Compile options:
#"-D MAN520_DEBUG" 
COMPILE="clang++ -std=c++17 -D MAN520_DEBUG -g $(find ./engine -type f -iregex ".*\.cpp") ./sandbox/src/*.cpp ./lib/glad/src/glad.c -I./sandbox/include -I./engine -I./lib/spdlog/include -I./lib/stb -I./lib/glm -I./lib/glad/include -I./lib/entt/include -o ./bin/prog -lsdl2 -lsdl2_image -ldl"

#echo ${PRECOMPILEHEADER}
#eval $PRECOMPILEHEADER
echo ${COMPILE}
eval $COMPILE
