#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include <DirectXMath.h>

#include "defs.h"
#include "timer.h"
#include "shader.h"
#include "sprite_sheet.h"
#include "arena.h"
#include "entity.h"
#include "linker.h"
#include "input_buffer.h"

#include "global_defs.cpp"

#include "timer.cpp"
#include "entity.cpp"
#include "tex_load.cpp"
#include "shader.cpp"
#include "sprite_sheet.cpp"
#include "arena.cpp"
#include "globals.cpp"
#include "linker.cpp"
#include "input_buffer.cpp"

void WinMainCRTStartup()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	load_dx_globals();
	load_globals();

	float col[] = { 0.4706f, 0.3176f, 0.6627f, 1.0f };

	vertex_shader vs;
	pixel_shader ps;
	sprite_sheet ss;

	init_vertex_shader(&vs, L"shader_out/anim_sprite_vs.cso", VERT_SHADER_MODE_POSTEX);
	init_pixel_shader(&ps, L"shader_out/def_tex_sample_ps.cso");
	create_sprite_sheet(&ss, L"res/char_a_p1_0bas_humn_v00.png", 8, 8, 2.0f);

	MSG msg;
	while (true)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) goto finish;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_timer.tick();

		for (int i = 0; i < g_ib.num_cmds; ++i)
		{
		}

		G_IBUFF_CLEAR;

		g_con->ClearRenderTargetView(g_target, col);

		vs.bind();
		ps.bind();
		ss.render(4, 6, 100.0f, 100.0f);

		g_swap->Present(1, 0);
		g_con->OMSetRenderTargets(1u, &g_target, nullptr);
	}

finish:
	destroy_sprite_sheet(&ss);
	destroy_pixel_shader(&ps);
	destroy_vertex_shader(&vs);

	free_globals();
	free_dx_globals();
	CoUninitialize();
	ExitProcess(0);
}
