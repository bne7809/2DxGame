struct input_buffer
{
	entity_cmd buff[5];
	union
	{
		int num_cmds;
		int index;
	};

	void push(entity_cmd c);
};

#define G_IBUFF_EMPTY	(g_ib.index == 0)
#define G_IBUFF_CLEAR	g_ib.index = 0
