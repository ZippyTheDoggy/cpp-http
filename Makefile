FILES = src/*.cpp
OUT = dist/main.exe

OPT = 1
ARG = -Wall
DEP = -pthread

all:
	g++ $(FILES) -o $(OUT) -O$(OPT) $(ARG) $(DEP)

run:
	./$(OUT)