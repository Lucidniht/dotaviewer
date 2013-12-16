#include <fbxsdk.h>

#include "OSOMesh.h"
#include "OSOCamera.h"

#include <d3d11.h>

namespace OSO
{
	typedef std::string String;

	class Application
	{
	public:
		Application(HINSTANCE window_isntance, String cap, UINT w, UINT h);

        ~Application();

        void Loop();

        void InitializeD3D();

        void LoadResource();

	public:
		static LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE window_instance;
		String caption;
		HWND window_handle;

        UINT width;
        UINT height;

        ID3D11Device* d3d11_device;
        IDXGISwapChain* swap_chain;
        ID3D11DeviceContext* d3d11_device_context;

        Camera* camera;

        FbxManager* fbx_manager;
	};




}