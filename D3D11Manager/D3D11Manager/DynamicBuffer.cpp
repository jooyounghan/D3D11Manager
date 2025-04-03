#include "DynamicBuffer.h"

using namespace std;
using namespace D3D11;

CDynamicBuffer::CDynamicBuffer(
	UINT elementSize, 
	UINT arrayCount, 
	const void* cpuData, 
	D3D11_BIND_FLAG bindFlag 
)
	: AUploadableBuffer(elementSize, arrayCount, cpuData), m_bindFlag(bindFlag)
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