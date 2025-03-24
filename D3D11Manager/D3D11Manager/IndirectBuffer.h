#pragma once

#ifndef INDIRECTBUFFER_H
#define INDIRECTBUFFER_H

#include "ABuffer.h" 

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>;

namespace D3D11
{
	class D3D11MANAGER_API IndirectBuffer : public ABuffer
	{
	public:
		IndirectBuffer(UINT arrayCount, const D3D11_DRAW_INSTANCED_INDIRECT_ARGS* cpuData);
		~IndirectBuffer() override = default;

	protected:
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_indirectUAV;

	public:
		ID3D11UnorderedAccessView* const GetUAV() const noexcept { return m_indirectUAV.Get(); }

	public:
		virtual D3D11_BUFFER_DESC CreateBufferDesc() noexcept override;
		virtual D3D11_UNORDERED_ACCESS_VIEW_DESC CreateUnorderedAccessViewDesc() noexcept;
		virtual void InitializeBuffer(ID3D11Device* const device) override;
	};
}

#endif
