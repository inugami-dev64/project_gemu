CPPFLAGS += -I SFML/include
LD_LIBRARY_PATH=SFML/lib

gemu: engine.o main.o objects.o positions.o staging.o stats.o base64.o aes.o	
	g++ engine.o main.o objects.o positions.o staging.o stats.o base64.o aes.o -o gemu -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

engine.o: engine.cpp
	g++ -c engine.cpp -I SFML/include

main.o: main.cpp
	g++ -c main.cpp -I SFML/include

objects.o: objects.cpp
	g++ -c objects.cpp -I SFML/include

positions.o: positions.cpp
	g++ -c positions.cpp -I SFML/include

staging.o: staging.cpp
	g++ -c staging.cpp -I SFML/include

stats.o: stats.cpp	
	g++ -c stats.cpp -I SFML/include

base64.o: aes128cbc/base64cpp/base64.cpp
	g++ -c aes128cbc/base64cpp/base64.cpp

aes.o: aes128cbc/aes.cpp
	g++ -c aes128cbc/aes.cpp -I aes128cbc/base64cpp

clean:
	rm *.o
