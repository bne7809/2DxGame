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
