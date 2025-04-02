#include "AShader.h"

#include <vector>

using namespace std;
using namespace D3D11;

void AShader::CreateShader(
	const wstring& shaderPath, 
	const string& entryPoint, 
	const string& targetVersion, 
	ID3D11Device* device
)
{
	HRESULT hResult = D3DCompileFromFile(
		shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint.c_str(), targetVersion.c_str(), ShaderCompileFlag, 0,
		m_shaderByteCode.GetAddressOf(), m_errorByteCode.GetAddressOf()
	);
	if (FAILED(hResult)) throw exception("D3DCompileFromFile Failed");

	CreateShaderImpl(device);

	m_shaderByteCode.Reset();
	m_errorByteCode.Reset();
}

void D3D11::AShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext, 
	ID3D11SamplerState* const* samplerStates,
	UINT samplerStatesCount
) noexcept
{
	m_samplerStateCount = samplerStatesCount;
}
