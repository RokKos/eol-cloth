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

		// BOX ------
		auto vertex_array_box = Core::VertexArray::Create();
		Core::Ref<Core::Transform> transform_box = Core::CreateRef<Core::Transform>(glm::vec3(2, 0, 3));
		auto model_data = Core::ModelLoader::LoadModel(general_setting->RESOURCE_DIR + "bunny.obj");

		auto vertex_buffer_box = Core::VertexBuffer::Create(model_data.vertices.data(), model_data.vertices.size() * sizeof(glm::vec3));
		Core::BufferLayout layout_box = {
		{ Core::ShaderDataType::Float3, "a_Position" },
		};

		vertex_buffer_box->SetLayout(layout_box);
		vertex_array_box->AddVertexBuffer(vertex_buffer_box);

		Core::Ref<Core::IndexBuffer> index_buffer_box = Core::IndexBuffer::Create(model_data.indices.data(), model_data.indices.size());
		vertex_array_box->SetIndexBuffer(index_buffer_box);

		auto shape = Core::CreateRef<Core::Shape>(vertex_array_box, transform_box, model_data, "Shape01");
		auto shape2 = Core::CreateRef<Core::Shape>(vertex_array_box, Core::CreateRef<Core::Transform>(glm::vec3(1, 1, 1)), model_data, "Shape02");
		auto shape3 = Core::CreateRef<Core::Shape>(vertex_array_box, Core::CreateRef<Core::Transform>(glm::vec3(0, 0, 0)), model_data, "Shape03");
		scene_.AddShape(shape);
		scene_.AddShape(shape2);
		scene_.AddShape(shape3);

		// GL ENABLE SMOOTH POINTS
		scene_.AddPoint(Core::CreateRef<Core::Point>(10, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)));
		scene_.AddPoint(Core::CreateRef<Core::Point>(100, glm::vec3(10, 2, 5), glm::vec3(0, 1, 0)));
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

		for (auto shape : scene_.GetShapes())
		{
			Core::Renderer::Submit(shader_library_.Get("TriangleTest"), shape->GetVertexArray(), shape->GetTransform()->GetTransformMatrix());
		}

		Core::Renderer::DrawPoints(scene_.GetPoints());
		
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

		if (ImGui::TreeNode("Scene View")) {

			for (auto shape : scene_.GetShapes())
			{
				if (ImGui::TreeNode(shape->GetName().c_str())) {
					// TODO(Rok Kos): Refac this
					auto shape_transform = shape->GetTransform();

					glm::vec3 t_pos = shape_transform->GetPosition();
					float pos[3] = { t_pos.x, t_pos.y, t_pos.z };
					ImGui::Text("Pos:"); ImGui::InputFloat3("a", &pos[0]);
					t_pos.x = pos[0];
					t_pos.y = pos[1];
					t_pos.z = pos[2];
					shape_transform->SetPosition(t_pos);


					glm::vec3 t_rot = shape_transform->GetRotation();
					float rot[3] = { t_rot.x, t_rot.y, t_rot.z };
					ImGui::Text("Rot:"); ImGui::InputFloat3("b", &rot[0]);
					t_rot.x = rot[0];
					t_rot.y = rot[1];
					t_rot.z = rot[2];
					shape_transform->SetRotation(t_rot);



					glm::vec3 t_scale = shape_transform->GetScale();
					float scl[3] = { t_scale.x, t_scale.y, t_scale.z };
					ImGui::Text("Scale:"); ImGui::InputFloat3("c", &scl[0]);
					t_scale.x = scl[0];
					t_scale.y = scl[1];
					t_scale.z = scl[2];
					shape_transform->SetScale(t_scale);

					ImGui::TreePop();
				}
			}
			
			
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
		/*switch (e.GetKeyCode()) {
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
		}*/
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