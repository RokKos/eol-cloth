#include "EOLLayer.h"

#include "../Core/Renderer/Renderer.h"
#include "../Core/Renderer/RenderCommand.h"
#include "../Core/Core.h"
#include "../Core/Input.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Tools/ModelLoader.h"

namespace EOL {
	EOLLayer::EOLLayer(Core::Ref<GeneralSettings> general_setting)
		: Core::Layer("EOLLayer"), perspective_camera_controller_()
	{
		auto phongShader = shader_library_.Load(general_setting->RESOURCE_DIR +"Phong.glsl");
		auto simpleShader = shader_library_.Load(general_setting->RESOURCE_DIR + "Simple.glsl");
		auto triangle_test_shader = shader_library_.Load(general_setting->RESOURCE_DIR + "TriangleTest.glsl");

		// Test out new VertexArrays and stuff
		vertex_array_ = Core::VertexArray::Create();

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		auto vertex_buffer = Core::VertexBuffer::Create(vertices, sizeof(vertices));
		Core::BufferLayout layout = {
		{ Core::ShaderDataType::Float3, "a_Position" },
		};

		vertex_buffer->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertex_buffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Core::Ref<Core::IndexBuffer> index_buffer = Core::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		vertex_array_->SetIndexBuffer(index_buffer);


		// BOX ------
		vertex_array_box_ = Core::VertexArray::Create();

		auto model_data = Core::ModelLoader::LoadModel(general_setting->RESOURCE_DIR + "box.obj");

		float vertices_box[3 * 8] = {
1.000000 ,1.000000 ,-1.000000,
1.000000 ,-1.000000 ,-1.000000,
1.000000 ,1.000000 ,1.000000,
1.000000 ,-1.000000 ,1.000000,
-1.000000 ,1.000000 ,-1.000000,
-1.000000 ,-1.000000 ,-1.000000,
-1.000000 ,1.000000 ,1.000000,
-1.000000 ,-1.000000 ,1.000000,
		};

		auto vertex_buffer_box = Core::VertexBuffer::Create(vertices_box, sizeof(vertices_box));
		Core::BufferLayout layout_box = {
		{ Core::ShaderDataType::Float3, "a_Position" },
		};

		vertex_buffer_box->SetLayout(layout_box);
		vertex_array_box_->AddVertexBuffer(vertex_buffer_box);

		uint32_t indices_box[3 * 12] = {
			1, 3, 4,
			1, 4, 2,
			5, 3, 1,
			5, 1, 2,
			2, 4, 8,
			2, 8, 6,
			3, 8, 4,
			3, 7, 8,
			7, 6, 8,
			5, 2, 6,
			5, 7, 3,
			7, 5, 6,			
		};
		Core::Ref<Core::IndexBuffer> index_buffer_box = Core::IndexBuffer::Create(indices_box, sizeof(indices_box) / sizeof(uint32_t));
		vertex_array_box_->SetIndexBuffer(index_buffer_box);

		
	}

	void EOLLayer::OnAttach()
	{
		Core::Layer::OnAttach();
	}

	void EOLLayer::OnDetach()
	{
		Core::Layer::OnDetach();

	}

	void EOLLayer::OnUpdate(Core::TimeStep ts)
	{
		Core::Layer::OnUpdate(ts);
		perspective_camera_controller_.OnUpdate(ts);

		Core::Renderer::BeginScene(perspective_camera_controller_.GetCamera());

		prev_time_step_ = ts;

		Core::RenderCommand::SetClearColor(bg_color_);
		Core::RenderCommand::Clear();

		//Core::Renderer::Submit(shader_library_.Get("TriangleTest"), vertex_array_);
		Core::Renderer::Submit(shader_library_.Get("TriangleTest"), vertex_array_box_);
		
		Core::Renderer::EndScene();
	}

	void EOLLayer::OnImGuiRender()
	{
		Core::Layer::OnImGuiRender();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("BG Color", glm::value_ptr(bg_color_));

		ImGui::Text("Delta time: %f", prev_time_step_.GetSeconds());

		ImGui::End();

		
		ImGui::Begin("Camera Controls");
		
		float camera_movement_speed = perspective_camera_controller_.GetCameraMovementSpeed();
		ImGui::InputFloat("Camera movement speed", &camera_movement_speed);
		perspective_camera_controller_.SetCameraMovementSpeed(camera_movement_speed);

		float camera_rotation_speed = perspective_camera_controller_.GetCameraRotationSpeed();
		ImGui::InputFloat("Camera rotation speed", &camera_rotation_speed);
		perspective_camera_controller_.SetCameraRotationSpeed(camera_rotation_speed);

		ImGui::Text("Yaw: %f", perspective_camera_controller_.GetYaw());
		ImGui::Text("Pitch: %f", perspective_camera_controller_.GetPitch());
		auto camera_front = perspective_camera_controller_.GetCamerFront();
		ImGui::Text("Camera front x: %f y: %f z: %f", camera_front.x, camera_front.y, camera_front.z);
		
		ImGui::End();
	}

	void EOLLayer::OnEvent(Core::Event& e)
	{
		Core::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Core::KeyPressedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Core::KeyTypedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<Core::MouseMovedEvent>(BIND_EVENT_FN(EOLLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<Core::MouseButtonPressedEvent>(BIND_EVENT_FN(EOLLayer::OnMouseButtonPressedEvent));

		perspective_camera_controller_.OnEvent(e);
		Core::Layer::OnEvent(e);
	}

	bool EOLLayer::OnKeyPressedEvent(Core::KeyPressedEvent& e)
	{
		LOG_INFO("EOL LAYER::OnKeyPressedEvent key pressed: {0}", e.GetKeyCode());
		return false;
	}

	bool EOLLayer::OnKeyTypedEvent(Core::KeyTypedEvent& e)
	{
		LOG_INFO("EOLLayer::OnKeyTypedEvent key pressed: {0}", e.GetKeyCode());
		
		switch (e.GetKeyCode()) {
		case Core::KeyCode::H:
			//scene->step(gs->online, gs->exportObjs);
			return true;
		case Core::KeyCode::R:
			//scene->reset();  It was before commented out
			return true;
		case Core::KeyCode::P:
			//scene->partialStep();
			return true;
		case Core::KeyCode::V:
			//camera->toggleFlatView();
			return true;
		}

		return false;
	}

	bool EOLLayer::OnMouseMovedEvent(Core::MouseMovedEvent& e)
	{
		if (Core::Input::IsMouseButtonPressed(Core::MouseCode::Button1)) {
			//camera->mouseMoved(xmouse, ymouse);
			return true;
		}

		return false;
	}

	bool EOLLayer::OnMouseButtonPressedEvent(Core::MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Core::MouseCode::Button1) {
			double mouse_x = Core::Input::GetMouseX();
			double mouse_y = Core::Input::GetMouseY();

			if (Core::Input::IsKeyPressed(Core::KeyCode::LeftShift) || Core::Input::IsKeyPressed(Core::KeyCode::RightShift)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			}
			else if (Core::Input::IsKeyPressed(Core::KeyCode::LeftControl) || Core::Input::IsKeyPressed(Core::KeyCode::RightControl)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			} 
			else if (Core::Input::IsKeyPressed(Core::KeyCode::LeftAlt) || Core::Input::IsKeyPressed(Core::KeyCode::RightAlt)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			}
			
		}

		return false;
		
	}

}