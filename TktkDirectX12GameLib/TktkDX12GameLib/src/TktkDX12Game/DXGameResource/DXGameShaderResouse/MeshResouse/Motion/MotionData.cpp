#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionData.h"

#include <algorithm>
#include <TktkFileIo/lodevmd.h>
#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionBoneParam.h"

namespace tktk
{
    MotionData::MotionData(const std::string& motionFileName)
    {
        // vmd�t�@�C���̓ǂݍ��݌��ʂ̍\����
        tktkFileIo::lodevmd::loadData outData{};

        // vmd�t�@�C���̓ǂݍ��ݏ���
        tktkFileIo::lodevmd::load(&outData, motionFileName);

        m_endFrameNo = 0U;

        // �ǂݍ��񂾃��[�V�����f�[�^�̃L�[�t���[���̔z������񂷂�
        for (const auto& node : outData.motionData)
        {
            // �������݂̍ŏI�L�[�t���[�������傫�ȃL�[���������炻�̒l�ɍX�V����
            if (m_endFrameNo < node.frameNo) m_endFrameNo = node.frameNo;

            // �{�[���̖��̖��ɃL�[�t���[���̔z������
            m_boneKeyFrames[node.boneName].push_back({ node.frameNo, node.location, tktkMath::Vector3_v::one, node.rotation });
        }

        // �L�[�t���[���̏��Ԃ𐮗�����
        for (auto& motion : m_boneKeyFrames)
        {
            // �L�[�t���[���̏��ԂŃ\�[�g����
            std::sort(
                std::begin(motion.second),
                std::end(motion.second),
                [](const KeyFrame& lval, const KeyFrame& rval) { return lval.frameNo <= rval.frameNo; }
            );
        }
    }

    MotionData::MotionData(MotionData&& other) noexcept
        : m_endFrameNo(other.m_endFrameNo)
        , m_boneKeyFrames(std::move(other.m_boneKeyFrames))
    {
    }

    size_t MotionData::getEndFrameNo() const
    {
        return m_endFrameNo;
    }

    std::vector<MotionBoneParam> MotionData::calculateBoneTransformMatrices(size_t frame) const
    {
        // �{�[�����̍��W�ϊ��s��̔z��
        std::vector<MotionBoneParam> result{};
        result.reserve(m_boneKeyFrames.size());

        // ���[�V�����ɓo�^����Ă���{�[���̎�ނ�������
        for (const auto& keyFrames : m_boneKeyFrames)
        {
            // ���݂̃t���[���ɑΉ������L�[�t���[�������߂�
            auto keyFrame = calculateKeyFrame(keyFrames.second, frame);

            // �L�[�t���[���̍��W�ϊ����s��ɂ܂Ƃ߂�
            auto transformMat
                = tktkMath::Matrix4::createScale(keyFrame.scale)
                * tktkMath::Matrix4::createFromQuaternion(keyFrame.rotation)
                * tktkMath::Matrix4::createTranslation(keyFrame.position);

            result.push_back({ keyFrames.first, transformMat });
        }
        return result;
    }

    MotionData::KeyFrame MotionData::calculateKeyFrame(const std::vector<MotionData::KeyFrame, std::allocator<MotionData::KeyFrame>>& keyFrames, size_t frame) const
    {
        // �n�܂�̃C���f�b�N�X
        size_t startKey   = 0;
        // �I���̃C���f�b�N�X
        size_t endKey     = keyFrames.size() - 1;

        // ���������݂̃t���[�����n�܂�̃L�[�̃t���[�������O�ł����
        if (keyFrames.at(startKey).frameNo >= frame)
        {
            // �n�܂�̃L�[�t���[����Ԃ�
            return keyFrames.at(startKey);
        }

        // ���������݂̃t���[�����I���̃L�[�̃t���[��������ł����
        if (keyFrames.at(endKey).frameNo <= frame)
        {
            // �I���̃L�[�t���[����Ԃ�
            return keyFrames.at(endKey);
        }

        // �n�܂�̃C���f�b�N�X�ɂP�𑫂��������I���̃C���f�b�N�X�������������胋�[�v
        while ((startKey + 1) < endKey)
        {
            // �n�܂�ƏI���̃C���f�b�N�X�̒��ԓ_�����߂�
            const size_t mid = (startKey + endKey) / 2;

            // ���������݂̃t���[�������Ԃ̃L�[�̃t���[���ƈꏏ�ł����
            if (keyFrames.at(mid).frameNo == frame)
            {
                // ���̃t���[����Ԃ�
                return keyFrames.at(mid);
            }
            // ���������݂̃t���[�������Ԃ̃L�[�̃t���[��������ł����
            else if (keyFrames.at(mid).frameNo < frame)
            {
                // ���̌㏄�񂷂�͈͂𒆊Ԃ�����ɂ���
                startKey = mid;
            }
            // ���������݂̃t���[�������Ԃ̃L�[�̃t���[�������O�ł����
            else
            {
                // ���̌㏄�񂷂�͈͂𒆊Ԃ���O�ɂ���
                endKey = mid;
            }
        }
        
        // �⊮�Ɏg�p����L�[
        const auto& firstKey    = keyFrames.at(startKey);
        const auto& secondKey   = keyFrames.at(endKey);

        // �⊮�Ɏg�p���銄��
        float amount = static_cast<float>(frame - firstKey.frameNo) / static_cast<float>(secondKey.frameNo - firstKey.frameNo);

        // �⊮�̌v�Z
        MotionData::KeyFrame result{};
        result.frameNo = frame;
        result.scale    = tktkMath::Vector3::lerp(firstKey.scale, secondKey.scale, amount);
        result.rotation = tktkMath::Quaternion::slerp(firstKey.rotation, secondKey.rotation, amount);
        result.position = tktkMath::Vector3::lerp(firstKey.position, secondKey.position, amount);

        return result;
    }
}