build:	Matrix.cpp
	clang++ Matrix.cpp -o Matrix

run:	Matrix
	@./Matrix

vim:	Matrix.cpp
	vim Matrix.cpp

go:	Matrix.cpp Matrix
	clang++ Matrix.cpp -o Matrix
	./Matrix
