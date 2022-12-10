#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
class Effect;

struct Vertex_PosCol
{
	dae::Vector3 position;
	dae::ColorRGB color;

};

//-----------------------------------------------------
// Mesh Class									
//-----------------------------------------------------
class Mesh final
{
public:
	Mesh(ID3D11Device* pDevice, std::vector<Vertex_PosCol>& vertices, std::vector<uint32_t>& indices);	// Constructor
	~Mesh();						// Destructor

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

private:
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

};