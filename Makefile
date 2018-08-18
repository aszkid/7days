sfml_dir = /home/aszkid/dev/sfml/2.5.0
sfml_libs = -lsfml-graphics -lsfml-window -lsfml-system
json_dir = $(CURDIR)/ext/nlohmann-json-3.1.2

.PHONY: clean
all: 7days
7days: main.cpp
	mkdir -p build
	g++ $< -o build/7days -std=c++11 -I$(sfml_dir)/include -I$(json_dir)/include -L$(sfml_dir)/lib $(sfml_libs)
	chmod +x build/7days
run: 7days
	cd build; \
	  LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(sfml_dir)/lib ./7days
clean:
	rm -f -r build

