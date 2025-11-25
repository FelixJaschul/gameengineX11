all: build run


build: bin
	g++ -O3 game.cpp -DOLIVEC_IMPLEMENTATION -Iext -I/opt/homebrew/include -L/opt/homebrew/lib -lX11 -lm -o bin/game

run:
	./bin/game
	clear

clean:
	rm -rf bin
	mkdir bin

git:
	rm -rf bin .idea
	git add . 
	git commit -a -m "AUTO COMMIT" 
	git push
	mkdir bin
