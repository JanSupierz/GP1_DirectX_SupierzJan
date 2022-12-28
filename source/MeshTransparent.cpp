//---------------------------
// Includes
//---------------------------
#include "pch.h"
#include "MeshTransparent.h"
#include "Texture.h"
#include "EffectTransparent.h"

//---------------------------
// Constructor & Destructor
//---------------------------

MeshTransparent::MeshTransparent(ID3D11Device* pDevice, const std::string& filename, Texture* pDiffuseMap)
	:Mesh(pDevice, filename)
{
	PrintTypeName();

	//Effect
	m_pEffect = std::make_unique<EffectTransparent>(pDevice, L"Resources/Transparent.fx");

	SetDiffuseMap(pDiffuseMap);
}

//---------------------------
// Member functions
//---------------------------

void MeshTransparent::PrintTypeName()
{
	std::cout << "----------------------------\n";
	std::cout << "Transparent Mesh\n";
	std::cout << "----------------------------\n";
}

void MeshTransparent::SetDiffuseMap(Texture* pDiffuseMap)
{
	static_cast<EffectTransparent*>(m_pEffect.get())->SetDiffuseMap(pDiffuseMap);
}