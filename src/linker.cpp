void linker::add_table_entry(void *key, void *val)
{
	if (table_size < LINKER_TABLE_SIZE)
	{
		keys[table_index] = key;
		vals[table_index] = val;
		++table_index;
	}
}

void linker::stack_push(linker_data d)
{
	if (stack_size < LINKER_STACK_SIZE)
	{
		stack[stack_index++] = d;
	}
}

void linker::exec()
{
	while (stack_size > 0)
	{
		size_t et = stack[--stack_index].exec_type;
		switch (et)
		{
		case 1:
		default:
			break;
		}
	}
}
