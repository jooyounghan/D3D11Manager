#include "IndirectBuffer.h"

using namespace std;
using namespace D3D11;

IndirectBuffer::IndirectBuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: ABuffer(elementSize, arrayCount, cpuData)
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
	bufferDesc.StructureByteStride = m_elementSize;
	return bufferDesc;
}
