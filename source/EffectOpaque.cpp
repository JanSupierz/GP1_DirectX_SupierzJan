//---------------------------
// Includes
//---------------------------

#include "pch.h"
#include "EffectOpaque.h"
#include "Texture.h"
#include "Camera.h"

//---------------------------
// Constructor & Destructor
//---------------------------

EffectOpaque::EffectOpaque(ID3D11Device* pDevice, const std::wstring& assetFile)
	:Effect(pDevice, assetFile)
{
	//-----------------------------------------------------
	// Matrices								
	//-----------------------------------------------------

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
}

EffectOpaque::~EffectOpaque()
{
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
}

void EffectOpaque::SetMatrices(dae::Camera* pCamera, const dae::Matrix& worldMatrix)
{
	Effect::SetMatrices(pCamera, worldMatrix);

	m_pWorldMatrix->SetMatrix(reinterpret_cast<const float*>(&(worldMatrix)));
	m_pViewInverseMatrix->SetMatrix(reinterpret_cast<const float*>(&(pCamera->invViewMatrix)));
}

void EffectOpaque::SetDiffuseMap(Texture* pDiffuseTexture)
{
	if (m_pDiffuseMapVariable)
		m_pDiffuseMapVariable->SetResource(pDiffuseTexture->GetResource());
	std::wcout << L"Diffuse map: OK\n";
}

void EffectOpaque::SetNormalMap(Texture* pNormalTexture)
{
	if (m_pNormalMapVariable)
		m_pNormalMapVariable->SetResource(pNormalTexture->GetResource());
	std::wcout << L"Normal map: OK\n";
}

void EffectOpaque::SetSpecularMap(Texture* pSpecularTexture)
{
	if (m_pSpecularMapVariable)
		m_pSpecularMapVariable->SetResource(pSpecularTexture->GetResource());
	std::wcout << L"Specular map: OK\n";
}

void EffectOpaque::SetGlossinessMap(Texture* pGlossinessTexture)
{
	if (m_pGlossinessMapVariable)
		m_pGlossinessMapVariable->SetResource(pGlossinessTexture->GetResource());

	std::wcout << L"Glossines map: OK\n";
}

