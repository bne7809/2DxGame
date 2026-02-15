mem_arena *mem_arena::create(size_t capacity)
{
	mem_arena *ret = (mem_arena *)HeapAlloc(GetProcessHeap(), 0, capacity);
	ret->capacity = capacity;
	ret->pos = sizeof(mem_arena);
	return ret;
}

void mem_arena::release()
{
	HeapFree(GetProcessHeap(), 0, this);
}

void *mem_arena::push(size_t size)
{
	size = CEIL_POW2(size, 16);
	size_t pos_aligned = pos;
	size_t new_pos = pos_aligned + size + sizeof(block_desc);

	if (new_pos > capacity)
	{
		MessageBox(g_hwnd, L"Mem Arena ran out of memory!", nullptr, 0);
		return NULL;
	}

	block_desc *desc = (block_desc *)((char *)this + new_pos - sizeof(block_desc));
	desc->size = size;
	desc->end = 0;

	pos = new_pos;

	return (char *)this + pos_aligned;
}

void mem_arena::pop()
{
	block_desc *desc = (block_desc *)((char *)this + pos - sizeof(block_desc));
	size_t size = desc->size + sizeof(block_desc);
	pos -= size;
}

void mem_arena::begin()
{
	size_t pos_aligned = pos;
	size_t new_pos = pos_aligned + sizeof(block_desc);

	if (new_pos > capacity)
	{
		MessageBox(g_hwnd, L"Mem Arena ran out of memory!", nullptr, 0);
		return;
	}

	block_desc *desc = (block_desc *)((char *)this + pos_aligned);
	desc->size = 0;
	desc->end = 1;

	pos = new_pos;
}

void mem_arena::end()
{
	while (1)
	{
		block_desc *desc = (block_desc *)((char *)this + pos - sizeof(block_desc));
		size_t size = desc->size + sizeof(block_desc);
		pos -= size;
		if (desc->end)
			break;
	}
}
