#include "DeferredContext.h"

#include <exception>

using namespace std;
using namespace D3D11;

CDeferredContext::CDeferredContext(ID3D11Device* const device)
{
	HRESULT hResult = device->CreateDeferredContext(NULL, m_deferredContext.GetAddressOf());
	if (FAILED(hResult)) throw exception("CreateDeferredContext Failed");
}

ID3D11CommandList* CDeferredContext::FinishCommandList()
{
	ID3D11CommandList* commandList;

	HRESULT hResult = m_deferredContext->FinishCommandList(TRUE, &commandList);
	if (FAILED(hResult)) throw exception("FinishCommandList Failed");

	return commandList;
}
