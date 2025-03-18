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

void D3D11::ABuffer::InitializeBuffer(ID3D11Device* const device)
{
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();
	D3D11_BUFFER_DESC bufferDesc = CreateBufferDesc();

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateBuffer With InitializeBuffer Failed");
}
