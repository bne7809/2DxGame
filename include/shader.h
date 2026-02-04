struct pixel_shader
{
	ID3D11PixelShader *ps;

	void bind();
};

#define VERT_SHADER_MODE_POSTEX	0
#define VERT_SHADER_MODE_POS	1

struct vertex_shader
{
	ID3D11VertexShader *vs;
	ID3D11InputLayout *layout;

	void bind();
};

void init_pixel_shader(pixel_shader *s, LPCWSTR ps_file);
void destroy_pixel_shader(pixel_shader *s);

void init_vertex_shader(vertex_shader *s, LPCWSTR vs_file, UINT mode);
void destroy_vertex_shader(vertex_shader *s);
