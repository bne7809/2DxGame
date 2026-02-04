void input_buffer::push(entity_cmd c)
{
	if(index < 5)
	{
		buff[index] = c;
		++index;
	}
}
