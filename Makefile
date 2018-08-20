sfml_dir = /home/aszkid/dev/sfml/2.5.0
sfml_libs = -lsfml-graphics -lsfml-window -lsfml-system
json_dir = $(CURDIR)/ext/nlohmann-json-3.1.2
spdlog_dir = $(CURDIR)/ext/spdlog-1.1.0
fmt_dir = $(CURDIR)/ext/fmt-5.1.0

.PHONY: clean
all: build/7days
build/7days: main.cpp tilemap.cpp
	mkdir -p build
	g++ $^ -o $@ -std=c++11 -I$(sfml_dir)/include -I$(json_dir)/include -I$(spdlog_dir)/include -I$(fmt_dir)/include -L$(sfml_dir)/lib $(sfml_libs)
	chmod +x $@
run: build/7days
	cd build; \
	  LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(sfml_dir)/lib ./7days
clean:
	rm -f -r build

