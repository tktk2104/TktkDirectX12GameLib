#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionData.h"

#include <algorithm>
#include <TktkFileIo/lodevmd.h>
#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionBoneParam.h"

namespace tktk
{
    MotionData::MotionData(const std::string& motionFileName)
    {
        // vmdファイルの読み込み結果の構造体
        tktkFileIo::lodevmd::loadData outData{};

        // vmdファイルの読み込み処理
        tktkFileIo::lodevmd::load(&outData, motionFileName);

        m_endFrameNo = 0U;

        // 読み込んだモーションデータのキーフレームの配列を巡回する
        for (const auto& node : outData.motionData)
        {
            // もし現在の最終キーフレームよりも大きなキーがあったらその値に更新する
            if (m_endFrameNo < node.frameNo) m_endFrameNo = node.frameNo;

            // ボーンの名称毎にキーフレームの配列を作る
            m_boneKeyFrames[node.boneName].push_back({ node.frameNo, node.location, tktkMath::Vector3_v::one, node.rotation });
        }

        // キーフレームの順番を整理する
        for (auto& motion : m_boneKeyFrames)
        {
            // キーフレームの順番でソートする
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
        // ボーン毎の座標変換行列の配列
        std::vector<MotionBoneParam> result{};
        result.reserve(m_boneKeyFrames.size());

        // モーションに登録されているボーンの種類だけ巡回
        for (const auto& keyFrames : m_boneKeyFrames)
        {
            // 現在のフレームに対応したキーフレームを求める
            auto keyFrame = calculateKeyFrame(keyFrames.second, frame);

            // キーフレームの座標変換を行列にまとめる
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
        // 始まりのインデックス
        size_t startKey   = 0;
        // 終わりのインデックス
        size_t endKey     = keyFrames.size() - 1;

        // もしも現在のフレームが始まりのキーのフレームよりも前であれば
        if (keyFrames.at(startKey).frameNo >= frame)
        {
            // 始まりのキーフレームを返す
            return keyFrames.at(startKey);
        }

        // もしも現在のフレームが終わりのキーのフレームよりも後であれば
        if (keyFrames.at(endKey).frameNo <= frame)
        {
            // 終わりのキーフレームを返す
            return keyFrames.at(endKey);
        }

        // 始まりのインデックスに１を足した数が終わりのインデックスよりも小さい限りループ
        while ((startKey + 1) < endKey)
        {
            // 始まりと終わりのインデックスの中間点を求める
            const size_t mid = (startKey + endKey) / 2;

            // もしも現在のフレームが中間のキーのフレームと一緒であれば
            if (keyFrames.at(mid).frameNo == frame)
            {
                // そのフレームを返す
                return keyFrames.at(mid);
            }
            // もしも現在のフレームが中間のキーのフレームよりも後であれば
            else if (keyFrames.at(mid).frameNo < frame)
            {
                // この後巡回する範囲を中間から後ろにする
                startKey = mid;
            }
            // もしも現在のフレームが中間のキーのフレームよりも前であれば
            else
            {
                // この後巡回する範囲を中間から前にする
                endKey = mid;
            }
        }
        
        // 補完に使用するキー
        const auto& firstKey    = keyFrames.at(startKey);
        const auto& secondKey   = keyFrames.at(endKey);

        // 補完に使用する割合
        float amount = static_cast<float>(frame - firstKey.frameNo) / static_cast<float>(secondKey.frameNo - firstKey.frameNo);

        // 補完の計算
        MotionData::KeyFrame result{};
        result.frameNo = frame;
        result.scale    = tktkMath::Vector3::lerp(firstKey.scale, secondKey.scale, amount);
        result.rotation = tktkMath::Quaternion::slerp(firstKey.rotation, secondKey.rotation, amount);
        result.position = tktkMath::Vector3::lerp(firstKey.position, secondKey.position, amount);

        return result;
    }
}