#include "RTVOption.h"

using namespace D3D11;

void RTVOption::InitializeByOption(
    ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    ID3D11Resource* resource
)
{
	device->CreateRenderTargetView(resource, NULL, &m_rtv);
}

void RTVOption::Swap(RTVOption& rtvOptionIn)
{
	m_rtv.Swap(rtvOptionIn.m_rtv);
}
