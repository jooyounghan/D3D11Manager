#include "StructuredBuffer.h"
#include <exception>

using namespace std;
using namespace D3D11;

CStructuredBuffer::CStructuredBuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData)
	: AUploadableBuffer(elementSize, arrayCount, cpuData)
{
}

void CStructuredBuffer::InitializeBuffer(ID3D11Device* const device)
{
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = m_elementSize;
	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateBuffer For StructuredBuffer Failed");


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.BufferEx.NumElements = m_arrayCount;
	hResult = device->CreateShaderResourceView(m_buffer.Get(), &srvDesc, m_structuredSRV.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateShaderResourceView For StructuredBuffer Failed");
}
