#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
class Effect;
class Texture;

struct Vertex
{
	dae::Vector3 position;
	dae::Vector2 uv;
	dae::Vector3 normal;
	dae::Vector3 tangent;
};

//-----------------------------------------------------
// Mesh Class									
//-----------------------------------------------------
class Mesh
{
public:
	Mesh(ID3D11Device* pDevice, const std::string& filePath );
	virtual ~Mesh();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Mesh(const Mesh& other) = delete;
	Mesh(Mesh&& other) noexcept = delete;
	Mesh& operator=(const Mesh& other) = delete;
	Mesh& operator=(Mesh&& other)	noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Render(ID3D11DeviceContext* pDeviceContext);
	void SetSamplerState(ID3D11SamplerState* pSamplerState);

	void Translate(const dae::Vector3& translation);
	void RotateY(float angle);

	virtual void PrintTypeName() = 0;
protected:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::unique_ptr<Effect> m_pEffect;

	uint32_t m_NumIndices;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	dae::Matrix m_WorldMatrix{};
};