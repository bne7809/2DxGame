struct mem_arena
{
	size_t capacity;
	size_t pos;

	void *push(size_t size);
	void pop();

	void begin();
	void end();

	static mem_arena *create(size_t capacity);

	void release();
};

struct block_desc
{
	size_t size;
	size_t end;
};
