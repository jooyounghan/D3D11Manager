#include "ConstantBuffer.h"

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