#include "DynamicBuffer.h"
#include <exception>

using namespace std;
using namespace D3D11;

CDynamicBuffer::CDynamicBuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData)
	: AUploadableBuffer(elementSize, arrayCount, cpuData)
{
}

void CDynamicBuffer::InitializeBuffer(ID3D11Device* const device)
{
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = 0;

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateBuffer For DynamicBuffer Failed");
}
