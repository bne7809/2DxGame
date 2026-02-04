void timer_init(timer *t)
{
	QueryPerformanceFrequency(&t->freq);
	QueryPerformanceCounter(&t->last);
}

void timer::tick()
{
	LARGE_INTEGER now;

	QueryPerformanceCounter(&now);
	delta = (float)(now.QuadPart - last.QuadPart) / freq.QuadPart;
	last = now;
}
