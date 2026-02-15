struct pixel_shader
{
	pixel_shader(LPCWSTR ps_file);

	ID3D11PixelShader *ps;

	void bind();
	void release();
};

enum class vshadermode
{
	POSTEX,
	POS
};

struct vertex_shader
{
	vertex_shader(LPCWSTR vs_file, vshadermode mode);

	ID3D11VertexShader *vs;
	ID3D11InputLayout *layout;

	void bind();
	void release();
};
