#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

#include "AnimatedMesh.h"
#include "MeshTexture.h"
#include "Joint.h"
#include "Animator.h"
#include "Animation.h"
#include <vector>

class AnimatedModel
{
public:
	AnimatedModel() {}
	AnimatedModel(AnimatedMesh model, MeshTexture texture, Joint rootJoint, int jointCount)
	{
		this->model = model;
		this->texture = texture;
		this->rootJoint = rootJoint;
		this->jointCount = jointCount;
		this->animator = Animator(this);
		rootJoint.CalculateInverseBindTransform(glm::mat4(1.0));
	}

	AnimatedMesh GetModel() { return this->model; }
	MeshTexture GetTexture() { return this->texture; }
	Joint GetRootJoint() { return this->rootJoint; }

	void PerformAnimation(Animation animation) { animator.PerformAnimation(animation); }
	void Update() { animator.Update(); }

	std::vector<glm::mat4> GetJointTransforms()
	{
		std::vector<glm::mat4> jointMatrices;
		AddJointsToVector(rootJoint, &jointMatrices);
		return jointMatrices;
	}

private:
	AnimatedMesh model;
	MeshTexture texture;
	Joint rootJoint;
	int jointCount;
	Animator animator;

	void AddJointsToVector(Joint headJoint, std::vector<glm::mat4>* jointMatrices)
	{
		jointMatrices->push_back(headJoint.GetAnimationTransform());
		for (Joint childJoint : headJoint.children)
		{
			AddJointsToVector(childJoint, jointMatrices);
		}
	}
};

#endif // !ANIMATEDMODEL_H