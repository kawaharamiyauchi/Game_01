/*!
 * @brief	���f���V�F�[�_�[�B
 */


 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
Texture2D<float4> g_albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B
Texture2D<float4> g_shadowMap:register(t2);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/*!
 * @brief	���_�V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	
	//todo ���C�g�r���[�s���ǉ��B
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
};

/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
struct SDirectionLight {
	float3 direction;
	float4 color;

};
static const int NUM_DIRECTION_LIG = 4;
/*!
 *@brief	���C�g�p�̒萔�o�b�t�@�B
 */
cbuffer LightCb : register(b1) {
	/*float3 dligDirection[NUM_DIRECTION_LIG];
	float4 dligColor[NUM_DIRECTION_LIG];
	float3 eyePos;
	float specPow;*/
	SDirectionLight directionLight;
	float3 eyePos;
	float specPow;
	float3 ambientLight;
};

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
}
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;		//���_���W�B
	float3 Normal   : NORMAL;			//�@���B
	float3 Tangent	: TANGENT;
	float2 TexCoord	: TEXCOORD0;		//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//���_���W�B
	float3 Normal   : NORMAL;				//�@���B
	float2 TexCoord	: TEXCOORD0;			//UV���W�B
	float3 Tangent	: TANGENT;				//�ڃx�N�g���B
	uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
	float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput {
	float4 Position 	: SV_POSITION;	//���W�B
	float3 Normal		: NORMAL;		//�@���B
	float3 Tangent		: TANGENT;
	float2 TexCoord		: TEXCOORD0;	//UV���W�B
	float4 posInLVP		: TEXCOORD1;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	float3 WorldPos		: TEXCOORD2;	//���[���h���W�B����U


};

/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};

float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}

	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain(VSInputNmTxVcTangent In)
{
	
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 m_worldPos = mul(mWorld, In.Position);
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	psInput.Position = mul(mView, m_worldPos);
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	psInput.Position = mul(mProj, psInput.Position);

	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, m_worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//UV���W�͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.TexCoord = In.TexCoord;
	//�@���͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	//psInput.Normal = In.Normal;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin(VSInputNmTxWeights In)
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}

	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));
	
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 m_worldPos = mul(mWorld, In.Position);
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	psInput.Position = mul(mView, m_worldPos);
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	psInput.Position = mul(mProj, psInput.Position);

	psInput.WorldPos = m_worldPos;

	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, m_worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	return psInput;
}

//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = g_albedoTexture.Sample(g_sampler, In.TexCoord);
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B


	
	/// <summary>
	/// ���C�g4�{(�f�B���N�V�������C�g�{���ʔ���)
	/// </summary>
	/*float3 toEyeDir[NUM_DIRECTION_LIG];
	float3 reflectEyeDir[NUM_DIRECTION_LIG];
	float t[NUM_DIRECTION_LIG];
	float3 specLig[NUM_DIRECTION_LIG];*/
	//for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//	lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) *  dligColor[i];
	//	toEyeDir[i] = normalize(eyePos - In.WorldPos);
	//	reflectEyeDir[i] = -toEyeDir[i] + 2 * dot(In.Normal, toEyeDir[i]) * In.Normal;
	//	t[i] = max(0.0f, dot(-dligDirection[i], reflectEyeDir[i]));
	//	//���ʔ��˂𔽎ˌ��ɉ��Z����B
	//	lig += pow(0.1, 1.0f) * dligColor[i].xyz;

	//}
	/// <summary>
	/// ���C�g1�{
	/// </summary>
	/// �g�U���ˌ�
	float3 lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction)) * directionLight.color.xyz;
	
	float3 toEyeDir = normalize(eyePos - In.WorldPos);

	float3 reflectEyeDir = -toEyeDir + 2 * dot(In.Normal, toEyeDir) * In.Normal;

	float t = max(0.0f, dot(-directionLight.direction, reflectEyeDir));

	float3 specLig = pow(t, specPow) * directionLight.color.xyz;
	

	

	float3 halflig = lig*0.5 ;

		if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B
			//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
			float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
			//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
			if (shadowMapUV.x < 1.0f
				&& shadowMapUV.x > 0.0f
				&& shadowMapUV.y < 1.0f
				&& shadowMapUV.y > 0.0f
				) {

				///LVP��Ԃł̐[�x�l���v�Z�B
				float zInLVP = In.posInLVP.z / In.posInLVP.w;
				//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
				float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);
				

				//float z = zInLVP - zInShadowMap;
				if (zInLVP - zInShadowMap > 0.005f) {
					//�e�������Ă���̂ŁA�����キ����
					lig *= 0.1f;
				}
				//VSM??
				//Variance Shadow Maps�i���U�V���h�E�}�b�v�j
				float add = 0.0f;
				//for (int i = 2; i < 20; i++) {
				//	//2*0.05 =0.1
				//	add = 0.01f*i;
				//	if (zInLVP - zInShadowMap > add) {

				//		lig += halflig / 20.0f;
				//		//lig *= 0.99f;
				//	}
				//}
				}
			
		}
	
		
	
	lig += ambientLight;

	//���ʔ��˂𔽎ˌ��ɉ��Z����B
	lig += specLig;
	
	
	
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// �X�L�������p�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
// <summary>
/// �X�L������V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = CalcSkinMatrix(In);
	float4 pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}
