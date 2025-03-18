#include "DepthStencilState.h"
#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11DepthStencilState> CDepthStencilState::gDSSDraw;
ComPtr<ID3D11DepthStencilState> CDepthStencilState::gDSSMasking;
ComPtr<ID3D11DepthStencilState> CDepthStencilState::gDSSConditionalDraw;

CDepthStencilState::CDepthStencilState(
	ID3D11Device* device, 
	BOOL depthEnable, 
	D3D11_DEPTH_WRITE_MASK depthWriteMask, 
	D3D11_COMPARISON_FUNC depthFunc, 
	BOOL stencilEnable, UINT8 stencilReadMask, 
	UINT8 stencilWriteMask, 
	D3D11_STENCIL_OP frontStencilFailOp, 
	D3D11_STENCIL_OP frontStencilDepthFailOp, 
	D3D11_STENCIL_OP frontStencilPassOp,
	D3D11_COMPARISON_FUNC frontStencilFunc, 
	D3D11_STENCIL_OP backStencilFailOp, 
	D3D11_STENCIL_OP backStencilDepthFailOp, 
	D3D11_STENCIL_OP backStencilPassOp, 
	D3D11_COMPARISON_FUNC backStencilFunc
)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = depthEnable;
	depthStencilDesc.DepthWriteMask = depthWriteMask;
	depthStencilDesc.DepthFunc = depthFunc;
	depthStencilDesc.StencilEnable = stencilEnable;
	depthStencilDesc.StencilReadMask = stencilReadMask;
	depthStencilDesc.StencilWriteMask = stencilWriteMask;
	depthStencilDesc.FrontFace.StencilFailOp = frontStencilFailOp;
	depthStencilDesc.FrontFace.StencilDepthFailOp = frontStencilDepthFailOp;
	depthStencilDesc.FrontFace.StencilPassOp = frontStencilPassOp;
	depthStencilDesc.FrontFace.StencilFunc = frontStencilFunc;
	depthStencilDesc.BackFace.StencilFailOp = backStencilFailOp;
	depthStencilDesc.BackFace.StencilDepthFailOp = backStencilDepthFailOp;
	depthStencilDesc.BackFace.StencilPassOp = backStencilPassOp;
	depthStencilDesc.BackFace.StencilFunc = backStencilFunc;

	HRESULT hResult = device->CreateDepthStencilState(&depthStencilDesc, m_depthStencilState.GetAddressOf());
	if (FAILED(hResult)) { throw exception("CreateDepthStencilState Failed"); }
}

void CDepthStencilState::InitializeDefaultDepthStencilState(ID3D11Device* device)
{
    
    CDepthStencilState tempDSSDraw(device, true, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS, false);
	CDepthStencilState tempDSSMasking(device, true, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS, true, 0xFF, 0xFF,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS
	);
	CDepthStencilState tempDSSConditionalDraw(device, true, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL, true, 0xFF, 0xFF,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_EQUAL,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS
	);

	gDSSDraw.Swap(tempDSSDraw.m_depthStencilState);
	gDSSMasking.Swap(tempDSSMasking.m_depthStencilState);
	gDSSConditionalDraw.Swap(tempDSSConditionalDraw.m_depthStencilState);
}
