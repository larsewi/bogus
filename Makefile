.PHONY: all configure build run clean dependencies

all: configure build run

configure:
	cmake . -DCMAKE_BUILD_TYPE=Debug -B build/

build:
	make -C build/

run:
	./build/sandbox/sandbox

clean:
	git clean -fxd

dependencies:
	wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
	sudo apt update
	sudo apt install vulkan-sdk libglfw3-dev
