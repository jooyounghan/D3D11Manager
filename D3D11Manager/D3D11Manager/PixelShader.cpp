#include "PixelShader.h"

#include <vector>

using namespace std;
using namespace D3D11;

void CPixelShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreatePixelShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_pixelShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreatePixelShader Failed");
}

void CPixelShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->PSSetShader(m_pixelShader.Get(), NULL, NULL);
}

void CPixelShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->PSSetShader(nullptr, NULL, NULL);
}

void CPixelShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	ID3D11SamplerState* const* samplerStates,
	UINT samplerStatesCount
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates, samplerStatesCount);
	deviceContext->PSSetSamplers(0, samplerStatesCount, samplerStates);
}

void CPixelShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->PSSetSamplers(0, m_samplerStateCount, resetSamplerState.data());
}
