struct sprite_sheet
{
	struct sprite_cb
	{
		DirectX::XMFLOAT4X4 tex_mat;
		DirectX::XMFLOAT4X4 mod_mat;
	};

	ID3D11Buffer *vert_buff;
	ID3D11Buffer *const_buff;
	ID3D11ShaderResourceView *srv;

	float fracw;
	float frach;

	void render(UINT row, UINT col, float x, float y);
};

void create_sprite_sheet(sprite_sheet *ss, LPCWSTR file, UINT num_x, UINT num_y, float scale);
void destroy_sprite_sheet(sprite_sheet *ss);
