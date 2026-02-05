enum class entity_cmd
{
	NOTHING,
	MV_RIGHT,
	ST_RIGHT,
	MV_LEFT,
	ST_LEFT,
	MV_UP,
	ST_UP,
	MV_DOWN,
	ST_DOWN
};

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

typedef int (*anim_conv_func)(anim_type t);

struct anim_entity
{
	int *data;
	anim_conv_func conv_func;

	anim_type curr;

	int nframes;
	int row;
	int curr_index;
	int ftime;
	int *frames;
	int *delays;

	inline int get_row() { return row; }
	inline int get_col() { return frames[curr_index]; }

	void update(int dt);
};

void init_anim_entity(anim_entity *ae, int *d, anim_conv_func cf, anim_type t);

#define ENTITY_STATE_LOOK_RIGHT	1
#define ENTITY_STATE_LOOK_LEFT	2
#define ENTITY_STATE_LOOK_UP	4
#define ENTITY_STATE_LOOK_DOWN	8
#define ENTITY_STATE_MOVING		16
#define ENTITY_STATE_RUNNING	32

struct entity
{
	UINT state;

	float x;
	float y;
	float vx;
	float vy;

	anim_type anim;

	bool translate_cmd(entity_cmd cmd);
};
