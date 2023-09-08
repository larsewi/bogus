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
	wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.261-jammy.list https://packages.lunarg.com/vulkan/1.3.261/lunarg-vulkan-1.3.261-jammy.list
	sudo apt update
	sudo apt install cmake vulkan-sdk libglfw3-dev libglm-dev libxxf86vm-dev libxi-dev libspdlog-dev
