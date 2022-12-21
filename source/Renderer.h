#pragma once
struct SDL_Window;
struct SDL_Surface;

class Sampler;
class Mesh;
class Texture;

namespace dae
{
	struct Camera;

	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(const Timer* pTimer);
		void Render() const;

		void ToggleFilteringMethods();
	private:

		enum class FilteringMethod { Point, Linear, Anisotropic };
		FilteringMethod m_FilteringMethod{ FilteringMethod::Point };

		SDL_Window* m_pWindow{};

		int m_Width{};
		int m_Height{};

		bool m_IsInitialized{ false };

		//DIRECTX
		HRESULT InitializeDirectX();

		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

		IDXGISwapChain* m_pSwapChain;

		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11DepthStencilView* m_pDepthStencilView;

		ID3D11Resource* m_pRenderTargetBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;

		//Meshes
		std::unique_ptr<Mesh> m_pMesh;
		bool m_ShouldRotate{ true };

		//Camera
		std::unique_ptr<Camera> m_pCamera;

		//Textures
		std::unique_ptr<Texture> m_pDiffuseMap;

		//Samplers
		std::unique_ptr<Sampler> m_pSampler;
	};
}
