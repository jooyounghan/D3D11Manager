#include "ABuffer.h"

using namespace std;
using namespace D3D11;

ABuffer::ABuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: m_elementSize(elementSize), m_arrayCount(arrayCount), m_cpuData(cpuData)
{
	if ((elementSize * arrayCount) % 16) throw exception("The GPU buffer must be aligned to 16bytes.");
}

D3D11_SUBRESOURCE_DATA ABuffer::GetSubResourceData() const noexcept
{
	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(subresourceData));

	subresourceData.pSysMem = m_cpuData;
	return subresourceData;
}