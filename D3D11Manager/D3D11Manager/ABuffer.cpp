#include "ABuffer.h"

using namespace D3D11;

ABuffer::ABuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData) noexcept
	: m_elementSize(elementSize), m_arrayCount(arrayCount), m_cpuData(cpuData)
{
}

D3D11_SUBRESOURCE_DATA ABuffer::GetSubResourceData() const noexcept
{
	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(subresourceData));

	subresourceData.pSysMem = m_cpuData;
	return subresourceData;
}
