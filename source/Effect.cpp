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
	
	//-----------------------------------------------------
	// Techniques								
	//-----------------------------------------------------

	m_pTechnique = m_pEffect->GetTechniqueByName("DefaultTechnique");

	if (!m_pTechnique->IsValid())
	{
		std::wcout << L"Technique not valid\n";
	}

	//-----------------------------------------------------
	// Matrices								
	//-----------------------------------------------------

	m_pWorldViewProjectionMatrix = m_pEffect->GetVariableByName("gWorldViewProj")->AsMatrix();

	if (!m_pWorldViewProjectionMatrix->IsValid())
	{
		std::wcout << L"WorldViewProjection matrix not valid\n";
	}

	m_pWorldMatrix = m_pEffect->GetVariableByName("gWorld")->AsMatrix();

	if (!m_pWorldMatrix->IsValid())
	{
		std::wcout << L"World matrix not valid\n";
	}

	m_pViewInverseMatrix = m_pEffect->GetVariableByName("gViewInverse")->AsMatrix();

	if (!m_pViewInverseMatrix->IsValid())
	{
		std::wcout << L"View inverse matrix not valid\n";
	}

	//-----------------------------------------------------
	// Maps								
	//-----------------------------------------------------

	m_pDiffuseMapVariable = m_pEffect->GetVariableByName("gDiffuseMap")->AsShaderResource();

	if (!m_pDiffuseMapVariable->IsValid())
	{
		std::wcout << L"Diffuse map not valid\n";
	}

	m_pNormalMapVariable = m_pEffect->GetVariableByName("gNormalMap")->AsShaderResource();

	if (!m_pNormalMapVariable->IsValid())
	{
		std::wcout << L"Normal map not valid\n";
	}

	m_pSpecularMapVariable = m_pEffect->GetVariableByName("gSpecularMap")->AsShaderResource();

	if (!m_pSpecularMapVariable->IsValid())
	{
		std::wcout << L"Specular map not valid\n";
	}

	m_pGlossinessMapVariable = m_pEffect->GetVariableByName("gGlossinessMap")->AsShaderResource();

	if (!m_pGlossinessMapVariable->IsValid())
	{
		std::wcout << L"Glossiness map not valid\n";
	}

	//-----------------------------------------------------
	// States								
	//-----------------------------------------------------

	m_pSamplerStateVariable = m_pEffect->GetVariableByName("gSamplerState")->AsSampler();

	if (!m_pSamplerStateVariable->IsValid())
	{
		std::wcout << L"Sampler state not valid\n";
	}
}

Effect::~Effect()
{
	if (m_pInputLayout)
	{
		m_pInputLayout->Release();
	}

	if (m_pSamplerStateVariable)
	{
		m_pSamplerStateVariable->Release();
	}

	//Maps

	if (m_pGlossinessMapVariable)
	{
		m_pGlossinessMapVariable->Release();
	}

	if (m_pSpecularMapVariable)
	{
		m_pSpecularMapVariable->Release();
	}

	if (m_pNormalMapVariable)
	{
		m_pNormalMapVariable->Release();
	}

	if (m_pDiffuseMapVariable)
	{
		m_pDiffuseMapVariable->Release();
	}
	
	//Matrices

	if (m_pViewInverseMatrix)
	{
		m_pViewInverseMatrix->Release();
	}

	if (m_pWorldMatrix)
	{
		m_pWorldMatrix->Release();
	}

	if (m_pWorldViewProjectionMatrix)
	{
		m_pWorldViewProjectionMatrix->Release();
	}

	if (m_pTechnique)
	{
		m_pTechnique->Release();
	}

	if (m_pEffect)
	{
		m_pEffect->Release();
	}
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

void Effect::SetMatrices(const dae::Matrix& worldViewProjection, const dae::Matrix& world, const dae::Matrix& viewInverse)
{
	m_pWorldViewProjectionMatrix->SetMatrix(reinterpret_cast<const float*>(&worldViewProjection));
	m_pWorldMatrix->SetMatrix(reinterpret_cast<const float*>(&world));
	m_pViewInverseMatrix->SetMatrix(reinterpret_cast<const float*>(&viewInverse));
}

void Effect::SetSamplerState(ID3D11SamplerState* pSamplerState)
{
	HRESULT hr{ m_pSamplerStateVariable->SetSampler(0, pSamplerState) };
	if (FAILED(hr)) std::wcout << L"Failed to change sample state";
}

void Effect::SetDiffuseMap(Texture* pDiffuseTexture)
{
	if (m_pDiffuseMapVariable)
		m_pDiffuseMapVariable->SetResource(pDiffuseTexture->GetResource());
	std::wcout << L"Diffuse map: OK\n";
}

void Effect::SetNormalMap(Texture* pNormalTexture)
{
	if (m_pNormalMapVariable)
		m_pNormalMapVariable->SetResource(pNormalTexture->GetResource());
	std::wcout << L"Normal map: OK\n";
}

void Effect::SetSpecularMap(Texture* pSpecularTexture)
{
	if (m_pSpecularMapVariable)
		m_pSpecularMapVariable->SetResource(pSpecularTexture->GetResource());
	std::wcout << L"Specular map: OK\n";
}

void Effect::SetGlossinessMap(Texture* pGlossinessTexture)
{
	if (m_pGlossinessMapVariable)
		m_pGlossinessMapVariable->SetResource(pGlossinessTexture->GetResource());

	std::wcout << L"Glossines map: OK\n";
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
