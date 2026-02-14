pixel_shader::pixel_shader(LPCWSTR ps_file)
{
	ID3DBlob *pblob;

	HRESULT hr = D3DReadFileToBlob(ps_file, &pblob);
	if (FAILED(hr)) {
        MessageBox(g_hwnd, L"Failed to load pixel shader!", nullptr, 0);
        return;
    }

	g_dev->CreatePixelShader(pblob->GetBufferPointer(), pblob->GetBufferSize(), nullptr, &ps);

	pblob->Release();
}

void pixel_shader::bind()
{
	g_con->PSSetShader(ps, nullptr, 0);
}

void pixel_shader::release()
{
	ps->Release();
	ps = nullptr;
}

vertex_shader::vertex_shader(LPCWSTR vs_file, UINT mode)
{
	ID3DBlob *vblob;

	HRESULT hr = D3DReadFileToBlob(vs_file, &vblob);
	if (FAILED(hr)) {
        MessageBox(g_hwnd, L"Failed to load vertex shader!", nullptr, 0);
        return;
    }

	D3D11_INPUT_ELEMENT_DESC *elem_desc = nullptr;
	UINT n = 0;

	switch (mode)
	{
	case VERT_SHADER_MODE_POSTEX:
		n = 1;
		elem_desc = (D3D11_INPUT_ELEMENT_DESC *)g_arena->push(n * sizeof(D3D11_INPUT_ELEMENT_DESC));
		elem_desc[0] = {"POSTEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
		break;
	case VERT_SHADER_MODE_POS:
		n = 1;
		elem_desc = (D3D11_INPUT_ELEMENT_DESC *)g_arena->push(n * sizeof(D3D11_INPUT_ELEMENT_DESC));
		elem_desc[0] = {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
		break;
	default:
		MessageBox(g_hwnd, L"Invalid vertex shader mode!", nullptr, 0);
		break;
	}

	hr = g_dev->CreateVertexShader(vblob->GetBufferPointer(), vblob->GetBufferSize(), nullptr, &vs);
	if (FAILED(hr)) { MessageBox(g_hwnd, L"CreateVertexShader failed", nullptr, 0); }
	hr = g_dev->CreateInputLayout(elem_desc, n, vblob->GetBufferPointer(), vblob->GetBufferSize(), &layout);
	if (FAILED(hr)) { MessageBox(g_hwnd, L"CreateInputLayout failed", nullptr, 0); }

	g_arena->pop();
	vblob->Release();
}

void vertex_shader::bind()
{
	g_con->VSSetShader(vs, nullptr, 0);
	g_con->IASetInputLayout(layout);
}

void vertex_shader::release()
{
	vs->Release();
	layout->Release();
	vs = nullptr;
	layout = nullptr;
}
