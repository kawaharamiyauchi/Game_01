/*!
 * @brief	���f���V�F�[�_�[�B
 */

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
Texture2D<float4> g_albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B
Texture2D<float4> g_shadowMap : register(t1);		//todo �V���h�E�}�b�v�B

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);


/// <summary>
/// ���f���V�F�[�_�[�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ModelFxConstantBuffer : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ���C�g�r���[�s���ǉ��B
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
};
static const int NUM_DIRECTION_LIG = 4;

/// <summary>
/// ���C�g�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer LightCb : register(b1){
	float3 dligDirection[NUM_DIRECTION_LIG];
	float4 dligColor[NUM_DIRECTION_LIG];
};

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ShadowMapCb : register( b1 ){
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
}

/// <summary>
/// �X�L���Ȃ����f���̒��_�\���́B
/// </summary>
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;		//���_���W�B
    float3 Normal   : NORMAL;			//�@���B
   	float2 TexCoord	: TEXCOORD0;		//UV���W�B
};


/// <summary>
/// �s�N�Z���V�F�[�_�[�̓��́B
/// </summary>
struct PSInput{
	float4 Position 	: SV_POSITION;	//���W�B
	float3 Normal		: NORMAL;		//�@���B
	float2 TexCoord		: TEXCOORD0;	//UV���W�B
	float4 posInLVP		: TEXCOORD1;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
};
/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};

/// <summary>
/// �X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 worldPos = mul(mWorld, In.Position);
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	psInput.Position  = mul(mView, worldPos);
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	psInput.Position = mul(mProj, psInput.Position);
	
	if(isShadowReciever == 1 ){
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul( mLightView, worldPos );
		psInput.posInLVP = mul( mLightProj, psInput.posInLVP );
	}
	
	//UV���W�͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.TexCoord = In.TexCoord;
	//�@���͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.Normal = In.Normal;
	
	return psInput;
}


/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain(PSInput In) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = g_albedoTexture.Sample(g_sampler, In.TexCoord);
	
	float3 lig = 0.0f;
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
		
	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
	}
	
	if(isShadowReciever == 1 ){	//�V���h�E���V�[�o�[�B
		//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if ( shadowMapUV.x < 1.0f 
			&& shadowMapUV.x > 0.0f 
			&& shadowMapUV.y < 1.0f 
			&& shadowMapUV.y > 0.0f
		) {
			
			///LVP��Ԃł̐[�x�l���v�Z�B
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.01f) {
				//�e�������Ă���̂ŁA�����キ����
				lig *= 0.5f;
			}
		}
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
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
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z  / In.Position.w;
}

