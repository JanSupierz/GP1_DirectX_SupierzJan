//---------------------------
// Includes
//---------------------------
#include "pch.h"
#include "MeshOpaque.h"
#include "Texture.h"
#include "EffectOpaque.h"

//---------------------------
// Constructor & Destructor
//---------------------------

MeshOpaque::MeshOpaque(ID3D11Device* pDevice, const std::string& filename, Texture* pDiffuseMap, Texture* pNormalMap, Texture* pSpecularMap, Texture* pGlossinessMap)
	:Mesh(pDevice, filename)
{
	PrintTypeName();

	//Effect
	m_pEffect = std::make_unique<EffectOpaque>(pDevice, L"Resources/Opaque.fx");

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
	std::cout << "----------------------------\n";
	std::cout << "Opaque Mesh\n";
	std::cout << "----------------------------\n";
}

void MeshOpaque::SetDiffuseMap(Texture* pDiffuseMap)
{
	static_cast<EffectOpaque*>(m_pEffect.get())->SetDiffuseMap(pDiffuseMap);
}

void MeshOpaque::SetNormalMap(Texture* pNormalMap)
{
	static_cast<EffectOpaque*>(m_pEffect.get())->SetNormalMap(pNormalMap);
}

void MeshOpaque::SetSpecularMap(Texture* pSpecularMap)
{
	static_cast<EffectOpaque*>(m_pEffect.get())->SetSpecularMap(pSpecularMap);
}

void MeshOpaque::SetGlossinessMap(Texture* pGlossinessMap)
{
	static_cast<EffectOpaque*>(m_pEffect.get())->SetGlossinessMap(pGlossinessMap);
}


