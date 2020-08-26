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
#include "../Component/ComponentManager.h"			// �e���v���[�g�����Ɍ^����n���K�v������׉B���ł��Ȃ�
#include "../EventMessage/MessageAttachment.h"		// ���b�Z�[�W�𑗐M���鎞�ɍD���Ȍ^�̕ϐ���Y�t����
#include "../DXGameResource/Scene/SceneVTable.h"	// �V�[���}�l�[�W���[�N���X���B������ׂɃe���v���[�g�֘A�̂ݕ���
#include "DX12GameManagerInitParam.h"
#include "DX12GameManagerInitParamIncluder.h"
#include "DX12GameManagerFuncArgsIncluder.h"

namespace tktk
{
	// �O���錾
	class Window;
	class DX3DBaseObjects;
	class GameObjectManager;
	class DXGameResource;
	class SystemDXGameResourceIdGetter;
	class DirectInputWrapper;
	class ElapsedTimer;
	class Mouse;

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

	//************************************************************
	/* �E�B���h�E�̏��� */
	public:

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* �V�[���̏��� */
	public:

		// �V�[�����쐬���Ēǉ�����
		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args&&... constructorArgs);

		// �V�[����L���ɂ���
		static void enableScene(unsigned int id);

		// �V�[���𖳌��ɂ���
		static void disableScene(unsigned int id);

