#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Effect.h"

//-----------------------------------------------------
// EffectUV Class									
//-----------------------------------------------------

class EffectTransparent final : public Effect
{
public:
	EffectTransparent(ID3D11Device* pDevice, const std::wstring& assetFile);
	~EffectTransparent();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	EffectTransparent(const EffectTransparent& other) = delete;
	EffectTransparent(EffectTransparent&& other) noexcept = delete;
	EffectTransparent& operator=(const EffectTransparent& other) = delete;
	EffectTransparent& operator=(EffectTransparent&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void SetDiffuseMap(Texture* pDiffuseTexture);

private:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;
};


