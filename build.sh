
COMPILE="g++ -std=c++17 -g ./src/*.cpp ./lib/glad/src/glad.c -I./include -I./lib/glad/include -I./lib/entt/include -o ./bin/prog -lsdl2 -lsdl2_image -ldl"
echo ${COMPILE}
eval $COMPILE
