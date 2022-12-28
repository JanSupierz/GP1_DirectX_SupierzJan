//---------------------------
// Includes
//---------------------------
#include "pch.h"
#include "MeshTransparent.h"
#include "Texture.h"
#include "EffectUV.h"

//---------------------------
// Constructor & Destructor
//---------------------------

MeshTransparent::MeshTransparent(ID3D11Device* pDevice, const std::string& filename, Texture* pDiffuseMap)
	:Mesh(pDevice, filename)
{
	//Effect
	m_pEffect = std::make_unique<EffectUV>(pDevice, L"Resources/Transparent.fx");

	SetDiffuseMap(pDiffuseMap);
}

//---------------------------
// Member functions
//---------------------------

void MeshTransparent::PrintTypeName()
{
	std::cout << "Transparent Mesh\n";
}

void MeshTransparent::SetDiffuseMap(Texture* pDiffuseMap)
{
	m_pEffect->SetDiffuseMap(pDiffuseMap);
}

void MeshTransparent::SetMatrix(const dae::Matrix& worldViewProjectionMatrix)
{
	m_pEffect->SetMatrix(m_WorldMatrix * worldViewProjectionMatrix);
}