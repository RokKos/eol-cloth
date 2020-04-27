#pragma once

#include "../Components/Transform.h"

namespace Core {

	enum class LightType : unsigned char {
		kNone = 0,
		kDirectional = 1,
		kPoint = 2,
		kReflector = 3,
	};

	class LightSource
	{
	public:
		LightSource() = default;

		LightSource(LightType type, const Ref<Transform>& transform, glm::vec3 color) :
			type_(type),
			transform_(transform),
			color_(color)
		{
		};

		const glm::vec3& GetPosition() const { return transform_->GetPosition(); }
		const glm::vec3& GetDirection() const { return transform_->GetRotation(); }
		const glm::vec3& GetIntensity() const { return transform_->GetScale(); }
		const glm::vec3& GetColor() const { return color_; }

	private:
		LightType type_ = LightType::kNone;
		Ref<Transform> transform_;  // Pos = Pos, Rotation = Light Direction, Scale = Light Intensity
		glm::vec3 color_;
	};

}