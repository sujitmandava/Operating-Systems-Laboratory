LD_LIBRARY_PATH := lib:$(LD_LIBRARY_PATH)
export LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH

.PHONY: all clear build libs run cleanTest test

all: bin lib bin/main

bin/main: build/main.o lib/libscalar.a lib/libmatrix.so
	g++ -Iinclude src/main.cpp -Llib -lscalar -lmatrix -o bin/main

build/main.o: src/main.cpp
	gcc -c -Iinclude src/main.cpp -o build/main.o

lib/libscalar.a: build/scalarAddition.o build/scalarSubtraction.o build/scalarMultiplication.o build/scalarDivision.o
	ar rcs -o lib/libscalar.a $^

lib/libmatrix.so: build/matrixAddition.o build/matrixSubtraction.o build/matrixMultiplication.o build/matrixDeterminant.o build/matrixTranspose.o
	gcc -shared -o lib/libmatrix.so $^

build/%.o: src/%.cpp	
	gcc -c $< -o $@

bin: 
	mkdir -p bin

lib: 
	mkdir -p lib build

libs: lib lib/libmatrix.so lib/libscalar.a

build: all

run: all
	./bin/main < run.in > run.out

clean: 
	rm -rf lib build bin tests/*.out

cleanTest:
	rm -rf tests/*.out

test: all
	./test.sh