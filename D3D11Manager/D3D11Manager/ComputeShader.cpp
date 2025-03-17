#include "ComputeShader.h"

using namespace std;
using namespace D3D11;

void ComputeShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateComputeShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_computeShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateComputeShader Failed");
}

void ComputeShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->CSSetShader(m_computeShader.Get(), NULL, NULL);
}

void ComputeShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->CSSetShader(nullptr, NULL, NULL);
}

void ComputeShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->CSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());
}

void ComputeShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->CSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
