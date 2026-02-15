timer::timer()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);
}

void timer::tick()
{
	LARGE_INTEGER now;

	QueryPerformanceCounter(&now);
	delta = (float)(now.QuadPart - last.QuadPart) / freq.QuadPart;
	last = now;
}
