#include "TextureUtilities.h"

#include <unordered_map>
#include <exception>

using namespace std;
using namespace D3D11;

void TextureUtilities::CreateTexture2D(
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
)
{
	ZeroMemory(texture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
	texture2DDesc->Width = width;
	texture2DDesc->Height = height;
	texture2DDesc->ArraySize = arraySize;
	texture2DDesc->MipLevels = mipLevels;
	texture2DDesc->BindFlags = bindFlag;
	texture2DDesc->CPUAccessFlags = cpuAccessFlag;
	texture2DDesc->MiscFlags = miscFlagIn;
	texture2DDesc->SampleDesc.Count = 1;
	texture2DDesc->SampleDesc.Quality = 0;
	texture2DDesc->Usage = usage;
	texture2DDesc->Format = format;

	HRESULT hResult = device->CreateTexture2D(texture2DDesc, NULL, texture2DAddress);
	if (FAILED(hResult)) throw exception("CreateTexture2D Failed");
}

void TextureUtilities::UpdateTexture2D(
	const vector<vector<UINT8>>& textureDataPerArray, 
	const vector<UINT>& textureRowPitchPerArray, 
	UINT mipLevels,
	ID3D11DeviceContext* deviceContext, 
	ID3D11Texture2D* texture2D
) noexcept
{
	for (size_t arrayIdx = 0; arrayIdx < textureDataPerArray.size(); ++arrayIdx)
	{
		const uint8_t* imageBuffer = textureDataPerArray[arrayIdx].data();
		deviceContext->UpdateSubresource(
			texture2D, D3D11CalcSubresource(0, static_cast<UINT>(arrayIdx), mipLevels),
			nullptr, imageBuffer, textureRowPitchPerArray[arrayIdx], NULL
		);
	}
}

void TextureUtilities::CreateShaderResourceView(
	ID3D11Device* device, 
	ID3D11DeviceContext* deviceContext, 
	ID3D11Resource* resource, 
	ID3D11ShaderResourceView** srv
)
{
	ID3D11Texture2D* texture2D = nullptr;
	HRESULT hResult = resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture2D));
	if (FAILED(hResult)) throw exception("QueryInterface ID3D11Texture2D Failed");

	D3D11_TEXTURE2D_DESC texture2DDesc;
	texture2D->GetDesc(&texture2DDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = GetShaderResourceViewDesc(texture2DDesc);
	hResult = device->CreateShaderResourceView(resource, &srvDesc, srv);
	if (FAILED(hResult)) throw exception("CreateShaderResourceView Failed");

	if (texture2DDesc.MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS)
	{
		deviceContext->GenerateMips(*srv);
	}
	texture2D->Release();
}

void D3D11::TextureUtilities::CreateDepthStencilView(
	ID3D11Device* device, 
	ID3D11Resource* resource,
	ID3D11DepthStencilView** dsv
)
{
	ID3D11Texture2D* texture2D = nullptr;
	HRESULT hResult = resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture2D));
	if (FAILED(hResult)) throw exception("CreateTexture2D Failed");

	D3D11_TEXTURE2D_DESC texture2DDesc;
	texture2D->GetDesc(&texture2DDesc);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = GetDepthStencilViewDesc(texture2DDesc);
	hResult = device->CreateDepthStencilView(resource, &dsvDesc, dsv);
	if (FAILED(hResult)) throw exception("CreateDepthStencilView Failed");

	texture2D->Release();
}

void D3D11::TextureUtilities::CreateUnorderedAccessView(
	ID3D11Device* device, 
	ID3D11Resource* resource, 
	ID3D11UnorderedAccessView** uav
)
{
	ID3D11Texture2D* texture2D = nullptr;
	HRESULT hResult = resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture2D));
	if (FAILED(hResult)) throw exception("CreateTexture2D Failed");

	D3D11_TEXTURE2D_DESC texture2DDesc;
	texture2D->GetDesc(&texture2DDesc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = GetUnorderedAccessViewDesc(texture2DDesc);
	hResult = device->CreateUnorderedAccessView(resource, &uavDesc, uav);
	if (FAILED(hResult)) throw exception("CreateUnorderedAccessView Failed");

	texture2D->Release();
}

