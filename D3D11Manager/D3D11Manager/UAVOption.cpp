#include "UAVOption.h"

using namespace D3D11;

void UAVOption::InitializeByOption(
	ID3D11Device* device, 
	ID3D11DeviceContext* deviceContext,
	ID3D11Resource* resource
)
{
	device->CreateUnorderedAccessView(resource, NULL, &m_uav);
}

void UAVOption::Swap(UAVOption& uavOptionIn)
{
	m_uav.Swap(uavOptionIn.m_uav);
}
