#include "GeometryShader.h"

using namespace std;
using namespace D3D11;

void GeometryShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateGeometryShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_geometryShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateGeometryShader Failed");
}

void GeometryShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->GSSetShader(m_geometryShader.Get(), NULL, NULL);
}

void GeometryShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->GSSetShader(nullptr, NULL, NULL);
}

void GeometryShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->GSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());
}

void GeometryShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->GSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
