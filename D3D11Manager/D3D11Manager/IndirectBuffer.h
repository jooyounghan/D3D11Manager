#pragma once

#ifndef INDIRECTBUFFER_H
#define INDIRECTBUFFER_H

#include "ABuffer.h" 

namespace D3D11
{
	class D3D11MANAGER_API IndirectBuffer : public ABuffer
	{
	public:
		IndirectBuffer(
			UINT elementSize, UINT arrayCount,
			const void* cpuData
		);
		~IndirectBuffer() override = default;

	public:
		virtual D3D11_BUFFER_DESC CreateBufferDesc() noexcept override;
	};
}

#endif
