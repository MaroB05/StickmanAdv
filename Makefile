filename=stickman
compile:
	mkdir -p build
	g++ -W src/main.cpp -o ./build/$(filename)

run:
	./build/$(filename)

debug:
	g++ src/main.cpp -g -o ./build/$(filename)
	gdb ./build/$(filename)

memdebug:
	g++ src/main.cpp -g -o ./build/$(filename)
	valgrind ./build/$(filename)
