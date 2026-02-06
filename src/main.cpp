#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include <DirectXMath.h>

#include "defs.h"
#include "timer.h"
#include "input_buffer.h"
#include "shader.h"
#include "sprite_sheet.h"
#include "arena.h"
#include "entity.h"
#include "linker.h"

#include "global_defs.cpp"
#include "global_data.cpp"

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

	input_buffer ib = {};

	vertex_shader vs(L"shader_out/anim_sprite_vs.cso", VERT_SHADER_MODE_POSTEX);
	pixel_shader ps(L"shader_out/def_tex_sample_ps.cso");
	sprite_sheet ss(L"res/char_a_p1_0bas_humn_v00.png", 8, 8, 2.0f);

	anim_entity ae(100.0f, 100.0f, 100.0f, 100.0f, g_player_anim, gf_player_anim_conv);

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

		if (g_key_states['W'])
			ib.push(entity_cmd::MV_UP);
		if (g_key_states['S'])
			ib.push(entity_cmd::MV_DOWN);
		if (g_key_states['D'])
			ib.push(entity_cmd::MV_RIGHT);
		if (g_key_states['A'])
			ib.push(entity_cmd::MV_LEFT);

		ae.reset();

		for (int i = 0; i < ib.num_cmds; ++i)
		{
			ae.translate_cmd(ib.buff[i]);
		}

		ib.num_cmds = 0;

		ae.update(g_timer.delta);

		g_con->ClearRenderTargetView(g_target, col);

		vs.bind();
		ps.bind();
		ss.render(ae.get_row(), ae.get_col(), ae.x, ae.y);

		g_swap->Present(1, 0);
		g_con->OMSetRenderTargets(1u, &g_target, nullptr);
	}

finish:
	ss.release();
	ps.release();
	vs.release();

	free_globals();
	free_dx_globals();
	CoUninitialize();
	ExitProcess(0);
}
