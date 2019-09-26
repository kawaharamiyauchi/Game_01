/*!
 * @brief	���f���V�F�[�_�[�B
 */

 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
Texture2D<float4> g_albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B

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
/*!
 *@brief	���C�g�p�̒萔�o�b�t�@�B
 */
cbuffer LightCb : register(b0) {
	float3 dligDirection[4];
	float4 dligColor[4];
};

/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;		//���_���W�B
	float3 Normal   : NORMAL;			//�@���B
	float2 TexCoord	: TEXCOORD0;		//UV���W�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput {
	float4 Position 	: SV_POSITION;	//���W�B
	float3 Normal		: NORMAL;		//�@���B
	float2 TexCoord		: TEXCOORD0;	//UV���W�B
};

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
	//UV���W�͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.TexCoord = In.TexCoord;
	//�@���͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.Normal = In.Normal;
	return psInput;
}

/*!--------------------------------------------------------------------------------------
* @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin(VSInputNmTxVcTangent In)
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	//UV���W�͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.TexCoord = In.TexCoord;
	//�@���͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.Normal = In.Normal;
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


	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];

	}
	
	//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection)) * dligColor;



	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}