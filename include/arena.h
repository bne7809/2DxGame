struct mem_arena
{
	size_t capacity;
	size_t pos;

	void *push(size_t size);
	void pop(size_t size);
};

mem_arena *arena_create(size_t capacity);

void arena_destroy(mem_arena *arena);
