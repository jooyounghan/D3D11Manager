#include "RasterizerState.h"
#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11RasterizerState> CRasterizerState::gRSSolidCWSS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSWireframeCWSS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSSolidCCWSS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSWireframeCCWSS;

ComPtr<ID3D11RasterizerState> CRasterizerState::gRSSolidCWMS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSWireframeCWMS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSSolidCCWMS;
ComPtr<ID3D11RasterizerState> CRasterizerState::gRSWireframeCCWMS;

CRasterizerState::CRasterizerState(
	ID3D11Device* device, 
	D3D11_FILL_MODE fillMode, 
	D3D11_CULL_MODE cullMode, 
	BOOL frontCounterClockwise, 
	BOOL multisampleEnable, 
	INT depthBias, 
	FLOAT depthBiasClamp, 
	FLOAT slopeScaledDepthBias, 
	BOOL depthClipEnable, 
	BOOL scissorEnable, 
	BOOL antialiasedLineEnable
)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

	rasterizerDesc.FillMode = fillMode;
	rasterizerDesc.CullMode = cullMode;
	rasterizerDesc.FrontCounterClockwise = frontCounterClockwise;
	rasterizerDesc.DepthBias = depthBias;
	rasterizerDesc.DepthBiasClamp = depthBiasClamp;
	rasterizerDesc.SlopeScaledDepthBias = slopeScaledDepthBias;
	rasterizerDesc.DepthClipEnable = depthClipEnable;
	rasterizerDesc.ScissorEnable = scissorEnable;
	rasterizerDesc.MultisampleEnable = multisampleEnable;
	rasterizerDesc.AntialiasedLineEnable = antialiasedLineEnable;

	HRESULT hResult = device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());
	if (FAILED(hResult)) { throw exception("CreateRasterizerState Failed"); }
}

void CRasterizerState::InitializeDefaultRasterizerStates(ID3D11Device* device)
{
	CRasterizerState tempSolidCWSS(device, D3D11_FILL_SOLID, D3D11_CULL_BACK, FALSE);
	CRasterizerState tempWireframeCWSS(device, D3D11_FILL_WIREFRAME, D3D11_CULL_BACK, FALSE);
	CRasterizerState tempSolidCCWSS(device, D3D11_FILL_SOLID, D3D11_CULL_BACK, TRUE);
	CRasterizerState tempWireframeCCWSS(device, D3D11_FILL_WIREFRAME, D3D11_CULL_BACK, TRUE);

	gRSSolidCWSS.Swap(tempSolidCWSS.m_rasterizerState);
	gRSWireframeCWSS.Swap(tempWireframeCWSS.m_rasterizerState);
	gRSSolidCCWSS.Swap(tempSolidCCWSS.m_rasterizerState);
	gRSWireframeCCWSS.Swap(tempWireframeCCWSS.m_rasterizerState);

	CRasterizerState tempSolidCWMS(device, D3D11_FILL_SOLID, D3D11_CULL_BACK, FALSE, TRUE);
	CRasterizerState tempWireframeCWMS(device, D3D11_FILL_WIREFRAME, D3D11_CULL_BACK, FALSE, TRUE);
	CRasterizerState tempSolidCCWMS(device, D3D11_FILL_SOLID, D3D11_CULL_BACK, TRUE, TRUE);
	CRasterizerState tempWireframeCCWMS(device, D3D11_FILL_WIREFRAME, D3D11_CULL_BACK, TRUE, TRUE);

	gRSSolidCWMS.Swap(tempSolidCWMS.m_rasterizerState);
	gRSWireframeCWMS.Swap(tempWireframeCWMS.m_rasterizerState);
	gRSSolidCCWMS.Swap(tempSolidCCWMS.m_rasterizerState);
	gRSWireframeCCWMS.Swap(tempWireframeCCWMS.m_rasterizerState);
}
