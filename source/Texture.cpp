//---------------------------
// Includes
//---------------------------

#include "pch.h"
#include "Texture.h"
#include "assert.h"

//---------------------------
// Constructor & Destructor
//---------------------------

Texture::Texture(ID3D11Device* pDevice, const std::string& path)
{
	SDL_Surface* pSurface{ IMG_Load(path.c_str()) };

	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = pSurface->w;
	desc.Height = pSurface->h;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = pSurface->pixels;
	initData.SysMemPitch = static_cast<UINT>(pSurface->pitch);
	initData.SysMemSlicePitch = static_cast<UINT>(pSurface->h * pSurface->pitch);

	HRESULT result = pDevice->CreateTexture2D(&desc, &initData, &m_pResource);
	if (FAILED(result)) assert(false);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
	SRVDesc.Format = format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	result = pDevice->CreateShaderResourceView(m_pResource, &SRVDesc, &m_pSRV);
	if (FAILED(result)) assert(false);

	SDL_FreeSurface(pSurface);

	m_pRed = new Uint8;
	m_pGreen = new Uint8;
	m_pBlue = new Uint8;
}

Texture::~Texture()
{
	delete m_pRed;
	delete m_pGreen;
	delete m_pBlue;

	m_pSRV->Release();
	m_pResource->Release();
}

//---------------------------
// Member functions
//---------------------------

ID3D11ShaderResourceView* Texture::GetResource() const
{
	return m_pSRV;
}

dae::ColorRGB Texture::Sample(const dae::Vector2& uv) const
{
	//Sample the correct texel for the given uv

	SDL_GetRGB(m_pSurfacePixels[static_cast<Uint32>(int(uv.x * m_pSurface->w) + int(uv.y * m_pSurface->h) * m_pSurface->w)], m_pSurface->format, m_pRed, m_pGreen, m_pBlue);

	return { *m_pRed / 255.f, *m_pGreen / 255.f, *m_pBlue / 255.f };
}