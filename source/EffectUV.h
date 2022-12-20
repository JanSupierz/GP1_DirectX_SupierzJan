#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Effect.h"

//-----------------------------------------------------
// EffectUV Class									
//-----------------------------------------------------

class EffectUV final : public Effect
{
public:
	EffectUV(ID3D11Device* pDevice, const std::wstring& assetFile);
	~EffectUV() = default;

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	EffectUV(const EffectUV& other) = delete;
	EffectUV(EffectUV&& other) noexcept = delete;
	EffectUV& operator=(const EffectUV& other) = delete;
	EffectUV& operator=(EffectUV&& other)	noexcept = delete;
};


