extern "C" {
	int _fltused(0x9875);

	double fabs(double x)
	{
		return x < 0.0 ? -x : x;
	}

	void _wassert(wchar_t const* message, wchar_t const* filename, unsigned line)
	{
	}
}
