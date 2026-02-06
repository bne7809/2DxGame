void input_buffer::push_no_rep(entity_cmd c)
{
	for (int i = 0; i < num_cmds; ++i)
	{
		if (buff[i] == c)
			return;
	}
	if(index < INPUT_BUFFER_MAX)
		buff[index++] = c;
}

entity_cmd input_buffer::top()
{
	if (num_cmds > 0)
		return buff[index - 1];
	else
		return entity_cmd::NOTHING;
}

entity_cmd input_buffer::pop()
{
	if (num_cmds > 0)
		return buff[--index];
	else
		return entity_cmd::NOTHING;
}

void input_buffer::remove(entity_cmd c)
{
	for (int i = 0; i < num_cmds; ++i)
	{
		if (buff[i] == c)
		{
			for (int j = i; j < num_cmds - 1; ++j)
			{
				buff[j] = buff[j + 1];
			}
			--num_cmds;
			return;
		}
	}
}
