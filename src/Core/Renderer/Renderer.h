#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "../Components/Material.h"
#include "Buffers/VertexArray.h"
#include "Cameras/Camera.h"

namespace Core {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();
		static void Submit(const Ref<Material>& material, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		static void DrawPoints(const std::vector<Ref<Point>>& points);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}