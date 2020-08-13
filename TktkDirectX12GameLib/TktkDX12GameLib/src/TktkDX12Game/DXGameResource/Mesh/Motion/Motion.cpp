#include "TktkDX12Game/DXGameResource/Mesh/Motion/Motion.h"

namespace tktk
{
	Motion::Motion(unsigned int motionNum)
		: m_motionArray(motionNum)
	{
	}

	void Motion::load(unsigned int id, const std::string& motionFileName)
	{
		m_motionArray.emplaceAt(id, motionFileName);
	}

	std::vector<MotionBoneParam> Motion::calculateBoneTransformMatrices(unsigned int id, unsigned int frame) const
	{
		return m_motionArray.at(id)->calculateBoneTransformMatrices(frame);
	}
}