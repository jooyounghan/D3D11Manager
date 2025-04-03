#include "BlendState.h"
#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11BlendState> CBlendState::gBSAccumulateSS;
ComPtr<ID3D11BlendState> CBlendState::gBSAccumulateMS;
ComPtr<ID3D11BlendState> CBlendState::gBSAlphaBlendSS;
ComPtr<ID3D11BlendState> CBlendState::gBSAlphaBlendMS;

D3D11::CBlendState::CBlendState(
	ID3D11Device* device,
	BOOL alphaToCoverageEnable,
	UINT renderTargetBlendDescCount,
	D3D11_RENDER_TARGET_BLEND_DESC* renderTargetBlendDescs
)
{
	if (renderTargetBlendDescCount >= 8) { throw exception("renderTargetBlendDescCount exceeds 8"); }

	D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.AlphaToCoverageEnable = alphaToCoverageEnable;
	blendDesc.IndependentBlendEnable = static_cast<BOOL>(renderTargetBlendDescCount > 1);
	memcpy(blendDesc.RenderTarget, renderTargetBlendDescs, renderTargetBlendDescCount * sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

	HRESULT hResult = device->CreateBlendState(&blendDesc, m_blendState.GetAddressOf());
	if (FAILED(hResult)) { throw exception("CreateBlendState Failed"); }
}

void D3D11::CBlendState::InitializeDefaultBlendStates(ID3D11Device* device)
{
    D3D11_RENDER_TARGET_BLEND_DESC accumulateBlendDesc;
    accumulateBlendDesc.BlendEnable = true;
    accumulateBlendDesc.SrcBlend = D3D11_BLEND_BLEND_FACTOR;
    accumulateBlendDesc.DestBlend = D3D11_BLEND_BLEND_FACTOR;
    accumulateBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    accumulateBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    accumulateBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    accumulateBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    accumulateBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    CBlendState tempBSAccumulateSS(device, false, 1, &accumulateBlendDesc);
    CBlendState tempBSAccumulateMS(device, true, 1, &accumulateBlendDesc);

    gBSAccumulateSS.Swap(tempBSAccumulateSS.m_blendState);
    gBSAccumulateMS.Swap(tempBSAccumulateMS.m_blendState);


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

	gBSAlphaBlendSS.Swap(tempBSAlphaSS.m_blendState);
	gBSAlphaBlendMS.Swap(tempBSAlphaMS.m_blendState);

}
