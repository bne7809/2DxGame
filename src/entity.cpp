void init_anim_entity(anim_entity *ae, int *d, anim_conv_func cf, anim_type t)
{
	ae->data = d;
	ae->conv_func = cf;
	ae->curr = t;

	int index = d[cf(t)];
	ae->nframes = d[index++];
	ae->row = d[index++];
	ae->curr_index = 0;
	ae->ftime = 0;
	ae->frames = &d[index];
	ae->delays = &d[index + ae->nframes];
}

void anim_entity::update(int dt)
{
	if (ftime >= delays[curr_index])
	{
		curr_index = (curr_index + 1) % nframes;
		ftime = 0;
	} else {
		ftime += dt;
	}
}

bool entity::translate_cmd(entity_cmd cmd)
{
	switch (cmd)
	{
	case entity_cmd::MV_RIGHT:
		BIT_ON(state, ENTITY_STATE_LOOK_RIGHT);
		BIT_ON(state, ENTITY_STATE_MOVING);
		return true;
	case entity_cmd::MV_LEFT:
		BIT_ON(state, ENTITY_STATE_LOOK_LEFT);
		BIT_ON(state, ENTITY_STATE_MOVING);
		return true;
	case entity_cmd::MV_UP:
		BIT_ON(state, ENTITY_STATE_LOOK_UP);
		BIT_ON(state, ENTITY_STATE_MOVING);
		return true;
	case entity_cmd::MV_DOWN:
		BIT_ON(state, ENTITY_STATE_LOOK_DOWN);
		BIT_ON(state, ENTITY_STATE_MOVING);
		return true;
	case entity_cmd::ST_RIGHT:
	case entity_cmd::ST_LEFT:
	case entity_cmd::ST_UP:
	case entity_cmd::ST_DOWN:
		BIT_OFF(state, ENTITY_STATE_MOVING);
		return false;
	default:
		return false;
	}
}
