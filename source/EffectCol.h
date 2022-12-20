#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Effect.h"

//-----------------------------------------------------
// EffectUV Class									
//-----------------------------------------------------

class EffectCol final : public Effect
{
public:
	EffectCol(ID3D11Device* pDevice, const std::wstring& assetFile);
	~EffectCol() = default;

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	EffectCol(const EffectCol& other) = delete;
	EffectCol(EffectCol&& other) noexcept = delete;
	EffectCol& operator=(const EffectCol& other) = delete;
	EffectCol& operator=(EffectCol&& other)	noexcept = delete;
};


