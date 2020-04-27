#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "../Primitives/LightSource.h"
#include "../Components/Material.h"
#include "Buffers/VertexArray.h"
#include "Cameras/Camera.h"

#include <vector>

namespace Core {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera, std::vector<Ref<LightSource>> light_sources);
		static void EndScene();
		static void Submit(const Ref<Material>& material, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		static void DrawPoints(const std::vector<Ref<Point>>& points);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:

		// TODO(Rok Kos): Rething this Scene Data... maybe replace with Scene
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec3 camera_position_;
			std::vector<Ref<LightSource>> light_sources_;
		};

		static Scope<SceneData> s_SceneData;
	};
}