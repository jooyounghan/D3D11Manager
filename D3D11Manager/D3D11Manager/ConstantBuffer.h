#pragma once

#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

#include "ABuffer.h" 

namespace D3D11
{
	class D3D11MANAGER_API CConstantBuffer : public ABuffer
	{
	public:
		CConstantBuffer(
			const UINT& elementSize, const UINT& arrayCount,
			const void* cpuDataIn,
			const D3D11_BIND_FLAG& bindFlag = D3D11_BIND_CONSTANT_BUFFER,
			const D3D11_USAGE& usage = D3D11_USAGE_IMMUTABLE
		);
		~CConstantBuffer() override = default;

	protected:
		D3D11_USAGE m_usage;
		D3D11_BIND_FLAG m_bindFlag;

	public:
		virtual D3D11_BUFFER_DESC CreateBufferDesc() noexcept override;
	};
}

#endif