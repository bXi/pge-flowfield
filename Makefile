main: 
	g++ -o flow main.cpp flowfield.cpp particle.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17