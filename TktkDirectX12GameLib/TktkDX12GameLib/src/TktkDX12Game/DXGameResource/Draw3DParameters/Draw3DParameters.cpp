#include "TktkDX12Game/DXGameResource/Draw3DParameters/Draw3DParameters.h"

#include "TktkDX12Game/DXGameResource/Draw3DParameters/Light/LightManager.h"
#include "TktkDX12Game/DXGameResource/Draw3DParameters/Camera/CameraManager.h"
#include "TktkDX12Game/DXGameResource/Draw3DParameters/Draw3DParametersInitParam.h"

namespace tktk
{
    Draw3DParameters::Draw3DParameters(const Draw3DParametersInitParam& initParam)
    {
        m_light     = std::make_unique<LightManager>(initParam.lightMgrParam);
        m_camera    = std::make_unique<CameraManager>(initParam.cameraMgrParam);
    }

    // デストラクタを非インライン化する
    Draw3DParameters::~Draw3DParameters() = default;

    size_t Draw3DParameters::createCamera()
    {
        return m_camera->create();
    }

    const tktkMath::Matrix4& Draw3DParameters::getViewMatrix(size_t handle) const
    {
        return m_camera->getViewMatrix(handle);
    }

    void Draw3DParameters::setViewMatrix(size_t handle, const tktkMath::Matrix4& view)
    {
        m_camera->setViewMatrix(handle, view);
    }

    const tktkMath::Matrix4& Draw3DParameters::getProjectionMatrix(size_t handle) const
    {
        return m_camera->getProjectionMatrix(handle);
    }

    void Draw3DParameters::setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection)
    {
        m_camera->setProjectionMatrix(handle, projection);
    }

    size_t Draw3DParameters::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
    {
        return m_light->create(ambient, diffuse, speqular, position);
    }

    void Draw3DParameters::updateLightCBuffer(size_t handle) const
    {
        m_light->updateLightCBuffer(handle);
    }

    void Draw3DParameters::setLightAmbient(size_t handle, const tktkMath::Color& ambient)
    {
        m_light->setAmbient(handle, ambient);
    }

    void Draw3DParameters::setLightDiffuse(size_t handle, const tktkMath::Color& diffuse)
    {
        m_light->setDiffuse(handle, diffuse);
    }

    void Draw3DParameters::setLightSpeqular(size_t handle, const tktkMath::Color& speqular)
    {
        m_light->setSpeqular(handle, speqular);
    }

    void Draw3DParameters::setLightPosition(size_t handle, const tktkMath::Vector3& position)
    {
        m_light->setPosition(handle, position);
    }
}