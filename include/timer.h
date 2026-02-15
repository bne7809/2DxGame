struct timer
{
	LARGE_INTEGER last;
	LARGE_INTEGER freq;

	float delta;

	timer();

	void tick();

	inline operator float() const { return delta; }
};
