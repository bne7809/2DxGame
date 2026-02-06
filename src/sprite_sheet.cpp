sprite_sheet::sprite_sheet(LPCWSTR file, UINT num_x, UINT num_y, float scale)
{
	fracw = 1.0f / num_x;
	frach = 1.0f / num_y;

	UINT rwidth, rheight;
	load_tex_from_file(file, &srv, &rwidth, &rheight);

	float width = rwidth * scale * fracw;
	float height = rheight * scale * frach;

	float vertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		width, 0.0f, fracw, 0.0f,
		0.0f, height, 0.0f, frach,

		width, 0.0f, fracw, 0.0f,
		width, height, fracw, frach,
		0.0f, height, 0.0f, frach
	};

	D3D11_BUFFER_DESC vb_desc = {};
	vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
	vb_desc.ByteWidth = sizeof(vertices);
	vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vdata = {};
	vdata.pSysMem = vertices;

	g_dev->CreateBuffer(&vb_desc, &vdata, &vert_buff);

	D3D11_BUFFER_DESC cb_desc = {};
	cb_desc.Usage = D3D11_USAGE_DYNAMIC;
	cb_desc.ByteWidth = sizeof(sprite_sheet::sprite_cb);
	cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_dev->CreateBuffer(&cb_desc, nullptr, &const_buff);
}

void sprite_sheet::render(UINT row, UINT col, float x, float y)
{
	DirectX::XMMATRIX tex_mat = DirectX::XMMatrixTranslation(col * fracw, row * frach, 0.0f);
	DirectX::XMMATRIX mod_mat = DirectX::XMMatrixTranslation(x, y, 0.0f);
	DirectX::XMMATRIX ortho = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, WIN_WIDTH, WIN_HEIGHT, 0.0f, 0.0f, 1.0f);
	mod_mat = mod_mat * ortho;

	D3D11_MAPPED_SUBRESOURCE mapped = {};

	g_con->Map(const_buff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	sprite_cb *tmp = (sprite_cb *)mapped.pData;
	DirectX::XMStoreFloat4x4(&tmp->tex_mat, tex_mat);
	DirectX::XMStoreFloat4x4(&tmp->mod_mat, mod_mat);

	g_con->Unmap(const_buff, 0);

	g_con->VSSetConstantBuffers(0, 1, &const_buff);
	g_con->PSSetShaderResources(0, 1, &srv);
	
	UINT stride = 4 * sizeof(float);
	UINT offset = 0;

	g_con->IASetVertexBuffers(0, 1, &vert_buff, &stride, &offset);
	g_con->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_con->Draw(6, 0);
}

void sprite_sheet::release()
{
	srv->Release();
	vert_buff->Release();
	const_buff->Release();
	srv = nullptr;
	vert_buff = nullptr;
	const_buff = nullptr;
}
