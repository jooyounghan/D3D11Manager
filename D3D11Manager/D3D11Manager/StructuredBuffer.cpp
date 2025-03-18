#include "StructuredBuffer.h"

using namespace std;
using namespace D3D11;

CStructuredBuffer::CStructuredBuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: AUploadableBuffer(elementSize, arrayCount, cpuData)
{
}

D3D11_BUFFER_DESC D3D11::CStructuredBuffer::CreateBufferDesc() noexcept
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = m_elementSize;

	return bufferDesc;
}

D3D11_SHADER_RESOURCE_VIEW_DESC CStructuredBuffer::CreateShaderResourceViewDesc() noexcept
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.BufferEx.NumElements = m_arrayCount;
	return srvDesc;
}

D3D11_UNORDERED_ACCESS_VIEW_DESC CStructuredBuffer::CreateUnorderedAccessViewDesc() noexcept
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));

	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = m_arrayCount;
	return uavDesc;
}

void CStructuredBuffer::InitializeBuffer(ID3D11Device* const device)
{
	AUploadableBuffer::InitializeBuffer(device);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = CreateShaderResourceViewDesc();
	HRESULT hResult = device->CreateShaderResourceView(m_buffer.Get(), &srvDesc, m_structuredSRV.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateShaderResourceView For InitializeBuffer Failed");

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = CreateUnorderedAccessViewDesc();
	hResult = device->CreateUnorderedAccessView(m_buffer.Get(), &uavDesc, m_structuredUAV.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateUnorderedAccessView For InitializeBuffer Failed");
}
