#define CEIL_POW2(x, p)		(((x) + (p) - 1) & (~((p) - 1)))
#define FLOOR_POW2(x, p)	((x) & (~((p) - 1)))
#define ROUND_POW2(x, p)	(((x) + ((p) >> 1)) & (~((p) - 1)))

#define KiB(n)				((size_t)(n) << 10)
#define MiB(n)				((size_t)(n) << 20)
#define GiB(n)				((size_t)(n) << 30)

#define BIT_ON(flag, pos)	((flag) |= (1 << (pos)))
#define BIT_OFF(flag, pos)	((flag) &= ~(1 << (pos)))
#define IS_BIT(flag, pos)	(((flag) >> (pos)) & 1)

#define WIN_WIDTH	1280
#define WIN_HEIGHT	720
