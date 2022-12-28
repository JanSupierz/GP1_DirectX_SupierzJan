#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Mesh.h"
class Effect;
class Texture;


//-----------------------------------------------------
// Mesh Class									
//-----------------------------------------------------
class MeshTransparent final : public Mesh
{
public:
	MeshTransparent(ID3D11Device* pDevice, const std::string& filename, Texture* pDiffuseMap);
	~MeshTransparent() = default;

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	MeshTransparent(const MeshTransparent& other) = delete;
	MeshTransparent(MeshTransparent&& other) noexcept = delete;
	MeshTransparent& operator=(const MeshTransparent& other) = delete;
	MeshTransparent& operator=(MeshTransparent&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void PrintTypeName() override;

	void SetDiffuseMap(Texture* pDiffuseMap);
};