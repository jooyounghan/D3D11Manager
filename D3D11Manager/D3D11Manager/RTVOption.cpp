#include "RTVOption.h"
#include "MacroUtilities.h"

#include <unordered_map>

using namespace std;
using namespace D3D11;

void RTVOption::InitializeByOption(
    ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    ID3D11Resource* resource
)
{
	ID3D11Texture2D* texture2D = nullptr;
	HRESULT hr = resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texture2D));

	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC texture2DDesc;
		texture2D->GetDesc(&texture2DDesc);
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = GetRenderTargetViewDesc(texture2DDesc);
		device->CreateRenderTargetView(resource, &rtvDesc, &m_rtv);
		texture2D->Release();
	}

}

void RTVOption::Swap(RTVOption& rtvOptionIn)
{
	m_rtv.Swap(rtvOptionIn.m_rtv);
}

D3D11_RENDER_TARGET_VIEW_DESC D3D11::RTVOption::GetRenderTargetViewDesc(const D3D11_TEXTURE2D_DESC& texture2dDesc)
{
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
    ZeroMem(rtvDesc);
    rtvDesc.Format = GetRenderTargetViewFormatFromTextureFormat(texture2dDesc.Format);
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    return rtvDesc;
}

DXGI_FORMAT RTVOption::GetRenderTargetViewFormatFromTextureFormat(const DXGI_FORMAT& textureFormat)
{
	static unordered_map<DXGI_FORMAT, DXGI_FORMAT> textureFormatToRTVFormat{
		{ DXGI_FORMAT_R32_TYPELESS, DXGI_FORMAT_R32_FLOAT },
	};

	if (textureFormatToRTVFormat.find(textureFormat) != textureFormatToRTVFormat.end())
	{
		return textureFormatToRTVFormat[textureFormat];
	}
	return textureFormat;
}
