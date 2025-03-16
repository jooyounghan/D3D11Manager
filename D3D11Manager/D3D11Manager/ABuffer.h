#pragma once

#ifndef ABUFFER_H
#define ABUFFER_H

#include "D3D11DllHelper.h"

#include <wrl/client.h>
#include <d3d11.h>

namespace D3D11
{
	class D3D11MANAGER_API ABuffer
	{
	public:
		ABuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuDataIn) noexcept;
		virtual ~ABuffer() { m_buffer.Reset(); };

	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	protected:
		UINT m_elementSize;
		UINT m_arrayCount;
		const void* m_cpuData;

	public:
		D3D11_SUBRESOURCE_DATA GetSubResourceData() const noexcept;
		inline ID3D11Buffer* GetBuffer() const noexcept { return m_buffer.Get(); }

	public:
		virtual void InitializeBuffer(ID3D11Device* const device) = 0;
	};
}
#endif

