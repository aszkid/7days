sfml_dir = /home/aszkid/dev/sfml/2.5.0
sfml_libs = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean
all: 7days
7days: main.cpp
	mkdir -p build
	g++ $< -o build/7days -I$(sfml_dir)/include -L$(sfml_dir)/lib $(sfml_libs)
	chmod +x build/7days
run: 7days
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(sfml_dir)/lib ./build/7days
clean:
	rm -f -r build

