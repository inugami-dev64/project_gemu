CPPFLAGS += -I SFML/include
LD_LIBRARY_PATH=SFML/lib

gemu: engine.o main.o objects.o positions.o staging.o stats.o base64.o aes.o calc.o
	g++ engine.o main.o objects.o positions.o staging.o stats.o base64.o aes.o calc.o -o gemu -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

engine.o: src/engine.cpp
	g++ -c src/engine.cpp -I SFML/include

main.o: src/main.cpp
	g++ -c src/main.cpp -I SFML/include

objects.o: src/objects.cpp
	g++ -c src/objects.cpp -I SFML/include

positions.o: src/positions.cpp
	g++ -c src/positions.cpp -I SFML/include

staging.o: src/staging.cpp
	g++ -c src/staging.cpp -I SFML/include

stats.o: src/stats.cpp	
	g++ -c src/stats.cpp -I SFML/include

calc.o: src/calc.cpp
	g++ -c src/calc.cpp

base64.o: aes128cbc/base64cpp/base64.cpp
	g++ -c aes128cbc/base64cpp/base64.cpp

aes.o: aes128cbc/aes.cpp
	g++ -c aes128cbc/aes.cpp -I aes128cbc/base64cpp

clean:
	rm *.o
