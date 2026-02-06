enum class entity_cmd
{
	NOTHING,
	MV_RIGHT,
	MV_LEFT,
	MV_UP,
	MV_DOWN,
};

#define INPUT_BUFFER_MAX	5

struct input_buffer
{
	entity_cmd buff[INPUT_BUFFER_MAX];
	union
	{
		int num_cmds;
		int index;
	};

	void push_no_rep(entity_cmd c);
	void remove(entity_cmd c);

	entity_cmd top();
	entity_cmd pop();
};
