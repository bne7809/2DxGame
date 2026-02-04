mem_arena *arena_create(size_t capacity)
{
	mem_arena *ret = (mem_arena *)HeapAlloc(g_proc_heap, 0, capacity);
	ret->capacity = capacity;
	ret->pos = sizeof(mem_arena);
	return ret;
}

void arena_destroy(mem_arena *arena)
{
	HeapFree(g_proc_heap, 0, arena);
}

void *mem_arena::push(size_t size)
{
	size_t pos_aligned = CEIL_POW2(pos, 16);
	size_t new_pos = pos_aligned + size;

	if (new_pos > capacity)
	{
		MessageBox(g_hwnd, L"Mem Arena ran out of memory!", nullptr, 0);
		return NULL;
	}

	pos = new_pos;

	return (char *)this + pos_aligned;
}

void mem_arena::pop(size_t size)
{
	size = min(size, pos - sizeof(mem_arena));
	pos -= size;
}
