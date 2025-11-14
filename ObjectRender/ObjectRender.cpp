#include <iostream>
#include "Window.h"
#include "ObjectVertexes.h"

int main()
{
    std::cout << "Hello World!\n";

    RenderWindow window({ 1920, 1080 }, "Test");

    std::thread renderThread(&RenderWindow::CreateWindow, &window);
    //renderThread.join();

    RenderObject obj;
    obj.SetTexturePath("Resources/Textures/container.jpg");
    obj.SetVertexes(cube, sizeof(cube)/sizeof(cube[]));

    window.AddObject(obj);

    std::cout << "Press ENTER to continue...";
    std::cin.get();
}