default:
	g++ ../game.cpp -o game.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	g++ ../main2.cpp -o main2.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	rm -f game.exe main2.exe	
run:
	main2.exe	
#clean build and run
cleanrun:
	rm -f game.exe main2.exe
	g++ ../game.cpp -o game.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	g++ ../main2.cpp  -o main2.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	main2.exe
linux:
	g++ ../game.cpp -o game.out -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	g++ ../main2.cpp -o main.out -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./game.out