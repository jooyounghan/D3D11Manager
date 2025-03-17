#include "VertexShader.h"

using namespace std;
using namespace D3D11;

CVertexShader::CVertexShader(const size_t& inputLayoutCount)
	: m_inputLayoutCount(inputLayoutCount)
{
	m_inputElementDescs = new D3D11_INPUT_ELEMENT_DESC[m_inputLayoutCount];
}

CVertexShader::~CVertexShader()
{
	delete[] m_inputElementDescs;
}

void CVertexShader::CreateShaderImpl(ID3D11Device* device)
{
	HRESULT hResult = device->CreateVertexShader(
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		NULL, m_vertexShader.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateVertexShader Failed");

	hResult = device->CreateInputLayout(
		m_inputElementDescs, static_cast<UINT>(m_inputLayoutCount),
		m_shaderByteCode->GetBufferPointer(),
		m_shaderByteCode->GetBufferSize(),
		m_inputLayout.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("CreateInputLayout Failed");
}

void D3D11::CVertexShader::AddInputLayoutElement(const D3D11_INPUT_ELEMENT_DESC& inputElementDesc)
{
	if (m_currentLayoutCount >= m_inputLayoutCount) throw exception("Can't Add D3D11_INPUT_ELEMENT_DESC Because Of The Total Count");
	m_inputElementDescs[m_currentLayoutCount] = inputElementDesc;
}

void CVertexShader::SetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->VSSetShader(m_vertexShader.Get(), NULL, NULL);
}

void CVertexShader::ResetShader(ID3D11DeviceContext* deviceContext) const noexcept
{
	deviceContext->VSSetShader(nullptr, NULL, NULL);
}

void CVertexShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	const vector<ID3D11SamplerState*>& samplerStates
) noexcept
{
	AShader::SetSamplerState(deviceContext, samplerStates);
	deviceContext->VSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());

}

void CVertexShader::ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept
{
	vector<ID3D11SamplerState*> resetSamplerState;
	resetSamplerState.resize(m_samplerStateCount, nullptr);
	deviceContext->VSSetSamplers(0, static_cast<UINT>(m_samplerStateCount), resetSamplerState.data());
}
