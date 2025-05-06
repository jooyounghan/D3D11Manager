#include "ABuffer.h"
#include "MacroUtilities.h"

using namespace std;
using namespace D3D11;

ABuffer::ABuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: m_elementSize(elementSize), m_arrayCount(arrayCount), m_cpuData(cpuData)
{
}

D3D11_SUBRESOURCE_DATA ABuffer::GetSubResourceData() const noexcept
{
	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMem(subresourceData);

	subresourceData.pSysMem = m_cpuData;
	return subresourceData;
}