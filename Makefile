all: build run

build:
	$(CMAKE_CMD) -S . -B ./cmake-build-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64
	$(CMAKE_CMD) --build ./cmake-build-debug --target GameEngineX11

run:
	./cmake-build-debug/GameEngineX11

clean:
	rm -rf ./cmake-build-debug