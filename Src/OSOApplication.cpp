#include "OSOApplication.h"


namespace OSO
{

	Application* g_oso_app;

	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Forward hwnd on because we can get messages (e.g., WM_CREATE)
		// before CreateWindow returns, and thus before mhMainWnd is valid.
		return g_oso_app->MsgProc(hwnd, msg, wParam, lParam);
	}


	Application::Application(HINSTANCE _wisntance, String cap, UINT w, UINT h) :
		window_instance(_wisntance), caption(cap), width(w), height(h), camera(NULL)
	{
		WNDCLASSEX wc;
		wc.style         = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc   = MainWndProc; 
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = _wisntance;
		wc.hIcon         = LoadIcon(_wisntance, IDI_APPLICATION);
		wc.hCursor       = LoadCursor(_wisntance, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName  = 0;
		wc.lpszClassName = "D3DWndClassName";
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.hIconSm       = 0;

		if( !RegisterClassEx(&wc) )
		{
			MessageBox(0, "RegisterClass Failed.", 0, 0);
			return;
		}

		// Compute window rectangle dimensions based on requested client area dimensions.
		RECT R = { 0, 0, w, h };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, FALSE);

		window_handle = CreateWindow(wc.lpszClassName, caption.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, R.right - R.left, R.bottom - R.top, 0, 0, _wisntance, 0); 
		if( !window_handle )
		{
			MessageBox(0, "CreateWindow Failed.", 0, 0);
			return;
		}

		ShowWindow(window_handle, SW_SHOW);
		UpdateWindow(window_handle);

        InitializeD3D();

        LoadResource();
	}

    Application::~Application()
    {
        if(camera)
            delete camera;
    }

    void Application::InitializeD3D()
    {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory( &sd, sizeof( sd ) );
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = window_handle;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        UINT flag = 0;
        #ifdef _DEBUG
        flag |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };

        UINT numFeatureLevels = ARRAYSIZE( featureLevels );

        LRESULT hr = D3D11CreateDeviceAndSwapChain( NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &swap_chain, &d3d11_device, NULL, &d3d11_device_context );

        if(FAILED(hr))
        {
            return;
        }

        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        d3d11_device_context->RSSetViewports( 1, &vp );

        camera = new Camera;
        

    }

    void Application::LoadResource()
    {
        FbxManager* fbx_manager = FbxManager::Create();

        FbxIOSettings* ios = FbxIOSettings::Create(fbx_manager, IOSROOT);
	    fbx_manager->SetIOSettings(ios);


        FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "My Scene");


        std::vector<String> file_names;

        file_names.push_back(".\\..\\Asserts\\forge_spirit.fbx");
        file_names.push_back(".\\..\\Asserts\\invoker_arms.fbx");
        file_names.push_back(".\\..\\Asserts\\invoker_back.fbx");
        file_names.push_back(".\\..\\Asserts\\invoker_body.fbx");
        file_names.push_back(".\\..\\Asserts\\invoker_head.fbx");
        file_names.push_back(".\\..\\Asserts\\invoker_shoulders.fbx");

        for(size_t i = 0; i < file_names.size(); ++i)
        {


        }
        
    }

    void Application::Loop()
    {
        MSG msg = {0};
        while( WM_QUIT != msg.message )
        {
            if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
    }


	LRESULT Application::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
        return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}