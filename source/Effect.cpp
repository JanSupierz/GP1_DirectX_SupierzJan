//---------------------------
// Includes
//---------------------------

#include "pch.h"
#include "Effect.h"
#include "Texture.h"
#include <assert.h>

//---------------------------
// Constructor & Destructor
//---------------------------

Effect::Effect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
	m_pEffect = LoadEffect(pDevice, assetFile);

	m_pTechnique = m_pEffect->GetTechniqueByName("DefaultTechnique");

	if (!m_pTechnique->IsValid())
	{
		std::wcout << L"Technique not valid\n";
	}

	m_pWorldViewProjectionMatrix = m_pEffect->GetVariableByName("gWorldViewProj")->AsMatrix();

	if (!m_pWorldViewProjectionMatrix->IsValid())
	{
		std::wcout << L"WorldViewProjection matrix not valid\n";
	}

	m_pDiffuseMapVariable = m_pEffect->GetVariableByName("gDiffuseMap")->AsShaderResource();

	if (!m_pDiffuseMapVariable->IsValid())
	{
		std::wcout << L"Diffuse map not valid\n";
	}
}

Effect::~Effect()
{
	m_pInputLayout->Release();

	m_pDiffuseMapVariable->Release();
	m_pWorldViewProjectionMatrix->Release();
	m_pTechnique->Release();
	m_pEffect->Release();
}

//---------------------------
// Member functions
//---------------------------

ID3DX11Effect* Effect::GetEffect() const
{
	return m_pEffect;
}

ID3DX11EffectTechnique* Effect::GetTechnique() const
{
	return m_pTechnique;
}

ID3D11InputLayout* Effect::GetInputLayout() const
{
	return m_pInputLayout;
}

void Effect::SetMatrix(const dae::Matrix& matrix)
{
	m_pWorldViewProjectionMatrix->SetMatrix(reinterpret_cast<const float*>(&matrix));
}

void Effect::SetDiffuseMap(Texture* pDiffuseTexture)
{
	if (m_pDiffuseMapVariable)
		m_pDiffuseMapVariable->SetResource(pDiffuseTexture->GetResource());
}

ID3DX11Effect* Effect::LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
	HRESULT result;
	ID3D10Blob* pErrorBlob{ nullptr };
	ID3DX11Effect* pEffect;

	DWORD shaderFlags{ 0 };

#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	result = D3DX11CompileEffectFromFile(assetFile.c_str(), nullptr, nullptr, shaderFlags, 0, pDevice, &pEffect, &pErrorBlob);

	if (FAILED(result))
	{
		if (pErrorBlob != nullptr)
		{
			const char* pErrors = static_cast<char*>(pErrorBlob->GetBufferPointer());

			std::wstringstream ss;
			for (unsigned int i{}; i < pErrorBlob->GetBufferSize(); ++i)
			{
				ss << pErrors[i];
			}

			OutputDebugStringW(ss.str().c_str());
			pErrorBlob->Release();
			pErrorBlob = nullptr;

			std::wcout << ss.str() << std::endl;
		}
		else
		{
			std::wstringstream ss;
			ss << "EffectLoader: Failed to CreateEffectFromFile!\nPath: " << assetFile;
			std::wcout << ss.str() << std::endl;

			return nullptr;
		}
	}

	return pEffect;
}
