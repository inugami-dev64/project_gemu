CXX = g++
TARGET = gemu
OBJ = engine.cpp.o \
	  main.cpp.o \
	  objects.cpp.o \
	  positions.cpp.o \
	  staging.cpp.o \
	  stats.cpp.o \
	  base64.cpp.o \
	  aes.cpp.o \
	  calc.cpp.o 

LD_FLAGS = -lsfml-graphics \
		   -lsfml-window \
		   -lsfml-system


$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LD_FLAGS)

engine.cpp.o: src/engine.cpp
	$(CXX) -c src/engine.cpp -o engine.cpp.o

main.cpp.o: src/main.cpp
	$(CXX) -c src/main.cpp -o main.cpp.o

objects.cpp.o: src/objects.cpp
	$(CXX) -c src/objects.cpp -o objects.cpp.o

positions.cpp.o: src/positions.cpp
	$(CXX) -c src/positions.cpp -o positions.cpp.o

staging.cpp.o: src/staging.cpp
	$(CXX) -c src/staging.cpp -o staging.cpp.o

stats.cpp.o: src/stats.cpp	
	$(CXX) -c src/stats.cpp -o stats.cpp.o

calc.cpp.o: src/calc.cpp
	$(CXX) -c src/calc.cpp -o calc.cpp.o

base64.cpp.o: aes128cbc/base64cpp/base64.cpp
	$(CXX) -c aes128cbc/base64cpp/base64.cpp -o base64.cpp.o

aes.cpp.o: aes128cbc/aes.cpp
	$(CXX) -c aes128cbc/aes.cpp -I aes128cbc/base64cpp -o aes.cpp.o

clean:
	rm -rf gemu
	rm *.o
