#pragma once

#ifndef ASHADER_H
#define ASHADER_H

#include "D3D11DllHelper.h"

#include <vector>
#include <string>
#include <exception>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#if defined(_DEBUG)
constexpr UINT ShaderCompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
constexpr UINT ShaderCompileFlag = NULL;
#endif

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3DBlob>;

namespace D3D11
{
	class D3D11MANAGER_API AShader
	{
	public:
		AShader() = default;
		virtual ~AShader() = default;

	public:
		void CreateShader(
			const std::wstring& shaderPath,
			const std::string& entryPoint,
			const std::string& targetVersion,
			ID3D11Device* device
		);

	protected:
		virtual void CreateShaderImpl(ID3D11Device* device) = 0;

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> m_shaderByteCode;
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorByteCode;

	protected:
		size_t m_samplerStateCount = 0;

	public:
		virtual void SetShader(ID3D11DeviceContext* deviceContext) const noexcept = 0;
		virtual void ResetShader(ID3D11DeviceContext* deviceContext) const noexcept = 0;
		virtual void SetSamplerState(
			ID3D11DeviceContext* deviceContext,
			const std::vector<ID3D11SamplerState*>& samplerStates
		) noexcept;
		virtual void ResetSamplerState(ID3D11DeviceContext* deviceContext) const noexcept = 0;
	};
}
#endif