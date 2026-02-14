struct mem_arena
{
	size_t capacity;
	size_t pos;

	void *push(size_t size);
	void pop();

	void begin();
	void end();

	void release();
};

struct block_desc
{
	size_t size;
	size_t end;
};

mem_arena *arena_create(size_t capacity);
