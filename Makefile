run: clean
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build -j
	./build/GameEngineX11

clean:
	rm -rf cmake-build-debug
	rm -rf build
