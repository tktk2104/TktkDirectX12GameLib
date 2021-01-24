#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

/* SelfInitParam */
#include "DX12GameManagerInitParam.h"

/* funcUseType */
#include <string>
#include <typeindex>
#include <array>
#include <vector>
#include <forward_list>

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Matrix4.h>

#include <TktkDX12Wrapper/Resource/Viewport/ViewportInitParam.h>
#include <TktkDX12Wrapper/Resource/ScissorRect/ScissorRectInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignatureInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/CopySourceDataCarrier.h>
#include <TktkDX12Wrapper/Resource/Buffer/Upload/UploadBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/Vertex/VertexDataCarrier.h>
#include <TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/Texture/TextureBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeapParam.h>

#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"

#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/TempSpriteMaterialInstanceData.h"
#include "../DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardDrawFuncBaseArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardMaterialInstanceData.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshDrawFuncBaseArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmdArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmxArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmdReturnValue.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmxReturnValue.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamUpdateFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/Structs/SkeletonInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamUpdateFuncArgs.h"
#include "../DXGameResource/GameObjectResouse/GameObject/GameObjectPtr.h"
#include "../DXGameResource/GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "../DXGameResource/GameObjectResouse/Component/ComponentVTable.h"
#include "../DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentListVTable.h" // TODO : �t�H���_�K�w
#include "../DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "../DXGameResource/OtherResouse/Scene/Structs/SceneInitParam.h"

#include "../UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseBtnType.h"
#include "../UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "../UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "../UtilityProcessManager/InputManager/CommandTypeManager/CommandIdCarrier.h"
#include "../UtilityProcessManager/InputManager/CommandTypeManager/DirectionCommandId.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemUploadBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemSpriteType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemMeshType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemMeshMaterialType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectDrawFuncRunnerType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

#include "../../TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"


namespace tktk
{
	// �O���錾
	class GraphicManager;
	class DXGameResource;
	class UtilityProcessManager;
	
	// �Q�[���t���[�����[�N�̃��C���}�l�[�W���[
	// ���ȗ��Ń}�l�[�W���[�́utktk::DX12Game�v�ł�
	class DX12GameManager
	{
	//************************************************************
	/* ���̃}�l�[�W���[���̂̏��� */
	public:

		// ������
		static void initialize(const DX12GameManagerInitParam& initParam);

		// ���s
		static void run();

		// �I��
		static void exit();

	//************************************************************
	/* �E�B���h�E�̏��� */
	public:
	
		// �Q�[���`��G���A�T�C�Y���擾����
		static const tktkMath::Vector2& getDrawGameAreaSize();

		// �X�N���[���T�C�Y���擾����
		static const tktkMath::Vector2& getScreenSize();
	
	//************************************************************
	/* �V�[���̏��� */
	public:
	
		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t addScene(const SceneInitParam& initParam);
	
		// �V�[�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t addSceneAndAttachId(ResourceIdCarrier id, const SceneInitParam& initParam);
	
		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		static void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);
	
		// �V�[����L���ɂ���
		static void enableScene(size_t handle);
	
		// �V�[���𖳌��ɂ���
		static void disableScene(size_t handle);
	
