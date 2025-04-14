#include "DynamicBuffer.h"

using namespace std;
using namespace D3D11;

CDynamicBuffer::CDynamicBuffer(
	UINT elementSize, 
	UINT arrayCount, 
	const void* cpuData, 
	UINT bindFlag 
)
	: ABuffer(elementSize, arrayCount, cpuData), m_bindFlag(bindFlag)
{
}

D3D11_BUFFER_DESC CDynamicBuffer::CreateBufferDesc() noexcept
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = m_bindFlag;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = m_elementSize;

	return bufferDesc;
}

void CDynamicBuffer::InitializeBuffer(ID3D11Device* const device)
{
	if (m_cpuData)
	{
		D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();
		D3D11_BUFFER_DESC bufferDesc = CreateBufferDesc();

		HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
		if (FAILED(hResult)) throw exception("CreateBuffer With InitializeBuffer Failed");

		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		bufferDesc.MiscFlags = NULL;
		bufferDesc.StructureByteStride = m_elementSize;

		hResult = device->CreateBuffer(&bufferDesc, &initialData, m_stagingBuffer.GetAddressOf());
		if (FAILED(hResult)) throw exception("CreateBuffer For StagingBuffer Failed");
	}
	else
	{
		throw exception("CPU Data Link For DynamicBuffer Failed");
	}
}

void CDynamicBuffer::Stage(ID3D11DeviceContext* const deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));

	HRESULT hResult = deviceContext->Map(m_stagingBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedResource);
	if (FAILED(hResult)) { throw exception("Map For Staging Buffer Failed"); }

	memcpy(mappedResource.pData, m_cpuData, static_cast<size_t>(m_elementSize) * m_arrayCount);
	deviceContext->Unmap(m_stagingBuffer.Get(), 0);
}

void CDynamicBuffer::Upload(ID3D11DeviceContext* const deviceContext) noexcept
{
	deviceContext->CopyResource(m_buffer.Get(), m_stagingBuffer.Get());
}
