#include "AppendBuffer.h"

using namespace std;
using namespace D3D11;

CAppendBuffer::CAppendBuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: CStructuredBuffer(elementSize, arrayCount, cpuData)
{
}

void CAppendBuffer::SwapConsumeAppend(CAppendBuffer* appendBuffer1, CAppendBuffer* appendBuffer2)
{
	if (appendBuffer1->m_elementSize != appendBuffer2->m_elementSize) throw exception("Element Sizes Are Not Equal For Swapping Consume-Append Buffer");
	if (appendBuffer1->m_arrayCount != appendBuffer2->m_arrayCount) throw exception("Array Counts Are Not Equal For Swapping Consume-Append Buffer");

	appendBuffer1->m_buffer.Swap(appendBuffer2->m_buffer);
	appendBuffer1->m_stagingBuffer.Swap(appendBuffer2->m_stagingBuffer);
	appendBuffer1->m_structuredSRV.Swap(appendBuffer2->m_structuredSRV);
	appendBuffer1->m_structuredUAV.Swap(appendBuffer2->m_structuredUAV);
}

D3D11_UNORDERED_ACCESS_VIEW_DESC D3D11::CAppendBuffer::CreateUnorderedAccessViewDesc() noexcept
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));

	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = m_arrayCount;
	uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
	return uavDesc;
}
