#include "IndirectBuffer.h"
#include "DispatchIndirectStructure.h"

template class D3D11MANAGER_API D3D11::CIndirectBuffer<D3D11_DRAW_INSTANCED_INDIRECT_ARGS>;
template class D3D11MANAGER_API D3D11::CIndirectBuffer<D3D11_DRAW_INDEXED_INSTANCED_INDIRECT_ARGS>;
template class D3D11MANAGER_API D3D11::CIndirectBuffer<D3D11_DISPATCH_INDIRECT_ARGS>;
