#include "AUploadableBuffer.h"

#include <exception>

using namespace std;
using namespace D3D11;

AUploadableBuffer::AUploadableBuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData) noexcept
	: ABuffer(elementSize, arrayCount, cpuData)
{
}

void AUploadableBuffer::Upload(ID3D11DeviceContext* const deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));

	HRESULT hResult = deviceContext->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hResult)) { throw exception("Map For Uploading Buffer Failed"); }

	memcpy(mappedResource.pData, m_cpuData, m_elementSize * m_arrayCount);
	deviceContext->Unmap(m_buffer.Get(), 0);
}
