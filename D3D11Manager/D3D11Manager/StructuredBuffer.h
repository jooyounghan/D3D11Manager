#pragma once

#ifndef STRUCTUREDBUFFER_H
#define STRUCTUREDBUFFER_H

#include "AUploadableBuffer.h"

template class D3D11MANAGER_API Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;

namespace D3D11
{
	class D3D11MANAGER_API CStructuredBuffer : public AUploadableBuffer
	{
	public:
		CStructuredBuffer(
			const UINT& elementSize, 
			const UINT& arrayCount, 
			const void* cpuData
		);
		~CStructuredBuffer() override = default;

	protected:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_structuredSRV;

	public:
		ID3D11ShaderResourceView* const GetSRV() const { return m_structuredSRV.Get(); }

	public:
		virtual void InitializeBuffer(ID3D11Device* const device) override;

	};
}

#endif
