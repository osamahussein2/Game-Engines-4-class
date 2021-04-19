#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

struct BoundingBox {
	glm::vec3 minVert, maxVert;
	glm::mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		// When an AABB intersection occurs
		return maxCorner.x > otherMinCorner.x &&
			minCorner.x < otherMaxCorner.x &&
			maxCorner.y > otherMinCorner.y &&
			minCorner.y < otherMaxCorner.y &&
			maxCorner.z > otherMinCorner.z &&
			minCorner.z < otherMaxCorner.z;
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};

#endif // !BOUNDINGBOX_H