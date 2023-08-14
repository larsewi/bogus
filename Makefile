.PHONY: all debug release clean dependencies

all: debug

debug:
	clang-format -i engine/*.?pp sandbox/*.?pp
	cmake . -DCMAKE_BUILD_TYPE=Debug -B build/
	make -C build/
	./build/sandbox/sandbox

release:
	clang-format -i engine/*.?pp sandbox/*.?pp
	cmake . -DCMAKE_BUILD_TYPE=Release -B build/
	make -C build/
	./build/sandbox/sandbox

clean:
	rm -rf build/

dependencies:
	wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
	sudo apt update
	sudo apt install vulkan-sdk libglfw3-dev libglm-dev libxxf86vm-dev libxi-dev
