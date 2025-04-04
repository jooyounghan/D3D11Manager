#include "ConstantBuffer.h"

using namespace std;
using namespace D3D11;

CConstantBuffer::CConstantBuffer(
	UINT elementSize, UINT arrayCount,
	const void* cpuData,
	D3D11_BIND_FLAG bindFlag,
	D3D11_USAGE usage
)
	: ABuffer(elementSize, arrayCount, cpuData), m_bindFlag(bindFlag), m_usage(usage)
{

}
D3D11_BUFFER_DESC D3D11::CConstantBuffer::CreateBufferDesc() noexcept
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = m_usage;
	bufferDesc.BindFlags = m_bindFlag;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = 0;
	return bufferDesc;
}

void CConstantBuffer::InitializeBuffer(ID3D11Device* const device)
{
	if (m_cpuData)
	{
		D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();
		D3D11_BUFFER_DESC bufferDesc = CreateBufferDesc();

		HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
		if (FAILED(hResult)) throw exception("CreateBuffer With InitializeBuffer Failed");
	}
	else
	{
		throw exception("CPU Data Link For ConstantBuffer Failed");
	}
}
