#define LINKER_TABLE_SIZE	16
#define LINKER_STACK_SIZE	128

union linker_data
{
	size_t exec_type;
	void *from;
	struct
	{
		float f1;
		float f2;
	};
	struct
	{
		int i1;
		int i2;
	};
};

struct linker
{
	union
	{
		int stack_index;
		int stack_size;
	};

	linker_data stack[LINKER_STACK_SIZE];

	union
	{
		int table_index;
		int table_size;
	};

	void *keys[LINKER_TABLE_SIZE];
	void *vals[LINKER_TABLE_SIZE];

	void stack_push(linker_data d);
	void add_table_entry(void *key, void *val);
	void remove_table_entry(void *key);
	void exec();
};
