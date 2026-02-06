HANDLE g_proc_heap;

HWND g_hwnd;

IDXGISwapChain *g_swap;
ID3D11Device *g_dev;
ID3D11DeviceContext *g_con;
ID3D11RenderTargetView *g_target;
ID3D11BlendState *g_def_blend;
ID3D11SamplerState *g_sampler;

IWICImagingFactory *g_img_factory;

timer g_timer;
mem_arena *g_arena;
linker g_linker;

bool g_key_states[256];

LRESULT CALLBACK gf_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		bool rep = (lParam & (1 << 30)) != 0;
		if (!rep)
		{
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				break;
			}
		}
		g_key_states[wParam] = true;
	}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		g_key_states[wParam] = false;
	}
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
