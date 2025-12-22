all: clean build run

clean:
	clear
	rm -rf cmake-build-debug
	rm -rf build
	rm -rf .idea

build: 
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build -j

run:
	./build/GameEngineX11

n:
	nvim


# GIT HELPER

MESSAGE = .

push: clean add commit
	git push

add:
	git add .

commit:
	git commit -a -m "$(MESSAGE)"

