template <typename T>
struct pool
{
	struct chunk
	{
		chunk *next;
		size_t index;
		T data;
	};

	size_t nchunks;
	chunk *head;

	static constexpr size_t aligned_chunk_size = CEIL_POW2(sizeof(chunk), 16);

	static pool *create(size_t nc)
	{
		pool *ret = (pool *)g_arena->push(sizeof(pool) + nc * aligned_chunk_size);
		ret->nchunks = nc;
		ret->head = (chunk *)((char *)ret + sizeof(pool));


		chunk *c = ret->head;
		for (size_t i = 0; i < nc; ++i)
		{
			if (i == nc - 1)
				c->next = nullptr;
			else
				c->next = (chunk *)((char *)ret + sizeof(pool) + (i + 1) * aligned_chunk_size);
			c->index = i;
			c = c->next;
		}

		return ret;
	}

	T *alloc()
	{
		chunk *c = head;
		head = c->next;
		c->next = nullptr;
		return &c->data;
	}

	void dealloc(T *t)
	{
		chunk *c = (chunk *)((char *)t - offsetof(chunk, data));
		c->next = head;
		head = c;
	}
};
