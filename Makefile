clean:
	rm -rf build
	mkdir build

configure:
	cmake -B build -S . -G "Unix Makefiles"

build_p:
	cmake --build build --target FEM_project --config Debug -j 10
run:
	./build/src/FEM_project.exe

run_test_area:
	./build/src/FEM_project.exe examples/omega/test_area.msh examples/omega/dirichlet.txt examples/omega/neuman.txt examples/omega/parameters.txt

run_omega:
	./build/src/FEM_project.exe examples/omega/omega.msh examples/omega/dirichlet.txt examples/omega/neuman.txt examples/omega/parameters.txt
