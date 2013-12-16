#include "OSOApplication.h"
#include <Windows.h>

OSO::Application* g_oso_app;

int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{

    OSO::Application app = OSO::Application(hInstance, "dota viewer", 800, 640);
    g_oso_app = &app;

    app.Loop();

	return 0;

}