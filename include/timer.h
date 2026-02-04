struct timer
{
	LARGE_INTEGER last;
	LARGE_INTEGER freq;

	float delta;

	void tick();
};

void timer_init(timer *t);
