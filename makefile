driver: mshah71proj6.o Airport.o
	g++ -o driver mshah71proj6.o Airport.o

mshah71proj6.o: mshah71proj6.cpp Classes.h
	g++ -c mshah71proj6.cpp

Airport.o: Airport.cpp Classes.h
	g++ -c Airport.cpp

clean:
	rm driver mshah71proj6.o Airport.o