	//************************************************************
	/* �Q�[���I�u�W�F�N�g�̏��� */
	public:

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessageAll(unsigned int messageId, const MessageAttachment& value = {});

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag);

	//************************************************************
	/* �R���|�[�l���g�̏��� */
	public:

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		static void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args&&... args);

	//************************************************************
	/* ����DX12�̏������Ă� */
	public:

		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();

		// �w�i�F��ݒ肷��
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		static void setRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		static void setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		static void setOnlyDsv(unsigned int dsvDescriptorHeapHandle);

		// �o�b�N�o�b�t�@�[��ݒ肷��
		static void setBackBufferView();

		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		static void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		static void unSetRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		static void unSetDsv(unsigned int dsvDescriptorHeapHandle);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		static void setViewport(unsigned int handle);

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		static void setScissorRect(unsigned int handle);

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		static void setPipeLineState(unsigned int handle);

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setVertexBuffer(unsigned int handle);

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setIndexBuffer(unsigned int handle);

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// �u�����h�t�@�N�^�[��ݒ肷��
		static void setBlendFactor(const std::array<float, 4>& blendFactor);

		// �v���~�e�B�u�g�|���W��ݒ肷��
		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		// �C���X�^���X�`����s��
		static void drawInstanced(
			unsigned int vertexCountPerInstance,
			unsigned int instanceCount,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		static void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

	//************************************************************
	/* ����DX12�̃��\�[�X����� */
	public:

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createRootSignature(const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		template <class VertexData>
		static unsigned int createVertexBuffer(const std::vector<VertexData>& vertexDataArray);

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createIndexBuffer(const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		template <class ConstantBufferDataType>
		static unsigned int createCBuffer(const ConstantBufferDataType& rawConstantBufferData);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// �f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static unsigned int gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ�
		static unsigned int cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static unsigned int gpuPriorityLoadTextureBuffer(const std::string& texDataPath);
		
	//************************************************************
	/* ����DX12�̃��\�[�X���폜���� */
	public:

		// �w��̃r���[�|�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseViewport(unsigned int handle);

		// �w��̃V�U�[��`���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseScissorRect(unsigned int handle);

		// �w��̃��[�g�V�O�l�`�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRootSignature(unsigned int handle);

		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void erasePipeLineState(unsigned int handle);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseVertexBuffer(unsigned int handle);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseIndexBuffer(unsigned int handle);

		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseCBuffer(unsigned int handle);

		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseTextureBuffer(unsigned int handle);

		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseDsBuffer(unsigned int handle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRtBuffer(unsigned int handle);

		// �w��̒ʏ�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseBasicDescriptorHeap(unsigned int handle);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseRtvDescriptorHeap(unsigned int handle);

		// �w��̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		static void eraseDsvDescriptorHeap(unsigned int handle);

	//************************************************************
	/* ����DX12�̃��\�[�X��ݒ�A�擾���� */
	public:

		// �w��̒��_�o�b�t�@���X�V����
		template <class VertexData>
		static void updateVertexBuffer(unsigned int handle, const std::vector<VertexData>& vertexDataArray);

		// �w��̃C���f�b�N�X�o�b�t�@���X�V����
		static void updateIndexBuffer(unsigned int handle, const std::vector<unsigned short>& indexDataArray);

		// �w��̒萔�o�b�t�@���X�V����
		template <class ConstantBufferDataType>
		static void updateCBuffer(unsigned int handle, const ConstantBufferDataType& rawConstantBufferData);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		static void clearRtv(unsigned int handle, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���i�e�N�Z���j�j
		static const tktkMath::Vector3& getTextureBufferSizePx(unsigned int handle);
		static const tktkMath::Vector2& getDsBufferSizePx(unsigned int handle);
		static const tktkMath::Vector2& getRtBufferSizePx(unsigned int handle);

	//************************************************************
	/* �X�v���C�g�֌W�̏��� */
	public:

		// �X�v���C�g�}�e���A�������
		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		static void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* 2D���C���֌W�̏��� */
	public:

		// �Q�c���C�������
		static void createLine(unsigned int id);

		// ����`�悷��
		static void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* ���b�V���֌W�̏��� */
	public:

		// �ʏ탁�b�V�������
		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���̃R�s�[�����
		static void copyBasicMesh(unsigned int id, unsigned int originalId);

		// �ʏ탁�b�V���}�e���A�������
		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����
		static void copyBasicMeshMaterial(unsigned int id, unsigned int originalId);

		// �ʏ탁�b�V�����g�p���Ă���}�e���A�����X�V����
		static void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		static void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		static void setMaterialData(unsigned int id);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		template <class CbufferType>
		static void addMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, CbufferType&& value);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		template <class CbufferType>
		static void updateMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, const CbufferType& value);

		// �w��̒ʏ탁�b�V����`�悷��
		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	//************************************************************
	/* �X�P���g���֘A�̏��� */
	public:

		// �X�P���g�����쐬����
		static void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		static void updateBoneMatrixCbuffer(unsigned int id);

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		static void resetBoneMatrixCbuffer();

	//************************************************************
	/* ���[�V�����֌W�̏��� */
	public:

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		static void loadMotion(unsigned int id, const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		static unsigned int getMotionEndFrameNo(unsigned int id);

		// 2��ނ̃��[�V����������`�⊮���ăX�P���g�����X�V����
		// ���⊮�����̒l�́u0.0f��preFrame100%�v�A�u1.0f��curFrame100%�v�ƂȂ�
		static void updateMotion(
			unsigned int skeletonId,
			unsigned int curMotionId,
			unsigned int preMotionId,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	//************************************************************
	/* �|�X�g�G�t�F�N�g�֌W�̏��� */
	public:

		// �|�X�g�G�t�F�N�g�̃}�e���A�������
		static void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		static void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* �J�����֌W�̏��� */
	public:

		// �J���������
		static void createCamera(unsigned int id);

		// �w��̃J�����̃r���[�s����擾����
		static const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId);

		// �w��̃J�����̃r���[�s���ݒ肷��
		static void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		static const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId);

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		static void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	//************************************************************
	/* ���C�g�֌W�̏��� */
	public:

		// ���C�g�����
		static void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		static void updateLightCBuffer(unsigned int id);

		// �w��̃��C�g�̊�����ݒ肷��
		static void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		static void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		static void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		static void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

	//************************************************************
	/* �T�E���h�֌W�̏��� */
	public:

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		static void loadSound(unsigned int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		static void playSound(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		static void stopSound(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		static void pauseSound(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		static void setMasterVolume(float volume);

	//************************************************************
	/* �}�E�X���͊֌W�̏��� */
	public:

		// �w��̃{�^����������Ă��邩
		static bool isPush(MouseButtonType buttonType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseButtonType buttonType);

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

		static unsigned int getSystemHandle(SystemViewportType type);
		static unsigned int getSystemHandle(SystemScissorRectType type);
		static unsigned int getSystemHandle(SystemVertexBufferType type);
		static unsigned int getSystemHandle(SystemIndexBufferType type);
		static unsigned int getSystemHandle(SystemCBufferType type);
		static unsigned int getSystemHandle(SystemTextureBufferType type);
		static unsigned int getSystemHandle(SystemDsBufferType type);
		static unsigned int getSystemHandle(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemDsvDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemRootSignatureType type);
		static unsigned int getSystemHandle(SystemPipeLineStateType type);
		static unsigned int getSystemId(SystemBasicMeshType type);
		static unsigned int getSystemId(SystemBasicMeshMaterialType type);
		static unsigned int getSystemId(SystemPostEffectMaterialType type);

	//************************************************************
	/* �V�X�e���̃��\�[�X���g�����߂̃n���h���ƃV�X�e���̃��\�[�X�̎�ނ����т��� */

		static void setSystemHandle(SystemViewportType type,			unsigned int handle);
		static void setSystemHandle(SystemScissorRectType type,			unsigned int handle);
		static void setSystemHandle(SystemVertexBufferType type,		unsigned int handle);
		static void setSystemHandle(SystemIndexBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemCBufferType type,				unsigned int handle);
		static void setSystemHandle(SystemTextureBufferType type,		unsigned int handle);
		static void setSystemHandle(SystemRtBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemDsBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemRootSignatureType type,		unsigned int handle);
		static void setSystemHandle(SystemPipeLineStateType type,		unsigned int handle);

	//************************************************************
	/* ������ */
	public:

		static unsigned int createVertexBufferImpl(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static unsigned int createCbufferImpl(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		static void createSceneImpl(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		static void updateVertexBufferImpl(unsigned int handle, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void updateCbufferImpl(unsigned int handle, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void addMaterialAppendParamImpl(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);
		static void updateMaterialAppendParamImpl(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

	//************************************************************
	private:

		static std::unique_ptr<Window>							m_window;
		static std::unique_ptr<DX3DBaseObjects>					m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>				m_gameObjectManager;
		static std::unique_ptr<ComponentManager>				m_componentManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<SystemDXGameResourceIdGetter>	m_systemDXGameResourceIdGetter;
		static std::unique_ptr<DirectInputWrapper>				m_directInputWrapper;
		static std::unique_ptr<Mouse>							m_mouse;
		static std::unique_ptr<ElapsedTimer>					m_elapsedTimer;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �V�[�����쐬���Ēǉ�����
	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args&&...constructorArgs)
	{
		createSceneImpl(id, std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...), &SceneVTableInitializer<SceneType>::m_vtable);
	}

	// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
	template<class ComponentType>
	inline void DX12GameManager::addUpdatePriority(float priority)
	{
		m_componentManager->addUpdatePriority<ComponentType>(priority);
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> DX12GameManager::createComponent(Args&&...args)
	{
		return m_componentManager->createComponent<ComponentType>(std::forward<Args>(args)...);
	}

	// ���_�o�b�t�@�����
	template<class VertexData>
	inline unsigned int DX12GameManager::createVertexBuffer(const std::vector<VertexData>& vertexDataArray)
	{
		return createVertexBufferImpl(sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	// �萔�o�b�t�@�����
	template<class ConstantBufferDataType>
	inline unsigned int DX12GameManager::createCBuffer(const ConstantBufferDataType& rawConstantBufferData)
	{
		return createCbufferImpl(sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	// �w��̒��_�o�b�t�@���X�V����
	template<class VertexData>
	inline void DX12GameManager::updateVertexBuffer(unsigned int handle, const std::vector<VertexData>& vertexDataArray)
	{
		updateVertexBufferImpl(handle, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	// �w��̒萔�o�b�t�@���X�V����
	template<class ConstantBufferDataType>
	inline void DX12GameManager::updateCBuffer(unsigned int handle, const ConstantBufferDataType& rawConstantBufferData)
	{
		updateCbufferImpl(handle, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
	template<class CbufferType>
	inline void DX12GameManager::addMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, CbufferType&& value)
	{
		addMaterialAppendParamImpl(id, cbufferHandle, sizeof(CbufferType), new CbufferType(std::forward<CbufferType>(value)));
	}

	// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
	template<class CbufferType>
	inline void DX12GameManager::updateMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, const CbufferType& value)
	{
		updateMaterialAppendParamImpl(id, cbufferHandle, sizeof(CbufferType), &value);
	}
}
#endif // !DX12_GAME_MANAGER_H_