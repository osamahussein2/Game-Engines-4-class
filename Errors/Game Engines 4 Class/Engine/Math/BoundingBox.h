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

		// Create float variables to find the difference in both axes for each bounding box
		float aab1x = box_->minVert.x - maxVert.x;
		float aab1y = box_->minVert.y - maxVert.y;

		float aab2x = minVert.x - box_->maxVert.x;
		float aab2y = minVert.y - box_->maxVert.y;

		// If any of float variables are greater than 0, then there's no intersection and we can return false
		if (aab1x > 0.0f || aab1y > 0.0f) {
			return false;
		}

		if (aab2x > 0.0f || aab2y > 0.0f) {
			return false;
		}

		// When an AABB intersection occurs
		return true;
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform[3].y, transform[3].z) + point_;
	}
};

#endif // !BOUNDINGBOX_H