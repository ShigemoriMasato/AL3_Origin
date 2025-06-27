#include "Object.h"
#include "../Engine/Render/Render.h"

namespace {
	Vector4 Convert(Vector3 vec) {
		return Vector4(vec.x, vec.y, vec.z, 1.0f);
	}
}

void Object::Draw() const {
	if (!camera_) {
		return;
	}

	if (type_ < ShapeType::Triangle || type_ >= ShapeType::Count) {
		return;
	}

	if (handle_ < 0) {
		return;
	}

	MaterialData materialData;
	materialData.color = { 
		float(color & 0xff000000) / 255.0f,
		float(color & 0x00ff0000) / 255.0f,
		float(color & 0x0000ff00) / 255.0f,
		float(color & 0x000000ff) / 255.0f
	};

	switch (type_) {
	case ShapeType::Triangle:

		Render::DrawTriangle(Convert(lt), Convert(rt), Convert(lb),
			MakeAffineMatrix(transform_), camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Sphere:

		Render::DrawSphere(lt.Length(), MakeAffineMatrix(transform_), camera_, materialData, {}, handle_);

		break;

	case ShapeType::Cube:

		Render::DrawBox(MakeAffineMatrix(transform_), camera_, materialData, {}, handle_);

		break;

	case ShapeType::Sprite:

		Render::DrawSprite(
			Convert(lt), Convert(rt), Convert(lb), Convert(rb),
			MakeAffineMatrix(transform_), camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Line:

		Render::DrawLine(
			Convert(lt), Convert(rt), 
			MakeAffineMatrix(transform_), camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Model:

		Render::DrawModel(handle_, MakeAffineMatrix(transform_), camera_, materialData, {});

		break;
	}
}
