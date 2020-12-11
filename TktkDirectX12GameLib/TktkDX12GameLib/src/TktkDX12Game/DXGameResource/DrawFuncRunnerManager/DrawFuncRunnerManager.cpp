#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/DrawFuncRunnerManager.h"

#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/PostEffect/PostEffectDrawFuncRunnerManager.h"
//#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/Billboard/BillboardDrawFuncRunnerManager.h"
//#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/Mesh/MeshDrawFuncRunnerManager.h"

#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/Structs/DrawFuncRunnerManagerInitParam.h"

namespace tktk
{
    DrawFuncRunnerManager::DrawFuncRunnerManager(const DrawFuncRunnerManagerInitParam& initParam)
    {
        m_postEffectDrawFuncRunnerManager = std::make_unique<PostEffectDrawFuncRunnerManager>(initParam.postEffectDrawFuncRunnerMgrParam);
    }

    // デストラクタを非インライン化する
    DrawFuncRunnerManager::~DrawFuncRunnerManager() = default;


    void DrawFuncRunnerManager::createSystemPostEffectDrawFuncRunner()
    {
        m_postEffectDrawFuncRunnerManager->createSystemResource();
    }

    size_t DrawFuncRunnerManager::createPostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam)
    {
        return m_postEffectDrawFuncRunnerManager->create(postEffectMaterialHandle, initParam);
    }

    void DrawFuncRunnerManager::startPostEffect(size_t handle)
    {
        m_postEffectDrawFuncRunnerManager->startPostEffect(handle);
    }

    void DrawFuncRunnerManager::stopPostEffect()
    {
        m_postEffectDrawFuncRunnerManager->stopPostEffect();
    }
}