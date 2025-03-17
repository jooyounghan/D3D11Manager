#include "VertexShader.h"

using namespace std;
using namespace D3D11;

void VertexShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateVertexShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_vertexShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateVertexShader Failed");
}

void VertexShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->VSSetShader(m_vertexShader.Get(), NULL, NULL);
}

void VertexShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->VSSetShader(nullptr, NULL, NULL);
}

void VertexShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->VSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());

}

void VertexShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->VSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
