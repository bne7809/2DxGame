int g_player_anim[] = {
	24, 28, 32, 36, 40, 54, 68, 82, 96, 110, 124, 138, 152, 158, 164, 170, 176, 182, 188, 194, 200, 210, 220, 230,

	1, 0, 0, 1000,
	1, 1, 0, 1000,
	1, 2, 0, 1000,
	1, 3, 0, 1000,

	6, 4, 0, 1, 2, 3, 4, 5, 135, 135, 135, 135, 135, 135,
	6, 5, 0, 1, 2, 3, 4, 5, 135, 135, 135, 135, 135, 135,
	6, 6, 0, 1, 2, 3, 4, 5, 135, 135, 135, 135, 135, 135,
	6, 7, 0, 1, 2, 3, 4, 5, 135, 135, 135, 135, 135, 135,

	6, 4, 0, 1, 6, 3, 4, 7, 80, 55, 125, 80, 55, 125,
	6, 5, 0, 1, 6, 3, 4, 7, 80, 55, 125, 80, 55, 125,
	6, 6, 0, 1, 6, 3, 4, 7, 80, 55, 125, 80, 55, 125,
	6, 7, 0, 1, 6, 3, 4, 7, 80, 55, 125, 80, 55, 125,

	2, 0, 1, 2, 300, 300,
	2, 1, 1, 2, 300, 300,
	2, 2, 1, 2, 300, 300,
	2, 3, 1, 2, 300, 300,

	2, 0, 3, 4, 400, 400,
	2, 1, 3, 4, 400, 400,
	2, 2, 3, 4, 400, 400,
	2, 3, 3, 4, 400, 400,

	4, 0, 5, 6, 7, 5, 300, -1, -2, 300,
	4, 1, 5, 6, 7, 5, 300, -1, -2, 300,
	4, 2, 5, 6, 7, 5, 300, -1, -2, 300,
	4, 3, 5, 6, 7, 5, 300, -1, -2, 300
};

int gf_player_anim_conv(anim_type t)
{
	switch (t)
	{
	case anim_type::WALK_RIGHT:
		return 6;
	case anim_type::WALK_LEFT:
		return 7;
	case anim_type::WALK_UP:
		return 5;
	case anim_type::WALK_DOWN:
		return 4;
	case anim_type::IDLE_RIGHT:
		return 2;
	case anim_type::IDLE_LEFT:
		return 3;
	case anim_type::IDLE_UP:
		return 1;
	case anim_type::IDLE_DOWN:
		return 0;
	case anim_type::RUN_RIGHT:
		return 10;
	case anim_type::RUN_LEFT:
		return 11;
	case anim_type::RUN_UP:
		return 9;
	case anim_type::RUN_DOWN:
		return 8;
	default:
		return -1;
	}
}
