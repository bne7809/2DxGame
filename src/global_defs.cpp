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
input_buffer g_ib;
linker g_linker;

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
			switch (wParam)
			{
			case 'W':
				g_ib.push(entity_cmd::MV_UP);
				break;
			case 'A':
				g_ib.push(entity_cmd::MV_LEFT);
				break;
			case 'S':
				g_ib.push(entity_cmd::MV_DOWN);
				break;
			case 'D':
				g_ib.push(entity_cmd::MV_RIGHT);
				break;
			}
		}
	}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		switch (wParam)
		{
		case 'W':
			g_ib.push(entity_cmd::ST_UP);
			break;
		case 'A':
			g_ib.push(entity_cmd::ST_LEFT);
			break;
		case 'S':
			g_ib.push(entity_cmd::ST_DOWN);
			break;
		case 'D':
			g_ib.push(entity_cmd::ST_RIGHT);
			break;
		}
	}
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
