void load_tex_from_file(LPCWSTR file, ID3D11ShaderResourceView **out_srv, UINT *out_w, UINT *out_h)
{
	IWICBitmapDecoder *decoder = nullptr;
	HRESULT hr = g_img_factory->CreateDecoderFromFilename(file, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr) || decoder == nullptr) {
		MessageBox(g_hwnd, L"Failed to load image!", nullptr, 0);
		return;
	}

	IWICBitmapFrameDecode *frame = nullptr;
	decoder->GetFrame(0, &frame);

	IWICFormatConverter *converter = nullptr;
	g_img_factory->CreateFormatConverter(&converter);

	converter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);

	UINT width, height;
	frame->GetSize(&width, &height);

	UINT size = width * height * 4;

	BYTE *pixels = (BYTE *)g_arena->push(size);

	converter->CopyPixels(nullptr, width * 4, size, pixels);

	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.Usage = D3D11_USAGE_IMMUTABLE;
	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA s_data = {};
	s_data.pSysMem = pixels;
	s_data.SysMemPitch = width * 4;

	ID3D11Texture2D *texture = nullptr;
	g_dev->CreateTexture2D(&tex_desc, &s_data, &texture);

	g_dev->CreateShaderResourceView(texture, nullptr, out_srv);
	*out_w = width;
	*out_h = height;

	g_arena->pop(size);
	texture->Release();
	converter->Release();
	frame->Release();
	decoder->Release();
}
