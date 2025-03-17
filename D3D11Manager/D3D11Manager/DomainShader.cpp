#include "DomainShader.h"

using namespace std;
using namespace D3D11;

void DomainShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateDomainShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_domainShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateDomainShader Failed");
}

void DomainShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->DSSetShader(m_domainShader.Get(), NULL, NULL);
}

void DomainShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->DSSetShader(nullptr, NULL, NULL);
}

void DomainShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->DSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());
}

void DomainShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->DSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
