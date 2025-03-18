#include "BlendState.h"
#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11BlendState> CBlendState::gBSAccumulateSS;
ComPtr<ID3D11BlendState> CBlendState::gBSAccumulateMS;

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
    D3D11_RENDER_TARGET_BLEND_DESC accumulateSSRTBlendDesc;
    accumulateSSRTBlendDesc.BlendEnable = true;
    accumulateSSRTBlendDesc.SrcBlend = D3D11_BLEND_BLEND_FACTOR;
    accumulateSSRTBlendDesc.DestBlend = D3D11_BLEND_BLEND_FACTOR; // INV พฦดิ
    accumulateSSRTBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    accumulateSSRTBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    accumulateSSRTBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    accumulateSSRTBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    accumulateSSRTBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    CBlendState tempBSAccumulateSS(device, false, 1, &accumulateSSRTBlendDesc);
    CBlendState tempBSAccumulateMS(device, true, 1, &accumulateSSRTBlendDesc);

    gBSAccumulateSS.Swap(tempBSAccumulateSS.m_blendState);
    gBSAccumulateMS.Swap(tempBSAccumulateMS.m_blendState);
}
