enum class entity_cmd
{
	NOTHING,
	MV_RIGHT,
	MV_LEFT,
	MV_UP,
	MV_DOWN,
};

struct input_buffer
{
	entity_cmd buff[5];
	union
	{
		int num_cmds;
		int index;
	};

	void push(entity_cmd c);
	inline entity_cmd pop() { return buff[--index]; }
};
