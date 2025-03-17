#pragma once

#ifndef DYNAMICBUFFER_H
#define DYNAMICBUFFER_H

#include "AUploadableBuffer.h"

namespace D3D11
{
	class D3D11MANAGER_API CDynamicBuffer : public AUploadableBuffer
	{
	public:
		CDynamicBuffer(
			const UINT& elementSize, 
			const UINT& arrayCount, 
			const void* cpuData
		);
		~CDynamicBuffer() override = default;

	public:
		virtual void InitializeBuffer(ID3D11Device* const device) override;
	};
}

#endif
