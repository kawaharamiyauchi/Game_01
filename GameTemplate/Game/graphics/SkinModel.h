#pragma once

#include "Skeleton.h"
#include "C3DModelEffect.h"



/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	/// <summary>
/// �����_�����O���[�h�B
/// </summary>
	enum EnRenderMode {
		enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
		enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
		enRenderMode_Normal,			//�ʏ탌���_�����O�B
		enRenderMode_Num,				//�����_�����O���[�h�̐��B
	};
	/// <summary>
	/// ���f���G�t�F�N�g�p�̍\���́B
	/// </summary>
	/// <remarks>
	/// �����ύX������AAsserts/shader/model.fx��
	/// VSCb���ύX����K�v������܂��B
	/// ���̍\���̂�16byte�A���C�����g�ɂȂ��Ă���K�v������܂��B
	/// </remarks>
	struct SModelFxConstantBuffer {
		CMatrix mWorld;			//���[���h�s��B
		CMatrix mView;			//�r���[�s��B
		CMatrix mProj;			//�v���W�F�N�V�����s��B
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;	//todo �V���h�E���V�[�o�[�̃t���O�B
	};
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/// <summary>
	/// �`�揈�����s�����ǂ���
	/// </summary>
	/// <param name="flag">�A�N�e�B�u�t���O</param>
	void SetActiveFlag(bool flag)
	{
		IsActiveflag = flag;
	}
	/// <summary>
	/// �A�N�e�B�u�t���O���擾
	/// </summary>
	/// <returns>�A�N�e�B�u�t���O</returns>
	bool GetActiveFlag()
	{
		return IsActiveflag;
	}
	/// <summary>
	/// �f�B���N�V�������C�g��t�^���邩�ǂ���
	/// </summary>
	/// <param name="flag">�f�B���N�V�������C�g�t���O</param>
	void SetlightFlag(bool flag)
	{
		lightFlag = flag;
	}
	/// <summary>
	/// ��֐�
	/// </summary>
	/// <param name="flag"></param>
	void SetColorFlag(bool flag)
	{
		colorFlag = flag;
	}
	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	void Draw(/*EnRenderMode renderMode, */CMatrix viewMatrix, CMatrix projMatrix );
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};

	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">true��n���ƃV���h�E���V�[�o�[�ɂȂ�</param>
	/// <remarks>
	/// �V���h�E���V�[�o�[�Ƃ͉e�𗎂Ƃ����I�u�W�F�N�g�̂��Ƃł��B
	/// �V���h�E�L���X�^�[�ɂ���Đ������ꂽ�A�V���h�E�}�b�v�𗘗p����
	/// ���g�ɉe�𗎂Ƃ��܂��B
	/// �I�u�W�F�N�g���V���h�E���V�[�o�[���V���h�E�L���X�^�[�ɂȂ��Ă���ꍇ��
	/// �Z���t�V���h�E(�����̉e�������ɗ�����)���s�����Ƃ��ł��܂��B
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/// <summary>
	/// �}�e���A���ɑ΂��ăN�G�����s���B
	/// </summary>
	/// <param name="func">�₢���킹�֐�</param>
	void QueryMaterials(std::function<void(C3DModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<C3DModelEffect*>(material));
			});
	}
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	void InitDirectionLight()
	{
		m_light.directionLight.direction[0] = { 0.0f,-0.8f,0.0f,0.0f };
		m_light.directionLight.color[0] = { 1.0f,1.0f,1.0f,1.0f };
		m_light.specPow[0] = 10.0f;
		
		m_light.directionLight.direction[1] = { 0.0f,0.8f,0.0f,0.0f };
		m_light.directionLight.color[1] = { 1.0f,1.0f,1.0f,1.0f };
		m_light.specPow[1] = 10.0f;

		m_light.directionLight.direction[2] = { 1.0f,0.0f,1.0f,0.0f };
		m_light.directionLight.color[2] = { 1.0f,1.0f,1.0f,0.5f };
		m_light.specPow[2] = 10.0f;

		m_light.directionLight.direction[3] = { -1.0f,0.0f,-1.0f,0.0f };
		m_light.directionLight.color[3] = { 1.0f,1.0f,1.0f,0.5f };
		m_light.specPow[3] = 10.0f;
	}
	void UpDate() {
		
	}
	
private:
	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	struct DirectionLight {
		CVector4 direction[4];
		CVector4 color[4];
		
	};

	struct Light {
		DirectionLight		directionLight;		//�f�B���N�V�������C�g
		CVector3			eyePos;				//���_�̍��W
		float				specPow[4];			//���ʔ��˂̍i��B
	
	};
private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*		m_lightCb = nullptr;			//!<���C�g�p�̒萔�o�b�t�@�B>
	ID3D11Buffer*		m_nullCb = nullptr;				//null�萔�o�b�t�@�B>
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	Light				m_light;
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	
	bool m_isShadowReciever;
	bool IsActiveflag = true;							//!<�A�N�e�B�u�t���O
	bool lightFlag = true;
	bool colorFlag = false;
};

