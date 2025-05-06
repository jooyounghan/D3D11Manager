#include "BlendState.h"
#include "MacroUtilities.h"

#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11BlendState> CBlendState::gBSAdditiveSS;
ComPtr<ID3D11BlendState> CBlendState::gBSAdditiveMS;
ComPtr<ID3D11BlendState> CBlendState::gBSAlphaSS;
ComPtr<ID3D11BlendState> CBlendState::gBSAlphaMS;
ComPtr<ID3D11BlendState> CBlendState::gBSPreMultipliedAlphaSS;
ComPtr<ID3D11BlendState> CBlendState::gBSPreMultipliedAlphaMS;
ComPtr<ID3D11BlendState> CBlendState::gBSMultiplicativeAlphaSS;
ComPtr<ID3D11BlendState> CBlendState::gBSMultiplicativeAlphaMS;

D3D11::CBlendState::CBlendState(
	ID3D11Device* device,
	BOOL alphaToCoverageEnable,
	UINT renderTargetBlendDescCount,
	D3D11_RENDER_TARGET_BLEND_DESC* renderTargetBlendDescs
)
{
	if (renderTargetBlendDescCount >= 8) { throw exception("renderTargetBlendDescCount exceeds 8"); }

	D3D11_BLEND_DESC blendDesc;
    ZeroMem(blendDesc);

	blendDesc.AlphaToCoverageEnable = alphaToCoverageEnable;
	blendDesc.IndependentBlendEnable = static_cast<BOOL>(renderTargetBlendDescCount > 1);
	memcpy(blendDesc.RenderTarget, renderTargetBlendDescs, renderTargetBlendDescCount * sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

	HRESULT hResult = device->CreateBlendState(&blendDesc, m_blendState.GetAddressOf());
	if (FAILED(hResult)) { throw exception("CreateBlendState Failed"); }
}

void D3D11::CBlendState::InitializeDefaultBlendStates(ID3D11Device* device)
{
    D3D11_RENDER_TARGET_BLEND_DESC additivieBlendDesc;
    additivieBlendDesc.BlendEnable = true;
    additivieBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    additivieBlendDesc.DestBlend = D3D11_BLEND_ONE;
    additivieBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    additivieBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    additivieBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    additivieBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    additivieBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    CBlendState tempBSAdditiveSS(device, false, 1, &additivieBlendDesc);
	CBlendState tempBSAdditiveMS(device, true, 1, &additivieBlendDesc);

	gBSAdditiveSS.Swap(tempBSAdditiveSS.m_blendState);
	gBSAdditiveMS.Swap(tempBSAdditiveMS.m_blendState);

	D3D11_RENDER_TARGET_BLEND_DESC alphaBlendDesc;
	alphaBlendDesc.BlendEnable = true;
	alphaBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	alphaBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	alphaBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	alphaBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	CBlendState tempBSAlphaSS(device, false, 1, &alphaBlendDesc);
	CBlendState tempBSAlphaMS(device, true, 1, &alphaBlendDesc);

	gBSAlphaSS.Swap(tempBSAlphaSS.m_blendState);
	gBSAlphaMS.Swap(tempBSAlphaMS.m_blendState);	

	D3D11_RENDER_TARGET_BLEND_DESC premultipliedAlphaBlendDesc;
	premultipliedAlphaBlendDesc.BlendEnable = true;
	premultipliedAlphaBlendDesc.SrcBlend = D3D11_BLEND_ONE;
	premultipliedAlphaBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	premultipliedAlphaBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	premultipliedAlphaBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	premultipliedAlphaBlendDesc.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	premultipliedAlphaBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	premultipliedAlphaBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	CBlendState tempBSPreMultipliedAlphaSS(device, false, 1, &premultipliedAlphaBlendDesc);
	CBlendState tempBSPreMultipliedAlphaMS(device, true, 1, &premultipliedAlphaBlendDesc);

	gBSPreMultipliedAlphaSS.Swap(tempBSPreMultipliedAlphaSS.m_blendState);
	gBSPreMultipliedAlphaMS.Swap(tempBSPreMultipliedAlphaMS.m_blendState);

	D3D11_RENDER_TARGET_BLEND_DESC multiplicativeAlphaBlendDesc;
	multiplicativeAlphaBlendDesc.BlendEnable = TRUE;
	multiplicativeAlphaBlendDesc.SrcBlend = D3D11_BLEND_ZERO;
	multiplicativeAlphaBlendDesc.DestBlend = D3D11_BLEND_SRC_COLOR;
	multiplicativeAlphaBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	multiplicativeAlphaBlendDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
	multiplicativeAlphaBlendDesc.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	multiplicativeAlphaBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	multiplicativeAlphaBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	CBlendState tempBSMultiplicativeAlphaSS(device, false, 1, &multiplicativeAlphaBlendDesc);
	CBlendState tempBSMultiplicativeAlphaMS(device, true, 1, &multiplicativeAlphaBlendDesc);

	gBSMultiplicativeAlphaSS.Swap(tempBSMultiplicativeAlphaSS.m_blendState);
	gBSMultiplicativeAlphaMS.Swap(tempBSMultiplicativeAlphaMS.m_blendState);
}
