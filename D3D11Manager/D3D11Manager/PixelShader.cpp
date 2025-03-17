#include "PixelShader.h"

using namespace std;
using namespace D3D11;

void PixelShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreatePixelShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_pixelShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreatePixelShader Failed");
}

void PixelShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->PSSetShader(m_pixelShader.Get(), NULL, NULL);
}

void PixelShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->PSSetShader(nullptr, NULL, NULL);
}

void PixelShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->PSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());
}

void PixelShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->PSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