D3D11_SHADER_RESOURCE_VIEW_DESC TextureUtilities::GetShaderResourceViewDesc(const D3D11_TEXTURE2D_DESC& texture2dDesc) noexcept
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = GetShaderResourceViewFormatFromTextureFormat(texture2dDesc.Format);

	if (texture2dDesc.SampleDesc.Count == 1)
	{
		if (texture2dDesc.ArraySize > 1)
		{
			if (texture2dDesc.MiscFlags & D3D11_RESOURCE_MISC_TEXTURECUBE)
			{
				if (texture2dDesc.ArraySize == 6)
				{
					srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
					srvDesc.Texture2DArray.ArraySize = texture2dDesc.ArraySize;
				}
				else
				{
					srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
					srvDesc.Texture2DArray.ArraySize = texture2dDesc.ArraySize / 6;
				}
			}
			else
			{
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				srvDesc.Texture2DArray.ArraySize = texture2dDesc.ArraySize;
			}
			srvDesc.Texture2DArray.MostDetailedMip = 0;
			srvDesc.Texture2DArray.MipLevels = texture2dDesc.MipLevels;
			srvDesc.Texture2DArray.FirstArraySlice = 0;
		}
		else
		{
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = texture2dDesc.MipLevels;
		}
	}
	else
	{
		if (texture2dDesc.ArraySize > 1)
		{
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
			srvDesc.Texture2DMSArray.FirstArraySlice = 0;
			srvDesc.Texture2DMSArray.ArraySize = texture2dDesc.ArraySize;
		}
		else
		{
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
	}
	return srvDesc;

}

DXGI_FORMAT TextureUtilities::GetShaderResourceViewFormatFromTextureFormat(DXGI_FORMAT textureFormat) noexcept
{
	static unordered_map<DXGI_FORMAT, DXGI_FORMAT> textureFormatToSRVFormat
	{
		{ DXGI_FORMAT_R32_TYPELESS, DXGI_FORMAT_R32_FLOAT },
		{ DXGI_FORMAT_R24G8_TYPELESS, DXGI_FORMAT_R24_UNORM_X8_TYPELESS }
	};

	if (textureFormatToSRVFormat.find(textureFormat) != textureFormatToSRVFormat.end())
	{
		return textureFormatToSRVFormat[textureFormat];
	}
	return textureFormat;
}

D3D11_DEPTH_STENCIL_VIEW_DESC TextureUtilities::GetDepthStencilViewDesc(const D3D11_TEXTURE2D_DESC& texture2dDesc) noexcept
{
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	dsvDesc.Format = GetDepthStencilViewFormatFromTextureFormat(texture2dDesc.Format);

	if (texture2dDesc.SampleDesc.Count == 1)
	{
		if (texture2dDesc.ArraySize > 1)
		{
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			dsvDesc.Texture2DArray.MipSlice = 0;
			dsvDesc.Texture2DArray.FirstArraySlice = 0;
			dsvDesc.Texture2DArray.ArraySize = texture2dDesc.ArraySize;
		}
		else
		{
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Texture2D.MipSlice = 0;
		}
	}
	else
	{
		if (texture2dDesc.ArraySize > 1)
		{
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
			dsvDesc.Texture2DMSArray.FirstArraySlice = 0;
			dsvDesc.Texture2DMSArray.ArraySize = texture2dDesc.ArraySize;
		}
		else
		{
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
	}
	return dsvDesc;
}

DXGI_FORMAT TextureUtilities::GetDepthStencilViewFormatFromTextureFormat(DXGI_FORMAT textureFormat) noexcept
{
	static unordered_map<DXGI_FORMAT, DXGI_FORMAT> textureFormatToDSVFormat{
		{ DXGI_FORMAT_R32_TYPELESS, DXGI_FORMAT_D32_FLOAT },
		{ DXGI_FORMAT_R24G8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT}
	};

	if (textureFormatToDSVFormat.find(textureFormat) != textureFormatToDSVFormat.end())
	{
		return textureFormatToDSVFormat[textureFormat];
	}
	return textureFormat;
}

D3D11_UNORDERED_ACCESS_VIEW_DESC TextureUtilities::GetUnorderedAccessViewDesc(const D3D11_TEXTURE2D_DESC& texture2dDesc)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));

	uavDesc.Format = GetUnorderedAccessViewFormatFromTextureFormat(texture2dDesc.Format);

	if (texture2dDesc.SampleDesc.Count == 1)
	{
		if (texture2dDesc.ArraySize > 1)
		{
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			uavDesc.Texture2DArray.MipSlice = 0;
			uavDesc.Texture2DArray.FirstArraySlice = 0;
			uavDesc.Texture2DArray.ArraySize = texture2dDesc.ArraySize;
		}
		else
		{
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavDesc.Texture2D.MipSlice = 0;
		}
	}
	else
	{
		throw exception("MultiSampled Texture Is Not Available");
	}
	return uavDesc;
}

DXGI_FORMAT TextureUtilities::GetUnorderedAccessViewFormatFromTextureFormat(DXGI_FORMAT textureFormat) noexcept
{
	return textureFormat;
}
