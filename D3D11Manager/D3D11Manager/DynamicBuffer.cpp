#include "DynamicBuffer.h"
#include "MacroUtilities.h"

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
	ZeroMem(bufferDesc);

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
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();
	D3D11_BUFFER_DESC bufferDesc = CreateBufferDesc();
	HRESULT hResult = m_cpuData ?
		device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf()) :
		device->CreateBuffer(&bufferDesc, nullptr, m_buffer.GetAddressOf());

	if (FAILED(hResult)) throw exception("CreateBuffer With InitializeBuffer Failed");

	ZeroMem(bufferDesc);

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_STAGING;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = m_elementSize;

	if (m_cpuData)
	{
		hResult = device->CreateBuffer(&bufferDesc, &initialData, m_stagingBuffer.GetAddressOf());
		if (FAILED(hResult)) throw exception("CreateBuffer For StagingBuffer Failed");
	}
}

void CDynamicBuffer::Stage(ID3D11DeviceContext* const deviceContext)
{
	if (m_cpuData)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMem(mappedResource);

		HRESULT hResult = deviceContext->Map(m_stagingBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedResource);
		if (FAILED(hResult)) { throw exception("Map For Staging Buffer Failed"); }

		memcpy(mappedResource.pData, m_cpuData, static_cast<size_t>(m_elementSize) * m_arrayCount);
		deviceContext->Unmap(m_stagingBuffer.Get(), 0);
	}
	else
	{
		throw exception("CPU Data is Not Link For Staging");
	}
}

void CDynamicBuffer::Upload(ID3D11DeviceContext* const deviceContext) noexcept
{
	deviceContext->CopyResource(m_buffer.Get(), m_stagingBuffer.Get());
}


void CDynamicBuffer::StageNthElement(
	ID3D11DeviceContext* const deviceContext,
	UINT* elementIndices,
	UINT elementIndicesCount
)
{
	if (m_cpuData)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMem(mappedResource);

		HRESULT hResult = deviceContext->Map(m_stagingBuffer.Get(), 0, D3D11_MAP_WRITE, 0, &mappedResource);
		if (FAILED(hResult)) { throw exception("Map For Staging Buffer Failed"); }

		uint8_t* mapped = reinterpret_cast<uint8_t*>(mappedResource.pData);
		const uint8_t* source = reinterpret_cast<const uint8_t*>(m_cpuData);

		for (UINT idx = 0; idx < elementIndicesCount; ++idx)
		{
			UINT index = elementIndices[idx];
			if (index < m_arrayCount)
			{
				memcpy(
					mapped + m_elementSize * index,
					source + m_elementSize * index,
					m_elementSize
				);
			}
			else
			{
				throw exception("Element Indice Exceed Array Count");
			}
		}
		deviceContext->Unmap(m_stagingBuffer.Get(), 0);
	}
	else
	{
		throw exception("CPU Data is Not Link For Staging");
	}
}

void CDynamicBuffer::UploadNthElement(
	ID3D11DeviceContext* const deviceContext,
	UINT* elementIndices,
	UINT elementIndicesCount
)
{
	for (UINT idx = 0; idx < elementIndicesCount; ++idx)
	{
		UINT index = elementIndices[idx];

		if (index < m_arrayCount)
		{
			D3D11_BOX box = {};
			box.left = m_elementSize * index;
			box.right = box.left + m_elementSize;
			box.top = 0;
			box.bottom = 1;
			box.front = 0;
			box.back = 1;

			deviceContext->CopySubresourceRegion(
				m_buffer.Get(), 0, m_elementSize * index, 0, 0,
				m_stagingBuffer.Get(), 0, &box
			);
		}
		else
		{
			throw exception("Element Indice Exceed Array Count");
		}
	}
}
