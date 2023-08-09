.PHONY: all configure compile run clean dependencies

all: compile

configure:
	cmake . -DCMAKE_BUILD_TYPE=Debug -B build/

compile:
	make -C build/

run:
	./build/sandbox/sandbox

clean:
	rm -rf build/

dependencies:
	wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
	sudo apt update
	sudo apt install vulkan-sdk libglfw3-dev
