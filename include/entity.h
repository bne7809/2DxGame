enum class anim_type
{
	WALK_RIGHT,
	WALK_LEFT,
	WALK_UP,
	WALK_DOWN,

	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_DOWN,

	RUN_RIGHT,
	RUN_LEFT,
	RUN_UP,
	RUN_DOWN
};

struct entity
{
	entity(float x, float y, float vx, float vy);

	UINT state;

	float x;
	float y;
	float vx;
	float vy;

	void reset();
	void translate_cmd(entity_cmd cmd);
};

typedef int (*anim_conv_func)(anim_type t);

struct anim_entity : entity
{
	anim_entity(float x, float y, float vx, float vy, int *d, anim_conv_func cf);

	int *data;
	anim_conv_func conv_func;

	anim_type curr_anim;

	int nframes;
	int row;
	int curr_index;
	int ftime;
	int *frames;
	int *delays;

	inline int get_row() { return row; }
	inline int get_col() { return frames[curr_index]; }

	void update(float dt);
};

#define ENTITY_STATE_LOOK_DOWN	0
#define ENTITY_STATE_LOOK_RIGHT	1
#define ENTITY_STATE_LOOK_UP	2
#define ENTITY_STATE_LOOK_LEFT	3
#define ENTITY_STATE_MOVING		2
