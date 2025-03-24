#include "IndirectBuffer.h"

using namespace std;
using namespace D3D11;

IndirectBuffer::IndirectBuffer(UINT arrayCount, const D3D11_DRAW_INSTANCED_INDIRECT_ARGS* cpuData)
	: ABuffer(sizeof(D3D11_DRAW_INSTANCED_INDIRECT_ARGS), arrayCount, cpuData)
{
}

D3D11_BUFFER_DESC IndirectBuffer::CreateBufferDesc() noexcept
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
	return bufferDesc;
}

D3D11_UNORDERED_ACCESS_VIEW_DESC D3D11::IndirectBuffer::CreateUnorderedAccessViewDesc() noexcept
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));

	uavDesc.Format = DXGI_FORMAT_R32_UINT;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = 4;
	return uavDesc;
}

void D3D11::IndirectBuffer::InitializeBuffer(ID3D11Device* const device)
{
	ABuffer::InitializeBuffer(device);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = CreateUnorderedAccessViewDesc();
	HRESULT hResult = device->CreateUnorderedAccessView(m_buffer.Get(), &uavDesc, m_indirectUAV.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateUnorderedAccessView For InitializeBuffer Failed");
}
