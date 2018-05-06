#ifndef JOINT_H
#define JOINT_H

#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Joint
{
public:
	int index;
	char* name;
	std::vector<Joint> children;

	Joint() {}
	Joint(int index, char* name, glm::mat4 bindLocalTransform)
	{
		this->index = index;
		this->name = name;
		this->localBindTransform = bindLocalTransform;
	}

	void AddChild(Joint child) { this->children.push_back(child); }
	glm::mat4 GetAnimationTransform() { return this->animatedTransform; }
	void SetAnimationTransform(glm::mat4 transform) { this->animatedTransform = transform; }
	glm::mat4 GetInverseBindTransform() { return this->inverseBindTransform; }

	void CalculateInverseBindTransform(glm::mat4 parentBindTransform)
	{
		glm::mat4 bindTransform = glm::matrixCompMult(parentBindTransform, localBindTransform);
		inverseBindTransform = glm::inverse(bindTransform);
		for (Joint child : children)
		{
			child.CalculateInverseBindTransform(bindTransform);
		}
	}

private:
	glm::mat4 animatedTransform = glm::mat4(1.0);
	glm::mat4 localBindTransform = glm::mat4(1.0);
	glm::mat4 inverseBindTransform = glm::mat4(1.0);
};

#endif