#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Effect.h"

//-----------------------------------------------------
// Effect Class									
//-----------------------------------------------------

class EffectOpaque final : public Effect
{
public:
	EffectOpaque(ID3D11Device* pDevice, const std::wstring& assetFile);
	~EffectOpaque();

	//-------------------------------------------------
	// Copy/move constructors and assignment operators
	//-------------------------------------------------

	EffectOpaque(const EffectOpaque& other) = delete;
	EffectOpaque(EffectOpaque&& other) noexcept = delete;
	EffectOpaque& operator=(const EffectOpaque& other) = delete;
	EffectOpaque& operator=(EffectOpaque&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual void SetMatrices(dae::Camera* pCamera, const dae::Matrix& worldMatrix) override;

	void SetDiffuseMap(Texture* pDiffuseTexture);
	void SetNormalMap(Texture* pNormalTexture);
	void SetSpecularMap(Texture* pSpecularTexture);
	void SetGlossinessMap(Texture* pGlossinessTexture);

private:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ID3DX11EffectMatrixVariable* m_pViewInverseMatrix;
	ID3DX11EffectMatrixVariable* m_pWorldMatrix;

	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pNormalMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pSpecularMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pGlossinessMapVariable;
};


