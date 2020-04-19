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
		general_setting_ = general_setting;
		auto phongShader = shader_library_.Load(general_setting->RESOURCE_DIR +"Phong.glsl");
		auto simpleShader = shader_library_.Load(general_setting->RESOURCE_DIR + "Simple.glsl");
		auto triangle_test_shader = shader_library_.Load(general_setting->RESOURCE_DIR + "TriangleTest.glsl");

		// Test out new VertexArrays and stuff
		vertex_array_ = Core::VertexArray::Create();

		glm::vec3 vertices[3] = {
			glm::vec3{-0.5f, -0.5f, 0.0f},
			glm::vec3{ 0.5f, -0.5f, 0.0f},
			glm::vec3{0.0f,  0.5f, 0.0f}
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
		transform_box_ = Core::Transform(glm::vec3(2,0,3));
		auto model_data = Core::ModelLoader::LoadModel(general_setting->RESOURCE_DIR + "bunny.obj");

		auto vertex_buffer_box = Core::VertexBuffer::Create(model_data.vertices.data(), model_data.vertices.size() * sizeof(glm::vec3));
		Core::BufferLayout layout_box = {
		{ Core::ShaderDataType::Float3, "a_Position" },
		};

		vertex_buffer_box->SetLayout(layout_box);
		vertex_array_box_->AddVertexBuffer(vertex_buffer_box);

		Core::Ref<Core::IndexBuffer> index_buffer_box = Core::IndexBuffer::Create(model_data.indices.data(), model_data.indices.size());
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

		// Load Models on themand

		//Core::Renderer::Submit(shader_library_.Get("TriangleTest"), vertex_array_);
		Core::Renderer::Submit(shader_library_.Get("TriangleTest"), vertex_array_box_, transform_box_.GetTransformMatrix());
		Core::Renderer::Submit(shader_library_.Get("TriangleTest"), vertex_array_box_);
		
		Core::Renderer::EndScene();
	}

	void EOLLayer::OnImGuiRender()
	{
		Core::Layer::OnImGuiRender();

		ImGui::Begin("Debug Controlls");
		if (ImGui::TreeNode("Misc")) {
			ImGui::ColorEdit4("BG Color", glm::value_ptr(bg_color_));
			ImGui::Text("Delta time: %f", prev_time_step_.GetSeconds());

			ImGui::TreePop();
		}

	
		if (ImGui::TreeNode("Camera Controls")) {

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
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Transform Controls")) {
			// TODO(Rok Kos): Refac this
			glm::vec3 t_pos = transform_box_.GetPosition();
			float pos[3] = { t_pos.x, t_pos.y, t_pos.z };
			ImGui::Text("Pos:"); ImGui::InputFloat3("a", &pos[0]);
			t_pos.x = pos[0];
			t_pos.y = pos[1];
			t_pos.z = pos[2];
			transform_box_.SetPosition(t_pos);


			glm::vec3 t_rot = transform_box_.GetRotation();
			float rot[3] = { t_rot.x, t_rot.y, t_rot.z };
			ImGui::Text("Rot:"); ImGui::InputFloat3("b", &rot[0]);
			t_rot.x = rot[0];
			t_rot.y = rot[1];
			t_rot.z = rot[2];
			transform_box_.SetRotation(t_rot);



			glm::vec3 t_scale = transform_box_.GetScale();
			float scl[3] = { t_scale.x, t_scale.y, t_scale.z };
			ImGui::Text("Scale:"); ImGui::InputFloat3("c", &scl[0]);
			t_scale.x = scl[0];
			t_scale.y = scl[1];
			t_scale.z = scl[2];
			transform_box_.SetScale(t_scale);
			
			ImGui::TreePop();
		}
		
		ImGui::End();

	}

	void EOLLayer::OnEvent(Core::Event& e)
	{
		Core::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Core::KeyPressedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Core::KeyTypedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyTypedEvent));

		perspective_camera_controller_.OnEvent(e);
		Core::Layer::OnEvent(e);
	}

	bool EOLLayer::OnKeyPressedEvent(Core::KeyPressedEvent& e)
	{
		LOG_INFO("EOL LAYER::OnKeyPressedEvent key pressed: {0}", e.GetKeyCode());
		switch (e.GetKeyCode()) {
		case Core::KeyCode::Up: {
			glm::vec3 pos = transform_box_.GetPosition();
			pos.y += 1.0 * prev_time_step_;
			transform_box_.SetPosition(pos);
			return true;
		}
		case Core::KeyCode::Down: {
			glm::vec3 pos = transform_box_.GetPosition();
			pos.y -= 1.0 * prev_time_step_;
			transform_box_.SetPosition(pos);
			return true;
		}
		case Core::KeyCode::Left: {
			glm::vec3 pos = transform_box_.GetPosition();
			pos.x -= 1.0 * prev_time_step_;
			transform_box_.SetPosition(pos);
			return true;
		}
		case Core::KeyCode::Right: {
			glm::vec3 pos = transform_box_.GetPosition();
			pos.x += 1.0 * prev_time_step_;
			transform_box_.SetPosition(pos);
			return true;
		}
		}
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

}