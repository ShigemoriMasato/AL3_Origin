#include "Object.h"
#include "../Engine/Render/Render.h"

namespace {
	Vector4 Convert(Vector3 vec) {
		return Vector4(vec.x, vec.y, vec.z, 1.0f);
	}
}

void Object::Draw(const Matrix4x4* worldMatrix) const {
	if (!camera_) {
		return;
	}

	if (type_ < ShapeType::Triangle || type_ >= ShapeType::Count) {
		return;
	}

	if (handle_ < 0) {
		return;
	}

	Matrix4x4 worldMat;
	if(worldMatrix) {
		worldMat = *worldMatrix;
	} else {
		worldMat = MakeAffineMatrix(*transform_);
	}

	MaterialData materialData;
	materialData.color = { 
		float((color & 0xff000000) >> 24) / 255.0f,
		float((color & 0x00ff0000) >> 16) / 255.0f,
		float((color & 0x0000ff00) >> 8) / 255.0f,
		float(color & 0x000000ff) / 255.0f
	};

	switch (type_) {
	case ShapeType::Triangle:

		Render::DrawTriangle(Convert(lt), Convert(rt), Convert(lb),
			worldMat, camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Sphere:

		Render::DrawSphere(lt.Length(), worldMat, camera_, materialData, {}, handle_);

		break;

	case ShapeType::Cube:

		Render::DrawBox(worldMat, camera_, materialData, {}, handle_);

		break;

	case ShapeType::Sprite:

		Render::DrawSprite(
			Convert(lt), Convert(rt), Convert(lb), Convert(rb),
			worldMat, camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Line:

		Render::DrawLine(
			Convert(lt), Convert(rt), 
			worldMat, camera_, materialData, {}, handle_
		);

		break;

	case ShapeType::Model:

		Render::DrawModel(handle_, worldMat, camera_, materialData, {});

		break;
	}
}
