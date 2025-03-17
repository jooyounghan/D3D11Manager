#include "ConstantBuffer.h"
#include <exception>

using namespace std;
using namespace D3D11;

CConstantBuffer::CConstantBuffer(
	const UINT& elementSize, const UINT& arrayCount,
	const void* cpuDataIn,
	const D3D11_BIND_FLAG& bindFlag,
	const D3D11_USAGE& usage
)
	: ABuffer(elementSize, arrayCount, cpuDataIn), m_bindFlag(bindFlag), m_usage(usage)
{

}
void CConstantBuffer::InitializeBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA initialData = GetSubResourceData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.ByteWidth = m_elementSize * m_arrayCount;
	bufferDesc.Usage = m_usage;
	bufferDesc.BindFlags = m_bindFlag;
	bufferDesc.CPUAccessFlags = NULL;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = 0;

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initialData, m_buffer.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateBuffer For ConstantBuffer Failed");
}
