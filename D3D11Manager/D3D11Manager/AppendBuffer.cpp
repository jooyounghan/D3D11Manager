#include "AppendBuffer.h"

using namespace std;
using namespace D3D11;

CAppendBuffer::CAppendBuffer(UINT elementSize, UINT arrayCount, const void* cpuData)
	: CStructuredBuffer(elementSize, arrayCount, cpuData)
{
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
