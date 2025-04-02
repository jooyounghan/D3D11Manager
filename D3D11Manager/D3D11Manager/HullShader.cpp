#include "HullShader.h"

#include <vector>

using namespace std;
using namespace D3D11;

void CHullShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateHullShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_hullShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateHullShader Failed");
}

void CHullShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->HSSetShader(m_hullShader.Get(), NULL, NULL);
}

void CHullShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->HSSetShader(nullptr, NULL, NULL);
}

void CHullShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	ID3D11SamplerState* const* samplerStates,
	UINT samplerStatesCount
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates, samplerStatesCount);
	deviceContext->HSSetSamplers(0, samplerStatesCount, samplerStates);
}

void CHullShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->HSSetSamplers(0, m_samplerStateCount, resetSamplerState.data());
}
