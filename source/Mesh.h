#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
class Effect;
class Texture;

//#define PosCol

#ifdef PosCol
struct Vertex
{
	dae::Vector3 position;
	dae::ColorRGB color;
};
#else
struct Vertex
{
	dae::Vector3 position;
	dae::Vector2 uv;
};
#endif

//-----------------------------------------------------
// Mesh Class									
//-----------------------------------------------------
class Mesh final
{
public:
	Mesh(ID3D11Device* pDevice, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	~Mesh();

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

	void SetDiffuseMap(Texture* pDiffuseMap);
	void SetSamplerState(ID3D11SamplerState* pSamplerState);

	void Translate(const dae::Vector3& translation);
	void RotateY(float angle);

	void SetWorldViewProjectionMatrix(const dae::Matrix& viewProjectionMatrix);
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

	dae::Matrix m_WorldMatrix{};
};