entity::entity(float x, float y, float vx, float vy)
	: state(0), x(x), y(y), vx(vx), vy(vy)
{
}

anim_entity::anim_entity(float x, float y, float vx, float vy, int *d, anim_conv_func cf)
	: entity(x, y, vx, vy), data(d), conv_func(cf), curr_anim(anim_type::IDLE_DOWN)
{
	int index = d[cf(anim_type::IDLE_DOWN)];
	nframes = d[index++];
	row = d[index++];
	curr_index = 0;
	ftime = 0;
	frames = &d[index];
	delays = &d[index + nframes];
}

void anim_entity::update(float dt)
{
	anim_type tmp = curr_anim;
	UINT dir_state = (state & 3);
	float xmul = 0.0f;
	float ymul = 0.0f;

	if (IS_BIT(state, ENTITY_STATE_MOVING))
	{
		if (dir_state == ENTITY_STATE_LOOK_UP)
		{
			ymul = -1.0f;
			curr_anim = anim_type::WALK_UP;
		} else if (dir_state == ENTITY_STATE_LOOK_DOWN) {
			ymul = 1.0f;
			curr_anim = anim_type::WALK_DOWN;
		} else if (dir_state == ENTITY_STATE_LOOK_RIGHT) {
			xmul = 1.0f;
			curr_anim = anim_type::WALK_RIGHT;
		} else if (dir_state == ENTITY_STATE_LOOK_LEFT) {
			xmul = -1.0f;
			curr_anim = anim_type::WALK_LEFT;
		}
	} else {
		if (dir_state == ENTITY_STATE_LOOK_UP)
			curr_anim = anim_type::IDLE_UP;
		else if (dir_state == ENTITY_STATE_LOOK_DOWN)
			curr_anim = anim_type::IDLE_DOWN;
		else if (dir_state == ENTITY_STATE_LOOK_RIGHT)
			curr_anim = anim_type::IDLE_RIGHT;
		else if (dir_state == ENTITY_STATE_LOOK_LEFT)
			curr_anim = anim_type::IDLE_LEFT;
	}

	if (tmp != curr_anim)
	{
		int index = data[conv_func(curr_anim)];
		nframes = data[index++];
		row = data[index++];
		curr_index = 0;
		ftime = 0;
		frames = &data[index];
		delays = &data[index + nframes];
	}

	if (ftime >= delays[curr_index])
	{
		curr_index = (curr_index + 1) % nframes;
		ftime = 0;
	} else {
		ftime += (int)(dt * 1000.0f);
	}

	x += xmul * vx * dt;
	y += ymul * vy * dt;
}

void entity::reset()
{
	BIT_OFF(state, ENTITY_STATE_MOVING);
}

void entity::translate_cmd(entity_cmd cmd)
{
	switch (cmd)
	{
	case entity_cmd::MV_RIGHT:
		state = ((-4) & state) | ENTITY_STATE_LOOK_RIGHT;
		BIT_ON(state, ENTITY_STATE_MOVING);
		return;
	case entity_cmd::MV_LEFT:
		state = ((-4) & state) | ENTITY_STATE_LOOK_LEFT;
		BIT_ON(state, ENTITY_STATE_MOVING);
		return;
	case entity_cmd::MV_UP:
		state = ((-4) & state) | ENTITY_STATE_LOOK_UP;
		BIT_ON(state, ENTITY_STATE_MOVING);
		return;
	case entity_cmd::MV_DOWN:
		state = ((-4) & state) | ENTITY_STATE_LOOK_DOWN;
		BIT_ON(state, ENTITY_STATE_MOVING);
		return;
	default:
		return;
	}
}
