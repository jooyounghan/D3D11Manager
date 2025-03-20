#include "SamplerState.h"
#include <exception>

using namespace std;
using namespace D3D11;
using namespace Microsoft::WRL;

ComPtr<ID3D11SamplerState> SamplerState::gSSWrap;
ComPtr<ID3D11SamplerState> SamplerState::gSSClamp;
ComPtr<ID3D11SamplerState> SamplerState::gSSWrapLess;
ComPtr<ID3D11SamplerState> SamplerState::gSSClampLess;

SamplerState::SamplerState(
	ID3D11Device* device, 
	D3D11_FILTER filter, 
	D3D11_TEXTURE_ADDRESS_MODE addressU, 
	D3D11_TEXTURE_ADDRESS_MODE addressV, 
	D3D11_TEXTURE_ADDRESS_MODE addressW, 
	FLOAT mipLODBias, 
	UINT maxAnisotropy, 
	D3D11_COMPARISON_FUNC comparisonFunc, 
	const FLOAT* borderColor, 
	FLOAT minLOD, 
	FLOAT maxLOD
)
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));

	samplerDesc.Filter = filter;
	samplerDesc.AddressU = addressU;
	samplerDesc.AddressV = addressV;
	samplerDesc.AddressW = addressW;
	samplerDesc.MipLODBias = mipLODBias;
	samplerDesc.MaxAnisotropy = maxAnisotropy;
	samplerDesc.ComparisonFunc = comparisonFunc;
	const float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (!borderColor) borderColor = defaultColor;
	samplerDesc.BorderColor[0] = borderColor[0];
	samplerDesc.BorderColor[1] = borderColor[1];
	samplerDesc.BorderColor[2] = borderColor[2];
	samplerDesc.BorderColor[3] = borderColor[3];
	samplerDesc.MinLOD = minLOD;
	samplerDesc.MaxLOD = maxLOD;

	HRESULT hResult = device->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
	if (FAILED(hResult)) { throw exception("CreateSamplerState Failed"); }

}

void SamplerState::InitializeSamplerState(ID3D11Device* device)
{
	SamplerState tempSSWrap(device, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_COMPARISON_NEVER);
	SamplerState tempSSClamp(device, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_NEVER);
	SamplerState tempSSWrapLess(device, D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_COMPARISON_LESS);
	SamplerState tempSSClampLess(device, D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_LESS);

	gSSWrap.Swap(tempSSWrap.m_samplerState);
	gSSClamp.Swap(tempSSClamp.m_samplerState);
	gSSWrapLess.Swap(tempSSWrapLess.m_samplerState);
	gSSClampLess.Swap(tempSSClampLess.m_samplerState);
}
