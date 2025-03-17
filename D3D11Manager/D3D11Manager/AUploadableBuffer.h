#pragma once

#ifndef AUPLOADABLEBUFFER_H
#define AUPLOADABLEBUFFER_H

#include "ABuffer.h"

namespace D3D11
{
	class D3D11MANAGER_API AUploadableBuffer : public ABuffer
	{
	public:
		AUploadableBuffer(const UINT& elementSize, const UINT& arrayCount, const void* cpuData);
		~AUploadableBuffer() override = default;

	public:
		virtual void Upload(ID3D11DeviceContext* const deviceContext);
	};
}
#endif
