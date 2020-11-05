#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <utility>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../GameObject/GameObjectPtr.h"			// �Q�[���I�u�W�F�N�g���������Ɏg�p����
#include "../GameObject/GameObjectTagCarrier.h"
#include "../Component/ComponentManager.h"			// �e���v���[�g�����Ɍ^����n���K�v������׉B���ł��Ȃ�
#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"		// ���b�Z�[�W�𑗐M���鎞�ɍD���Ȍ^�̕ϐ���Y�t����
#include "../DXGameResource/Scene/SceneVTable.h"	// �V�[���}�l�[�W���[�N���X���B������ׂɃe���v���[�g�֘A�̂ݕ���
#include "DX12GameManagerInitParam.h"
#include "DX12GameManagerInitParamIncluder.h"
#include "DX12GameManagerFuncArgsIncluder.h"

#include "TktkDX12Game/DXGameResource/_HandleGetter/ResourceIdCarrier.h"

namespace tktk
{
	// �O���錾
	class Window;
	class DX3DBaseObjects;
	class GameObjectManager;
	class DXGameResource;
	class DXGameResourceHandleGetter;
	class SystemDXGameResourceHandleGetter;
	class DirectInputWrapper;
	class ElapsedTimer;
	class Mouse;
	class InputManager;

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

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* �V�[���̏��� */
	public:

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t addScene(const SceneDataInitParam& initParam);

		// �V�[�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t addSceneAndAttachId(ResourceIdCarrier id, const SceneDataInitParam& initParam);

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
		static void addUpdatePriority(float priority) { m_componentManager->addUpdatePriority<ComponentType>(priority); }

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		static void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(const GameObjectPtr& user, Args&&... args) { return m_componentManager->createComponent<ComponentType>(user, std::forward<Args>(args)...); }

	//************************************************************
	/* ����DX12�̏������Ă� */
	public:

		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();

		// �w�i�F��ݒ肷��
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

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

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setIndexBuffer(size_t handle);

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// �u�����h�t�@�N�^�[��ݒ肷��
		static void setBlendFactor(const std::array<float, 4>& blendFactor);

		// �v���~�e�B�u�g�|���W��ݒ肷��
		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

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

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createRootSignature(const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// �A�b�v���[�h�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createUploadBuffer(const UploadBufferInitParam& initParam);
		
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

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static size_t gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ�
		static size_t cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static size_t gpuPriorityLoadTextureBuffer(const std::string& texDataPath);
		
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

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		static void clearRtv(size_t handle, size_t rtvLocationIndex, const tktkMath::Color& color);

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���i�e�N�Z���j�j
		static const tktkMath::Vector3& getTextureBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getDsBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getRtBufferSizePx(size_t handle);

	//************************************************************
	/* �X�v���C�g�֌W�̏��� */
	public:

		// �X�v���C�g�}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// �X�v���C�g�}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		static void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		static void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate);

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		static void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam);

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
		static size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam);

		// �r���{�[�h�}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam);

