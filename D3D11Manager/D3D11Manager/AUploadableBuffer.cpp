#include "AUploadableBuffer.h"

#include <exception>

using namespace std;
using namespace D3D11;

AUploadableBuffer::AUploadableBuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData)
	: ABuffer(elementSize, arrayCount, cpuData)
{
}

void D3D11::AUploadableBuffer::InitializeBuffer(ID3D11Device* const device)
{
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_STAGING;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = m_elementSize;

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_stagingBuffer.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateBuffer For StagingBuffer Failed");

}

void D3D11::AUploadableBuffer::Stage(ID3D11DeviceContext* const deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));

	HRESULT hResult = deviceContext->Map(m_stagingBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedResource);
	if (FAILED(hResult)) { throw exception("Map For Staging Buffer Failed"); }

	memcpy(mappedResource.pData, m_cpuData, m_elementSize * m_arrayCount);
	deviceContext->Unmap(m_stagingBuffer.Get(), 0);
}

void AUploadableBuffer::Upload(ID3D11DeviceContext* const deviceContext) noexcept
{
	deviceContext->CopyResource(m_buffer.Get(), m_stagingBuffer.Get());
}
