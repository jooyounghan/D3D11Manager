#pragma once

#ifndef TEXTUREUTILITIES_H
#define TEXTUREUTILITIES_H

#include "D3D11DllHelper.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

namespace D3D11
{
	class D3D11MANAGER_API TextureUtilities
	{
	public:
		static void CreateTexture2D(
			UINT width,
			UINT height,
			UINT arraySize,
			UINT mipLevels,
			UINT cpuAccessFlag,
			UINT miscFlagIn,
			D3D11_USAGE usage,
			DXGI_FORMAT format,
			UINT bindFlag,
			ID3D11Device* device,
			D3D11_TEXTURE2D_DESC* texture2DDesc,
			ID3D11Texture2D** texture2DAddress
		);

		static void UpdateTexture2D(
			const std::vector<std::vector<UINT8>>& textureDataPerArray,
			const std::vector<UINT>& textureRowPitchPerArray,
			UINT mipLevels,
			ID3D11DeviceContext* deviceContext,
			ID3D11Texture2D* texture2D
		) noexcept;

		static void CreateShaderResourceView(
			ID3D11Device* device,
			ID3D11DeviceContext* deviceContext,
			ID3D11Resource* resource,
			ID3D11ShaderResourceView** srv
		);

		static void CreateDepthStencilView(
			ID3D11Device* device,
			ID3D11Resource* resource,
			ID3D11DepthStencilView** dsv
		);

		static void CreateUnorderedAccessView(
			ID3D11Device* device,
			ID3D11Resource* resource,
			ID3D11UnorderedAccessView** uav
		);

	private:
		static D3D11_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc(
			const D3D11_TEXTURE2D_DESC& texture2dDesc
		) noexcept;
		static DXGI_FORMAT GetShaderResourceViewFormatFromTextureFormat(
			DXGI_FORMAT textureFormat
		) noexcept;
		static D3D11_DEPTH_STENCIL_VIEW_DESC GetDepthStencilViewDesc(
			const D3D11_TEXTURE2D_DESC& texture2dDesc
		) noexcept;
		static DXGI_FORMAT GetDepthStencilViewFormatFromTextureFormat(
			DXGI_FORMAT textureFormat
		) noexcept;
		static D3D11_UNORDERED_ACCESS_VIEW_DESC GetUnorderedAccessViewDesc(
			const D3D11_TEXTURE2D_DESC& texture2dDesc
		);
		static DXGI_FORMAT GetUnorderedAccessViewFormatFromTextureFormat(
			DXGI_FORMAT textureFormat
		) noexcept;
	};
}

#endif
