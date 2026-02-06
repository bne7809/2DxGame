struct pixel_shader
{
	pixel_shader(LPCWSTR ps_file);

	ID3D11PixelShader *ps;

	void bind();
	void release();
};

#define VERT_SHADER_MODE_POSTEX	0
#define VERT_SHADER_MODE_POS	1

struct vertex_shader
{
	vertex_shader(LPCWSTR vs_file, UINT mode);

	ID3D11VertexShader *vs;
	ID3D11InputLayout *layout;

	void bind();
	void release();
};