		// �w�肵���r���{�[�h��`�悷��
		static void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs);

		// �������\���R�s�[�o�b�t�@���g���Ē萔�o�b�t�@���X�V����
		static void updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs);

		// �������\���R�s�[�o�b�t�@���g���Ē萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		static void updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam);

	//************************************************************
	/* ���b�V���֌W�̏��� */
	public:

		// �ʏ탁�b�V�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createBasicMesh(const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createBasicMeshAndAttachId(ResourceIdCarrier id, const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copyBasicMesh(size_t originalHandle);

		// �ʏ탁�b�V���̃R�s�[�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t copyBasicMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle);

		// �ʏ탁�b�V���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createBasicMeshMaterialAndAttachId(ResourceIdCarrier id, const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copyBasicMeshMaterial(size_t originalHandle);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t copyBasicMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle);

		// �ʏ탁�b�V�����g�p���Ă���}�e���A�����X�V����
		static void setMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		static void writeBasicMeshShadowMap(size_t handle);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		static void setMaterialData(size_t handle);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		template <class CbufferType>
		static void addMaterialAppendParam(size_t handle, size_t cbufferHandle, CbufferType&& value)			{ addMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), new CbufferType(std::forward<CbufferType>(value))); }

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		template <class CbufferType>
		static void updateMaterialAppendParam(size_t handle, size_t cbufferHandle, const CbufferType& value)	{ updateMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), &value); }

		// �w��̒ʏ탁�b�V����`�悷��
		static void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

		// pmx�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);

	//************************************************************
	/* �X�P���g���֘A�̏��� */
	public:

		// �X�P���g�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createSkeleton(const SkeletonInitParam& initParam);

		// �X�P���g���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		static size_t copySkeleton(size_t originalHandle);

		// �w��̃X�P���g���̍����̒萔�o�b�t�@�̒l�ɃA�b�v���[�h���邽�߂̃o�b�t�@�����A���̃n���h����Ԃ�
		// �����̊֐��Ŏ擾�����n���h���͎g�p��ɁuDX12GameManager::eraseUploadBuffer(handle)�v��K���ǂ�Ńo�b�t�@���폜���Ă�������
		static size_t createSkeletonUploadBufferHandle(size_t handle);

		// �X�P���g�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam);

		// �w��̃X�P���g�����g���Ĉ������\���R�s�[�o�b�t�@���g���������Ǘ�����萔�o�b�t�@���X�V����
		static void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle);

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		static void resetBoneMatrixCbuffer();

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
			size_t curFrame,
			size_t preFrame,
			float amount
		);

	//************************************************************
	/* �|�X�g�G�t�F�N�g�֌W�̏��� */
	public:

		// �|�X�g�G�t�F�N�g�̃}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		static size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// �|�X�g�G�t�F�N�g�̃}�e���A�������A���̃��\�[�X�̃n���h���ƈ����̃n���h�������ѕt����
		static size_t createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		static void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

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
	/* ���͊֌W���ʂ̏��� */
	public:

		// ����̓��͂�������Ă��邩���n�߂�
		// �u�Ή�������́FMouseButtonType, KeybordKeyType, GamePadBtnType�v
		// ��L�ȊO�̈����̌^�̏ꍇ�AInputManager���g�������͌��m�ɂȂ�
		template <class T>
		static bool isPush(T type);

		// ����̓��͂�������n�߂������n�߂�
		// �u�Ή�������́FMouseButtonType, KeybordKeyType, GamePadBtnType�v
		// ��L�ȊO�̈����̌^�̏ꍇ�AInputManager���g�������͌��m�ɂȂ�
		template <class T>
		static bool isTrigger(T type);

	//************************************************************
	/* �C���v�b�g�}�l�[�W���[�̏��� */
	public:

		// ID�ɑΉ��������͂�������Ă��邩�𔻒�
		static bool isPushCommand(int commandId);

		// ID�ɑΉ��������͂�������n�߂����𔻒�
		static bool isTriggerCommand(int commandId);

		// �ړ��������擾
		static const tktkMath::Vector2& moveVec();

		// ���_�ړ��������擾
		static const tktkMath::Vector2& lookVec();

		// �e����͂�ID�����т���
		static void addCommand(int commandId, KeybordKeyType keyType);
		static void addCommand(int commandId, GamePadBtnType btnType);
		static void addCommand(int commandId, MouseButtonType btnType);

		// �e����͂ƈړ��R�}���h�����т���
		static void addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType);
		static void addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType);
		static void addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType);

	//************************************************************
	/* �}�E�X���͊֌W�̏��� */
	public:

		// �w��̃{�^����������Ă��邩
		static bool isMousePush(MouseButtonType buttonType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isMouseTrigger(MouseButtonType buttonType);

		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* �L�[�{�[�h���͊֌W�̏��� */
	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isKeybordPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		static bool isKeybordTrigger(KeybordKeyType keyType);

	//************************************************************
	/* �Q�[���p�b�h���͊֌W�̏��� */
	public:

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getLstick();

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getRstick();

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPadPush(GamePadBtnType btnType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isPadTrigger(GamePadBtnType btnType);

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
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemBasicMeshType type);
		static size_t getSystemHandle(SystemBasicMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);

	//************************************************************
	/* �V�X�e���̃��\�[�X���g�����߂̃n���h���ƃV�X�e���̃��\�[�X�̎�ނ����т��� */

		static void setSystemHandle(SystemViewportType type,			size_t handle);
		static void setSystemHandle(SystemScissorRectType type,			size_t handle);
		static void setSystemHandle(SystemVertexBufferType type,		size_t handle);
		static void setSystemHandle(SystemIndexBufferType type,			size_t handle);
		static void setSystemHandle(SystemCBufferType type,				size_t handle);
		static void setSystemHandle(SystemTextureBufferType type,		size_t handle);
		static void setSystemHandle(SystemRtBufferType type,			size_t handle);
		static void setSystemHandle(SystemDsBufferType type,			size_t handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemRootSignatureType type,		size_t handle);
		static void setSystemHandle(SystemPipeLineStateType type,		size_t handle);
		static void setSystemHandle(SystemCameraType type,				size_t handle);
		static void setSystemHandle(SystemLightType type,				size_t handle);
		static void setSystemHandle(SystemBasicMeshType type,			size_t handle);
		static void setSystemHandle(SystemBasicMeshMaterialType type,	size_t handle);
		static void setSystemHandle(SystemPostEffectMaterialType type,	size_t handle);

	//************************************************************
	/* ������ */
	public:

		static void addMaterialAppendParamImpl		(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);
		static void updateMaterialAppendParamImpl	(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

		static size_t getSceneHandle				(ResourceIdCarrier id);
		static size_t getSoundHandle				(ResourceIdCarrier id);
		static size_t getPostEffectMaterialHandle	(ResourceIdCarrier id);
		static size_t getSpriteMaterialHandle		(ResourceIdCarrier id);
		static size_t getLine2DMaterialHandle		(ResourceIdCarrier id);
		static size_t getBillboardMaterialHandle	(ResourceIdCarrier id);
		static size_t getSkeletonHandle				(ResourceIdCarrier id);
		static size_t getMotionHandle				(ResourceIdCarrier id);
		static size_t getBasicMeshHandle			(ResourceIdCarrier id);
		static size_t getBasicMeshMaterialHandle	(ResourceIdCarrier id);
		static size_t getCameraHandle				(ResourceIdCarrier id);
		static size_t getLightHandle				(ResourceIdCarrier id);

	//************************************************************
	private:

		static bool												m_isGameExit;
		static std::unique_ptr<Window>							m_window;
		static std::unique_ptr<DX3DBaseObjects>					m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>				m_gameObjectManager;
		static std::unique_ptr<ComponentManager>				m_componentManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<DXGameResourceHandleGetter>		m_resHandleGetter;
		static std::unique_ptr<SystemDXGameResourceHandleGetter>m_systemDXGameResourceHandleGetter;
		static std::unique_ptr<DirectInputWrapper>				m_directInputWrapper;
		static std::unique_ptr<Mouse>							m_mouse;
		static std::unique_ptr<InputManager>					m_inputManager;
		static std::unique_ptr<ElapsedTimer>					m_elapsedTimer;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͎��������߂̃e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ID�ɑΉ��������͂�������Ă��邩�𔻒�
	template<class T>
	inline bool DX12GameManager::isPush(T type)
	{
		return isPushCommand(static_cast<int>(type));
	}

	// �w��̃}�E�X�{�^����������Ă��邩
	template<>
	inline bool DX12GameManager::isPush(MouseButtonType type)
	{
		return isMousePush(type);
	}

	// �w��̃L�[��������Ă��邩�𔻒�
	template<>
	inline bool DX12GameManager::isPush(KeybordKeyType type)
	{
		return isKeybordPush(type);
	}

	// �w��̃p�b�h�{�^����������Ă��邩�𔻒�
	template<>
	inline bool DX12GameManager::isPush(GamePadBtnType type)
	{
		return isPadPush(type);
	}

	template<class T>
	inline bool DX12GameManager::isTrigger(T type)
	{
		return isTriggerCommand(static_cast<int>(type));
	}

	// �w��̃}�E�X�{�^����������n�߂����𔻒�
	template<>
	inline bool DX12GameManager::isTrigger(MouseButtonType type)
	{
		return isMouseTrigger(type);
	}

	// �w��̃L�[��������n�߂����𔻒�
	template<>
	inline bool DX12GameManager::isTrigger(KeybordKeyType type)
	{
		return isKeybordTrigger(type);
	}

	// �w��̃p�b�h�{�^����������n�߂����𔻒�
	template<>
	inline bool DX12GameManager::isTrigger(GamePadBtnType type)
	{
		return isPadTrigger(type);
	}
}
#endif // !DX12_GAME_MANAGER_H_