#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
class Texture;

//-----------------------------------------------------
// Effect Class									
//-----------------------------------------------------
class Effect
{
public:
	Effect() = default;
	Effect(ID3D11Device* pDevice, const std::wstring& assetFile);
	virtual ~Effect();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Effect(const Effect& other) = delete;
	Effect(Effect&& other) noexcept = delete;
	Effect& operator=(const Effect& other) = delete;
	Effect& operator=(Effect&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	ID3DX11Effect* GetEffect() const;
	ID3DX11EffectTechnique* GetTechnique() const;
	ID3D11InputLayout* GetInputLayout() const;

	void SetMatrices(const dae::Matrix& worldViewProjection, const dae::Matrix& world, const dae::Matrix& inverseView);
	void SetSamplerState(ID3D11SamplerState* pSamplerState);
	void SetDiffuseMap(Texture* pDiffuseTexture);
	void SetNormalMap(Texture* pNormalTexture);
	void SetSpecularMap(Texture* pSpecularTexture);
	void SetGlossinessMap(Texture* pGlossinessTexture);

protected:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;
	ID3D11InputLayout* m_pInputLayout;

	ID3DX11EffectMatrixVariable* m_pWorldViewProjectionMatrix;
	ID3DX11EffectMatrixVariable* m_pViewInverseMatrix;
	ID3DX11EffectMatrixVariable* m_pWorldMatrix;

	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pNormalMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pSpecularMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pGlossinessMapVariable;

	ID3DX11EffectSamplerVariable* m_pSamplerStateVariable;
};

