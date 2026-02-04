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
	IDLE
};

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
