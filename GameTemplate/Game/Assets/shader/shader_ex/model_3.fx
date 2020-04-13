/*!
 * @brief	���f���V�F�[�_�[�B
 */

 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
Texture2D<float4> g_albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B
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
};

/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
struct SDirectionLight {
	float3 direction[4];
	float4 color[4];

	//float3 direction;
	//float4 color;
};
/*!
 *@brief	���C�g�p�̒萔�o�b�t�@�B
 */
cbuffer LightCb : register(b0) {
	SDirectionLight		directionLight;		//�f�B���N�V�������C�g�B
	float3 eyePos[4];
	float specPow[4];

	//float3 eyePos;
	//float specPow;
};

/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;		//���_���W�B
	float3 Normal   : NORMAL;			//�@���B
	float3 Tangent		: TANGENT;
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
	float4 worldPos		: TEXCOORD1;	//���[���h���W�B
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
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
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


	float3 lig = float3(0.0f,0,0);
	for (int i = 0; i < 4; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) *  directionLight.color[i].xyz;
		//lig += max(0.0f, dot(In.Normal * -1.0f, float3(0,1,1))) *  directionLight.color[i].xyz;

		/*float3 R = directionLight.direction[i]
			+ 2 * dot(In.Normal, -directionLight.direction[i])
			*In.Normal;

		float3 E = normalize(In.worldPos - eyePos[i]);

		float specPower = max(0, dot(R, -E));

		lig += directionLight.color[i].xyz*pow(specPower, specPow[i]);*/

	}
	
	
		
	
	/*lig += max(0.0f, dot(In.Normal * -1.0f, directionLight.direction)) *  directionLight.color.xyz;
	float3 R = directionLight.direction
		+ 2 * dot(In.Normal, -directionLight.direction)
		*In.Normal;

	float3 E = normalize(In.worldPos - eyePos);

	float specPower = max(0, dot(R, -E));

	lig += directionLight.color.xyz*pow(specPower, specPow);*/


	lig += float3(0.5f, 0.5f, 0.5f);

	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}