#pragma once

#ifndef APPENDBUFFER_H
#define APPENDBUFFER_H

#include "StructuredBuffer.h"
namespace D3D11
{
	class D3D11MANAGER_API CAppendBuffer : public D3D11::CStructuredBuffer
	{
	public:
		CAppendBuffer(
			const UINT& elementSize,
			const UINT& arrayCount,
			const void* cpuData
		);
		~CAppendBuffer() override = default;

	public:
		static void SwapConsumeAppend(CAppendBuffer* appendBuffer1, CAppendBuffer* appendBuffer2);

	public:
		virtual D3D11_UNORDERED_ACCESS_VIEW_DESC CreateUnorderedAccessViewDesc() noexcept override;
	};
}
#endif