	//************************************************************
	/* �Q�[���I�u�W�F�N�g�̏��� */
	public:
	
		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment = {});
	
		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// ���Y���I�u�W�F�N�g�����������ꍇ�A���GameObjectPtr���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		static GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag);
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag);
	
		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		static void destroyGameObjectsWithTag(GameObjectTagCarrier tag);
	
	//************************************************************
	/* �R���|�[�l���g�̏��� */
	public:
	
		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		static void addRunFuncPriority(float priority)
		{
			addRunFuncPriority(typeid(ComponentType), priority);
		}

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		static void addRunFuncPriority(std::type_index type, float priority);
	
		// �Փ˔���̑g�ݍ��킹��ǉ�����
		static void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);
	
		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static ComponentPtr<ComponentType> createComponent(const GameObjectPtr& user, Args&&... args)
		{
			auto basePtr = addComponent(typeid(ComponentType), &ComponentVTableInitializer<ComponentType>::m_componentVTableBundle, &ComponentListVTableInitializer<ComponentType>::m_componentListVTable, user, std::make_shared<ComponentType>(std::forward<Args>(args)...));
			return basePtr.castPtr<ComponentType>();
		}

		// �����̃R���|�[�l���g��ǉ�����
		static ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

	//************************************************************
	/* ����DX12�̏������Ă� */
	public:
	
		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();
	
		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		static void setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);
	
		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		static void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);
	
		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		static void setOnlyDsv(size_t dsvDescriptorHeapHandle);
	
		// �o�b�N�o�b�t�@�[��ݒ肷��
		static void setBackBufferView();
	
		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		static void setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle);
	
		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		static void unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);
	
		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		static void unSetDsv(size_t dsvDescriptorHeapHandle);
	
		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		static void setViewport(size_t handle);
	
		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		static void setScissorRect(size_t handle);
	
		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		static void setPipeLineState(size_t handle);
	
		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setVertexBuffer(size_t handle);
	
		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����i�C���X�^���X�`��p�j
		static void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle);

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setIndexBuffer(size_t handle);
	
		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);
	
		// �u�����h�t�@�N�^�[��ݒ肷��
		static void setBlendFactor(const std::array<float, 4>& blendFactor);
	
		// �v���~�e�B�u�g�|���W��ݒ肷��
		static void setPrimitiveTopology(PrimitiveTopology topology);
	
		// �C���X�^���X�`����s��
		static void drawInstanced(
			size_t vertexCountPerInstance,
			size_t instanceCount,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		);
	
		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		static void drawIndexedInstanced(
			size_t indexCountPerInstance,
			size_t instanceCount,
			size_t startIndexLocation,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		);
	
	//************************************************************
	/* ����DX12�̃��\�[�X����� */
	public:
	
		// �r���[�|�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// �V�U�[��`�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createRootSignature(const RootSignatureInitParam& initParam);
	
		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);
	
		// �A�b�v���[�h�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createUploadBuffer(const UploadBufferInitParam& initParam);
		
		// �ꎞ�I�ȃA�b�v���[�h�o�b�t�@�����i���̃t���[���ł͏��ł���z��ׁ̈A�n���h���͕Ԃ��Ȃ��j
		static void createTempUploadBuffer(const UploadBufferInitParam& initParam);

		// �A�b�v���[�h�o�b�t�@�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t duplicateUploadBuffer(size_t originalHandle);
	
		// �R�s�[�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createVertexBuffer(const VertexDataCarrier& vertexData);
		
		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createIndexBuffer(const std::vector<unsigned short>& indices);
	
		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createCBuffer(const CopySourceDataCarrier& constantBufferData);
		
		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
	
		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createDsBuffer(const DepthStencilBufferInitParam& initParam);
	
		// �f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);
	
		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);
	
		// �[�x�X�e���V���f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);
	
		// �e�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static size_t createTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
	
		// �e�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static size_t loadTextureBuffer(const std::string& texDataPath);
		
	//************************************************************
	/* ����DX12�̃��\�[�X���폜���� */
	public:
	
		// �w��̃r���[�|�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseViewport(size_t handle);
	
		// �w��̃V�U�[��`���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseScissorRect(size_t handle);
	
		// �w��̃��[�g�V�O�l�`�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRootSignature(size_t handle);
	
		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void erasePipeLineState(size_t handle);
	
		// �w��̃A�b�v���[�h�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseUploadBuffer(size_t handle);
	
		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseVertexBuffer(size_t handle);
	
		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseIndexBuffer(size_t handle);
	
		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseCBuffer(size_t handle);
	
		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseTextureBuffer(size_t handle);
	
		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseDsBuffer(size_t handle);
	
		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRtBuffer(size_t handle);
	
		// �w��̒ʏ�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseBasicDescriptorHeap(size_t handle);
	
		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRtvDescriptorHeap(size_t handle);
	
		// �w��̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseDsvDescriptorHeap(size_t handle);
	
	//************************************************************
	/* ����DX12�̃��\�[�X��ݒ�A�擾���� */
	public:
	
		// �����̃|�C���^�̃f�[�^���w��̃A�b�v���[�h�o�b�t�@�ɃR�s�[����
		static void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// �w��̃A�b�v���[�h�o�b�t�@�̓��e��ݒ肵���o�b�t�@�ɃR�s�[����GPU���߂�ݒ肷��
		static void copyBuffer(size_t handle);
	
		// �w��̃����_�[�^�[�Q�b�g�r���[�����O�ɐݒ肵���N���A�J���[�ŃN���A����
		static void clearRtv(size_t handle, size_t rtvLocationIndex);
	
		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���i�e�N�Z���j�j
		static const tktkMath::Vector3& getTextureBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getDsBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getRtBufferSizePx(size_t handle);
	
	//************************************************************
	/* �X�v���C�g�֌W�̏��� */
	public:
	
		// �X�v���C�g�}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam, const SpriteDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// �X�v���C�g�}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam, const SpriteDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// �w�肵���X�v���C�g���g�p����e�N�X�`���̃T�C�Y���擾����
		static const tktkMath::Vector2& getSpriteTextureSize(size_t handle);

		// �w�肵���X�v���C�g�̍ő�̃C���X�^���X�����擾����
		static size_t getMaxSpriteInstanceCount(size_t handle);

		// �w�肵���X�v���C�g�̌��݂̃C���X�^���X�����擾����
		static size_t getCurSpriteInstanceCount(size_t handle);

		// �w�肵���X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		static void clearSpriteInstanceParam(size_t handle);

		// �w�肵���X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		static void addSpriteInstanceParam(size_t handle, float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// �w�肵�X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l�𒸓_�o�b�t�@�ɏ�������
		static void updateSpriteInstanceParam(size_t handle);

		// �w�肵���X�v���C�g��`�悷��
		static void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs);
	
	//************************************************************
	/* 2D���C���֌W�̏��� */
	public:
	
		// �Q�c���C���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createLine2DMaterial();
	
		// �Q�c���C���}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createLine2DMaterialAndAttachId(ResourceIdCarrier id);
	
		// �Q�c���C�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseLine(size_t handle);
	
		// ����`�悷��
		static void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);
	
	//************************************************************
	/* �r���{�[�h�֌W�̏��� */
	
		// �r���{�[�h�}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// �r���{�[�h�}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// �w�肵���r���{�[�h���g�p����e�N�X�`���̃T�C�Y���擾����
		static const tktkMath::Vector2& getBillboardTextureSize(size_t handle);

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		static void clearBillboardInstanceParam(size_t handle);

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		static void addBillboardInstanceParam(size_t handle, const BillboardMaterialInstanceData& instanceParam);

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l�����\�[�g���Ē��_�o�b�t�@�ɏ�������
		static void updateBillboardInstanceParam(size_t handle, const tktkMath::Matrix4& viewProjMatrix);

		// �w�肵���r���{�[�h��`�悷��
		static void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs);
	
	//************************************************************
	/* ���b�V���֌W�̏��� */
	public:
	
		// ���b�V�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createMesh(const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// ���b�V�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createMeshAndAttachId(ResourceIdCarrier id, const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// ���b�V���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copyMesh(size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// ���b�V���̃R�s�[�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t copyMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// ���b�V���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createMeshMaterial(const MeshMaterialInitParam& initParam);
	
		// ���b�V���}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createMeshMaterialAndAttachId(ResourceIdCarrier id, const MeshMaterialInitParam& initParam);
	
		// ���b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copyMeshMaterial(size_t originalHandle);
	
		// ���b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t copyMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle);
	
		// �e�N�X�`����\���������̃��b�V�������A���̃n���h����Ԃ�
		static size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �e�N�X�`����\���������̃��b�V�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t makeBoxMeshAndAttachId(ResourceIdCarrier id, size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �X�J�C�{�b�N�X���b�V�������A���̃n���h����Ԃ�
		static size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �X�J�C�{�b�N�X���b�V�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t makeSkyBoxMeshAndAttachId(ResourceIdCarrier id, size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmx�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// ���b�V�����g�p���Ă���}�e���A�����X�V����
		static void setMeshMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle);
	
		// �w��̃��b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		static void setMeshMaterialData(size_t handle);
	
		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		static void addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		static void updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		static void clearMeshInstanceParam(size_t handle);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		static void addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// �w��̃X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
		static void addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);
		
		// �w��̃��b�V���ŃV���h�E�}�b�v����������
		static void writeMeshShadowMap(size_t handle);

		// �w��̃X�L�j���O���b�V���ŃV���h�E�}�b�v����������
		static void writeMeshShadowMapUseBone(size_t handle);

		// �w��̃��b�V�����C���X�^���X�`�悷��
		static void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);

		// �X�L�j���O���b�V�����C���X�^���X�`�悷��
		static void drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);
	
	//************************************************************
	/* �X�P���g���֘A�̏��� */
	public:
	
		// �X�P���g�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createSkeleton(const SkeletonInitParam& initParam);
	
		// �X�P���g���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copySkeleton(size_t originalHandle);
	
		// �X�P���g�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam);
	
	//************************************************************
	/* ���[�V�����֌W�̏��� */
	public:
	
		// vmd�t�@�C����ǂݍ���Ń��[�V���������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t loadMotion(const std::string& motionFileName);
	
		// vmd�t�@�C����ǂݍ���Ń��[�V���������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t loadMotionAndAttachId(ResourceIdCarrier id, const std::string& motionFileName);
	
		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		static size_t getMotionEndFrameNo(size_t handle);
	
		// 2��ނ̃��[�V����������`�⊮���ăX�P���g�����X�V����
		// ���⊮�����̒l�́u0.0f��preFrame100%�v�A�u1.0f��curFrame100%�v�ƂȂ�
		static void updateMotion(
			size_t skeletonHandle,
			size_t curMotionHandle,
			size_t preMotionHnadle,
			float curFrame,
			float preFrame,
			float amount
		);
	
	//************************************************************
	/* �|�X�g�G�t�F�N�g�}�e���A���֌W�̏��� */
	public:
	
		// �|�X�g�G�t�F�N�g�̃}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);
	
		// �|�X�g�G�t�F�N�g�̃}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam);
	
		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		static void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);
	
		// �w�肵���|�X�g�G�t�F�N�g�}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		static void addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g�}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̒l���X�V����
		static void updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	//************************************************************
	/* �|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�̏��� */
	public:

		// �V���ȃ|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�����A���̃n���h����Ԃ�
		static size_t createPostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// �V���ȃ|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createPostEffectDrawFuncRunnerAndAttachId(ResourceIdCarrier id, size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g�����s�J�n����i���̃|�X�g�G�t�F�N�g�͒�~����j
		static void startPostEffect(size_t handle);

		// �S�Ẵ|�X�g�G�t�F�N�g���~����
		static void stopPostEffect();

	//************************************************************
	/* �J�����֌W�̏��� */
	public:
	
		// �J���������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createCamera();
	
		// �J���������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createCameraAndAttachId(ResourceIdCarrier id);
	
		// �w��̃J�����̃r���[�s����擾����
		static const tktkMath::Matrix4& getViewMatrix(size_t cameraHandle);
	
		// �w��̃J�����̃r���[�s���ݒ肷��
		static void setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view);
	
		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		static const tktkMath::Matrix4& getProjectionMatrix(size_t cameraHandle);
	
		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		static void setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection);
	
	//************************************************************
	/* ���C�g�֌W�̏��� */
	public:
	
		// ���C�g�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);
	
		// ���C�g�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createLightAndAttachId(
			ResourceIdCarrier id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);
	
		// ���C�g���̒萔�o�b�t�@���X�V����
		static void updateLightCBuffer(size_t handle);
	
		// �w��̃��C�g�̊�����ݒ肷��
		static void setLightAmbient(size_t handle, const tktkMath::Color& ambient);
	
		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		static void setLightDiffuse(size_t handle, const tktkMath::Color& diffuse);
	
		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		static void setLightSpeqular(size_t handle, const tktkMath::Color& speqular);
	
		// �w��̃��C�g�̍��W��ݒ肷��
		static void setLightPosition(size_t handle, const tktkMath::Vector3& position);
	
	//************************************************************
	/* �T�E���h�֌W�̏��� */
	public:
	
		// �V�����T�E���h��ǂݍ��݁A���̃��\�[�X�̃n���h����Ԃ�
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		static size_t loadSound(const std::string& fileName);
	
		// �V�����T�E���h��ǂݍ��݁A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t loadSoundAndAttachId(ResourceIdCarrier id, const std::string& fileName);
	
		// �w�肵���T�E���h���Đ�����
		static void playSound(size_t handle, bool loopPlay);
	
		// �w�肵���T�E���h���~����
		static void stopSound(size_t handle);
	
		// �w�肵���T�E���h���ꎞ��~����
		static void pauseSound(size_t handle);
	
		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		static void setMasterVolume(float volume);

	//************************************************************
	/* �t�H���g�֌W�̏��� */
	public:

		// �V�X�e���t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		static size_t createFont(const std::string& systemFontName, float fontThicknessRate);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		static size_t createFont(const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// �V�X�e���t�H���g���g�����������āA���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createFontAndAttachId(ResourceIdCarrier id, const std::string& systemFontName, float fontThicknessRate);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g�����������āA���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createFontAndAttachId(ResourceIdCarrier id, const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// �e�L�X�g�e�N�X�`���f�[�^�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		static size_t updateTextTextureData(size_t handle, const std::string& text, std::vector<unsigned char>* data);

		// �e�L�X�g�p�e�N�X�`���P�s���̃f�[�^�T�C�Y���v�Z
		static unsigned int getTextTextureLineDataSize();

		//// �w��̃A�b�v���[�h�o�b�t�@�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		//static size_t updateTextTextureUploadBuffData(size_t handle, const std::string& text);
	
		// �e�L�X�g�e�N�X�`���̃A�b�v���[�h�o�b�t�@�����ۂ̃e�N�X�`���o�b�t�@�ɃR�s�[����
		static void copyTextTextureUploadBuffer();

	//************************************************************
	/* �C���v�b�g�}�l�[�W���[�̏��� */
	public:
	
		// ID�ɑΉ��������͂�������Ă��邩�𔻒�
		static bool isPush(CommandIdCarrier commandId);
	
		// ID�ɑΉ��������͂�������n�߂����𔻒�
		static bool isTrigger(CommandIdCarrier commandId);
	
		// �ړ��������擾
		static const tktkMath::Vector2& getMoveInput();
	
		// ���_�ړ��������擾
		static const tktkMath::Vector2& getLookInput();
	
		// �e����͂�ID�����т���
		static void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		static void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);
		static void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
	
		// �e����͂ƈړ��R�}���h�����т���
		static void addDirectionCommand(DirectionCommandId directionCommand, KeybordKeyType keyType);
		static void addDirectionCommand(DirectionCommandId directionCommand, GamePadBtnType btnType);
		static void addDirectionCommand(DirectionCommandId directionCommand, MouseBtnType btnType);
	
	//************************************************************
	/* �}�E�X���͊֌W�̏��� */
	public:
	
		// �w��̃{�^����������Ă��邩
		static bool isPush(MouseBtnType buttonType);
	
		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseBtnType buttonType);
	
		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();
	
	//************************************************************
	/* �L�[�{�[�h���͊֌W�̏��� */
	public:
	
		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);
	
		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);
	
	//************************************************************
	/* �Q�[���p�b�h���͊֌W�̏��� */
	public:
	
		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getLstick();
	
		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getRstick();
	
		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(GamePadBtnType btnType);
	
		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(GamePadBtnType btnType);
	
	//************************************************************
	/* �^�C���֌W�̏��� */
	public:
	
		// �o�ߎ��Ԃ�����������
		static void resetElapsedTime();
	
		// �O�t���[���Ƃ̎��Ԃ̍������߂�
		static float deltaTime();
	
		// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
		static float noScaleDeltaTime();
	
		// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
		static float getCurTimeSec();
	
		// �ő��deltaTime�̒l��ݒ�i���̐��j
		static void setMaximumDeltaTime(float maximumDeltaTime);
	
		// ���Ԃ̌o�ߑ��x�������擾����
		static float getTimeScale();
	
		// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
		static void setTimeScale(float timeScaleRate);
	
		// ��ƂȂ�FPS��ݒ肷��
		static void setBaseFps(unsigned int baseFps = 60U);
	
		// ��ƂȂ�FPS���擾����
		static unsigned int getBaseFps();
	
		// �u�ԓI��FPS���擾����
		static float fps();
	
	//************************************************************
	/* �V�X�e���̃��\�[�X���g�����߂̃n���h�����擾���� */
	public:
	
		static size_t getSystemHandle(SystemViewportType type);
		static size_t getSystemHandle(SystemScissorRectType type);
		static size_t getSystemHandle(SystemUploadBufferType type);
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemRtBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemSpriteType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemMeshType type);
		static size_t getSystemHandle(SystemMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);
		static size_t getSystemHandle(SystemPostEffectDrawFuncRunnerType type);
	
	//************************************************************
	/* �V�X�e���̃��\�[�X���g�����߂̃n���h���ƃV�X�e���̃��\�[�X�̎�ނ����т��� */
	
		static void setSystemHandle(SystemViewportType type,					size_t handle);
		static void setSystemHandle(SystemScissorRectType type,					size_t handle);
		static void setSystemHandle(SystemUploadBufferType type,				size_t handle);
		static void setSystemHandle(SystemVertexBufferType type,				size_t handle);
		static void setSystemHandle(SystemIndexBufferType type,					size_t handle);
		static void setSystemHandle(SystemCBufferType type,						size_t handle);
		static void setSystemHandle(SystemTextureBufferType type,				size_t handle);
		static void setSystemHandle(SystemRtBufferType type,					size_t handle);
		static void setSystemHandle(SystemDsBufferType type,					size_t handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemRootSignatureType type,				size_t handle);
		static void setSystemHandle(SystemPipeLineStateType type,				size_t handle);
		static void setSystemHandle(SystemSpriteType type,						size_t handle);
		static void setSystemHandle(SystemCameraType type,						size_t handle);
		static void setSystemHandle(SystemLightType type,						size_t handle);
		static void setSystemHandle(SystemMeshType type,						size_t handle);
		static void setSystemHandle(SystemMeshMaterialType type,				size_t handle);
		static void setSystemHandle(SystemPostEffectMaterialType type,			size_t handle);
		static void setSystemHandle(SystemPostEffectDrawFuncRunnerType type,	size_t handle);
	
	//************************************************************
	/* ���\�[�XID���烊�\�[�X�n���h�����擾���� */
	public:
	
		static size_t getSceneHandle					(ResourceIdCarrier id);
		static size_t getSoundHandle					(ResourceIdCarrier id);
		static size_t getFontHandle						(ResourceIdCarrier id);
		static size_t getPostEffectMaterialHandle		(ResourceIdCarrier id);
		static size_t getSpriteMaterialHandle			(ResourceIdCarrier id);
		static size_t getLine2DMaterialHandle			(ResourceIdCarrier id);
		static size_t getBillboardMaterialHandle		(ResourceIdCarrier id);
		static size_t getSkeletonHandle					(ResourceIdCarrier id);
		static size_t getMotionHandle					(ResourceIdCarrier id);
		static size_t getBasicMeshHandle				(ResourceIdCarrier id);
		static size_t getBasicMeshMaterialHandle		(ResourceIdCarrier id);
		static size_t getPostEffectDrawFuncRunnerHandle	(ResourceIdCarrier id);
		static size_t getCameraHandle					(ResourceIdCarrier id);
		static size_t getLightHandle					(ResourceIdCarrier id);
	
	//************************************************************
	private:

		static bool												m_isGameExit;
		static std::unique_ptr<GraphicManager>					m_graphicManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<UtilityProcessManager>			m_utilityProcessManager;
	};
}
#endif // !DX12_GAME_MANAGER_H_