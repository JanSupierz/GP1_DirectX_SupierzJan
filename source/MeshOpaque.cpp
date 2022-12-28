//---------------------------
// Includes
//---------------------------
#include "pch.h"
#include "MeshOpaque.h"
#include "Texture.h"
#include "EffectUV.h"

//---------------------------
// Constructor & Destructor
//---------------------------

MeshOpaque::MeshOpaque(ID3D11Device* pDevice, const std::string& filename, Texture* pDiffuseMap, Texture* pNormalMap, Texture* pSpecularMap, Texture* pGlossinessMap)
	:Mesh(pDevice, filename)
{
	//Effect
	m_pEffect = std::make_unique<EffectUV>(pDevice, L"Resources/Opaque.fx");

	SetDiffuseMap(pDiffuseMap);
	SetNormalMap(pNormalMap);
	SetSpecularMap(pSpecularMap);
	SetGlossinessMap(pGlossinessMap);
}

//---------------------------
// Member functions
//---------------------------

void MeshOpaque::PrintTypeName()
{
	std::cout << "Opaque Mesh\n";
}

void MeshOpaque::SetMatrices(const dae::Matrix& viewProjectionMatrix, const dae::Matrix& viewInverseMatrix)
{
	m_pEffect->SetMatrices(m_WorldMatrix * viewProjectionMatrix, m_WorldMatrix, viewInverseMatrix);
}

void MeshOpaque::SetDiffuseMap(Texture* pDiffuseMap)
{
	m_pEffect->SetDiffuseMap(pDiffuseMap);
}

void MeshOpaque::SetNormalMap(Texture* pNormalMap)
{
	m_pEffect->SetNormalMap(pNormalMap);
}

void MeshOpaque::SetSpecularMap(Texture* pSpecularMap)
{
	m_pEffect->SetSpecularMap(pSpecularMap);
}

void MeshOpaque::SetGlossinessMap(Texture* pGlossinessMap)
{
	m_pEffect->SetGlossinessMap(pGlossinessMap);
}


