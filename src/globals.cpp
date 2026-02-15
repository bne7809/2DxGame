void load_dx_globals()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	ID3D11Texture2D *back;

    WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
    wc.hInstance     = hInstance;
    wc.lpfnWndProc   = gf_WindowProc;
    wc.lpszClassName = L"Test";

    RegisterClassEx(&wc);

    g_hwnd = CreateWindowEx(0, L"Test", L"2DxGame", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
							   CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferCount = 2;
	scd.BufferDesc.Width = WIN_WIDTH;
	scd.BufferDesc.Height = WIN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.SampleDesc.Count = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = g_hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
								nullptr, 0, D3D11_SDK_VERSION, &scd, &g_swap, &g_dev, nullptr, &g_con);

	g_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back);
	g_dev->CreateRenderTargetView(back, nullptr, &g_target);

	back->Release();

	g_con->OMSetRenderTargets(1u, &g_target, nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(WIN_WIDTH);
	vp.Height = static_cast<float>(WIN_HEIGHT);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	g_con->RSSetViewports(1, &vp);

	D3D11_BLEND_DESC blend_desc = {};
	blend_desc.RenderTarget[0].BlendEnable = TRUE;
	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	g_dev->CreateBlendState(&blend_desc, &g_def_blend);

	D3D11_SAMPLER_DESC samp_desc = {};
	samp_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samp_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samp_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samp_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samp_desc.MinLOD = 0;
	samp_desc.MaxLOD = D3D11_FLOAT32_MAX;

	g_dev->CreateSamplerState(&samp_desc, &g_sampler);

	g_con->OMSetBlendState(g_def_blend, nullptr, 0xffffffff);
	g_con->PSSetSamplers(0, 1, &g_sampler);

	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_img_factory));

    ShowWindow(g_hwnd, SW_SHOW);
}

void free_dx_globals()
{
	g_img_factory->Release();
	g_sampler->Release();
	g_def_blend->Release();
	g_target->Release();
	g_con->Release();
	g_dev->Release();
	g_swap->Release();
}

void load_globals()
{
	g_arena = arena_create(MiB(12));
}

void free_globals()
{
	g_arena->release();
}
